var socket;

var depthChart;
var depth = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

var attitudeChart;
var imu_x = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var imu_y = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var depth = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

var headingGauge;

$(document).ready(function () {

  //Chart.defaults.global.defaultFontFamily = 'Nunito', '-apple-system,system-ui,BlinkMacSystemFont,"Segoe UI",Roboto,"Helvetica Neue",Arial,sans-serif';
  //Chart.defaults.global.defaultFontColor = '#858796'

  var ctxAttitude = document.getElementById("attitudeChart").getContext('2d');
  attitudeChart = new Chart(ctxAttitude, {
    type: 'line',
    data: {
      labels: [, , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , ,],
      datasets: [{ label: "Pitch", data: imu_x, backgroundColor: ['rgba(105, 0, 132, 0)',], borderColor: ['rgba(200, 99, 132, .7)',], borderWidth: 2 },
      { label: "Roll", data: imu_y, backgroundColor: ['rgba(0, 137, 132, 0)',], borderColor: ['rgba(0, 10, 130, .7)',], borderWidth: 2 }]
    },
    options: { responsive: true, animation: false, elements: { point: { radius: 0 } } }
  });

  var ctxDepth = document.getElementById("depthChart").getContext('2d');
  depthChart = new Chart(ctxDepth,
    {
      type: 'line',
      data: {
        labels: [, , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , ,],
        datasets: [{ label: "Depth(m)", data: depth, backgroundColor: ['rgba(0, 137, 132, 0)',], borderColor: ['rgba(0, 10, 130, .7)',], borderWidth: 2 }]
      },
      options: { maintainAspectRatio: false, responsive: true, animation: false, elements: { point: { radius: 0 } } }
    });

  headingGauge = new RadialGauge({
    renderTo: 'imuz',
    minValue: 0,
    maxValue: 360,
    majorTicks: [
      "0",
      "45",
      "90",
      "135",
      "180",
      "225",
      "270",
      "315",
      "0"
    ],
    minorTicks: 22,
    ticksAngle: 360,
    startAngle: 180,
    strokeTicks: false,
    highlights: false,
    colorPlate: "#222",
    colorMajorTicks: "#f5f5f5",
    colorMinorTicks: "#ddd",
    colorNumbers: "#ccc",
    colorNeedle: "rgba(240, 128, 128, 1)",
    colorNeedleEnd: "rgba(255, 160, 122, .9)",
    valueBox: false,
    valueTextShadow: false,
    colorCircleInner: "#fff",
    colorNeedleCircleOuter: "#ccc",
    needleCircleSize: 10,
    needleCircleOuter: false,
    animationRule: "linear",
    needleType: "line",
    needleStart: 25,
    needleEnd: 99,
    needleWidth: 5,
    borders: true,
    borderInnerWidth: 0,
    borderMiddleWidth: 0,
    borderOuterWidth: 3,
    colorBorderOuter: "#ccc",
    colorBorderOuterEnd: "#ccc",
    colorNeedleShadowDown: "#222",
    borderShadowWidth: 0,
    animationDuration: 150,
    animateOnInit: true,
    animation: false
  }).draw();


  // Init websocket

  //display overlay...
  displayOverlay();

  socket = new WebSocket("ws://" + window.location.hostname + ":9002");

  socket.onmessage = function (event) {
    //console.log(event.data);
    var msg = JSON.parse(event.data);

    if (msg.telemetry) {
      processTelemetry(msg.telemetry);
    }
    else if (msg.recordingInfo) {
      var isLogging = msg.recordingInfo.status;
      var mode = msg.loggingMode.the_mode_is;
      processRecordingInfo(isLogging, mode);
    }

  };

  socket.onopen = function (event) {
    hideOverlay();
    //init display
    getLoggingInfo();
  };

  socket.onerror = function () {
    //display error div
    console.log("Error: Cannot connect to websocket")
    displayOverlay();
  }
});


function displayOverlay() {
  document.getElementById("overlay-text").innerHTML = "<p class='text-dark text-center'>Loading...</p><img src='/img/loading.gif'/>";//"<p class='text-light'>Loading...</p>"; //"<img href='/img/loading.gif'/>";
  document.getElementById("overlay").style.display = "block";
}

function hideOverlay() {
  document.getElementById("overlay").style.display = "none";
}

