{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    cmake
    pkg-config
    gnumake
  ];

  buildInputs = with pkgs; [
    glib
    harfbuzz
    freetype
    xorg.libX11
    xorg.libXrandr
    xorg.libXcursor
    xorg.libXi
    xorg.libXinerama
    xorg.libXext
    libGL
    udev
    flac
    libvorbis
    openal
    mbedtls
    harfbuzz
    freetype
    libpng
    zlib
    stdenv.cc
  ];

  shellHook = ''
    export CC=cc
    export CXX=c++
  '';
}
