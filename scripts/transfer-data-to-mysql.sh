#!/bin/bash
### Transfer data from SQLite to MySQL.
### This is done with the help of sqlfairy:
###   http://sqlfairy.sourceforge.net/
###   http://search.cpan.org/dist/SQL-Translator/
### In ubuntu install with:
###   aptitude install sqlfairy libdbd-sqlite3-perl

if [ "$1" = "" ]
then
  echo "Usage: $0 lng"
  echo "       where lng is like: en, de, fr, sq, etc."
  exit 1
fi

lng=$1

### first dump the data from the SQLite db
sqlt -f DBI --dsn dbi:SQLite:ten-$lng.db -t MySQL --add-drop-table > mysql-$lng.sql
sqlt -f DBI --dsn dbi:SQLite:ten-$lng.db -t Dumper --use-same-auth > dumper-$lng.pl
chmod +x dumper-$lng.pl
#./dumper-$lng.pl --help
./dumper-$lng.pl --add-truncate --mysql-loadfile > mysql-dump-$lng.sql
sed -e '/INDEX `idx`/ c \  INDEX `idx` (`word`(100)),' -i mysql-$lng.sql
sed -e 's/LOAD DATA INFILE/LOAD DATA LOCAL INFILE/' -i mysql-dump-$lng.sql

## then import them into MySQL
echo "drop database $lng" | mysql -p -u root
echo "create database $lng collate utf8_bin" | mysql -p -u root
mysql -p -u root -D $lng < mysql-$lng.sql
mysql -p -u root -D $lng < mysql-dump-$lng.sql

### clean up
rm phrases.txt words.txt locations.txt wp.txt
rm mysql-$lng.sql mysql-dump-$lng.sql
rm dumper-$lng.pl
