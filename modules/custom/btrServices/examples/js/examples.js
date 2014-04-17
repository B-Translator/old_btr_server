
$(document).ready(function() {

    $("#examples" ).accordion();

    // Load an example when it is clicked.
    $(".example").click(function(){
        var filename = this.id + '.js';
        $.get(filename, 'script')
            .done(function (file_content) {
                $("#code").text(file_content);
            });
    });
});