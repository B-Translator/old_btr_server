### This file can be used to build a docker image like this:
###   `docker build --tag=btr_server .`

FROM ubuntu-upstart:14.04

### Install packages.
COPY install/packages.sh /tmp/
RUN DEBIAN_FRONTEND=noninteractive /tmp/packages.sh

### Copy the source code and install.
COPY . /usr/local/src/btr_server/
ENV code_dir /usr/local/src/btr_server
WORKDIR /usr/local/src/btr_server/
RUN ["install/install.sh"]
