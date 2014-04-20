// Get an access  token.
var access_token = get_access_token(oauth2);

// POST btr/project/export
http_request(base_url + '/btr/project/export', {
    method: 'POST',
    data: {
        origin: 'test',
        project: 'kturtle',
        //export_mode: 'preferred_by_me',
    },
    headers: {
        'Authorization': 'Bearer ' + access_token,
    },

});
