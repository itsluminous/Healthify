#include <pebble.h>
#include "Main.h"

static Layer *window_layer;
static Window *watchface_window;
static BitmapLayer *health_layer;
static Layer *step_layer;
static Layer *cal_layer;
static Layer *sleep_layer;
static GBitmap *health_image_black;
static GBitmap *health_image_white;
static TextLayer *date_layer;
static TextLayer *hour_minute_layer;
static TextLayer *ampm_layer;
static TextLayer *weather_layer;
static TextLayer *weather_status_layer;
static TextLayer *info_layer;
static Layer *batt_layer;
static TextLayer *part1_layer;
static TextLayer *part2_layer;
static TextLayer *part3_layer;
static TextLayer *health_info_layer;
static TextLayer *no_bluetooth_layer;
static int battery_level;
static bool bt_connected;

//User Configuration
AppSettings settings;
HealthSettings healthSettings;
WeatherSettings weatherSettings;

void set_text_color(GColor color1, GColor color2){
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : set_color");
  text_layer_set_text_color(hour_minute_layer, color1);
  text_layer_set_text_color(weather_layer, color1);
  text_layer_set_text_color(weather_status_layer, color1);
  text_layer_set_text_color(ampm_layer, color1);
  text_layer_set_text_color(date_layer, color1);
  text_layer_set_text_color(info_layer, color1);  
  text_layer_set_text_color(health_info_layer, color1);
  text_layer_set_text_color(no_bluetooth_layer, color1);  
  
  text_layer_set_text_color(part1_layer, color2);
  text_layer_set_text_color(part2_layer, color2);
  text_layer_set_text_color(part3_layer, color2);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : set_color");
}

void set_step_color(){
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : set_step_color"); 
  layer_set_hidden(step_layer, false);
  layer_set_hidden(cal_layer, true);
  layer_set_hidden(sleep_layer, true);
  if(settings.icon_step == 0){
    bitmap_layer_set_bitmap(health_layer, health_image_black); 
    set_text_color(settings.text_step,GColorBlack);
  }
  else{
    bitmap_layer_set_bitmap(health_layer, health_image_white); 
    set_text_color(settings.text_step,GColorWhite);
  }
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : set_step_color");
}

void set_cal_color(){
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : set_cal_color");
  layer_set_hidden(step_layer, true);
  layer_set_hidden(cal_layer, false);
  layer_set_hidden(sleep_layer, true);
  if(settings.icon_cal == 0){
    bitmap_layer_set_bitmap(health_layer, health_image_black); 
    set_text_color(settings.text_cal,GColorBlack);
  }
  else{
    bitmap_layer_set_bitmap(health_layer, health_image_white); 
    set_text_color(settings.text_cal,GColorWhite);
  }
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : set_cal_color");
}

void set_sleep_color(){
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : set_sleep_color");
  layer_set_hidden(step_layer, true);
  layer_set_hidden(cal_layer, true);
  layer_set_hidden(sleep_layer, false);
  if(settings.icon_sleep == 0){
    bitmap_layer_set_bitmap(health_layer, health_image_black); 
    set_text_color(settings.text_sleep,GColorBlack);
  }
  else{
    bitmap_layer_set_bitmap(health_layer, health_image_white); 
    set_text_color(settings.text_sleep,GColorWhite);
  }
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : set_sleep_color");
}

void update_all_colors(){
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : update_all_colors");
  switch(healthSettings.lastLayer) {
   case STEPS_LAYER:
      set_step_color();
      break;
   case CAL_LAYER:
      set_cal_color();
      break;
   default :
      set_sleep_color();
  }
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : update_all_colors");
}

void update_step_colors(Layer *layer, GContext *ctx){
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : update_step_colors");
    
  GPath *s_my_path_ptr;
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&LOWER_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&LOWER_PATH_INFO);
  #endif
  graphics_context_set_fill_color(ctx, settings.lower_step);
  gpath_draw_filled(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&STEP_UPPER_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&STEP_UPPER_INFO); 
  #endif
  graphics_context_set_fill_color(ctx, settings.upper_step);
  gpath_draw_filled(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&STEP_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&STEP_PATH_INFO); 
  #endif
  graphics_context_set_stroke_color(ctx, settings.sep_step);
  graphics_context_set_stroke_width(ctx, 3);
  gpath_draw_outline_open(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&SEP1_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&SEP1_PATH_INFO); 
  #endif
  graphics_context_set_stroke_color(ctx, settings.sep_step);
  graphics_context_set_stroke_width(ctx, 1);
  gpath_draw_outline_open(ctx, s_my_path_ptr); 
  gpath_destroy(s_my_path_ptr);
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&SEP2_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&SEP2_PATH_INFO); 
  #endif
  graphics_context_set_stroke_color(ctx, settings.sep_step);
  graphics_context_set_stroke_width(ctx, 1);
  gpath_draw_outline_open(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&BATTERY_OUTLINE_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&BATTERY_OUTLINE_INFO); 
  #endif
  graphics_context_set_stroke_color(ctx, settings.text_step);
  gpath_draw_outline(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&BT_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&BT_PATH_INFO); 
  #endif
  graphics_context_set_stroke_color(ctx, settings.text_step);
  gpath_draw_outline_open(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : update_step_colors");
}

