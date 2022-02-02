#!/bin/bash
# bash is used for pushd/popd

BINUTILS=binutils-2.37
GCC=gcc-11.2.0

MAKEOPTS="-j12"
PREFIX="$HOME/opt/cross"
TARGET=i686-elf
BASEDIR=$(pwd)

set -xe

# Binutils
mkdir -p build/binutils && pushd build/binutils

$BASEDIR/$BINUTILS/configure --target=$TARGET --prefix="$PREFIX" \
--with-sysroot --disable-nls --disable-werror

make $MAKEOPTS
make install
popd

export PATH="$PREFIX/bin:$PATH"

# GCC
mkdir -p build/gcc && pushd build/gcc

$BASEDIR/$GCC/configure --target=$TARGET --prefix="$PREFIX" \
--disable-nls --enable-languages=c --without-headers

make $MAKEOPTS all-gcc
make $MAKEOPTS all-target-libgcc
make install-gcc
make install-target-libgcc
popd

# Confirm success
$PREFIX/bin/$TARGET-gcc --version