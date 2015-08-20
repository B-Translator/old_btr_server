// POST btr/report/topcontrib
var url = base_url + '/btr/report/topcontrib';
http_request(url, {
    method: 'POST',
    data: {
        lng: 'sq',
        period: 'week',
    },
});
