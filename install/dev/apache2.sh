#!/bin/bash
### Sometimes it may be more suitable for the development
### to use Apache2 instead of NGINX etc.

case $1 in
    start)
	service nginx stop
	service php5-fpm stop
	drush -y dis memcache
	service memcached stop
	service apache2 start
	;;
    stop)
	service apache2 stop
	service memcached start
	drush -y en memcache
	service php5-fpm start
	service nginx start
	;;
    *)
	echo " * Usage: $0 {start|stop}"
	;;
esac
