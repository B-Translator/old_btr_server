#!/usr/bin/python
# Copyright (c) 2013 Dashamir Hoxha <dashohoxha@gmail.com>

"""
Set MySQL passwords for the users 'btranslator' and 'btranslator_data'.
The first one is the user of the database 'btranslator' (containing Drupal)
and the second one is the user of the database 'btranslator_data'
(containing the translation data of B-Translator).

Options:
    --drupal-pass=    unless provided, will ask interactively
    --data-pass=      unless provided, will ask interactively

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

def escape_chars(s):
    """escape special characters: required by nested quotes in query"""
    s = s.replace("\\", "\\\\")  # \  ->  \\
    s = s.replace('"', '\\"')    # "  ->  \"
    s = s.replace("'", "'\\''")  # '  ->  '\''
    return s

def main():
    try:
        opts, args = getopt.gnu_getopt(sys.argv[1:], "h",
                     ['help', 'drupal-pass=', 'data-pass='])

    except getopt.GetoptError, e:
        usage(e)

    drupal_pass=""
    data_pass=""

    for opt, val in opts:
        if opt in ('-h', '--help'):
            usage()
        elif opt == '--drupal-pass':
            drupal_pass = val
        elif opt == '--data-pass':
            data_pass = val

    d = Dialog('TurnKey B-Translator - First boot configuration')
    if not drupal_pass:
        drupal_pass = d.get_password(
            "MySQL Password of Drupal Database",
            "Please enter new password for the MySQL 'btranslator' account.")
    if not data_pass:
        data_pass = d.get_password(
            "MySQL Password of the Translations Database",
            "Please enter new password for the MySQL 'btranslator_data' account.")

    # set passwords
    m = MySQL()
    m.execute('update mysql.user set Password=PASSWORD(\"%s\") where User=\"%s\"; flush privileges;' % (escape_chars(drupal_pass), 'btranslator'))
    m.execute('update mysql.user set Password=PASSWORD(\"%s\") where User=\"%s\"; flush privileges;' % (escape_chars(data_pass), 'btranslator_data'))

    # modify the configuration file of Drupal (settings.php)
    expr1 = "/^\\$databases = array/,+10  s/'password' => .*/'password' => '%s',/" % escape_chars(drupal_pass)
    expr2 = "/^\\$databases\\['l10n_feedback_db/,+5  s/'password' => .*/'password' => '%s',/" % escape_chars(data_pass)
    config_file = '/var/www/btranslator/sites/default/settings.php'
    try:
        getoutput('sed -e "%s" -e "%s" -i %s' % (expr1, expr2, config_file))
    except ExecError, e:
        d.msgbox('Failure', e.output)

    # modify also the connection settings on btranslator_data
    try:
        config_file = '/var/www/btranslator_data/db/settings.php'
        expr = "/^\\$dbpass/ s/= .*/= '%s'/" % data_pass
        getoutput('sed -e \"%s\" -i %s' % (expr, config_file))
    except ExecError, e:
        d.msgbox('Failure', e.output)

if __name__ == "__main__":
    main()
