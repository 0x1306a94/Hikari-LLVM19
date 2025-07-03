#!/bin/bash

CURDIR=$(dirname "$0")

# cffobf 会crash
# indibran 会crash
MLLVM_ARGS="-mllvm -hikari -mllvm -enable-strcry -mllvm -enable-bcfobf -mllvm -enable-splitobf -mllvm -enable-subobf -mllvm -enable-fco -mllvm -enable-funcwra -mllvm -enable-constenc"

$ANDROID_NDK_ROOT/toolchains/llvm/prebuilt/darwin-x86_64/bin/clang++ \
--target=aarch64-linux-android23 \
-x c \
-Xclang -load -Xclang libHikari.so \
-fpass-plugin=libHikari.so -shared -fPIC \
$MLLVM_ARGS \
-o $CURDIR/../build/test.so \
$CURDIR/test_ollvm.c