void update_cal_colors(Layer *layer, GContext *ctx){
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : update_cal_colors");
  static GPath *s_my_path_ptr;
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&LOWER_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&LOWER_PATH_INFO);
  #endif
  graphics_context_set_fill_color(ctx, settings.lower_cal);
  gpath_draw_filled(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);  
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&CAL_UPPER_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&CAL_UPPER_INFO);
  #endif
  graphics_context_set_fill_color(ctx, settings.upper_cal);
  gpath_draw_filled(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);  
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&CAL_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&CAL_PATH_INFO);
  #endif
  graphics_context_set_stroke_color(ctx, settings.sep_cal);
  graphics_context_set_stroke_width(ctx, 3);
  gpath_draw_outline_open(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);  
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&SEP1_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&SEP1_PATH_INFO);
  #endif
  graphics_context_set_stroke_color(ctx, settings.sep_cal);
  graphics_context_set_stroke_width(ctx, 1);
  gpath_draw_outline_open(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);  
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&SEP2_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&SEP2_PATH_INFO);
  #endif
  graphics_context_set_stroke_color(ctx, settings.sep_cal);
  graphics_context_set_stroke_width(ctx, 1);
  gpath_draw_outline_open(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);  
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&BATTERY_OUTLINE_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&BATTERY_OUTLINE_INFO);
  #endif
  graphics_context_set_stroke_color(ctx, settings.text_cal);
  gpath_draw_outline(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);  
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&BT_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&BT_PATH_INFO);
  #endif
  graphics_context_set_stroke_color(ctx, settings.text_cal);
  gpath_draw_outline_open(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : update_cal_colors");
}

void update_sleep_colors(Layer *layer, GContext *ctx){
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : update_sleep_colors");
  static GPath *s_my_path_ptr;
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&LOWER_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&LOWER_PATH_INFO);
  #endif
  graphics_context_set_fill_color(ctx, settings.lower_sleep);
  gpath_draw_filled(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&SLEEP_UPPER_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&SLEEP_UPPER_INFO);
  #endif
  graphics_context_set_fill_color(ctx, settings.upper_sleep);
  gpath_draw_filled(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&SLEEP_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&SLEEP_PATH_INFO);
  #endif 
  graphics_context_set_stroke_color(ctx, settings.sep_sleep);
  graphics_context_set_stroke_width(ctx, 3);
  gpath_draw_outline_open(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&SEP1_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&SEP1_PATH_INFO);
  #endif
  graphics_context_set_stroke_color(ctx, settings.sep_sleep);
  graphics_context_set_stroke_width(ctx, 1);
  gpath_draw_outline_open(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&SEP2_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&SEP2_PATH_INFO);
  #endif
  graphics_context_set_stroke_color(ctx, settings.sep_sleep);
  graphics_context_set_stroke_width(ctx, 1);
  gpath_draw_outline_open(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&BATTERY_OUTLINE_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&BATTERY_OUTLINE_INFO);
  #endif
  graphics_context_set_stroke_color(ctx, settings.text_sleep);
  gpath_draw_outline(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  
  #if PBL_DISPLAY_HEIGHT == 228
    s_my_path_ptr = gpath_create(&BT_PATH_INFO_2);
  #else
    s_my_path_ptr = gpath_create(&BT_PATH_INFO);
  #endif  
  graphics_context_set_stroke_color(ctx, settings.text_sleep);
  gpath_draw_outline_open(ctx, s_my_path_ptr);
  gpath_destroy(s_my_path_ptr);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : update_sleep_colors");
}

void update_time() {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : update_time");
  time_t temp = time(NULL); 
  struct tm *current_time = localtime(&temp);

  static char hour_minute[6];
  if(strcmp(settings.time_format,"12") == 0){
    strftime(hour_minute, sizeof(hour_minute), "%I:%M", current_time);
    text_layer_set_text(hour_minute_layer, hour_minute+(('0' == hour_minute[0])?1:0));
    static char ampm[3];
    strftime(ampm, sizeof(ampm), "%p", current_time);
    static char hour_only[3];
    strftime(hour_only, sizeof(hour_only), "%I", current_time);
    #if PBL_DISPLAY_HEIGHT == 228
      text_layer_set_text(ampm_layer, ampm); 
    #else
        if(atoi(hour_only) > 9){
        ampm[1] = ampm[0];
        ampm[0] = ' ';
      }
      text_layer_set_text(ampm_layer, ampm); 
    #endif   
  } 
  else {
    strftime(hour_minute, sizeof(hour_minute), "%R", current_time);
    text_layer_set_text(hour_minute_layer, hour_minute+(('0' == hour_minute[0])?1:0));
    text_layer_set_text(ampm_layer, "");
  }

  static char time_day[6];
  if(settings.day_of_week == true)
    strftime(time_day, sizeof(time_day), "%a, ", current_time);
  else
    snprintf(time_day, sizeof(time_day), "%s", "");

  static char time_date[14];

  strftime(time_date, sizeof(time_date), settings.date_format, current_time);
  
  static char display_date[16];
  snprintf(display_date, sizeof(display_date), "%s%s", time_day,time_date);

  text_layer_set_text(date_layer, display_date);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : update_time");
}

