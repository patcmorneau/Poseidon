(function ($) {
    "use strict"; // Start of use strict

    // Toggle the side navigation
    $("#sidebarToggle, #sidebarToggleTop").on('click', function (e) {
        if ($(".sidebar").hasClass("toggled") && $(window).width() > 768) {
            $('#homeIcon').css("display", "block");
        } else if ($(window).width() < 768) {
            $('#homeIcon').css("display", "block")
        } else {
            $('#homeIcon').css("display", "none")
        };
    });
    if ($(window).width() < 768) {
        $('#homeIcon').css("display", "block");
    }
})(jQuery); // End of use strict
