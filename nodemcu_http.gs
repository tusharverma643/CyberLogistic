function doGet(e) { 
  Logger.log( JSON.stringify(e) );  // view parameters
  var result = 'Ok'; // assume success
  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  }
  else {
    var sheet_id = '1lKUmZzmz3LjPJbSZWLnKZTG3p5vznaVX-ad-pF-7Shs'; 		// Spreadsheet ID
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();		// get Active sheet
    var newRow = sheet.getLastRow() + 1;						
    var rowData = [];
    rowData[0] = new Date(); 							// Timestamp in column A
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'output1': //Parameter
          rowData[1] = value; //Value in column B
          result = 'Written on column B';
          break;
        case 'output2': //Parameter
          rowData[2] = value; //Value in column C
          result += ' ,Written on column C';
          break;  
        case 'output3': //Parameter
          rowData[3] = value; //Value in column D
          result += ' ,Written on column D';
          break;
        case 'output4': //Parameter
          rowData[4] = value; //Value in column E
          result += ' ,Written on column E';
          break;
        case 'output5': //Parameter
          rowData[5] = value; //Value in column F
          result += ' ,Written on column F';
          break;
        default:
          result = "unsupported parameter";
      }
    }
    Logger.log(JSON.stringify(rowData));
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }
  // Return result of operation
  return ContentService.createTextOutput(result);
}

function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}