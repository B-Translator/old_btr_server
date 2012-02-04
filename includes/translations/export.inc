<?php
/**
 * @file
 *   Export the most voted translations of a project into a PO file.
 */

/**
 * Menu callback: translations/export
 * Export the most voted translations of a project into a PO file.
 */
function l10n_suggestions_export() {
  return 'Not implemented yet.

<xmp>
** How to use simple REST API for exporting projects

*** List:
    wget --no-check-certificate -O list.txt https://l10n-sq.org/translations/project/list
    cat list.txt
    wget --no-check-certificate -O list.txt https://l10n-sq.org/translations/project/list/GNOME
    wget --no-check-certificate -O list.txt https://l10n-sq.org/translations/project/list/GNOME/a*
    wget --no-check-certificate -O list.txt https://l10n-sq.org/translations/project/list/*/kturtle
    wget --no-check-certificate -O list.txt https://l10n-sq.org/translations/project/list/*/kturtle/json
    wget --no-check-certificate -O list.txt https://l10n-sq.org/translations/project/list/*/-
    wget --no-check-certificate -O list.txt https://l10n-sq.org/translations/project/list/*/*turtle*/text

*** Export:
    wget --no-check-certificate -O test1.po https://l10n-sq.org/translations/project/export/KDE/kturtle/sq
    vim test1.po

*** LibreOffice:
    + List:
      wget --no-check-certificate -O list.txt \
             https://l10n-sq.org/translations/project/list/LibreOffice
      cat list.txt

    + Export:
      wget --no-check-certificate -O LibreOffice-sw-fr.tgz \
             https://l10n-sq.org/translations/project/export_tgz/LibreOffice/sw/fr
      tar tvfz LibreOffice-sw-fr.tgz
      tar xfz LibreOffice-sw-fr.tgz

    + Export all the projects:
      wget --no-check-certificate -O LibreOffice-all-fr.tgz \
             https://l10n-sq.org/translations/project/export_tgz/LibreOffice/all/fr
      tar tvfz LibreOffice-all-fr.tgz
      tar xfz LibreOffice-all-fr.tgz

*** Mozilla:
    + List:
      wget --no-check-certificate -O list.txt \
             https://l10n-sq.org/translations/project/list/Mozilla
      cat list.txt

    + Export:
      wget --no-check-certificate -O Mozilla-browser-fr.tgz \
             https://l10n-sq.org/translations/project/export_tgz/Mozilla/browser/fr
      tar tvfz Mozilla-browser-fr.tgz
      tar xfz Mozilla-browser-fr.tgz

    + Export all the projects:
      wget --no-check-certificate -O Mozilla-all-fr.tgz \
             https://l10n-sq.org/translations/project/export_tgz/Mozilla/all/fr
      tar tvfz Mozilla-all-fr.tgz
      tar xfz Mozilla-all-fr.tgz

</xmp>
';
}

?>