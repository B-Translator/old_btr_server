
/**
 * Make an HTTP request to the given URL
 * and output debug information about it.
 */
var http_request = function(url, settings) {
    // If parameter settings is not given, assign a default value.
    settings = settings || {};

    var ajax_params = {
        url: url,
        type: settings.method || 'GET',
        data: settings.data,
        headers: settings.headers,
        dataType: 'json',
        async: settings.async,
        crossDomain: settings.crossDomain || true,
	processData: settings.processData || true,
        beforeSend: function() {
            var str_settings = JSON.stringify(settings, undefined, 4);
            debug("\n------------ start http_request -----------------"
                  + "\n===> URL: " + url
                  + "\n===> SETTINGS:\n" + str_settings);
            return true;
        }
    };
    if (settings.processData === false) {
	ajax_params.processData = false;
    };
    if (settings.contentType === false) {
	ajax_params.contentType = false;
    };

    var request = $.ajax(ajax_params);
    request.done(function(response) {
        debug("\n===> RESULT:\n" + JSON.stringify(response, undefined, 4));
    });
    request.fail(function(jqXHR, textStatus, errorThrown) {
        debug("\n===> ERROR " + jqXHR.status + ': ' + errorThrown);
	console.log(errorThrown);
    });
    request.always(function(){
        debug("\n------------ end http_request -----------------\n");
    });
    return request;
}
