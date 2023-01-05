#!/bin/bash

# install deps
apt-get install build-essential -y
apt-get install build-essential -y
apt-get install libssl-dev -y
apt-get install libdb++-dev -y 
apt-get install libboost-all-dev -y
apt-get install libminiupnpc-dev -y
apt-get install libgmp3-dev -y

# compile core
git clone https://github.com/MoneyByte/MoneyByteBlockchain.git
cd MoneyByteBlockchain/src
make -f makefile.unix -j10
cd ../bin
cp moneybyted /usr/bin
moneybyted && moneybyted
moneybyted stop
sleep 5
# download boostrap
cd /root/.MoneyByte
wget -c https://github.com/MoneyByte/MoneyByteBlockchain/releases/download/v1.3.0.1/bootstrap.dat
cd .. 
moneybyted && moneybyted
