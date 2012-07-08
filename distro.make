; Use this file to build a full distro including Drupal core (with patches) and
; the B-Translation install profile using the following command:
;
;     $ drush make distro.make [directory]

; Include Build Kit distro makefile via URL
includes[] = http://drupalcode.org/project/buildkit.git/blob_plain/refs/heads/7.x-2.x:/distro.make
projects[buildkit] = FALSE

projects[btranslator][type] = profile
projects[btranslator][download][type] = git
projects[btranslator][download][url] = https://github.com/dashohoxha/B-Translator.git
;;;for developing make files, comment the line above and use the following url and branch
;projects[btranslator][download][url] = /var/www/B-Translator
;projects[btranslator][download][branch] = test
