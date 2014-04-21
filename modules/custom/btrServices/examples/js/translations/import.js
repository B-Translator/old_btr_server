// Get an access  token.
//var access_token = get_access_token(oauth2);

var fileSelector = $('<input type="file" />');

var files;
console.log($('input[type=file]'));
$('input[type=file]').on('change', function(event)
              {
                  console.log(event);
                  // Grab the files and set them to our variable
                  files = event.target.files;
                  //debug(files);
              });

fileSelector.click();
debug("test\n");
//debug(files);