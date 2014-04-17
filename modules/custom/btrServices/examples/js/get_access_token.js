
var get_access_token = function(oauth2_config) {
    http_request(oauth2_config.url, {
        method: 'POST',
        data: {
            grant_type: 'password',
            username: oauth2_config.username,
            password: oauth2_config.password,
            scope: oauth2_config.scope,
        },
        headers: {
            'Content-type': 'application/x-www-form-urlencoded',
            'Authorization': 'Basic ' . base64_encode($params['client_id'] . ':' . $params['client_secret']),
        },
    });
}
