module.exports = function(minified) {
  var clayConfig = this;
  
  function toggleWeather(){
      if (this.get()) {
        clayConfig.getItemById('id_weather_unit').enable();
        clayConfig.getItemById('id_health_fix_layer').enable();
        clayConfig.getItemById('id_weather_refresh').enable();
        clayConfig.getItemById('id_weather_use_gps').enable();
        clayConfig.getItemById('id_weather_loc_name').enable();
    } else {
        clayConfig.getItemById('id_weather_unit').disable();
        clayConfig.getItemById('id_health_fix_layer').disable();
        clayConfig.getItemById('id_weather_refresh').disable();
        clayConfig.getItemById('id_weather_use_gps').disable();
        clayConfig.getItemById('id_weather_loc_name').disable();
    }  
  }

  function toggleInterval() {
    if (this.get()) {
      clayConfig.getItemById('id_health_refresh').show();
      clayConfig.getItemById('id_health_fix_layer').hide();
    } else {
      clayConfig.getItemById('id_health_refresh').hide();
      clayConfig.getItemById('id_health_fix_layer').show();
    }
  }  
  
  function toggleUseGPS() {
    if (this.get()) {
      clayConfig.getItemById('id_weather_loc_name').hide();
    } else {
      clayConfig.getItemById('id_weather_loc_name').show();
    }
  }  
  
  function redirectDonate() {    
    window.location = "https://www.paypal.me/prakashait/10";
  }  

  clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {
    var autoChangeLayer = clayConfig.getItemById('id_health_auto');
    toggleInterval.call(autoChangeLayer);
    autoChangeLayer.on('change', toggleInterval);
    
    var useGPS = clayConfig.getItemById('id_weather_use_gps');
    toggleUseGPS.call(useGPS);
    useGPS.on('change', toggleUseGPS);
    
    var useWeather = clayConfig.getItemById('id_weather_enable');
    toggleWeather.call(useWeather);
    useWeather.on('change', toggleWeather);
    
    var doDonate = clayConfig.getItemById('id_donate');
    doDonate.on('click', redirectDonate);
  });
};