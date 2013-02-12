; Include Drupal core and any core patches from Build Kit
includes[] = http://drupalcode.org/project/buildkit.git/blob_plain/refs/heads/7.x-2.x:/drupal-org-core.make
;projects[buildkit] = FALSE

projects[btranslator][type] = profile
projects[btranslator][download][type] = git
projects[btranslator][download][url] = https://github.com/dashohoxha/B-Translator.git
;projects[btranslator][download][url] = /var/www/B-Translator
;projects[btranslator][download][branch] = dev
