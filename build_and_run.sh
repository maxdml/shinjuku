#!/bin/sh -xe

# Create clean copy of DB.
#cd /opt/shinjuku/db
#rm -r my_db
#./create_db
#sudo rm -r /tmp/my_db
#cp -r /opt/shinjuku/db/my_db /tmp/my_db

# Build and run Shinjuku.
cd ${AE_DIR}/Persephone/submodules/shinjuku
make clean
make -sj
#sudo LD_PRELOAD=./deps/opnew/dest/libnew.so /opt/shinjuku/dp/shinjuku
sudo ${AE_DIR}/Persephone/submodules/shinjuku/dp/shinjuku -c $1 -p $2 -o $3
