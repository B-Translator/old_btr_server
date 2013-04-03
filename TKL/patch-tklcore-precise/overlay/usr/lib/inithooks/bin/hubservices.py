#!/usr/bin/python
# Copyright (c) 2011 Alon Swartz <alon@turnkeylinux.org> - all rights reserved
"""Initialize Hub Services (TKLBAM, HubDNS)

Options:
    --apikey=    if not provided, will ask interactively
    --fqdn=      if not provided, will ask interactively
"""

import sys
import getopt

from executil import ExecError, getoutput, system
from dialog_wrapper import Dialog

TEXT_SERVICES = """1) TurnKey Backup and Migration: saves changes to files,
   databases and package management to encrypted storage
   which servers can be automatically restored from.
   http://www.turnkeylinux.org/tklbam

2) TurnKey Domain Management and Dynamic DNS:
   http://www.turnkeylinux.org/dns

You can start using these services immediately if you initialize now. Or you can do this manually later (e.g., from the command line / Webmin)

API Key: (see https://hub.turnkeylinux.org/profile)
"""

TEXT_HUBDNS = """TurnKey supports dynamic DNS configuration, powered by Amazon Route 53, a robust cloud DNS service: http://www.turnkeylinux.org/dns

You can assign a hostname under:

1) Any custom domain you are managing with the Hub.
   For example: myhostname.mydomain.com

2) The tklapp.com domain, if the hostname is untaken.
   For example: myhostname.tklapp.com

Set hostname (or press Enter to skip):
"""

SUCCESS_TKLBAM = """Now that TKLBAM is initialized, you can backup using the following shell command (no arguments required):

    tklbam-backup

You can enable daily automatic backup updates with this command:

    chmod +x /etc/cron.daily/tklbam-backup

Documentation: http://www.turnkeylinux.org/tklbam
Manage your backups: https://hub.turnkeylinux.org
"""

SUCCESS_HUBDNS = """You can enable hourly automatic updates with this command:

    chmod +x /etc/cron.hourly/hubdns-update

Documentation: http://www.turnkeylinux.org/dns
Manage your hostnames: https://hub.turnkeylinux.org
"""

CONNECTIVITY_ERROR = """Unable to connect to the Hub.

Please try again once your network settings are configured, either via the Webmin interface, or by using the following shell commands:

    tklbam-init APIKEY

    hubdns-init APIKEY FQDN
    hubdns-update
"""

def usage(s=None):
    if s:
        print >> sys.stderr, "Error:", s
    print >> sys.stderr, "Syntax: %s [options]" % sys.argv[0]
    print >> sys.stderr, __doc__
    sys.exit(1)

def main():
    try:
        opts, args = getopt.gnu_getopt(sys.argv[1:], "h", 
                                       ['help', 'apikey=', 'fqdn='])
    except getopt.GetoptError, e:
        usage(e)

    apikey = ""
    fqdn = ""
    for opt, val in opts:
        if opt in ('-h', '--help'):
            usage()
        elif opt == '--apikey':
            apikey = val
        elif opt == '--fqdn':
            fqdn = val

    if apikey:
        system('tklbam-init %s' % apikey)

        if fqdn:
            system('hubdns-init %s %s' % (apikey, fqdn))
            system('hubdns-update')

        return

    initialized_tklbam = False
    d = Dialog('TurnKey Linux - First boot configuration')
    while 1:
        retcode, apikey = d.inputbox("Initialize Hub services", TEXT_SERVICES,
                                     apikey, "Apply", "Skip")

        if not apikey or retcode == 1:
            break

        d.infobox("Linking TKLBAM to the TurnKey Hub...")

        try:
            getoutput("host -W 2 hub.turnkeylinux.org")
        except ExecError, e:
            d.error(CONNECTIVITY_ERROR)
            break

        try:
            getoutput('tklbam-init %s' % apikey)
            d.msgbox('Success! Linked TKLBAM to Hub', SUCCESS_TKLBAM)
            initialized_tklbam = True
            break

        except ExecError, e:
            d.msgbox('Failure', e.output)
            continue

    if initialized_tklbam:
        while 1:
            retcode, fqdn = d.inputbox("Assign TurnKey DNS hostname", TEXT_HUBDNS,
                                       fqdn, "Apply", "Skip")

            if not fqdn or retcode == 1:
                break

            d.infobox("Linking HubDNS to the TurnKey Hub...")

            try:
                getoutput('hubdns-init %s %s' % (apikey, fqdn))
                getoutput('hubdns-update')
                d.msgbox('Success! Assigned %s' % fqdn, SUCCESS_HUBDNS)
                break

            except ExecError, e:
                d.msgbox('Failure', e.output)
                continue

if __name__ == "__main__":
    main()

