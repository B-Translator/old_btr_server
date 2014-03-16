api = 2
core = 7.x

;------------------------------
; Build Drupal core (with patches).
;------------------------------
includes[drupal] = https://raw.github.com/dashohoxha/B-Translator/master/drupal-org-core.make
;includes[drupal] = drupal-org-core.make

;------------------------------
; Get profile btranslator.
;------------------------------
projects[btranslator][type] = profile
projects[btranslator][download][type] = git
projects[btranslator][download][url] = https://github.com/dashohoxha/B-Translator.git
;projects[btranslator][download][url] = /var/www/B-Translator
;projects[btranslator][download][branch] = dev
