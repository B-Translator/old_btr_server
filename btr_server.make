api = 2
core = 7.x

;--------------------
; Specify defaults
;--------------------

defaults[projects][subdir] = contrib

;--------------------
; Bootstrap Theme
;--------------------

projects[bootstrap] = 3.0
projects[jquery_update] = 3.0-alpha3
projects[less] = 4.0

libraries[bootstrap][directory_name] = bootstrap
libraries[bootstrap][download][type] = get
libraries[bootstrap][download][url] = https://github.com/twbs/bootstrap/archive/v3.3.5.zip

libraries[lessphp][directory_name] = lessphp
libraries[lessphp][download][type] = get
libraries[lessphp][download][url] = https://github.com/oyejorge/less.php/archive/v1.7.0.5.tar.gz

;--------------------
; Web Services
;--------------------

projects[oauth2_loginprovider] = 1.6

;--------------------
; Contrib
;--------------------

;;; Development
projects[devel] = 1.5
;projects[coder] = 1.2
projects[diff] = 3.2

;;; Extensions
projects[ctools] = 1.9
projects[libraries] = 2.2
projects[entity] = 1.6
projects[xautoload] = 5.5
projects[token] = 1.6
projects[rules] = 2.9
projects[pathauto] = 1.3
projects[subpathauto] = 1.3

;;; User interface
projects[context] = 3.6
projects[views] = 3.11
projects[boxes] = 1.2
projects[edit_profile] = 1.0-beta2
projects[contact_forms] = 1.8
projects[menu_target] = 1.4
projects[empty_front_page] = 1.0

projects[wysiwyg] = 2.2
projects[nocurrent_pass] = 1.0

libraries[tinymce][directory_name] = tinymce
libraries[tinymce][download][type] = get
libraries[tinymce][download][url] = https://github.com/tinymce/tinymce/archive/4.1.6.zip

;;; Security
projects[captcha] = 1.3
projects[recaptcha] = 2.0
projects[honeypot] = 1.21
projects[user_restrictions] = 1.0

;;; Features
projects[features] = 2.7
projects[strongarm] = 2.0
projects[features_extra] = 1.0
projects[node_export] = 3.0
projects[uuid] = 1.0-beta1
;projects[menu_import] = 1.6

;;; Admin Utils
projects[module_filter] = 2.0
projects[drush_language] = 1.5
projects[delete_all] = 1.1
projects[l10n_update] = 2.0
projects[advuser] = 3.x-dev
projects[google_analytics] = 2.1

;;; Performance
projects[boost] = 1.0
projects[memcache] = 1.5


;--------------------
; Sending Emails
;--------------------

projects[mailsystem] = 2.34
projects[mimemail] = 1.0-beta4
projects[reroute_email] = 1.2

;projects[phpmailer] = 3.x-dev
projects[phpmailer][download][revision] = 8f7c632
projects[phpmailer][download][branch] = 7.x-3.x

libraries[phpmailer][directory_name] = phpmailer
libraries[phpmailer][download][type] = get
libraries[phpmailer][download][url] = https://github.com/PHPMailer/PHPMailer/archive/v5.2.9.zip

;--------------------
; HybridAuth
;--------------------

projects[hybridauth] = 2.14

libraries[hybridauth][directory_name] = hybridauth
libraries[hybridauth][download][type] = get
libraries[hybridauth][download][url] = https://github.com/hybridauth/hybridauth/archive/2.5.1.tar.gz
