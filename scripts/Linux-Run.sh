#!/usr/bin/env bash

set -euo pipefail

cd "$(dirname "$0")/.."

config="${1:-debug}"
case "$config" in
	debug) build_config="Debug" ;;
	release) build_config="Release" ;;
	dist) build_config="Dist" ;;
	*)
		echo "Usage: $0 [debug|release|dist]" >&2
		exit 2
		;;
esac

if [[ ! -f Makefile || ! -f Muto/Muto/Makefile ]]; then
	premake5 gmake2
fi

make config="$config" Sandbox
exec "./bin/${build_config}-linux-x86_64/Sandbox/Sandbox"
