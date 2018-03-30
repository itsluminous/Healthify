var Clay = require('pebble-clay');
var clayConfig = require('./config');
var customClay = require('./custom-clay');
var userData = {token: 'abc123'};
var clay = new Clay(clayConfig, customClay, {userData: userData});

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function isNotEmpty(str) {
  return (/\S/.test(str));
}

function requestWeather(url){
  // Send request to OpenWeatherMap
  console.log('url : ' + url);
  xhrRequest(url, 'GET', 
    function(responseText) {
      var dictionary;
      try{
        // responseText contains a JSON object with weather info
        var json = JSON.parse(responseText);
        console.log('response : ' + responseText);
  
        // Temperature in Kelvin requires adjustment
        var temperature = Math.round(json.main.temp - 273.15);
  
        // Conditions
        var conditions = json.weather[0].main;      
        
        // Assemble dictionary using our keys
        dictionary = {
          'TEMPERATURE': temperature,
          'CONDITIONS': conditions
        }; 
      }
      catch(ex){
        dictionary = {
          'TEMPERATURE': 999,
          'CONDITIONS': 'location'
        };
      }
      // Send to Pebble
      Pebble.sendAppMessage(dictionary,
        function(e) {
          console.log('Weather info sent to Pebble successfully!');
          console.log('url : ' + url);
          console.log('response : ' + responseText);
        },
        function(e) {
          console.log('Error sending weather info to Pebble!');
        }
      );
    }      
  );
}

function locationSuccess(pos) {
  // Construct URL
  var url = 'http://api.openweathermap.org/data/2.5/weather?lat=' +
      pos.coords.latitude + '&lon=' + pos.coords.longitude + '&appid=993a0dee29cb3e497032ae692aeadbb4';
  requestWeather(url);  
}

function locationError(err) {
  console.log('Error requesting location!');
  //var dictionary = {
  //    'TEMPERATURE': 998,
  //    'CONDITIONS': 'error'
  //  };
  
  //Pebble.sendAppMessage(dictionary,
  //  function(e) {
  //    console.log('Error info sent to Pebble successfully!');
  // },
  //  function(e) {
  //    console.log('Error sending error info to Pebble!');
  //  }
  //);
}

function customLocationWeather(loc) {
  var url = 'http://api.openweathermap.org/data/2.5/weather?q=' + loc + '&appid=993a0dee29cb3e497032ae692aeadbb4';
  console.log(url);
  requestWeather(url);
}

function getWeather(useGPS, customLocation) {
  if(useGPS == '0' && isNotEmpty(customLocation)){
    customLocationWeather(customLocation);
  }
  else{
    navigator.geolocation.getCurrentPosition(
      locationSuccess,
      locationError,
      {timeout: 15000, maximumAge: 60000}
    );
  }  
}

Pebble.addEventListener('appmessage',function(e) {
    getWeather(e.payload["0"],e.payload["1"]);
});

//Pebble.addEventListener("webviewclosed", function(e){
//    if (e.response !== null && e.response !== ''){
//      try{
        //var options = JSON.parse(decodeURIComponent(encodeURIComponent(e.response)));  
//        var options = JSON.parse(e.response); 
//        localStorage.setItem("useGPS", options.WEATHER_USE_GPS.value);
//        localStorage.setItem("customLocation", options.WEATHER_LOC_NAME.value);
//      }
//      catch(ex){
//        localStorage.setItem("useGPS", "true");
//      }
//    }
//});

// Listen for when the watchface is opened
//Pebble.addEventListener('ready', 
  //function(e) {
    //getWeather();
  //}
//);