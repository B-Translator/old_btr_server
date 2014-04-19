// POST public/btr/report/topcontrib
var url = base_url + '/public/btr/report/topcontrib';
http_request(url, {
    method: 'POST',
    data: {
        lng: 'sq',
        period: 'week',
    },
});