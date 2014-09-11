api = 2
core = 7.x

;------------------------------
; Build Drupal core (with patches).
;------------------------------
includes[drupal] = drupal-org-core.make

;------------------------------
; Get profile btr_server.
;------------------------------
projects[btr_server][type] = profile
projects[btr_server][download][type] = git
projects[btr_server][download][url] = /usr/local/src/btr_server
projects[btr_server][download][branch] = master
