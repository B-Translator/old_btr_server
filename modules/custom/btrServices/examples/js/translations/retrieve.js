// GET btr/translations
url = base_url + '/btr/translations/ed685775fa0608fa42e20b3d28454c63972f62cd?lng=sq';
http_request(url, {async: false});

// Note what happens when the requests are asynchronous (which is the default).
http_request(base_url + '/btr/translations/random?lng=sq');
http_request(base_url + '/btr/translations/translated?lng=sq');
http_request(base_url + '/btr/translations/untranslated?lng=sq');
