// POST btr/translations/search
http_request(base_url + '/btr/translations/search', {
    method: 'POST',
    data: {
        lng: 'sq',
        words: 'file',
        page: 2,
    },
});
