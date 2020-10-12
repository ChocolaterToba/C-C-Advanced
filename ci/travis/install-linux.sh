sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq

sudo apt-get -q update
sudo apt-get install -qq g++-7
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 90

sudo apt-get install snapd
sudo snap install cmake --classic
ln -s /snap/cmake/current/bin/cmake $HOME/bin/cmake