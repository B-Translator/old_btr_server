
// Function for adding a new translation.
var add_translation = function() {
    // POST btr/translations/add
    var request = http_request(base_url +  '/btr/translations/add', {
        method: 'POST',
        data: {
            sguid: sguid,
            lng: lng,
            translation: new_translation,
        },
        headers: {
            'Authorization': 'Bearer ' + access_token,
        },
    });

    // After adding the translation retrieve the string to check it.
    request.done(get_string);
};

// Function to retrieve the string.
var get_string = function(response) {
    // Keep the id of added translation on a global variable.
    // We will need it later for deleting it.
    tguid = response.tguid;

    var url = base_url + '/public/btr/translations/' + sguid + '?lng=sq';
    var request = http_request(url);

    // Now delete the translation.
    request.done(del_translation);
};

// Function for deleting the translation.
var del_translation = function() {
    // POST btr/translations/del
    var request = http_request(base_url +  '/btr/translations/del', {
        method: 'POST',
        data: { tguid: tguid },
        headers: { 'Authorization': 'Bearer ' + access_token },
    });
}

/******************************************************/

// Get an access  token.
var access_token = get_access_token(oauth2);

// Add a new translation to a string.
var sguid = '2a12b39f41bbd1ac78fdf456c25a480d2060c06b';
var lng = 'sq';
var new_translation = 'test-translation-' + Math.floor(Math.random() * 10);
add_translation();
