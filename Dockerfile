### This file can be used to build a docker image like this:
###   `docker build --tag=btr_server`
### It can also be used for automated builds in Docker Hub
### (see https://docs.docker.com/userguide/dockerrepos/#automated-builds)

FROM ubuntu:14.04

### Install packages first, in order to take advantage
### of caching features of `docker build`.
COPY install/scripts/packages-and-software.sh /tmp/
RUN DEBIAN_FRONTEND=noninteractive /tmp/packages-and-software.sh

### Copy the source code and run the installer.
COPY . /usr/local/src/btr_server/
ENV code_dir /usr/local/src/btr_server
WORKDIR /usr/local/src/btr_server/
RUN ["install/install-container.sh", "install/settings.sh"]

### Set the default command to run in the container.
CMD ["/usr/bin/supervisord", "-c", "/etc/supervisor/supervisord.conf", "--nodaemon"]

