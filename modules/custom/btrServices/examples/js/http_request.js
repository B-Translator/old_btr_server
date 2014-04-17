
var http_request = function(url, settings) {

    settings = settings || {};

    $('#code').html('')

    $('#output').html('------------ start http_request -----------------');
    $('#output').append("\n===> URL: " + url);
    var str_settings = JSON.stringify(settings, undefined, 4);
    $('#output').append("\n===> SETTINGS:\n" + str_settings);

    var request = $.ajax({
        url: url,
        type: settings.method || 'GET',
        data: settings.data,
        headers: settings.headers,
        dataType: 'json'
    });
    request.done(function(response) {
        var str_response = JSON.stringify(response, undefined, 4);
        $("#output").append("\n===> RESULT:\n" + str_response);
    });
    request.fail(function(jqXHR, textStatus, errorThrown ) {
        var error_msg = textStatus + ' ' + jqXHR.status + ': ' + errorThrown;
        $("#output").append(error_msg);
    });
    request.always(function(){
        $("#output").append("\n------------ end http_request -----------------");
    });
}