function processTelemetry(state) {

  // Update dashboard top marquees  

  if (!state.position.length || !state.attitude.length || !state.depth.length) {
    $("#systemStatus").removeClass("d-none").addClass("d-block");

    $("#systemStatusText").text("Check connexion with sensors and reload the page.");
  }
  else {
    $("#systemStatus").removeClass("d-block").addClass("d-none");
    $("#systemStatusText").text();
  }

  if (state.position.length) {
    $("#gnssStatus").removeClass("bg-gradient-warning").removeClass("bg-gradient-danger").addClass("bg-gradient-success");
    $("#gnssLongitudeValue").text(state.position[0].toFixed(8));
    $("#gnssLatitudeValue").text(state.position[1].toFixed(8));
    $("#gnssStatusText").text("");
  }
  else {
    $("#gnssStatus").removeClass("bg-gradient-warning").removeClass("bg-gradient-success").addClass("bg-gradient-danger");
    $("#gnssLongitudeValue").text("");
    $("#gnssLatitudeValue").text("");
    $("#gnssStatusText").text("No GNSS Data...");
  }

  if (state.attitude.length) {
    $("#imuStatus").removeClass("bg-gradient-warning").removeClass("bg-gradient-danger").addClass("bg-gradient-success");
    $("#imuHeadingValue").text(state.attitude[0].toFixed(3));
    $("#imuPitchValue").text(state.attitude[1].toFixed(3));
    $("#imuRollValue").text(state.attitude[2].toFixed(3));
    $("#imuStatusText").text("");
  }
  else {
    $("#imuStatus").removeClass("bg-gradient-warning").removeClass("bg-gradient-success").addClass("bg-gradient-danger");
    $("#imuHeadingValue").text("");
    $("#imuPitchValue").text("");
    $("#imuRollValue").text("");
    $("#imuStatusText").text("No IMU Data");
  }

  if (state.depth.length) {
    $("#sonarStatus").removeClass("bg-gradient-warning").removeClass("bg-gradient-danger").addClass("bg-gradient-success");
    $("#sonarDepthValue").text(state.depth[0].toFixed(2));
    $("#sonarStatusText").text("");
  }
  else {
    $("#sonarStatus").removeClass("bg-gradient-warning").removeClass("bg-gradient-success").addClass("bg-gradient-danger");
    $("#sonarDepthValue").text("");
    $("#sonarStatusText").text("No Sonar Data");
  }

  // Update attitude/depth plot

  imu_x.push(state.attitude[1]);
  imu_x.shift();

  imu_y.push(state.attitude[2]);
  imu_y.shift();

  //Display depth as negative Z 
  depth.push(-1 * state.depth[0]);
  depth.shift();

  attitudeChart.update();
  depthChart.update();

  headingGauge.value = (state.attitude[0]);

  if (state.vitals[3] < 1) {
    $("#hddFreeSpaceOK").removeClass("d-none").addClass("d-block alert alert-danger");
  }
  else {
    $("#hddFreeSpaceOK").removeClass("d-block alert alert-danger").addClass("d-none");
  }
}// End function processTelemetry

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
    if (isLogging) {
      //console.log("logging mode 1 : always ON");
      showRecording();
    }
    else {
      showNotRecording();
    }

  }
  else if (mode == "2") {
    $("#modeWidget").text("Manual");
    if (isLogging) {
      //console.log("logging mode 2 : manual , isLogging");
      showRecordingButton();
      showRecording();
    }
    else {
      //console.log("logging mode 2 : manual , is not logging");
      showNotRecording();
      showNotRecordingButton();
    }
  }
  else if (mode == "3") {
    hideLoggingButton();
    $("#modeWidget").text("speed based");
    if (isLogging) {
      //console.log("logging mode 3 : speed based , isLogging");
      showRecording();
    }
    else {
      //console.log("logging mode 3 : speed based , is not Logging");
      showNotRecording();
    }
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

function showRecording() {
  $("#recordingStatus").removeClass("d-none alert-danger").addClass("d-block alert-success");
  $("#recordingStatus").text("The system is currently recording data");
  $("#recordingStatus2").removeClass("d-none text-success").addClass("text-danger");
  $("#recordingStatus2").text("Active");
  // $("#modeWidget").removeClass("text-danger text-success").addClass("text-danger");
}

function showNotRecording() {
  $("#recordingStatus").removeClass("d-none alert-success").addClass("d-block alert-danger");
  $("#recordingStatus").text("The system is not recording data");
  $("#recordingStatus2").removeClass("d-none text-danger").addClass("text-success");
  $("#recordingStatus2").text("Inactive");
  // $("#modeWidget").removeClass("text-danger text-success").addClass("text-success");
}
function showRecordingButton() {
  $("#btnStartRecording").removeClass("d-inline").addClass("d-none");
  $("#btnStopRecording").removeClass("d-none").addClass("d-inline");
  $("#startRecIcon").removeClass("d-inline").addClass("d-none");
  $("#stopRecIcon").removeClass("d-none").addClass("d-inline");
}
function showNotRecordingButton() {
  $("#btnStartRecording").removeClass("d-none").addClass("d-inline");
  $("#btnStopRecording").removeClass("d-inline").addClass("d-none");
  $("#startRecIcon").removeClass("d-none").addClass("d-inline");
  $("#stopRecIcon").removeClass("d-inline").addClass("d-none");
}
function hideLoggingButton() {
  $("#btnStartRecording").removeClass("d-inline").addClass("d-none");
  $("#btnStopRecording").removeClass("d-inline").addClass("d-none");
  $("#startRecIcon").removeClass("d-inline").addClass("d-none");
  $("#stopRecIcon").removeClass("d-inline").addClass("d-none");
}