/**
 * Get and return an access token.
 */
var get_access_token = function(oauth2) {
    var result = http_request(oauth2.token_url, {
        async: false,
        method: 'POST',
        data: {
            grant_type: 'password',
            username: oauth2.username,
            password: oauth2.password,
            scope: oauth2.scope,
        },
        headers: {
            'Authorization': 'Basic ' 
                + btoa(oauth2.client_id + ':' + oauth2.client_secret),  // base64_encode
        },
    });

    return result.responseJSON.access_token;
}