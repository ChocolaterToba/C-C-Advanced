sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq

sudo apt-get -q update
sudo apt-get install -qq g++-8 gcc-8
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 80 /usr/bin/g++ g++ /usr/bin/g++-8 80

sudo pip install cpplint
sudo pip install gcovr

sudo apt-get install valgrind