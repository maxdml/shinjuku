#!/bin/sh

# Create clean copy of DB.
rm -r /tmp/my_db
cp -r /opt/shinjuku/db/my_db /tmp/my_db

# Build and run Shinjuku.
make clean
make -sj64
numactl -N0 -m0 bash -c "LD_PRELOAD=./deps/opnew/dest/libnew.so ./dp/shinjuku"
