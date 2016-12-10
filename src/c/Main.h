#pragma once
#include <pebble.h>

#define SETTINGS_KEY 1
#define HEALTH_SETTINGS_KEY 2
#define WEATHER_SETTINGS_KEY 3

#define STEPS_LAYER 0
#define CAL_LAYER 1
#define SLEEP_LAYER 2

// A structure containing our settings
typedef struct AppSettings {
  char time_format[4];
  bool day_of_week;
  char date_format[10];
  char temp_unit[4];
  int weather_refresh;
  bool bt_vibr_disconn;
  bool bt_vibr_reconn;
  char dist_unit[4];
  bool health_auto;  
  int health_refresh;
  int health_fix_layer;
  bool health_shake;
  bool health_realtime;
  bool night_mode;
  int night_start;
  int night_end;
  //weather
  bool weather_enable;
  bool useLocation;
  char customLocaton[40];
  //health
  int lastLayer;
  time_t health_last_updated;
  //step colors
  GColor upper_step;
  GColor lower_step;
  int icon_step;
  GColor text_step;
  GColor sep_step;
  
  //step colors
  GColor upper_cal;
  GColor lower_cal;
  int icon_cal;
  GColor text_cal;
  GColor sep_cal;
  
  //step colors
  GColor upper_sleep;
  GColor lower_sleep;
  int icon_sleep;
  GColor text_sleep;
  GColor sep_sleep;
} __attribute__((__packed__)) AppSettings;

typedef struct WeatherSettings {  
  
  int temperature;
  char conditions[20];
  time_t temp_last_updated;
} __attribute__((__packed__)) WeatherSettings;

typedef struct HealthSettings {  
  //health
  int lastLayer;
  time_t health_last_updated;
} __attribute__((__packed__)) HealthSettings;

static const GPathInfo LOWER_PATH_INFO = {
  .num_points = 4,
  .points = (GPoint []) {{-1, 121}, 
  {-1, 168}, {144, 168}, {144, 121}}
};

static const GPathInfo STEP_UPPER_INFO = {
  .num_points = 8,
  .points = (GPoint []) {{-1, 0},{-1, 119}, 
  {11, 119}, {24, 133}, {39, 119}, 
  {-1, 119}, {144, 119}, {144, 0}}
};

static const GPathInfo STEP_PATH_INFO = {
  .num_points = 5,
  .points = (GPoint []) {{0, 120}, 
  {11, 120}, {25, 134}, {39, 120}, 
  {144, 120}}
};

static const GPathInfo CAL_UPPER_INFO = {
  .num_points = 8,
  .points = (GPoint []) {{-1, 0},{-1, 119}, 
  {58, 119}, {72, 133}, {86, 119},
  {-1, 119}, {144, 119}, {144, 0}}
};

static const GPathInfo CAL_PATH_INFO = {
  .num_points = 5,
  .points = (GPoint []) {{0, 120}, 
  {58, 120}, {72, 134}, {86, 120},
  {144, 120}}
};

static const GPathInfo SLEEP_UPPER_INFO = {
  .num_points = 8,
  .points = (GPoint []) {{-1, 0},{-1, 119}, 
  {105, 119}, {119, 133}, {133, 119},
  {-1, 119}, {144, 119}, {144, 0}}
};

static const GPathInfo SLEEP_PATH_INFO = {
  .num_points = 5,
  .points = (GPoint []) {{0, 120}, 
  {105, 120}, {119, 134}, {133, 120},
  {144, 120}}
};

static const GPathInfo SEP1_PATH_INFO = {
  .num_points = 2,
  .points = (GPoint []) {{48, 124},{48, 166}}
};

static const GPathInfo SEP2_PATH_INFO = {
  .num_points = 2,
  .points = (GPoint []) {{96, 124},{96, 166}}
};

static const GPathInfo BATTERY_OUTLINE_INFO = {
  .num_points = 9,
  .points = (GPoint []) {{122, 5}, {140, 5},
  {140, 7}, {142, 7}, {142, 12}, {140, 12}, {140, 5},
  {140, 14}, {122,14}}
};

static const GPathInfo BT_PATH_INFO = {
  .num_points = 6,
  .points = (GPoint []) {{3, 7}, {11, 15}, {7, 19}, {7, 3}, {11, 7}, {3, 15}}
};

static const GPathInfo LOWER_PATH_INFO_2 = {
  .num_points = 4,
  .points = (GPoint []) {{-1, 164}, 
  {-1, 228}, {200, 228}, {200, 164}}
};

static const GPathInfo STEP_UPPER_INFO_2 = {
  .num_points = 8,
  .points = (GPoint []) {{-1, 0},{-1, 162}, 
  {15, 162}, {33, 181}, {54, 162}, 
  {-1, 162}, {200, 162}, {200, 0}}
};

static const GPathInfo STEP_PATH_INFO_2 = {
  .num_points = 5,
  .points = (GPoint []) {{0, 163}, 
  {15, 163}, {35, 182}, {54, 163}, 
  {200, 163}}
};

static const GPathInfo CAL_UPPER_INFO_2 = {
  .num_points = 8,
  .points = (GPoint []) {{-1, 0},{-1, 162}, 
  {80, 162}, {100, 181}, {119, 162},
  {-1, 162}, {200, 162}, {200, 0}}
};

static const GPathInfo CAL_PATH_INFO_2 = {
  .num_points = 5,
  .points = (GPoint []) {{0, 163}, 
  {80, 163}, {100, 182}, {119, 163},
  {200, 163}}
};

static const GPathInfo SLEEP_UPPER_INFO_2 = {
  .num_points = 8,
  .points = (GPoint []) {{-1, 0},{-1, 162}, 
  {146, 162}, {162, 181}, {181, 162},
  {-1, 162}, {200, 162}, {200, 0}}
};

static const GPathInfo SLEEP_PATH_INFO_2 = {
  .num_points = 5,
  .points = (GPoint []) {{0, 163}, 
  {146, 163}, {163, 182}, {181, 163},
  {200, 163}}
};

static const GPathInfo SEP1_PATH_INFO_2 = {
  .num_points = 2,
  .points = (GPoint []) {{67, 168},{67, 225}}
};

static const GPathInfo SEP2_PATH_INFO_2 = {
  .num_points = 2,
  .points = (GPoint []) {{133, 168},{133, 225}}
};

static const GPathInfo BATTERY_OUTLINE_INFO_2 = {
  .num_points = 9,
  .points = (GPoint []) {{169, 7}, {195, 7},
  {195, 9}, {197, 9}, {197, 16}, {195, 16}, {195, 7},
  {195, 19}, {169,19}}
};

static const GPathInfo BT_PATH_INFO_2 = {
  .num_points = 6,
  .points = (GPoint []) {{4, 9}, {15, 20}, {9, 26}, {9, 4}, {15, 9}, {4, 20}}
};

static void prv_default_settings();
static void prv_load_settings();
static void prv_save_settings();
static void prv_inbox_received_handler(DictionaryIterator *iter, void *context);
static void prv_init(void);