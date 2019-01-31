#!/bin/bash

echo "Copying new libs to lib/linux"

rm -f /host/lib/linux/*

# dependencies
cp -v /build/libopenabe-1.0.0/deps/root/lib/libcrypto.so /host/lib/linux
cp -v /build/libopenabe-1.0.0/deps/root/lib/libcrypto.so.* /host/lib/linux
cp -v /build/libopenabe-1.0.0/deps/root/lib/librelic.so /host/lib/linux
cp -v /build/libopenabe-1.0.0/deps/root/lib/librelic_ec.so /host/lib/linux
cp -v /build/libopenabe-1.0.0/deps/root/lib/libssl.so /host/lib/linux
cp -v /build/libopenabe-1.0.0/deps/root/lib/libssl.so.* /host/lib/linux

# core openabe library
cp -v /build/libopenabe-1.0.0/root/lib/libopenabe.so /host/lib/linux

# our bridge library
cp -v /build/sccplib/lib/libsccp.so /host/lib/linux

echo "DONE"
