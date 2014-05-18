
### Default settings for building the chroot.
target_dir='btr'
arch='i386'
suite='precise'
apt_mirror='http://archive.ubuntu.com/ubuntu'

### A reboot is needed after installation/configuration.
### If you want to do it automatically, set it to 'true'.
reboot='false'

### Start chroot service automatically on reboot.
start_on_boot='false'

### Domain of the website.
bcl_domain='example.org'
btr_domain='btr.example.org'

### Drupal 'admin' password.
bcl_admin_passwd='admin'
btr_admin_passwd='admin'

### Emails from the server are sent through the SMTP
### of a GMAIL account. Give the full email
### of the gmail account, and the password.
gmail_account='MyEmailAddress@gmail.com'
gmail_passwd=

### Translation languages supported by the B-Translator Server.
### Do not remove 'fr', because sometimes French translations
### are used instead of template files (when they are missing).
languages='fr de it sq'

### Translation language of B-Translator Client.
bcl_translation_lng='sq'

### Mysql passwords. Leave it as 'random'
### to generate a new one randomly
mysql_passwd_root='random'
mysql_passwd_bcl='random'
mysql_passwd_btr='random'
mysql_passwd_btr_data='random'
