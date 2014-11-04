
### Git branches that will be used.
git_branch='master'
bcl_git_branch='master'

### Domain of the website.
domain='btr.example.org'
bcl_domain='example.org'

### Drupal 'admin' password.
admin_passwd='admin'
bcl_admin_passwd='admin'

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
translation_lng='sq'

### Mysql passwords. Leave it as 'random'
### to generate a new one randomly
mysql_passwd_root='random'
mysql_passwd_bcl='random'
mysql_passwd_btr='random'
mysql_passwd_btr_data='random'

### Install also extra things that are useful for development.
development='true'

### Login through ssh.
### Only login through private keys is allowed.
### See also this:
###   http://dashohoxha.blogspot.com/2012/08/how-to-secure-ubuntu-server.html
sshd_port=2201
