api = 2
core = 7.x

;--------------------
; Specify defaults
;--------------------

defaults[projects][subdir] = "contrib"
defaults[libraries][type] = "library"

;--------------------
; Themes
;--------------------

projects[bootstrap][version] = "2.2"

;--------------------
; Contrib
;--------------------

projects[coder][version] = 1.2
projects[context][version] = 3.2
projects[ctools][version] = 1.4
projects[devel][version] = 1.4
projects[diff][version] = 3.2
projects[features][version] = 1.0
projects[strongarm][version] = 2.0
projects[views][version] = 3.7
projects[geshifilter][version] = "1.2"
projects[libraries][version] = "2.2"
projects[module_filter][version] = "1.8"
projects[profiler_builder][version] = "1.0-rc3"
projects[wysiwyg][version] = "2.2"
projects[google_analytics][version] = "1.3"
projects[token][version] = "1.5"
projects[edit_profile][version] = "1.0-beta2"
;projects[examples][version] = "1.x-dev"
projects[entity][version] = "1.5"
projects[rules][version] = "2.6"
projects[homebox][version] = "2.0-beta7"
projects[simpletest_clone][version] = "1.0-beta3"
projects[captcha][version] = "1.0"
projects[recaptcha][version] = "1.11"
projects[honeypot][version] = "1.16"
projects[features_extra][version] = "1.0-beta1"
projects[uuid][version] = "1.0-alpha5"
projects[node_export][version] = "3.0"
projects[xautoload][version] = "4.5"
projects[jquery_update][version] = "2.4"
projects[boxes][version] = "1.1"
projects[delete_all][version] = "1.1"
projects[user_restrictions][version] = "1.0"
projects[pathauto][version] = "1.2"
projects[menu_import][version] = "1.6"

;--------------------
; Drush Utilities
;--------------------
projects[drush_language][version] = "1.2"
;projects[drush_entity][version] = "5.x-dev"

;--------------------
; Web Services
;--------------------
projects[services][version] = "3.7"
projects[services][patch][] = "https://drupal.org/files/fix_controller_settings-1154420-51.patch"

projects[entityreference][version] = "1.1"
projects[oauth2_server][version] = "1.0"

libraries[oauth2-server-php][directory_name] = "oauth2-server-php"
libraries[oauth2-server-php][download][type] = "git"
libraries[oauth2-server-php][download][url] = "https://github.com/bshaffer/oauth2-server-php.git"
libraries[oauth2-server-php][download][branch] = "v1.1"

projects[wsclient][version] = "1.0"
projects[wsclient][patch][] = "https://drupal.org/files/wsclient-1285310-http_basic_authentication-14.patch"
projects[wsclient][patch][] = "https://drupal.org/files/issues/wsclient-2138617-oauth2_support.patch"

projects[http_client][version] = "2.x-dev"

projects[oauth2_client][version] = "1.0"
projects[oauth2_login][version] = "1.0"
projects[oauth2_loginprovider][version] = "1.0"


;--------------------
; Performance
;--------------------
projects[boost][version] = "1.0-beta2"
projects[memcache][version] = "1.0"

;--------------------
; Community and Social
;--------------------
projects[drupalchat][version] = "1.0-beta15"
projects[disqus][version] = "1.10"
projects[disqus][patch][] = "http://drupal.org/files/disqus-https.patch"
projects[sharethis][version] = "2.6"

projects[hybridauth][version] = "2.8"
projects[hybridauth][patch][] = "https://drupal.org/files/issues/hybridauth-2164869-Adding_support_for_DrupalOAuth2_provider.patch"
projects[hybridauth][patch][] = "https://drupal.org/files/issues/hybridauth-2164869-2-Small_fix_on_the_previous_patch.patch"

projects[fb][version] = "3.4-beta3"
projects[invite][version] = "2.1-beta2"

;--------------------
; Drupal Localization
;--------------------
projects[l10n_update][version] = "1.0"
projects[l10n_client][version] = "1.3"

;--------------------
; Mail Related
;--------------------
projects[mailsystem][version] = "2.34"
projects[phpmailer][version] = "3.x-dev"
projects[mimemail][version] = "1.0-beta3"
projects[reroute_email][version] = "1.1"
projects[simplenews][version] = "1.0"
projects[mass_contact][version] = "1.0-beta3"


;--------------------
; Libraries
;--------------------

libraries[phpmailer][directory_name] = "phpmailer"
libraries[phpmailer][download][type] = "get"
libraries[phpmailer][download][url] = "https://github.com/PHPMailer/PHPMailer/archive/v5.2.6.zip"

libraries[bootstrap][directory_name] = "bootstrap"
libraries[bootstrap][download][type] = "get"
libraries[bootstrap][download][url] = "https://github.com/twbs/bootstrap/archive/v3.0.0.zip"

libraries[facebook-php-sdk][directory_name] = "facebook-php-sdk"
libraries[facebook-php-sdk][download][type] = "git"
libraries[facebook-php-sdk][download][url] = "https://github.com/facebook/facebook-php-sdk.git"

libraries[geshi][directory_name] = "geshi"
libraries[geshi][download][type] = "get"
libraries[geshi][download][url] = "http://downloads.sourceforge.net/project/geshi/geshi/GeSHi%201.0.8.10/GeSHi-1.0.8.10.tar.gz"

libraries[tinymce][directory_name] = "tinymce"
libraries[tinymce][download][type] = "get"
libraries[tinymce][download][url] = "http://github.com/downloads/tinymce/tinymce/tinymce_3.5.7.zip"

libraries[hybridauth][directory_name] = "hybridauth-2.1.2"
;libraries[hybridauth][download][type] = "get"
;libraries[hybridauth][download][url] = "http://sourceforge.net/projects/hybridauth/files/hybridauth-2.1.2.zip"
libraries[hybridauth][download][type] = "git"
libraries[hybridauth][download][url] = "https://github.com/dashohoxha/hybridauth.git"

;libraries[hybridauth-additional-providers][directory_name] = "hybridauth-additional-providers-1.8"
;libraries[hybridauth-additional-providers][download][type] = "get"
;libraries[hybridauth-additional-providers][download][url] = "http://sourceforge.net/projects/hybridauth/files/hybridauth-additional-providers-1.8.zip"
