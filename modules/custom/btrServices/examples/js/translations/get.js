// POST btr/translations/get
var url = base_url + '/btr/translations/get';
var settings = {
    async: false,
    method: 'POST',
    data: {
        sguid: 'ed685775fa0608fa42e20b3d28454c63972f62cd',
        lng: 'sq',
    },
    headers: {},
};
http_request(url, settings);

settings.data.sguid = 'random';
http_request(url, settings);

settings.data.sguid = 'translated';
http_request(url, settings);

settings.data.sguid = 'untranslated';
http_request(url, settings);
