// POST btr/translations/get_random_sguid
var url = base_url + '/btr/translations/get_random_sguid';
var settings = {
    //async: false,
    method: 'POST',
    data: { target: 'random' },
};
http_request(url, settings);

settings.data = {
    target: 'translated',
    lng: 'sq',
};
http_request(url, settings);

settings.data = {
    target: 'random',
    scope: 'vocabulary/ICT_sq',
};
http_request(url, settings);
