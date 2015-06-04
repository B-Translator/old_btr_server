// POST public/btr/translations/get_random_sguid
var url = base_url + '/public/btr/translations/get_random_sguid';
var settings = {
    //async: false,
    method: 'POST',
    data: { target: 'next' },
};
http_request(url, settings);

settings.data = {
    target: 'translated',
    lng: 'sq',
};
http_request(url, settings);

settings.data = {
    target: 'next',
    scope: 'vocabulary/ICT_sq',
};
http_request(url, settings);
