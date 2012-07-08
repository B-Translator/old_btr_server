api = 2
core = 7.x

; Build Kit 7.x-2.x HEAD
includes[] = http://drupalcode.org/project/buildkit.git/blob_plain/refs/heads/7.x-2.x:/drupal-org.make

;---------------------------
; Override BuildKit settings
;---------------------------

projects[admin][subdir] = FALSE
projects[context][subdir] = FALSE
projects[ctools][subdir] = FALSE
projects[devel][subdir] = FALSE
projects[diff][subdir] = FALSE
projects[features][subdir] = FALSE
projects[openidadmin][subdir] = FALSE
projects[strongarm][subdir] = FALSE
projects[views][subdir] = FALSE

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

;projects[admin][version] = "2.0-beta3"
;projects[openidadmin][version] = "1.0"
;projects[context][version] = "3.0-beta3"
;projects[ctools][version] = "1.0"
;projects[diff][version] = "2.0"
;projects[features][version] = "1.0-rc2"
;projects[strongarm][version] = "2.0"
;projects[views][version] = "3.3"
;projects[devel][version] = "1.3"

projects[boost][version] = "1.x-dev"
projects[fb][version] = "3.x-dev"
projects[geshifilter][version] = "1.0"
projects[libraries][version] = "2.x-dev"
projects[module_filter][version] = "1.6"
projects[profiler_builder][version] = "1.0-alpha2"
projects[reroute_email][version] = "1.1"
projects[smtp][version] = "1.0-beta1"
projects[wysiwyg][version] = "2.1"

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
libraries[tinymce][download][url] = "http://github.com/downloads/tinymce/tinymce/tinymce_3.5b3.zip"

;--------------------
; Custom
;--------------------

;projects[B-Translator][type] = "module"
;projects[B-Translator][download][type] = "git"
;projects[B-Translator][download][url] = "https://github.com/dashohoxha/B-Translator.git"

