#!/bin/bash
# Build script for Tea Game web version
# Requires Emscripten SDK to be installed and activated
#
# Installation:
#   git clone https://github.com/emscripten-core/emsdk.git
#   cd emsdk
#   ./emsdk install latest
#   ./emsdk activate latest
#   source ./emsdk_env.sh
#
# Usage:
#   ./build_web.sh         # Build the game
#   ./build_web.sh clean   # Clean build directory
#   ./build_web.sh serve   # Build and start local server

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build_web"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

print_status() {
    echo -e "${GREEN}[BUILD]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check if Emscripten is available
check_emscripten() {
    if ! command -v emcmake &> /dev/null; then
        print_error "Emscripten not found!"
        echo ""
        echo "Please install and activate Emscripten SDK:"
        echo "  git clone https://github.com/emscripten-core/emsdk.git"
        echo "  cd emsdk"
        echo "  ./emsdk install latest"
        echo "  ./emsdk activate latest"
        echo "  source ./emsdk_env.sh"
        echo ""
        exit 1
    fi
}

clean() {
    print_status "Cleaning build directory..."
    rm -rf "${BUILD_DIR}"
    print_status "Done!"
}

build() {
    check_emscripten

    print_status "Creating build directory..."
    mkdir -p "${BUILD_DIR}"
    cd "${BUILD_DIR}"

    print_status "Configuring with CMake (Emscripten)..."
    emcmake cmake .. \
        -DCMAKE_BUILD_TYPE=Release

    print_status "Building..."
    emmake make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

    print_status "Build complete!"
    echo ""
    echo "Output files:"
    ls -la "${BUILD_DIR}"/*.html "${BUILD_DIR}"/*.js "${BUILD_DIR}"/*.wasm "${BUILD_DIR}"/*.data 2>/dev/null || true
    echo ""
    echo "To test locally, run:"
    echo "  cd ${BUILD_DIR}"
    echo "  python3 -m http.server 8080"
    echo "  # Then open http://localhost:8080/TeaGame.html"
}

serve() {
    build
    
    print_status "Starting local server on http://localhost:8080..."
    echo "Open http://localhost:8080/TeaGame.html in your browser"
    echo "Press Ctrl+C to stop the server"
    echo ""
    
    cd "${BUILD_DIR}"
    python3 -m http.server 8080
}

# Parse command line arguments
case "${1:-build}" in
    clean)
        clean
        ;;
    serve)
        serve
        ;;
    build|"")
        build
        ;;
    *)
        echo "Usage: $0 [build|clean|serve]"
        echo ""
        echo "Commands:"
        echo "  build   Build the web version (default)"
        echo "  clean   Remove the build directory"
        echo "  serve   Build and start a local web server"
        exit 1
        ;;
esac
