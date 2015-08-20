// GET btr/report/statistics
var request = http_request(base_url + '/btr/report/statistics?lng=sq');
request.done(function(response) {
    console.log(response);    // response is an Object
});
request.fail(function(jqXHR, textStatus, errorThrown ) {
    console.log(textStatus + ' ' + jqXHR.status + ': ' + errorThrown);
});
