
// Get a random translated string an get the tguid of the first translation.
var sguid, tguid;
var url = base_url + '/public/btr/translations/translated?lng=sq'
http_request(url, { async: false })
    .done(function(result){
        sguid = result['string']['sguid'];
        tguid = result['string']['translations'][0]['tguid'];
    });

// Get an access  token.
var access_token = get_access_token(oauth2);

// POST btr/translations/vote
http_request(base_url + '/btr/translations/vote', {
    async: false,
    method: 'POST',
    data: { tguid: tguid },
    headers: { 'Authorization': 'Bearer ' + access_token }
});

// Retrive the string and check that the translation has been voted.
var url = base_url + '/public/btr/translations/' + sguid + '?lng=sq';
http_request(url, { async: false });

// POST btr/translations/del_vote
http_request(base_url + '/btr/translations/del_vote', {
    method: 'POST',
    data: { tguid: tguid },
    headers: { 'Authorization': 'Bearer ' + access_token }
});
