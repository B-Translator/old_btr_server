#!/usr/bin/python
# Copyright (c) 2013 Dashamir Hoxha <dashohoxha@gmail.com>

"""
Set the main translation language and the auxiliary ones.
The code of the languages should be given as options.

Options:
    --main-lang=     unless provided, will ask interactively
    --other-langs=   unless provided, will ask interactively

Example:
    --main-lang=sq_AL   --other-langs="fr de it"

"""

import sys
import getopt

from dialog_wrapper import Dialog
from executil import getoutput, system, ExecError
from mysqlconf import MySQL

def usage(s=None):
    if s:
        print >> sys.stderr, "Error:", s
    print >> sys.stderr, "Syntax: %s [options]" % sys.argv[0]
    print >> sys.stderr, __doc__
    sys.exit(1)

def main():
    try:
        opts, args = getopt.gnu_getopt(sys.argv[1:], "h",
                     ['help', 'main-lang=', 'other-langs='])

    except getopt.GetoptError, e:
        usage(e)

    main_lang=""
    other_langs=""

    for opt, val in opts:
        if opt in ('-h', '--help'):
            usage()
        elif opt == '--main-lang':
            main_lang = val
        elif opt == '--other-langs':
            other_langs = val

    d = Dialog('TurnKey B-Translator - First boot configuration')
    if not main_lang:
        main_lang = d.get_input(
            "Main translation language of B-Translator",
            "Please enter the code of the main translation language of your site (something like 'sq' or 'sq_AL'):")
    if not other_langs:
        other_langs = d.get_input(
            "Auxiliary languages of B-Translator",
            "Please enter the codes of helping (auxiliary) languages, separated by space (like 'fr de it'):")

    config_file = '/var/www/btranslator_data/config.sh'
    languages = main_lang + ' ' + other_langs
    try:
        getoutput('sed -e "/languages=/d" -i %s' % config_file)
        getoutput('echo \'languages="%s"\' >> %s' % (languages, config_file))
        m = MySQL()   # start mysqld
        vset = "/usr/bin/drush --yes --exact vset %s %s"
        getoutput(vset % ('l10n_feedback_translation_lng', main_lang))
    except ExecError, e:
        d.msgbox('Failure', e.output)

    try:
        file_inc = '/var/www/btranslator/profiles/btranslator/modules/l10n_feedback/includes/common.inc'
        d.msgbox('Instructions', "Please edit the file '%s' and modify the list of languages appropriately." % file_inc)
        system('nano --syntax=php +20,5 %s' % file_inc)
    except ExecError, e:
        d.msgbox('Failure', e.output)

if __name__ == "__main__":
    main()
