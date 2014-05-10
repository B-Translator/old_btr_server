api = 2
core = 7.x

;------------------------------
; Build Drupal core (with patches).
;------------------------------
includes[drupal] = https://raw.github.com/B-Translator/btr_server/master/drupal-org-core.make
;includes[drupal] = drupal-org-core.make

;------------------------------
; Get profile btr_server.
;------------------------------
projects[btr_server][type] = profile
projects[btr_server][download][type] = git
projects[btr_server][download][url] = https://github.com/B-Translator/btr_server.git
;projects[btr_server][download][url] = /var/www/btr_server
;projects[btr_server][download][branch] = dev