void update_health_layers(bool updateBackground, bool calledOnLoad){
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : update_health_layers");
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "updateBackground %d",updateBackground==1);
	static char health_Info[20];
	static char stepDisplay[10]; 
	static char calDisplay[10];
	static char sleepDisplay[10];
  static char health_all_Info[30];
	
	const HealthMetric stepMetric = HealthMetricWalkedDistanceMeters;
	const HealthValue distance = health_service_sum_today(stepMetric);
	const HealthMetric stepMetric1 = HealthMetricStepCount;
	const HealthValue steps = health_service_sum_today(stepMetric1);
	
	const HealthMetric calMetric = HealthMetricActiveKCalories;
	const HealthValue calAct = health_service_sum_today(calMetric);
	const HealthMetric calMetric1 = HealthMetricRestingKCalories;
	const HealthValue calRest = health_service_sum_today(calMetric1);
	int totalCal = (int)calAct + (int)calRest;
	
	const HealthMetric sleepMetric = HealthMetricSleepSeconds;
	const HealthValue sleep = health_service_sum_today(sleepMetric);
	const HealthMetric sleepMetric1 = HealthMetricSleepRestfulSeconds;
	const HealthValue deepSleep = health_service_sum_today(sleepMetric1);
	int sleepHour = ((int)sleep)/3600;
	int sleepMin = ((int)sleep)/60 - sleepHour*60;
	
	snprintf(stepDisplay, sizeof(stepDisplay), "%d", (int)steps);
	snprintf(calDisplay, sizeof(calDisplay), "%d", totalCal); 
	snprintf(sleepDisplay, sizeof(sleepDisplay), "%dh%2d", sleepHour, sleepMin); 
  snprintf(health_all_Info, sizeof(health_all_Info), "%dst, %dcal, %dh%2d", (int)steps,totalCal,sleepHour, sleepMin);   
	
	if(calledOnLoad){
		updateBackground = true;
    if(!settings.health_auto){healthSettings.lastLayer = settings.health_fix_layer;}
  }
	
	if(updateBackground == true){
    if(!calledOnLoad){healthSettings.lastLayer = (healthSettings.lastLayer+1)%3;}
		layer_mark_dirty(batt_layer);
    update_all_colors();
  }
  
	//APP_LOG(APP_LOG_LEVEL_DEBUG , "Last Layer : %d", healthSettings.lastLayer);
	if(healthSettings.lastLayer == STEPS_LAYER)		//Steps
	{	   
		snprintf(stepDisplay, sizeof(stepDisplay), "%s", "");
	  if(strcmp(settings.dist_unit,"km") == 0)
		  snprintf(health_Info, sizeof(health_Info), "%d - %d.%02d km", (int)steps, (int)((int)distance/1000), ((int)((int)distance%1000)/10)); 
	  else
	    snprintf(health_Info, sizeof(health_Info), "%d - %d.%02d mi", (int)steps, (int)((int)distance/1613), (int)((int)distance%1613)); 
	}
	else if(healthSettings.lastLayer == CAL_LAYER)		//Calories
	{  
		snprintf(calDisplay, sizeof(stepDisplay), "%s", "");
		int activePercnt = (((int)calAct)*100) / totalCal;
		snprintf(health_Info, sizeof(health_Info), "%dCal - %d%%actv", totalCal,activePercnt); 
	}
	else			                 //Sleep
	{        
		snprintf(sleepDisplay, sizeof(stepDisplay), "%s", "");
		int deepPercnt = (((int)deepSleep) * 100) / (int)sleep;
		snprintf(health_Info, sizeof(health_Info), "%dh%2dm - %d%% deep", sleepHour, sleepMin, deepPercnt);
	} 
	text_layer_set_text(info_layer,health_Info);
	text_layer_set_text(part1_layer,stepDisplay);
	text_layer_set_text(part2_layer,calDisplay);
	text_layer_set_text(part3_layer,sleepDisplay);
  text_layer_set_text(health_info_layer,health_all_Info);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : update_health_layers");
}

bool isSleeping(){
	//APP_LOG(APP_LOG_LEVEL_INFO , "Method : isSleeping");
	HealthActivityMask activities = health_service_peek_current_activities();
	if(activities & HealthActivitySleep) {
		return true;
	} 
	else if(activities & HealthActivityRestfulSleep) {
		return true;
	}
  return false;
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : isSleeping");
}

void update_health(bool forced) {
	//APP_LOG(APP_LOG_LEVEL_INFO , "Method : update_health");
	int difference = difftime(time(NULL),healthSettings.health_last_updated);
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Health Difference %d",difference);
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Health current time %d",(int)time(NULL));
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Health saved time %d",(int)healthSettings.health_last_updated);
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Health update setting %d",settings.health_refresh);
  if(forced){
    update_health_layers(false,true);		
  }
	else if(settings.health_auto && difference >= settings.health_refresh*60 && !isSleeping()) {   
		healthSettings.health_last_updated = time(NULL); 
    update_health_layers(true,false);		   
	}
	else{	    
		update_health_layers(false,false);
	}  
	persist_write_data(HEALTH_SETTINGS_KEY, &healthSettings, sizeof(healthSettings));
	//APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : update_health");
}

void update_weather(bool forced) {  
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : update_weather");
  persist_read_data(WEATHER_SETTINGS_KEY, &weatherSettings, sizeof(weatherSettings));
  int difference = difftime(time(NULL),weatherSettings.temp_last_updated);
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "weather Difference %d",difference);
  if(settings.weather_enable && bt_connected){    
  	if(forced || (difference >= settings.weather_refresh*60)) {
      text_layer_set_text(weather_layer, "pebble");
      text_layer_set_text(weather_status_layer, " ");
  		DictionaryIterator *iter;
  		app_message_outbox_begin(&iter);	  
      if(settings.useLocation){
        dict_write_uint8 (iter, 0, 1);
      }
      else{
        dict_write_uint8 (iter, 0, 0);
      }
      
      dict_write_cstring (iter, 1, settings.customLocaton);
      dict_write_end (iter);
  		app_message_outbox_send();
    }
    else
    {
      static char temperature_buffer[8];
      static char conditions_buffer[32];
      int temp_reading;
      if(weatherSettings.temperature == 999){
        snprintf(temperature_buffer, sizeof(temperature_buffer), "%s", "invalid"); 
      }
      else if(weatherSettings.temperature == 998){
        //snprintf(temperature_buffer, sizeof(temperature_buffer), "%s", "gps"); 
        snprintf(temperature_buffer, sizeof(temperature_buffer), "%s", "pebble"); 
      }
      else{
        temp_reading = weatherSettings.temperature;
        if(strcmp(settings.temp_unit,"fa") == 0){
          temp_reading = (int)(((temp_reading)*1.8)+32);
          snprintf(temperature_buffer, sizeof(temperature_buffer), " %d°f", temp_reading);      
        }
        else{
          snprintf(temperature_buffer, sizeof(temperature_buffer), " %d°c", temp_reading);
        }   
      }  
      
      snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", weatherSettings.conditions);
      text_layer_set_text(weather_layer, temperature_buffer);
      text_layer_set_text(weather_status_layer, conditions_buffer);
    }
  }
  else{
    static char temperature_buffer[8];
    static char conditions_buffer[2];
    snprintf(temperature_buffer, sizeof(temperature_buffer), "%s", "pebble"); 
    snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", "");
    text_layer_set_text(weather_layer, temperature_buffer);
    text_layer_set_text(weather_status_layer, conditions_buffer);
  }
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : update_weather");
}

