var i;
var dataln;
var fileslist = Array();
var linklist = Array();
var dataArray = [];
var olddataln = 0;

function processState(state) {
  //******************************
  //populating data model
  //******************************
  dataln = state.fileslist.length;
  fileslist = state.fileslist;
  //******************************
  //Creating links to files
  //******************************
  for (i = 0; i < dataln; i++) {
    linklist[i] =
      '<a href="' +
      fileslist[i][1] +
      '" target="_blank" download>' +
      fileslist[i][0] +
      "</a>";
  }
  //******************************
  //populating display
  //******************************
  if (dataln !== olddataln) {
    olddataln = dataln;
    var table = document.getElementById("tableContents");
    var tabledata = " ";
    for (i = 0; i < dataln; i++) {
      if (tabledata.length < 2) {
        tabledata =
          '<tr class="remove"><td><div class="custom-control custom-checkbox"><input type="checkbox" class="custom-control-input" id="' +
          fileslist[i][0] +
          '"><label class="custom-control-label" for="' +
          fileslist[i][0] +
          '"></label></div></td><td class="search">' +
          linklist[i] +
          "</td></tr>";
        dataArray.push('<tr class="remove"><td><div class="custom-control custom-checkbox"><input type="checkbox" class="custom-control-input" id="' +
          fileslist[i][0] +
          '"><label class="custom-control-label" for="' +
          fileslist[i][0] +
          '"></label></div></td><td class="search">' +
          linklist[i] +
          "</td></tr>");
      } else {
        tabledata =
          tabledata +
          '<tr class="remove"><td><div class="custom-control custom-checkbox"><input type="checkbox" class="custom-control-input" id="' +
          fileslist[i][0] +
          '"><label class="custom-control-label" for="' +
          fileslist[i][0] +
          '"></label></div></td><td class="search">' +
          linklist[i] +
          "</td></tr>";
        dataArray.push('<tr class="remove"><td><div class="custom-control custom-checkbox"><input type="checkbox" class="custom-control-input" id="' +
          fileslist[i][0] +
          '"><label class="custom-control-label" for="' +
          fileslist[i][0] +
          '"></label></div></td><td class="search">' +
          linklist[i] +
          "</td></tr>");

      }
    }
    table.innerHTML = tabledata;
    tableFilter(dataArray);
  }
}
//******************************
//Sends a delete command for selected file
//******************************
function sendDelete() {
  for (i = 0; i < dataln; i++) {
    var checkBox = document.getElementById(fileslist[i][0]);
    if (checkBox.checked == true) {
      var cmd = { delete: fileslist[i][0] };
      socket.send(JSON.stringify(cmd));
      //socket.send("{\"delete\":[\""+ fileslist[i][0]+"\"]}");
    }
  }
}
//******************************
//Select all files
//******************************
function selectall() {
  for (i = 0; i < dataln; i++) {
    document.getElementById(fileslist[i][0]).checked =
      !document.getElementById(fileslist[i][0]).checked;
  }
}

//******************************
//Periodically poll for new files
//******************************
time = setInterval(function (list) {
  socket.send('{"f-list":"fileslist"}');
  setTimeout(list, 500);
}, 500);

//******************************
//Open websocket
//******************************

var socket = new WebSocket("ws://" + window.location.hostname + ":9003");
socket.onmessage = function (event) {
  // console.log(event.data);
  var state = JSON.parse(event.data);
  processState(state);
};

//******************************
//Open websocket
//******************************
function Search() {
  var value = $(".searchbar").val();
  value = value.toLowerCase();
  var files = $(".search");
  var el = $(".remove");
  for (i = 0; i < files.length; i++) {
    if (!files[i].innerHTML.toLowerCase().includes(value)) {
      el[i].style.display = "none";
    } else {
      el[i].style.display = "table-row";
    }
  }
}

$(window).on("resize", function () {
  if ($(window).width() < 766) {
    $("#searchbarDiv").removeClass("ml-auto");
  } else { $("#searchbarDiv").addClass("ml-auto") }
});
if ($(window).width() < 766) {
  $("#searchbarDiv").removeClass("ml-auto");
} else { $("#searchbarDiv").addClass("ml-auto") }

//******************************
//Datatable filtering
//******************************

function tableFilter(dataArray) {
  var currentPage = 1;
  var rowsPerPage = parseInt($('#perPageSelect').val());
  var totalPages = Math.ceil(dataArray.length / rowsPerPage);

  function displayTable() {
    var startIndex = (currentPage - 1) * rowsPerPage;
    var endIndex = startIndex + rowsPerPage;
    var displayedRows = dataArray.slice(startIndex, endIndex);
    var temp;

    // Clear existing rows
    $('#tableContents').empty();

    // Add rows to the table
    $.each(displayedRows, function (index, row) {
      $('#tableContents').append(row);
    });

    // Update pagination
    updatePagination();
  }

  function updatePagination() {
    var prevBtn = $('#prevBtn');
    var nextBtn = $('#nextBtn');

    // Disable/enable previous and next buttons based on current page
    if (currentPage === 1) {
      prevBtn.addClass('disabled');
    } else {
      prevBtn.removeClass('disabled');
    }

    if (currentPage === totalPages) {
      nextBtn.addClass('disabled');
    } else {
      nextBtn.removeClass('disabled');
    }

    // Update page information
    var infoText = 'Showing ' + ((currentPage - 1) * rowsPerPage + 1) + ' to ' + Math.min(currentPage * rowsPerPage, dataArray.length) + ' of ' + dataArray.length + ' entries';
    $('#dataTable_info').text(infoText);
  }

  // Handle perPageSelect change event
  $('#perPageSelect').change(function () {
    rowsPerPage = parseInt($(this).val());
    totalPages = Math.ceil(dataArray.length / rowsPerPage);
    currentPage = 1;
    displayTable();
  });

  // Handle previous button click
  $('#prevBtn').click(function (e) {
    e.preventDefault();
    if (currentPage > 1) {
      currentPage--;
      displayTable();
    }
  });

  // Handle next button click
  $('#nextBtn').click(function (e) {
    e.preventDefault();
    if (currentPage < totalPages) {
      currentPage++;
      displayTable();
    }
  });

  // Initial table display
  displayTable();
};
