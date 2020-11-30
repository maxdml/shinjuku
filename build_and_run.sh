#!/bin/sh -xe

# Create clean copy of DB.
cd /opt/shinjuku/db
rm -r my_db
./create_db
sudo rm -r /tmp/my_db
cp -r /opt/shinjuku/db/my_db /tmp/my_db

# Build and run Shinjuku.
cd /opt/shinjuku
make clean
make -sj64
#sudo LD_PRELOAD=./deps/opnew/dest/libnew.so /opt/shinjuku/dp/shinjuku
sudo /opt/shinjuku/dp/shinjuku
