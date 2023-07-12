var socket;

$(document).ready(function () {
    socket = new WebSocket("ws://" + window.location.hostname + ":9002");

    socket.onmessage = function (event) {
        //console.log(event.data);
        var msg = JSON.parse(event.data);

        if (msg.recordingInfo) {
            var isLogging = msg.recordingInfo.status;
            var mode = msg.loggingMode.the_mode_is;
            processRecordingInfo(isLogging, mode);
        }

    };

    socket.onopen = function (event) {
        //init display
        getLoggingInfo();
    };

    socket.onerror = function () {
        //display error div
        console.log("Error: Cannot connect to websocket")
    }
});

function getLoggingInfo() {
    var cmd = { command: "getLoggingInfo" };
    socket.send(JSON.stringify(cmd));
}

function processRecordingInfo(isLogging, mode) {
    //console.log(isLogging);
    //console.log(mode);
    if (mode == "1") {
        hideLoggingButton();
        $("#modeWidget").text("always ON"); text - success
    }
    else if (mode == "2") {
        $("#modeWidget").text("Manual");
        if (isLogging) {
            //console.log("logging mode 2 : manual , isLogging");
            showRecordingButton();
        }
        else {
            //console.log("logging mode 2 : manual , is not logging");
            showNotRecordingButton();
        }
    }
    else if (mode == "3") {
        hideLoggingButton();
        $("#modeWidget").text("speed based");
    }
}

function startRecording() {
    var cmd = { command: "startLogging" };
    socket.send(JSON.stringify(cmd));
}

function stopRecording() {
    var cmd = { command: "stopLogging" };
    socket.send(JSON.stringify(cmd));
}

function showRecordingButton() {
    $("#startRecIcon").removeClass("d-inline").addClass("d-none");
    $("#stopRecIcon").removeClass("d-none").addClass("d-inline");
}
function showNotRecordingButton() {
    $("#startRecIcon").removeClass("d-none").addClass("d-inline");
    $("#stopRecIcon").removeClass("d-inline").addClass("d-none");
}
function hideLoggingButton() {
    $("#startRecIcon").removeClass("d-inline").addClass("d-none");
    $("#stopRecIcon").removeClass("d-inline").addClass("d-none");
}