void update_battery_layer(Layer *layer, GContext *ctx){
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : update_battery_layer");
  //APP_LOG(APP_LOG_LEVEL_DEBUG , "Last Layer : %d", healthSettings.lastLayer);
  GRect bounds = layer_get_bounds(layer);

  // Find the width of the bar
  #if PBL_DISPLAY_HEIGHT == 228
    int width = (int)(float)(((float)battery_level / 100.0F) * 23.0F); 
  #else
    int width = (int)(float)(((float)battery_level / 100.0F) * 16.0F); 
  #endif  
  switch(healthSettings.lastLayer) {
   case STEPS_LAYER:
      graphics_context_set_fill_color(ctx, settings.text_step);
      break;
   case CAL_LAYER:
      graphics_context_set_fill_color(ctx, settings.text_cal);
      break;
   default :
      graphics_context_set_fill_color(ctx, settings.text_sleep);
  }
  graphics_fill_rect(ctx, GRect(0, 0, width, bounds.size.h), 0, GCornerNone);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : update_battery_layer");
}

void tick_handler(struct tm *current_time, TimeUnits units_changed) {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : tick_handler");
  update_time();
  update_health(false);
  update_weather(false);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : tick_handler");
}

void battery_handler(BatteryChargeState charge_state) {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : battery_handler");
  battery_level = charge_state.charge_percent;
  layer_mark_dirty(batt_layer);  
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : battery_handler");
}

void bt_handler(bool connected) {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : bt_handler");
  layer_set_hidden(text_layer_get_layer(no_bluetooth_layer), connected);
  if(!connected) {
    bt_connected = false;
    if(settings.bt_vibr_disconn)
      vibes_double_pulse();
  }
  else{
    bt_connected = true;
    if(settings.bt_vibr_reconn)
      vibes_double_pulse();
    update_weather(false);
  }
  
  
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : bt_handler");
}

static void health_handler(HealthEventType event, void *context) {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : health_handler");
  switch(event) {
    case HealthEventSignificantUpdate:
		  update_health_layers(false,false);
		  break;  
    case HealthEventMovementUpdate:
		  update_health_layers(false,false);
		  break;    
    default:
		break;
  }  
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : health_handler");
}

void accel_tap_handler(AccelAxisType axis, int32_t direction) {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : accel_tap_handler");
  if(!isSleeping()){
    update_health_layers(true,false);
    healthSettings.health_last_updated = time(NULL);
    persist_write_data(HEALTH_SETTINGS_KEY, &healthSettings, sizeof(healthSettings));
  }  
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : accel_tap_handler");
}

void update_weather_layers(DictionaryIterator *iterator, void *context) {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : update_weather_layers");
  static char temperature_buffer[8];
  static char conditions_buffer[32];
  
  prv_load_settings();
  
  Tuple *temp_tuple = dict_find(iterator, MESSAGE_KEY_TEMPERATURE);
  Tuple *conditions_tuple = dict_find(iterator, MESSAGE_KEY_CONDITIONS);
  if(temp_tuple && conditions_tuple) {
    static int temp_reading;
    if(((int)temp_tuple->value->int32) == 999){
      snprintf(temperature_buffer, sizeof(temperature_buffer), "invalid"); 
    }
    else if(((int)temp_tuple->value->int32) == 998){
      snprintf(temperature_buffer, sizeof(temperature_buffer), "gps"); 
    }
    else{
      if(strcmp(settings.temp_unit,"fa") == 0){
        temp_reading = (int)((((int)temp_tuple->value->int32)*1.8)+32); 
        snprintf(temperature_buffer, sizeof(temperature_buffer), " %d°f", temp_reading);      
      }
      else{
        temp_reading = (int)temp_tuple->value->int32;
        snprintf(temperature_buffer, sizeof(temperature_buffer), " %d°c", temp_reading);
      }
      weatherSettings.temp_last_updated = time(NULL);
    }       
    snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", conditions_tuple->value->cstring);
    text_layer_set_text(weather_layer, temperature_buffer);
    text_layer_set_text(weather_status_layer, conditions_buffer);
    weatherSettings.temperature = temp_tuple->value->int32;
    strcpy(weatherSettings.conditions,conditions_tuple->value->cstring);    
    persist_write_data(WEATHER_SETTINGS_KEY, &weatherSettings, sizeof(weatherSettings));
  }
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : update_weather_layers");
}

