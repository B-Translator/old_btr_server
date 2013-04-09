#!/usr/bin/python
# Copyright (c) 2013 Dashamir Hoxha <dashohoxha@gmail.com>
"""Change the domain (fqdn) in all the relevant config files.
This is the domain that you have registered (or plan to register)
for the B-Translator (usually something like l10n.org.xx).

It will modify the files:
 1) /etc/hostname
 2) /etc/hosts
 3) /etc/nginx/sistes-available/default
 4) /var/www/btranslator/sites/default/settings.php

Options:
    --fqdn=    if not provided, will ask interactively
"""

import sys
import getopt

from executil import ExecError, getoutput, system
from dialog_wrapper import Dialog

TEXT_FQDN = """
This is the domain that you have registered
(or plan to register) for the B-Translator.

It will modify the files:
 1) /etc/hostname
 2) /etc/hosts
 3) /etc/nginx/sistes-available/default
 4) /var/www/btranslator/sites/default/settings.php

Enter the domain (usually something like l10n.org.xx):
"""

def usage(s=None):
    if s:
        print >> sys.stderr, "Error:", s
    print >> sys.stderr, "Syntax: %s [options]" % sys.argv[0]
    print >> sys.stderr, __doc__
    sys.exit(1)

def setdomain(fqdn ='l10n.org.xx'):
    """
    It will change the hostname and modify the files:
    - /etc/hostname
    - /etc/hosts
    - /etc/nginx/sistes-available/default
    - /var/www/btranslator/sites/default/settings.php
    """
    try:
        getoutput("hostname %s" % fqdn)

        path = '/etc/hostname'
        getoutput("echo '%s' > %s" % (fqdn, path))

        path = '/etc/hosts'
        getoutput("sed -e '/^127.0.1.1/c 127.0.1.1 %s btranslator' -i %s" % (fqdn, path))

        path = '/etc/nginx/sites-available/default'
        getoutput("sed -e 's/server_name .*$/server_name %s;/' -i %s" % (fqdn, path))

        path = '/var/www/btranslator/sites/default/settings.php'
        getoutput("sed -e '/^\$base_url/c $base_url = \"https://%s\";' -i %s" % (fqdn, path))

    except ExecError, e:
        d = Dialog('TurnKey Linux - First boot configuration')
        d.msgbox('Failure', e.output)

def main():
    try:
        opts, args = getopt.gnu_getopt(sys.argv[1:], "h",
                                       ['help', 'fqdn='])
    except getopt.GetoptError, e:
        usage(e)

    fqdn = ""
    for opt, val in opts:
        if opt in ('-h', '--help'):
            usage()
        elif opt == '--fqdn':
            fqdn = val

    if fqdn:
        setdomain(fqdn)
        return

    d = Dialog('TurnKey B-Translator - First boot configuration')
    retcode, fqdn = d.inputbox("Set the domain name (fqdn) of the server",
                               TEXT_FQDN, "l10n.org.xx", "Apply", "Skip")
    if not fqdn or retcode == 1:
        return

    setdomain(fqdn)


if __name__ == "__main__":
    main()

