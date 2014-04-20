// Get an access  token.
var access_token = get_access_token(oauth2);

// POST btr/project/add_string
var url = base_url + '/btr/project/add_string';
var settings = {
    async: false,
    method: 'POST',
    data: {
        origin: 'test',
        project: 'pingus',
        string: 'Test string ' + Math.floor(Math.random() * 10),
    },
    headers: {
        'Authorization': 'Bearer ' + access_token,
    },

};
var sguid;
http_request(url, settings)
    .done(function(result){
        sguid = result.sguid;
    });

// Retrive the string.
var url = base_url + '/public/btr/translations/' + sguid + '?lng=sq';
http_request(url, { async: false });

// Delete the string that was added above.
http_request(base_url + '/btr/project/del_string', {
    method: 'POST',
    data: { sguid: sguid },
    headers: { 'Authorization': 'Bearer ' + access_token },
});
