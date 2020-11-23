#!/bin/sh

# Create clean copy of DB.
sudo rm -r /tmp/my_db
cp -r /opt/shinjuku/db/my_db /tmp/my_db

# Build and run Shinjuku.
cd /opt/shinjuku
make clean
make -sj64
#sudo /opt/shinjuku/dp/shinjuku
LD_PRELOAD=/opt/shinjuku/dest/libnew.so sudo -E /opt/shinjuku/dp/shinjuku
