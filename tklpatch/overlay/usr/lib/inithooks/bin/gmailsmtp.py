#!/usr/bin/python
# Copyright (c) 2013 Dashamir Hoxha <dashohoxha@gmail.com>

"""
Set smtp for sending email through a gmail account.
The email and password of the gmail account are
expected as parameters.

Options:
    --email=    unless provided, will ask interactively
    --passw=    unless provided, will ask interactively

"""

import sys
import getopt

from dialog_wrapper import Dialog
from executil import getoutput, ExecError
from mysqlconf import MySQL

def usage(s=None):
    if s:
        print >> sys.stderr, "Error:", s
    print >> sys.stderr, "Syntax: %s [options]" % sys.argv[0]
    print >> sys.stderr, __doc__
    sys.exit(1)

def main():
    try:
        opts, args = getopt.gnu_getopt(sys.argv[1:], "hep",
                     ['help', 'email=', 'passw='])
    except getopt.GetoptError, e:
        usage(e)

    email=""
    passw=""

    for opt, val in opts:
        if opt in ('-h', '--help'):
            usage()
        elif opt == '--email':
            gmail_user = val
        elif opt == '--passw':
            gmail_pass = val

    d = Dialog('TurnKey B-Translator - First boot configuration')
    if not email:
        email = d.get_email(
            "Email of the gmail account",
            "Emails from the server are sent through the SMTP of a GMAIL account.\n" +
            "Please enter the full email of the gmail account:",
            "MyEmailAddress@gmail.com")
    if not passw:
        passw = d.get_password(
            "Password of the gmail account",
            "Emails from the server are sent through the SMTP of a GMAIL account.\n" +
            "Please enter the password of the gmail account:")

    domain = email.split('@')[1]

    try:
        d.infobox("Modifying ssmtp configuration files...")

        # modify conf file /etc/ssmtp/ssmtp.conf
        config_file = '/etc/ssmtp/ssmtp.conf'
        getoutput('sed -e "/^root=/ c root=%s" -i %s' % (email, config_file))
        getoutput('sed -e "/^AuthUser=/ c AuthUser=%s" -i %s' % (email, config_file))
        getoutput('sed -e "/^AuthPass=/ c AuthPass=%s" -i %s' % (passw, config_file))
        getoutput('sed -e "/^rewriteDomain=/ c rewriteDomain=%s" -i %s' % (domain, config_file))
        getoutput('sed -e "/^hostname=/ c hostname=%s" -i %s' % (email, config_file))

        # modify conf file /etc/ssmtp/revaliases
        config_file = '/etc/ssmtp/revaliases'
        getoutput('sed -e "/^root:/ c root:%s:smtp.gmail.com:587" -i %s' % (email, config_file))
        getoutput('sed -e "/^admin:/ c admin:%s:smtp.gmail.com:587" -i %s' % (email, config_file))

        d.infobox("Modifying smtp drupal variables...")

        # modify drupal variables that are used for sending email
        m = MySQL()   # start mysqld
        vset = "/usr/bin/drush --yes --exact vset %s %s"
        getoutput(vset % ('site_mail', email))
        getoutput(vset % ('smtp_username', email))
        getoutput(vset % ('smtp_password', passw))

        getoutput(vset % ('smtp_host', 'smtp.googlemail.com'))
        getoutput(vset % ('smtp_port', '465'))
        getoutput(vset % ('smtp_protocol', 'ssl'))
        getoutput(vset % ('smtp_on', '1'))

        getoutput(vset % ('smtp_allowhtml', '1'))
        getoutput(vset % ('smtp_keepalive', '1'))
        getoutput(vset % ('smtp_always_replyto', '1'))

        getoutput(vset % ('smtp_from', email))
        getoutput(vset % ('mimemail_mail', email))
        getoutput(vset % ('simplenews_from_address', email))
        getoutput(vset % ('simplenews_test_address', email))
        getoutput(vset % ('mass_contact_default_sender_email', email))
        getoutput(vset % ('reroute_email_address', email))

    except ExecError, e:
        d.msgbox('Failure', e.output)

if __name__ == "__main__":
    main()
