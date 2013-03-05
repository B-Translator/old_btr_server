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
projects[geshifilter][subdir] = "contrib"
projects[libraries][version] = "2.0"
projects[libraries][subdir] = "contrib"
projects[module_filter][version] = "1.7"
projects[module_filter][subdir] = "contrib"
projects[profiler_builder][version] = "1.0-alpha2"
projects[profiler_builder][subdir] = "contrib"
projects[wysiwyg][version] = "2.1"
projects[wysiwyg][subdir] = "contrib"
projects[google_analytics][version] = "1.2"
projects[google_analytics][subdir] = "contrib"
projects[token][version] = "1.2"
projects[token][subdir] = "contrib"
projects[edit_profile][version] = "1.0-beta2"
projects[edit_profile][subdir] = "contrib"
projects[examples][version] = "1.x-dev"
projects[examples][subdir] = "contrib"
projects[entity][version] = "1.0-rc3"
projects[entity][subdir] = "contrib"
projects[rules][version] = "2.2"
projects[rules][subdir] = "contrib"
projects[homebox][version] = "2.0-beta6"
projects[homebox][subdir] = "contrib"
projects[simpletest_clone][version] = "1.0-beta3"
projects[simpletest_clone][subdir] = "contrib"
projects[captcha][version] = "1.0-beta2"
projects[captcha][subdir] = "contrib"
projects[recaptcha][version] = "1.8"
projects[recaptcha][subdir] = "contrib"
projects[honeypot][version] = "1.13"
projects[honeypot][subdir] = "contrib"

;--------------------
; Performance
;--------------------
projects[boost][version] = "1.x-dev"
projects[boost][subdir] = "contrib"
projects[memcache][version] = "1.0"
projects[memcache][subdir] = "contrib"

;--------------------
; Community and Social
;--------------------
projects[drupalchat][version] = "1.0-beta6"
projects[drupalchat][subdir] = "contrib"
projects[disqus][version] = "1.9"
projects[disqus][subdir] = "contrib"
projects[sharethis][version] = "2.5"
projects[sharethis][subdir] = "contrib"
projects[rpx][version] = "2.2"
projects[rpx][subdir] = "contrib"
projects[fb][version] = "3.3-beta5"
projects[fb][subdir] = "contrib"
projects[invite][version] = "2.1-beta2"
projects[invite][subdir] = "contrib"

;--------------------
; Drupal Localization
;--------------------
projects[l10n_update][version] = "1.0-beta3"
projects[l10n_update][subdir] = "contrib"
projects[l10n_client][version] = "1.1"
projects[l10n_client][subdir] = "contrib"

;--------------------
; Mail Related
;--------------------
projects[mailsystem][version] = "2.34"
projects[mailsystem][subdir] = "contrib"
projects[phpmailer][version] = "3.x-dev"
projects[phpmailer][subdir] = "contrib"
projects[mimemail][version] = "1.0-alpha2"
projects[mimemail][subdir] = "contrib"
projects[reroute_email][version] = "1.1"
projects[reroute_email][subdir] = "contrib"
projects[simplenews][version] = "1.0"
projects[simplenews][subdir] = "contrib"
projects[mass_contact][version] = "1.0-alpha6"
projects[mass_contact][subdir] = "contrib"


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
