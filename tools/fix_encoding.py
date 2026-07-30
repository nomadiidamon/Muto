from pathlib import Path
import argparse
import chardet
import sys


EXTENSIONS = {
    ".h",
    ".hpp",
    ".cpp",
    ".c",
    ".md",
    ".txt",
}

ROOT_FOLDERS = {
    "Muto/src",
    "Sandbox",
}

REPLACEMENTS = {
    "\u2018": "'",   # left single quote
    "\u2019": "'",   # right single quote
    "\u201c": '"',   # left double quote
    "\u201d": '"',   # right double quote
    "\u2013": "-",   # en dash
    "\u2014": "-",   # em dash
    "\u00b1": "+/-", # plus/minus
}

def find_files():
    files = []

    for folder in ROOT_FOLDERS:
        path = Path(folder)

        if not path.exists():
            continue

        for file in path.rglob("*"):
            if file.is_file() and file.suffix.lower() in EXTENSIONS:
                files.append(file)

    return files


def convert_file(path):
    data = path.read_bytes()

    detected = chardet.detect(data)
    encoding = detected["encoding"]

    if not encoding:
        print(f"Unable to determine encoding: {path}")
        return False

    if encoding.lower() in ("ascii", "utf-8", "utf_8"):
        return False

    print(f"Converting {path} ({encoding} -> UTF-8)")

    text = data.decode(encoding, errors="replace")

    for old, new in REPLACEMENTS.items():
        text = text.replace(old, new)

    path.write_text(text, encoding="utf-8")

    return True


def check_file(path):
    data = path.read_bytes()

    detected = chardet.detect(data)
    encoding = detected["encoding"]

    if not encoding:
        print(f"UNKNOWN: {path}")
        return True

    if encoding.lower() not in ("ascii", "utf-8", "utf_8"):
        print(f"BAD ENCODING: {path} ({encoding})")
        return True

    return False


def main():

    parser = argparse.ArgumentParser(
        description="Check or fix repository text file encodings"
    )

    parser.add_argument(
        "--fix",
        action="store_true",
        help="Convert files to UTF-8"
    )

    parser.add_argument(
        "--check",
        action="store_true",
        help="Check encodings only"
    )

    args = parser.parse_args()

    # Default behavior
    mode = "fix" if args.fix else "check"

    problems = False

    for file in find_files():

        if mode == "fix":
            convert_file(file)

        else:
            if check_file(file):
                problems = True

    if problems:
        print("\nEncoding issues found.")
        print("Run: python tools/fix_encoding.py --fix")
        sys.exit(1)

    print("\nEncoding check passed.")


if __name__ == "__main__":
    main()