FROM ubuntu:14.04

### Start ubuntu-upstart
### See: https://github.com/tianon/dockerfiles/tree/4d24a12b54b75b3e0904d8a285900d88d3326361/sbin-init/ubuntu/upstart/14.04

RUN echo '\
# fake some events needed for correct startup other services\n\
\n\
description     "In-Container Upstart Fake Events"\n\
\n\
start on startup\n\
\n\
script\n\
        rm -rf /var/run/*.pid \n\
        rm -rf /var/run/network/* \n\
        /sbin/initctl emit stopped JOB=udevtrigger --no-wait \n\
        /sbin/initctl emit started JOB=udev --no-wait \n\
        /sbin/initctl emit runlevel RUNLEVEL=3 --no-wait \n\
end script' \
    > /etc/init/fake-container-events.conf

RUN rm /usr/sbin/policy-rc.d; \
        rm /sbin/initctl; dpkg-divert --rename --remove /sbin/initctl

RUN locale-gen en_US.UTF-8 && update-locale LANG=en_US.UTF-8

RUN /usr/sbin/update-rc.d -f ondemand remove; \
        for f in \
                /etc/init/u*.conf \
                /etc/init/mounted-dev.conf \
                /etc/init/mounted-proc.conf \
                /etc/init/mounted-run.conf \
                /etc/init/mounted-tmp.conf \
                /etc/init/mounted-var.conf \
                /etc/init/hostname.conf \
                /etc/init/networking.conf \
                /etc/init/tty*.conf \
                /etc/init/plymouth*.conf \
                /etc/init/hwclock*.conf \
                /etc/init/module*.conf\
        ; do \
                dpkg-divert --local --rename --add "$f"; \
        done; \
        echo '# /lib/init/fstab: cleared out for bare-bones Docker' > /lib/init/fstab

ENV container docker
CMD ["/sbin/init"]
### End ubuntu-upstart

### Install packages.
COPY install/packages.sh /tmp/
RUN DEBIAN_FRONTEND=noninteractive /tmp/packages.sh

### Copy the source code and install.
COPY . /usr/local/src/btr_server/
ENV code_dir /usr/local/src/btr_server
WORKDIR /usr/local/src/btr_server/
RUN ["install/install.sh"]

### Set the default dir to the code of the application.
WORKDIR /var/www/btr/profiles/btr_server
