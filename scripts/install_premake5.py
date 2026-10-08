"""
Install Premake 5 if it is not already available on PATH.

Usage:

    python install_premake.py

    python install_premake.py path/to/bin

If no destination is supplied, Premake is installed to:

    <parent-of-this-script>/vendor/bin

The Premake executable and LICENSE.txt are placed in the destination
directory.

This script only installs Premake. It does not execute it.
"""

from __future__ import annotations

import hmac
import argparse
import hashlib
import os
import platform
import shutil
import stat
import sys
import tarfile
import tempfile
import urllib.error
import urllib.request
import zipfile
from pathlib import Path


PREMAKE_VERSION = "5.0.0"

PREMAKE_RELEASE_BASE = (
    f"https://github.com/premake/premake-core/releases/download/"
    f"v{PREMAKE_VERSION}"
)

LICENSE_URL = (
    "https://raw.githubusercontent.com/premake/premake-core/"
    "master/LICENSE.txt"
)

DOWNLOAD_TIMEOUT_SECONDS = 30
DOWNLOAD_ATTEMPTS = 3


# SHA-256 hashes for the official Premake release archives.
#
# These MUST be verified against the official release artifacts before
# being populated. An incorrect hash will cause installation to fail.
#
# Do not remove verification or replace these with hashes from an
# unofficial mirror.
EXPECTED_SHA256 = {
    "premake-5.0.0-windows.zip": "15e63506eed5dfd526b96c8e957a7feff2be6cfe70f46e353bfe4813b82e2fdc",
    "premake-5.0.0-linux.tar.gz": "8e50e143402de3ce0f0fefe4bb3f4f6a7db46c7d66203dc9f134c0348ebfe6c5",
    "premake-5.0.0-macosx.tar.gz": "8952855a0d824f63ca22721f3f32ee947a4762c01008f9eddefeba133bafda0d",
}


def find_premake() -> str | None:
    """
    Return the path to premake5 if it is available on PATH.
    """

    executable = "premake5.exe" if os.name == "nt" else "premake5"

    return shutil.which(executable)


def get_platform_archive() -> tuple[str, str]:
    """
    Return:

        (archive_name, executable_name)

    for the current platform.
    """

    system = platform.system().lower()
    machine = platform.machine().lower()

    if system == "windows":
        if machine in ("amd64", "x86_64", "x64"):
            return (
                f"premake-{PREMAKE_VERSION}-windows.zip",
                "premake5.exe",
            )

        raise RuntimeError(
            f"Unsupported Windows architecture: {machine}"
        )

    if system == "linux":
        if machine in ("x86_64", "amd64"):
            return (
                f"premake-{PREMAKE_VERSION}-linux.tar.gz",
                "premake5",
            )

        raise RuntimeError(
            f"Unsupported Linux architecture: {machine}"
        )

    if system == "darwin":
        if machine in (
            "x86_64",
            "amd64",
            "arm64",
            "aarch64",
        ):
            return (
                f"premake-{PREMAKE_VERSION}-macosx.tar.gz",
                "premake5",
            )

        raise RuntimeError(
            f"Unsupported macOS architecture: {machine}"
        )

    raise RuntimeError(
        f"Unsupported operating system: {platform.system()}"
    )


def download(url: str, destination: Path) -> None:
    """
    Download a URL to a file.
    """

    print(f"Downloading: {url}")

    request = urllib.request.Request(
        url,
        headers={
            "User-Agent": "premake-installer/1.0",
        },
    )

    for attempt in range(1, DOWNLOAD_ATTEMPTS + 1):
        try:
            with urllib.request.urlopen(
                request,
                timeout=DOWNLOAD_TIMEOUT_SECONDS,
            ) as response:
                with destination.open("wb") as output:
                    shutil.copyfileobj(response, output)
            return
        except OSError as exc:
            # URLError and timeouts are OSError subclasses.
            if attempt == DOWNLOAD_ATTEMPTS:
                raise
            print(
                f"Download failed ({exc}); retrying "
                f"({attempt}/{DOWNLOAD_ATTEMPTS})..."
            )


def write_atomically(
    source,
    output: Path,
    executable: bool = False,
) -> None:
    """
    Copy a stream to output via a temp file in the same directory,
    replacing output only after the copy succeeds.
    """

    fd, temp_name = tempfile.mkstemp(
        dir=output.parent,
        prefix=f"{output.name}.",
        suffix=".tmp",
    )
    temp_path = Path(temp_name)

    try:
        with os.fdopen(fd, "wb") as target:
            shutil.copyfileobj(source, target)

        os.chmod(temp_path, 0o755 if executable else 0o644)
        os.replace(temp_path, output)
    except BaseException:
        temp_path.unlink(missing_ok=True)
        raise


def sha256_file(path: Path) -> str:
    """
    Calculate the SHA-256 hash of a file.
    """

    digest = hashlib.sha256()

    with path.open("rb") as file:
        for chunk in iter(
            lambda: file.read(1024 * 1024),
            b"",
        ):
            digest.update(chunk)

    return digest.hexdigest()


