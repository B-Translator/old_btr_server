#!/bin/bash -x

### put the cache on RAM (to improve efficiency)
sed -e '/appended by installation scripts/,$ d' -i /etc/fstab
cat <<EOF >> /etc/fstab
##### appended by installation scripts
tmpfs		/dev/shm	tmpfs	defaults,noexec,nosuid	0	0
tmpfs		/var/www/btranslator/cache	tmpfs	defaults,size=5M,mode=0777,noexec,nosuid	0	0
devpts		/dev/pts	devpts	rw,noexec,nosuid,gid=5,mode=620		0	0
EOF

### create other dirs that are needed
mkdir -p /var/run/memcached/
chown nobody /var/run/memcached/
