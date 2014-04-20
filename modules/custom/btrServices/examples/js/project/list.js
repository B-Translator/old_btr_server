// POST public/btr/project/list
var url = base_url + '/public/btr/project/list';
var settings = {
    async: false,
    method: 'POST',
    data: {},
};
http_request(url, settings);

// Filter list by origin.
settings.data = { origin: 't*' };
http_request(url, settings);

// Retrieve only a list of origins.
settings.data = { project: '-' };
http_request(url, settings);

// Filter list by origin.
settings.data = {
    origin: 'test',
    project: 'p*',
};
http_request(url, settings);
