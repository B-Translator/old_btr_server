
var origin = prompt('Enter the origin of the project:', 'test1');
var project = prompt('Enter the name of the project:');
var fileSelector = $('<input type="file" />');

fileSelector.on('change',
	function(event) {
	    var fd = new FormData();
	    fd.append('origin', origin);
	    fd.append('project', project);
	    fd.append('file', event.target.files[0]);

	    // Make an http request for uploading the file.
	    http_request(base_url +  '/btr/project/import', {
		method: 'POST',
		headers: {
		    'Authorization': 'Bearer ' + get_access_token(oauth2),
		},
		data: fd,
		processData: false,
		contentType: false,
	    });
        });

fileSelector.click();
