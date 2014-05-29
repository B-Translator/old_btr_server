
/**
 * Base URL of the server that offers the services.
 */
var base_url = 'https://dev.btranslator.org';

/**
 * Settings for getting an OAuth2 access_token with
 * the user credentials flow ('password' grant_type).
 */
var oauth2 = {
    token_url: base_url + '/oauth2/token',
    client_id: 'emberjs',
    client_secret: '123456',
    username: 'user1',
    password: 'pass1',
    scope: 'user_profile',
};
