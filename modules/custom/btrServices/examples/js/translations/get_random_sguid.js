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
    target: 'translated',
    lng: 'sq',
    last_sguid: 'c7ac448a01c566680d8ffb00430a55ffc779f24b',
};
http_request(url, settings);

settings.data = {
    target: 'next',
    last_sguid: 'c7ac448a01c566680d8ffb00430a55ffc779f24b',
};
http_request(url, settings);
