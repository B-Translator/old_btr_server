; Include Build Kit install profile makefile via URL
includes[] = http://drupalcode.org/project/buildkit.git/blob_plain/refs/heads/7.x-2.x:/drupal-org.make

;--------------------
; Additional Themes
;--------------------

projects[abessive][version] = "1.3"
projects[acquia_marina][version] = "1.0-rc3"
projects[fusion][version] = "2.0-beta2"
projects[fusion_accelerator][version] = "2.0-beta1"

;--------------------
; Additional Contrib
;--------------------

projects[geshifilter][version] = "1.0"
projects[libraries][version] = "2.0"
projects[module_filter][version] = "1.7"
projects[profiler_builder][version] = "1.0-alpha2"
projects[wysiwyg][version] = "2.1"
projects[google_analytics][version] = "1.2"
projects[token][version] = "1.2"
projects[edit_profile][version] = "1.0-beta2"
projects[examples][version] = "1.x-dev"
projects[entity][version] = "1.0-rc3"
projects[rules][version] = "2.2"
projects[homebox][version] = "2.0-beta6"
projects[simpletest_clone][version] = "1.0-beta3"
projects[captcha][version] = "1.0-beta2"
projects[recaptcha][version] = "1.8"
projects[honeypot][version] = "1.13"

;--------------------
; Performance
;--------------------
projects[boost][version] = "1.x-dev"
projects[memcache][version] = "1.0"

;--------------------
; Community and Social
;--------------------
projects[drupalchat][version] = "1.0-beta6"
projects[disqus][version] = "1.9"
projects[sharethis][version] = "2.5"
projects[rpx][version] = "2.2"
projects[fb][version] = "3.3-beta5"
projects[invite][version] = "2.1-beta2"

;--------------------
; Drupal Localization
;--------------------
projects[l10n_update][version] = "1.0-beta3"
projects[l10n_client][version] = "1.1"

;--------------------
; Mail Related
;--------------------
projects[mailsystem][version] = "2.34"
projects[phpmailer][version] = "3.x-dev"
projects[mimemail][version] = "1.0-alpha2"
projects[reroute_email][version] = "1.1"
projects[simplenews][version] = "1.0"
projects[mass_contact][version] = "1.0-alpha6"


;--------------------
; Libraries
;--------------------

libraries[facebook-php-sdk][type] = "library"
libraries[facebook-php-sdk][directory_name] = "facebook-php-sdk"
libraries[facebook-php-sdk][download][type] = "git"
libraries[facebook-php-sdk][download][url] = "https://github.com/facebook/facebook-php-sdk.git"

libraries[geshi][type] = "library"
libraries[geshi][directory_name] = "geshi"
libraries[geshi][download][type] = "get"
libraries[geshi][download][url] = "http://downloads.sourceforge.net/project/geshi/geshi/GeSHi%201.0.8.10/GeSHi-1.0.8.10.tar.gz"

libraries[tinymce][type] = "library"
libraries[tinymce][directory_name] = "tinymce"
libraries[tinymce][download][type] = "get"
libraries[tinymce][download][url] = "http://github.com/downloads/tinymce/tinymce/tinymce_3.5.7.zip"

libraries[phpmailer][type] = "library"
libraries[phpmailer][directory_name] = "phpmailer"
libraries[phpmailer][download][type] = "get"
libraries[phpmailer][download][url] = "http://downloads.sourceforge.net/project/phpmailer/phpmailer%20for%20php5_6/PHPMailer%20v5.1/PHPMailer_v5.1.tar.gz"