void main_window_load(Window *window) {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : main_window_load");
  window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  GRect unobs_bounds = layer_get_unobstructed_bounds(window_layer);  
  
  step_layer = layer_create(bounds);
  layer_set_update_proc(step_layer, update_step_colors);
  layer_add_child(window_layer, step_layer);
  layer_mark_dirty(step_layer);
  
  cal_layer = layer_create(bounds);
  layer_set_update_proc(cal_layer, update_cal_colors);
  layer_add_child(window_layer, cal_layer);
  layer_mark_dirty(cal_layer);
  
  sleep_layer = layer_create(bounds);
  layer_set_update_proc(sleep_layer, update_sleep_colors);
  layer_add_child(window_layer, sleep_layer);
  layer_mark_dirty(sleep_layer);
  
  health_image_black = gbitmap_create_with_resource(RESOURCE_ID_HEALTH_BLACK);
  health_image_white = gbitmap_create_with_resource(RESOURCE_ID_HEALTH_WHITE);
  #if PBL_DISPLAY_HEIGHT == 228
    health_layer = bitmap_layer_create(GRect(2, 187, bounds.size.w, 39));
  #else
    health_layer = bitmap_layer_create(GRect(2, 133, bounds.size.w, 39));
  #endif    
  layer_add_child(window_layer, bitmap_layer_get_layer(health_layer));
  bitmap_layer_set_compositing_mode(health_layer, GCompOpSet);

  #if PBL_DISPLAY_HEIGHT == 228
    hour_minute_layer = text_layer_create(GRect(0, 62, bounds.size.w, 63));
    text_layer_set_font(hour_minute_layer, fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49));
  #else
    hour_minute_layer = text_layer_create(GRect(0, 46, bounds.size.w, 63));
    text_layer_set_font(hour_minute_layer, fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS));
  #endif    
  text_layer_set_background_color(hour_minute_layer, GColorClear);  
  text_layer_set_text_alignment(hour_minute_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(hour_minute_layer));
  
  #if PBL_DISPLAY_HEIGHT == 228
    ampm_layer = text_layer_create(GRect((bounds.size.w - 25), 85, 25, 63));   
    text_layer_set_font(ampm_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  #else
    ampm_layer = text_layer_create(GRect((bounds.size.w - 22), 69, 25, 63));
    text_layer_set_font(ampm_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  #endif   
  text_layer_set_background_color(ampm_layer, GColorClear);    
  text_layer_set_text_alignment(ampm_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(ampm_layer));

  #if PBL_DISPLAY_HEIGHT == 228
    weather_layer = text_layer_create(GRect(0, 0, bounds.size.w, 63));  
    text_layer_set_font(weather_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  #else
    weather_layer = text_layer_create(GRect(0, 0, bounds.size.w, 63));
    text_layer_set_font(weather_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  #endif     
  text_layer_set_background_color(weather_layer, GColorClear);  
  text_layer_set_text_alignment(weather_layer, GTextAlignmentCenter);
  text_layer_set_text(weather_layer,"pebble");
  layer_add_child(window_layer, text_layer_get_layer(weather_layer));
  
  #if PBL_DISPLAY_HEIGHT == 228
    weather_status_layer = text_layer_create(GRect(0, 20, bounds.size.w, 63));
    text_layer_set_font(weather_status_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  #else
    weather_status_layer = text_layer_create(GRect(0, 17, bounds.size.w, 63));
    text_layer_set_font(weather_status_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  #endif   
  text_layer_set_background_color(weather_status_layer, GColorClear);  
  text_layer_set_text_alignment(weather_status_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(weather_status_layer));
  
  #if PBL_DISPLAY_HEIGHT == 228
    date_layer = text_layer_create(GRect(0, 45, bounds.size.w, 25));
    text_layer_set_font(date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  #else
    date_layer = text_layer_create(GRect(0, 35, bounds.size.w, 25));
    text_layer_set_font(date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  #endif   
  text_layer_set_background_color(date_layer, GColorClear);  
  text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(date_layer));
  
  #if PBL_DISPLAY_HEIGHT == 228
    batt_layer = layer_create(GRect(171, 9, 22, 9));
  #else
    batt_layer = layer_create(GRect(124, 7, 15, 6));
  #endif  
  layer_set_update_proc(batt_layer, update_battery_layer);
  layer_add_child(window_layer, batt_layer);        
  
  no_bluetooth_layer = text_layer_create(GRect(13, 0, 14, 20));
  text_layer_set_background_color(no_bluetooth_layer, GColorClear);
  text_layer_set_font(no_bluetooth_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text_alignment(ampm_layer, GTextAlignmentLeft);
  text_layer_set_text(no_bluetooth_layer,"X");
  layer_add_child(window_layer, text_layer_get_layer(no_bluetooth_layer));
  
  if(connection_service_peek_pebble_app_connection()){
    layer_set_hidden(text_layer_get_layer(no_bluetooth_layer), true);
    bt_connected = true;
  }
  else{
    bt_connected = false;
  }
    
  #if PBL_DISPLAY_HEIGHT == 228
    info_layer = text_layer_create(GRect(0, 132, bounds.size.w, 63));
    text_layer_set_font(info_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  #else
    info_layer = text_layer_create(GRect(0, 96, bounds.size.w, 63));
    text_layer_set_font(info_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  #endif    
  text_layer_set_background_color(info_layer, GColorClear);  
  text_layer_set_text_alignment(info_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(info_layer));
  
  #if PBL_DISPLAY_HEIGHT == 228
    health_info_layer = text_layer_create(GRect(0, 134, bounds.size.w, 63));
    text_layer_set_font(health_info_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  #else
    health_info_layer = text_layer_create(GRect(0, 98, bounds.size.w, 63));
    text_layer_set_font(health_info_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  #endif    
  text_layer_set_background_color(health_info_layer, GColorClear);  
  text_layer_set_text_alignment(health_info_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(health_info_layer)); 
  
  if (grect_equal(&unobs_bounds, &bounds)) {
    layer_set_hidden(text_layer_get_layer(health_info_layer), true);
    layer_set_hidden(text_layer_get_layer(info_layer), false);
  }
  else{
    layer_set_hidden(text_layer_get_layer(health_info_layer), false);
    layer_set_hidden(text_layer_get_layer(info_layer), true);
  } 
  
  #if PBL_DISPLAY_HEIGHT == 228
    part1_layer = text_layer_create(GRect(0, 169, 69, 63));
    text_layer_set_font(part1_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  #else
    part1_layer = text_layer_create(GRect(0, 120, 50, 63));
    text_layer_set_font(part1_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  #endif    
  text_layer_set_background_color(part1_layer, GColorClear);  
  text_layer_set_text_alignment(part1_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(part1_layer));
  
  #if PBL_DISPLAY_HEIGHT == 228
    part2_layer = text_layer_create(GRect(67, 169, 69, 63));
    text_layer_set_font(part2_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  #else
    part2_layer = text_layer_create(GRect(48, 120, 50, 63));
    text_layer_set_font(part2_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  #endif   
  text_layer_set_background_color(part2_layer, GColorClear);  
  text_layer_set_text_alignment(part2_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(part2_layer));
  
  #if PBL_DISPLAY_HEIGHT == 228
    part3_layer = text_layer_create(GRect(133, 169, 69, 63));
    text_layer_set_font(part3_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  #else
    part3_layer = text_layer_create(GRect(96, 120, 52, 63));
    text_layer_set_font(part3_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  #endif     
  text_layer_set_background_color(part3_layer, GColorClear);  
  text_layer_set_text_alignment(part3_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(part3_layer));
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : main_window_load");
}

void main_window_unload(Window *window) {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : main_window_unload");
  //layer_destroy(window_layer);
  bitmap_layer_destroy(health_layer);
  layer_destroy(step_layer);
  layer_destroy(cal_layer);
  layer_destroy(sleep_layer);
  gbitmap_destroy(health_image_black);
  gbitmap_destroy(health_image_white);
  text_layer_destroy(date_layer);  
  text_layer_destroy(hour_minute_layer);
  text_layer_destroy(ampm_layer);
  text_layer_destroy(weather_layer);
  text_layer_destroy(weather_status_layer); 
  text_layer_destroy(info_layer);
  layer_destroy(batt_layer);
  text_layer_destroy(part1_layer);
  text_layer_destroy(part2_layer);
  text_layer_destroy(part3_layer);
  text_layer_destroy(health_info_layer);
  text_layer_destroy(no_bluetooth_layer);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : main_window_unload");
}

void prv_default_settings() {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : prv_default_settings");
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Inside default");
  strcpy(settings.time_format,"24");
  settings.day_of_week = true;
  strcpy(settings.date_format,"%d-%b-%y");
  strcpy(settings.temp_unit, "ce");
  settings.weather_enable = true;
  settings.weather_refresh = 60;
  //settings.useLocation = true;
  //settings.customLocaton = " ";
  settings.bt_vibr_disconn = true;
  settings.bt_vibr_reconn = true;
  strcpy(settings.dist_unit,"km");
  settings.health_auto = true;
  settings.health_refresh = 10;
  settings.health_fix_layer = STEPS_LAYER;
  settings.health_shake = false;
  settings.night_mode = false;
  settings.night_start = 22;
  settings.night_end = 7;
  settings.health_realtime = false;
  
  #if defined(PBL_COLOR)
    settings.upper_step = GColorCobaltBlue;
    settings.lower_step = GColorDarkGray;
    settings.icon_step = 1;
    settings.text_step = GColorWhite;
    settings.sep_step = GColorWhite;
    settings.upper_cal = GColorChromeYellow;
    settings.lower_cal = GColorWhite;
    settings.icon_cal = 0;
    settings.text_cal = GColorBlack;
    settings.sep_cal = GColorOrange;
    settings.upper_sleep = GColorWhite;
    settings.lower_sleep = GColorVividCerulean;
    settings.icon_sleep = 0;
    settings.text_sleep = GColorBlack;
    settings.sep_sleep = GColorDarkGray;
  #elif defined(PBL_BW)
    settings.upper_step = GColorWhite;
    settings.lower_step = GColorDarkGray;
    settings.icon_step = 0;
    settings.text_step = GColorBlack;
    settings.sep_step = GColorLightGray;
  
    settings.upper_cal = GColorLightGray;
    settings.lower_cal = GColorBlack;
    settings.icon_cal = 1;
    settings.text_cal = GColorBlack;
    settings.sep_cal = GColorWhite;
  
    settings.upper_sleep = GColorWhite;
    settings.lower_sleep = GColorLightGray;
    settings.icon_sleep = 1;
    settings.text_sleep = GColorDarkGray;
    settings.sep_sleep = GColorBlack;
  #endif
  
  
  //health
  healthSettings.lastLayer = 0;
  healthSettings.health_last_updated = time(NULL);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : prv_default_settings");
}

void prv_load_settings() {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : prv_load_settings");
  prv_default_settings();
  persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
  persist_read_data(HEALTH_SETTINGS_KEY, &healthSettings, sizeof(healthSettings));
  //APP_LOG(APP_LOG_LEVEL_DEBUG , "Last Layer from cache : %d",healthSettings.lastLayer);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : prv_load_settings");
}

void prv_save_settings() {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : prv_save_settings");
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
  // Update the display based on new settings
  update_time();
  if(!settings.health_auto){
    healthSettings.lastLayer = settings.health_fix_layer;
  }
  layer_mark_dirty(step_layer);
  layer_mark_dirty(cal_layer);
  layer_mark_dirty(sleep_layer);
  
  healthSettings.health_last_updated = (time(NULL) - 99999);
  update_health(true);
  update_weather(false);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : prv_save_settings");
}

void prv_inbox_received_handler(DictionaryIterator *iter, void *context) {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : prv_inbox_received_handler");
  Tuple *test_t = dict_find(iter, MESSAGE_KEY_TEMPERATURE);
  if(test_t) {
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "inside temp inbox");
	  update_weather_layers(iter, context);
  }
  else{
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "inside pref inbox");
	  Tuple *time_format_t = dict_find(iter, MESSAGE_KEY_DATE_TIME_FORMAT);
	  if(time_format_t) {
		strcpy(settings.time_format,time_format_t->value->cstring);
	  }
	  
	  Tuple *day_of_week_t = dict_find(iter, MESSAGE_KEY_DAY_OF_WEEK);
	  if(day_of_week_t) {
		settings.day_of_week = day_of_week_t->value->int32 == 1;
	  }
	  
	  Tuple *date_format_t = dict_find(iter, MESSAGE_KEY_DATE_TIME_FORMAT+ 1);
	  if(date_format_t) {
		  strcpy(settings.date_format,date_format_t->value->cstring);
	  }
	  
	  Tuple *temp_unit_t = dict_find(iter, MESSAGE_KEY_DIST_TEMP_UNIT);
	  if(temp_unit_t) {
      strcpy(settings.temp_unit, temp_unit_t->value->cstring);
	  }
    
    Tuple *weather_enable_t = dict_find(iter, MESSAGE_KEY_WEATHER_ENABLE);
	  if(weather_enable_t) {      
		  settings.weather_enable = weather_enable_t->value->int32 == 1;
	  }
	  
	  Tuple *weather_refresh_t = dict_find(iter, MESSAGE_KEY_WEATHER_REFRESH);
	  if(weather_refresh_t) {
		  settings.weather_refresh = weather_refresh_t->value->int32;
	  }
    
    Tuple *useLocation_t = dict_find(iter, MESSAGE_KEY_WEATHER_USE_GPS);
	  if(useLocation_t) {
      if(settings.useLocation != (useLocation_t->value->int32 == 1)){
        weatherSettings.temp_last_updated = (time(NULL) - 99999);
      }
		  settings.useLocation = useLocation_t->value->int32 == 1;
	  }
    
    Tuple *customLocatonn_t = dict_find(iter, MESSAGE_KEY_WEATHER_LOC_NAME);
	  if(customLocatonn_t) {
      if(strcmp(settings.customLocaton,customLocatonn_t->value->cstring) != 0){
        weatherSettings.temp_last_updated = (time(NULL) - 99999);
      }
      strcpy(settings.customLocaton, customLocatonn_t->value->cstring);
	  }
    
    persist_write_data(WEATHER_SETTINGS_KEY, &weatherSettings, sizeof(weatherSettings));
	  
	  Tuple *bt_vibr_disconn_t = dict_find(iter, MESSAGE_KEY_BT_VIBR);
	  if(bt_vibr_disconn_t) {
		  settings.bt_vibr_disconn = bt_vibr_disconn_t->value->int32 == 1;
	  }

	  Tuple *bt_vibr_reconn_t = dict_find(iter, MESSAGE_KEY_BT_VIBR + 1);
	  if(bt_vibr_reconn_t) {
		  settings.bt_vibr_reconn = bt_vibr_reconn_t->value->int32 == 1;
	  }
	  
	  Tuple *dist_unit_t = dict_find(iter, MESSAGE_KEY_DIST_TEMP_UNIT + 1);
	  if(dist_unit_t) {
		  strcpy(settings.dist_unit,dist_unit_t->value->cstring);
	  }
    
    Tuple *health_auto_t = dict_find(iter, MESSAGE_KEY_HEALTH_AUTO);
	  if(health_auto_t) {
		  settings.health_auto = health_auto_t->value->int32 == 1;
	  }
    
    Tuple *health_refresh_t = dict_find(iter, MESSAGE_KEY_HEALTH_REFRESH);
	  if(health_refresh_t) {
		  settings.health_refresh = health_refresh_t->value->int32;
	  }
    
    Tuple *health_fix_layer_t = dict_find(iter, MESSAGE_KEY_HEALTH_FIX_LAYER);
	  if(health_fix_layer_t) {
		  settings.health_fix_layer = atoi(health_fix_layer_t->value->cstring);
	  }
    
    Tuple *health_shake_t = dict_find(iter, MESSAGE_KEY_HEALTH_SHAKE);
	  if(health_shake_t) {
		  settings.health_shake = health_shake_t->value->int32 == 1;
	  }  
    
    Tuple *health_realtime_t = dict_find(iter, MESSAGE_KEY_HEALTH_REALTIME);
	  if(health_realtime_t) {
		  settings.health_realtime = health_realtime_t->value->int32 == 1;
	  }
    
    Tuple *upper_step_t = dict_find(iter, MESSAGE_KEY_UPPER_COLOR);
	  if(upper_step_t) {
		  settings.upper_step = GColorFromHEX(upper_step_t->value->int32);
	  } 
    
    Tuple *lower_step_t = dict_find(iter, MESSAGE_KEY_LOWER_COLOR);
	  if(lower_step_t) {
		  settings.lower_step = GColorFromHEX(lower_step_t->value->int32);
	  }
    
    Tuple *icon_step_t = dict_find(iter, MESSAGE_KEY_ICON_COLOR);
	  if(icon_step_t) {
		  settings.icon_step = atoi(icon_step_t->value->cstring);
	  }
    
    Tuple *text_step_t = dict_find(iter, MESSAGE_KEY_TEXT_COLOR);
	  if(text_step_t) {
		  settings.text_step = GColorFromHEX(text_step_t->value->int32);
	  }
    
    Tuple *sep_step_t = dict_find(iter, MESSAGE_KEY_SEP_COLOR);
	  if(sep_step_t) {
		  settings.sep_step = GColorFromHEX(sep_step_t->value->int32);
	  }
    
    Tuple *upper_cal_t = dict_find(iter, MESSAGE_KEY_UPPER_COLOR + 1);
	  if(upper_cal_t) {
		  settings.upper_cal = GColorFromHEX(upper_cal_t->value->int32);
	  } 
    
    Tuple *lower_cal_t = dict_find(iter, MESSAGE_KEY_LOWER_COLOR + 1);
	  if(lower_cal_t) {
		  settings.lower_cal = GColorFromHEX(lower_cal_t->value->int32);
	  }
    
    Tuple *icon_cal_t = dict_find(iter, MESSAGE_KEY_ICON_COLOR + 1);
	  if(icon_cal_t) {
		  settings.icon_cal = atoi(icon_cal_t->value->cstring);
	  }
    
    Tuple *text_cal_t = dict_find(iter, MESSAGE_KEY_TEXT_COLOR + 1);
	  if(text_cal_t) {
		  settings.text_cal = GColorFromHEX(text_cal_t->value->int32);
	  }
    
    Tuple *sep_cal_t = dict_find(iter, MESSAGE_KEY_SEP_COLOR + 1);
	  if(sep_cal_t) {
		  settings.sep_cal = GColorFromHEX(sep_cal_t->value->int32);
	  }
    
    Tuple *upper_sleep_t = dict_find(iter, MESSAGE_KEY_UPPER_COLOR + 2);
	  if(upper_sleep_t) {
		  settings.upper_sleep = GColorFromHEX(upper_sleep_t->value->int32);
	  } 
    
    Tuple *lower_sleep_t = dict_find(iter, MESSAGE_KEY_LOWER_COLOR + 2);
	  if(lower_sleep_t) {
		  settings.lower_sleep = GColorFromHEX(lower_sleep_t->value->int32);
	  }
    
    Tuple *icon_sleep_t = dict_find(iter, MESSAGE_KEY_ICON_COLOR + 2);
	  if(icon_sleep_t) {
		  settings.icon_sleep = atoi(icon_sleep_t->value->cstring);
	  }
    
    Tuple *text_sleep_t = dict_find(iter, MESSAGE_KEY_TEXT_COLOR + 2);
	  if(text_sleep_t) {
		  settings.text_sleep = GColorFromHEX(text_sleep_t->value->int32);
	  }
    
    Tuple *sep_sleep_t = dict_find(iter, MESSAGE_KEY_SEP_COLOR + 2);
	  if(sep_sleep_t) {
		  settings.sep_sleep = GColorFromHEX(sep_sleep_t->value->int32);
	  }
	  
    if(settings.health_shake)
      accel_tap_service_subscribe(accel_tap_handler);  // Subscribe to tap events
    else
      accel_tap_service_unsubscribe();
    
	  prv_save_settings();
  }
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : prv_inbox_received_handler");
}

static void prv_inbox_dropped_callback(AppMessageResult reason, void *context) {
  // A message was received, but had to be dropped
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped. Reason: %d", (int)reason);
}

void prv_unobstructed_did_change(void *context) {
  GRect full_bounds = layer_get_bounds(window_layer);
  GRect bounds = layer_get_unobstructed_bounds(window_layer);
  if (grect_equal(&full_bounds, &bounds)) {
    layer_set_hidden(text_layer_get_layer(health_info_layer), true);
    layer_set_hidden(text_layer_get_layer(info_layer), false);
  }
  else{
    layer_set_hidden(text_layer_get_layer(health_info_layer), false);
    layer_set_hidden(text_layer_get_layer(info_layer), true);
  }  
}

void prv_init(void) {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : prv_init");
  prv_load_settings();
  app_message_register_inbox_received(prv_inbox_received_handler);
  app_message_open(512, 512);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : prv_init");
}

void init() {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : init");
  watchface_window = window_create();

  window_set_window_handlers(watchface_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  app_message_register_inbox_dropped(prv_inbox_dropped_callback);
  window_stack_push(watchface_window, true);
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  battery_state_service_subscribe(battery_handler);  
  bluetooth_connection_service_subscribe(bt_handler);
  
  UnobstructedAreaHandlers handlers = {
    .did_change = prv_unobstructed_did_change
  };
  unobstructed_area_service_subscribe(handlers, NULL);
  
  if(settings.health_shake)
    accel_tap_service_subscribe(accel_tap_handler);  // Subscribe to tap events
  else
    accel_tap_service_unsubscribe(); 
  
  if(settings.health_realtime)
    health_service_events_subscribe(health_handler, NULL);  // Subscribe to health events
  else
    health_service_events_unsubscribe(); 
  
  update_time();
  update_health_layers(false,true);
  battery_handler(battery_state_service_peek());
  update_weather(false); 
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : init");
}

void deinit() {
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : deinit");
  window_destroy(watchface_window);
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : deinit");
}

int main(void) {  
  //APP_LOG(APP_LOG_LEVEL_INFO , "Method : main");
  prv_init();
  init();  
  app_event_loop();
  deinit();
  //APP_LOG(APP_LOG_LEVEL_WARNING , "Exit : main");
}