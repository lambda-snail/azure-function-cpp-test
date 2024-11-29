FROM ubuntu:24.04

# Disable installation prompt
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update
RUN apt-get upgrade -y

RUN apt-get -y install sudo
#RUN useradd -m docker && echo "docker:docker" | chpasswd && adduser docker sudo

#USER docker

RUN sudo apt-get -y install build-essential
RUN sudo apt-get -y install cmake make git clang
RUN sudo apt-get -y install libboost-all-dev