def verify_sha256(
    path: Path,
    expected_hash: str,
) -> None:
    """
    Verify a file against an expected SHA-256 hash.
    """

    if not expected_hash:
        raise RuntimeError(
            f"No SHA-256 hash has been configured for {path.name}."
        )

    actual_hash = sha256_file(path)

    if not hmac.compare_digest(
        actual_hash.lower(),
        expected_hash.lower(),
    ):
        raise RuntimeError(
            "SHA-256 verification failed!\n"
            f"  File:     {path}\n"
            f"  Expected: {expected_hash}\n"
            f"  Actual:   {actual_hash}"
        )

    print("SHA-256 verification passed.")


def extract_premake(
    archive: Path,
    executable_name: str,
    destination: Path,
) -> None:
    """
    Extract the Premake executable from its release archive.
    """

    if archive.suffix == ".zip":
        with zipfile.ZipFile(archive) as zf:
            executable = next(
                (
                    name
                    for name in zf.namelist()
                    if Path(name).name.lower()
                    == executable_name.lower()
                ),
                None,
            )

            if executable is None:
                raise RuntimeError(
                    f"Could not find {executable_name} "
                    f"in {archive.name}"
                )

            output = destination / executable_name

            with zf.open(executable) as source:
                write_atomically(source, output, executable=True)

    else:
        with tarfile.open(archive, "r:gz") as tf:
            executable = next(
                (
                    member
                    for member in tf.getmembers()
                    if Path(member.name).name.lower()
                    == executable_name.lower()
                ),
                None,
            )

            if executable is None:
                raise RuntimeError(
                    f"Could not find {executable_name} "
                    f"in {archive.name}"
                )

            source = tf.extractfile(executable)

            if source is None:
                raise RuntimeError(
                    f"Could not extract {executable_name}"
                )

            output = destination / executable_name

            write_atomically(source, output, executable=True)


def make_executable(path: Path) -> None:
    """
    Mark a Unix executable as executable.
    """

    if os.name == "nt":
        return

    mode = path.stat().st_mode

    path.chmod(
        mode
        | stat.S_IXUSR
        | stat.S_IXGRP
        | stat.S_IXOTH
    )


def install_premake(destination: Path) -> None:
    archive_name, executable_name = get_platform_archive()

    archive_url = f"{PREMAKE_RELEASE_BASE}/{archive_name}"

    expected_hash = EXPECTED_SHA256.get(archive_name)

    if not expected_hash:
        raise RuntimeError(
            f"No SHA-256 hash configured for {archive_name}.\n"
            "Refusing to install an unverified binary."
        )

    destination.mkdir(
        parents=True,
        exist_ok=True,
    )

    with tempfile.TemporaryDirectory(
        prefix="premake-install-"
    ) as temp_dir:

        temp = Path(temp_dir)
        archive = temp / archive_name

        # Download.
        download(
            archive_url,
            archive,
        )

        # Verify BEFORE extracting or installing anything.
        print("Verifying SHA-256...")
        verify_sha256(
            archive,
            expected_hash,
        )

        # Only verified archives reach this point.
        print(f"Installing Premake to: {destination}")

        extract_premake(
            archive,
            executable_name,
            destination,
        )

    # Keep the license next to the binary.
    license_path = destination / "LICENSE.txt"

    with tempfile.TemporaryDirectory(
        prefix="premake-license-"
    ) as temp_dir:
        temp_license = Path(temp_dir) / "LICENSE.txt"

        download(
            LICENSE_URL,
            temp_license,
        )

        with temp_license.open("rb") as source:
            write_atomically(source, license_path)

    print()
    print(
        f"Installed: {destination / executable_name}"
    )
    print(
        f"License:   {license_path}"
    )


def default_destination() -> Path:
    """
    Default location:

        <parent-of-script>/vendor/bin

    For example:

        project/
            tools/
                install_premake.py
            vendor/
                bin/
    """

    script_directory = (
        Path(__file__).resolve().parent
    )

    return (
        script_directory.parent
        / "vendor"
        / "bin"
        / "premake"
    )


def main() -> int:
    parser = argparse.ArgumentParser(
        description=(
            "Install Premake 5 if it is not already "
            "available on PATH."
        )
    )

    parser.add_argument(
        "destination",
        nargs="?",
        type=Path,
        help=(
            "Directory where Premake should be installed. "
            "Defaults to ../vendor/bin relative to this script."
        ),
    )

    args = parser.parse_args()

    # Don't download anything if Premake is already on PATH.
    existing = find_premake()

    if existing:
        print(
            f"Premake already installed: {existing}"
        )
        return 0

    destination = (
        args.destination
        if args.destination is not None
        else default_destination()
    )

    destination = (
        destination
        .expanduser()
        .resolve()
    )

    try:
        install_premake(destination)

    except (
        OSError,
        RuntimeError,
        urllib.error.URLError,
    ) as exc:
        print(
            f"error: {exc}",
            file=sys.stderr,
        )
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())

