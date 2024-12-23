# SystemC-PlayGround
This repository will hold code snippets of the lecture and exercise for the module SystemC. 
It will also hold different markdown files explaining different concepts of C++ and SystemC.


docker build --platform linux/amd64 --build-arg USER_ID=$(id -u) --build-arg GROUP_ID=$(id -g) -t my-ubuntu-systemc .

docker run --platform linux/amd64 -it --name SystemC_DEV -v ~/Desktop/SystemC-PlayGround/:/SystemC-PlayGround my-ubuntu-systemc /bin/bash