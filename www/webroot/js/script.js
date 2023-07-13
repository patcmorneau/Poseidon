(function ($) {
    "use strict"; // Start of use strict

    // Toggle the side navigation (3 horizontal bars)
    $("#sidebarToggle, #sidebarToggleTop").on('click', function (e) {
        if ($(".sidebar").hasClass("toggled") && $(window).width() > 768) {
            $('#homeIcon').css("display", "block");
        } else if ($(window).width() < 768) {
            $('#homeIcon').css("display", "block");
        } else {
            $('#homeIcon').css("display", "none");
        };
    });

    $("#sidebarToggle, #sidebarToggleTop").on('click', function (e) {
        if ($("#navWrap").hasClass("toggled")) {
            $("#navWrap").removeClass("mr-4");
        } else {
            $("#navWrap").addClass("mr-4");
        };
    });

    if ($(window).width() < 768) {
        $('#homeIcon').css("display", "block");
    }
})(jQuery); // End of use strict
