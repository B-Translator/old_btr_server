api = 2
core = 7.x

;--------------------
; Specify defaults
;--------------------

defaults[projects][subdir] = "contrib"

;--------------------
; Bootstrap Theme
;--------------------

projects[bootstrap][version] = "2.2"
projects[jquery_update][version] = "2.4"

libraries[bootstrap][directory_name] = "bootstrap"
libraries[bootstrap][download][type] = "get"
libraries[bootstrap][download][url] = "https://github.com/twbs/bootstrap/archive/v3.0.0.zip"

;--------------------
; Web Services
;--------------------

projects[oauth2_loginprovider][type] = "module"
projects[oauth2_loginprovider][download][type] = "git"
projects[oauth2_loginprovider][download][url] = "https://github.com/dashohoxha/oauth2_loginprovider.git"

;--------------------
; Contrib
;--------------------

;;; Development
projects[devel][version] = "1.5"
;projects[coder][version] = "1.2"
projects[diff][version] = "3.2"
;projects[simpletest_clone][version] = "1.0-beta3"

;;; Extensions
projects[ctools][version] = "1.4"
projects[libraries][version] = "2.2"
projects[entity][version] = "1.5"
projects[xautoload][version] = "4.5"
projects[token][version] = "1.5"
projects[rules][version] = "2.7"
projects[pathauto][version] = "1.2"
projects[subpathauto][version] = "1.3"

;;; User interface
projects[context][version] = "3.2"
projects[views][version] = "3.8"
projects[boxes][version] = "1.1"
projects[edit_profile][version] = "1.0-beta2"

projects[wysiwyg][version] = "2.2"

libraries[tinymce][directory_name] = "tinymce"
libraries[tinymce][download][type] = "get"
libraries[tinymce][download][url] = "http://github.com/downloads/tinymce/tinymce/tinymce_3.5.7.zip"

;;; Security
projects[captcha][version] = "1.0"
projects[recaptcha][version] = "1.11"
projects[honeypot][version] = "1.17"
projects[user_restrictions][version] = "1.0"

;;; Features
projects[features][version] = "1.0"
projects[strongarm][version] = "2.0"
projects[features_extra][version] = "1.0-beta1"
projects[node_export][version] = "3.0"
projects[uuid][version] = "1.0-alpha5"
;projects[menu_import][version] = "1.6"

;;; Admin Utils
projects[module_filter][version] = "1.8"
projects[drush_language][version] = "1.2"
projects[delete_all][version] = "1.1"
projects[l10n_update][version] = "1.0"

;;; Performance
projects[boost][version] = "1.0"
projects[memcache][version] = "1.0"

;--------------------
; Sending Emails
;--------------------

projects[mailsystem][version] = "2.34"
projects[mimemail][version] = "1.0-beta3"
projects[reroute_email][version] = "1.1"

;projects[phpmailer][version] = "3.x-dev"
projects[phpmailer][download][type] = "git"
projects[phpmailer][download][url] = "http://git.drupal.org/project/phpmailer.git"
projects[phpmailer][download][branch] = "7.x-3.x"

libraries[phpmailer][directory_name] = "phpmailer"
libraries[phpmailer][download][type] = "get"
libraries[phpmailer][download][url] = "https://github.com/PHPMailer/PHPMailer/archive/v5.2.6.zip"

;--------------------
; HybridAuth
;--------------------

projects[hybridauth][version] = "2.8"
projects[hybridauth][patch][] = "https://drupal.org/files/issues/hybridauth-2164869-Adding_support_for_DrupalOAuth2_provider.patch"
projects[hybridauth][patch][] = "https://drupal.org/files/issues/hybridauth-2164869-2-Small_fix_on_the_previous_patch.patch"

libraries[hybridauth][directory_name] = "hybridauth"
libraries[hybridauth][download][type] = "git"
libraries[hybridauth][download][url] = "https://github.com/dashohoxha/hybridauth.git"

;libraries[hybridauth][directory_name] = "hybridauth"
;libraries[hybridauth][download][type] = "get"
;libraries[hybridauth][download][url] = "http://sourceforge.net/projects/hybridauth/files/hybridauth-2.1.2.zip"
;libraries[hybridauth-additional-providers][directory_name] = "hybridauth-additional-providers-1.8"
;libraries[hybridauth-additional-providers][download][type] = "get"
;libraries[hybridauth-additional-providers][download][url] = "http://sourceforge.net/projects/hybridauth/files/hybridauth-additional-providers-1.8.zip"
