module.exports = [
  {
    "type": "heading",
    "defaultValue": "Healthify"
  },
  {
    "type": "text",
    "defaultValue": "v3.5 Watchface Configuration"
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Date/Time Settings"
      },
      {
        "type": "radiogroup",
        "messageKey": "DATE_TIME_FORMAT[0]",
        "label": "Time Format",
        "defaultValue": "24",
        "options": [
          { 
            "label": "12-Hour",
            "value": "12" 
          },
          { 
            "label": "24-Hour",
            "value": "24" 
          }
        ]
      },
      {
        "type": "toggle",
        "messageKey": "DAY_OF_WEEK",
        "label": "Show Day of Week",
        "defaultValue": true
      },
      {
        "type": "select",
        "messageKey": "DATE_TIME_FORMAT[1]",
        "defaultValue": "%d-%b-%y",
        "label": "Date Format",
        "options": [
          { 
            "label": "14-Nov-92",
            "value": "%d-%b-%y" 
          },
          { 
            "label": "Nov-14-92",
            "value": "%b-%d-%y" 
          },
          { 
            "label": "14/11/92",
            "value": "%d/%m/%y" 
          },
          { 
            "label": "11/14/92",
            "value": "%m/%d/%y" 
          },
          { 
            "label": "92-11-14",
            "value": "%y-%m-%d" 
          },
          { 
            "label": "14-11-92",
            "value": "%d-%m-%y" 
          }
        ]
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Weather Settings"
      },
      {
        "type": "toggle",
        "messageKey": "WEATHER_ENABLE",
        "label": "Enable Weather",
        "id": "id_weather_enable",
        "defaultValue": true
      },
      {
        "type": "radiogroup",
        "messageKey": "DIST_TEMP_UNIT[0]",
        "label": "Temperature Unit",
        "id": "id_weather_unit",
        "defaultValue": "ce",
        "options": [
          { 
            "label": "Celsius", 
            "value": "ce" 
          },
          { 
            "label": "Fahrenheit", 
            "value": "fa" 
          }
        ]
      },
      {
        "type": "slider",
        "messageKey": "WEATHER_REFRESH",
        "id": "id_weather_refresh",
        "defaultValue": 60,
        "label": "Refresh Interval (Minutes)",
        "min": 15,
        "max": 120,
        "step": 1
      },
      {
        "type": "toggle",
        "messageKey": "WEATHER_USE_GPS",
        "label": "Use GPS for Current Location",
        "id": "id_weather_use_gps",
        "defaultValue": true
      },
      {
        "type": "input",
        "messageKey": "WEATHER_LOC_NAME",
        "defaultValue": "",
        "id": "id_weather_loc_name",
        "label": "Custom Location",
        "attributes": {
          "placeholder": "City, Country  OR PinCode",
          "limit": 40
        }
      }
    ]
  },   
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Distance Settings"
      },
      {
        "type": "radiogroup",
        "messageKey": "DIST_TEMP_UNIT[1]",
        "label": "Distance Unit",
        "defaultValue": "km",
        "options": [
          { 
            "label": "Kilometers", 
            "value": "km" 
          },
          { 
            "label": "Miles", 
            "value": "mi" 
          }
        ]
      }  
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Bluetooth Settings"
      },
      {
        "type": "toggle",
        "messageKey": "BT_VIBR[0]",
        "label": "Vibrate on Bluetooth Disconnect",
        "defaultValue": true
      },
      {
        "type": "toggle",
        "messageKey": "BT_VIBR[1]",
        "label": "Vibrate on Bluetooth Reconnect",
        "defaultValue": true
      }
    ]
  }, 
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Display Settings"
      },
      {
        "type": "toggle",
        "messageKey": "HEALTH_AUTO",
        "label": "Automatically Change Layers",
        "id": "id_health_auto",
        "defaultValue": true
      },
      {
        "type": "slider",
        "messageKey": "HEALTH_REFRESH",
        "id": "id_health_refresh",
        "defaultValue": 10,
        "label": "Refresh Interval (Minutes)",
        "min": 1,
        "max": 90,
        "step": 1
      }, 
      {
        "type": "select",
        "messageKey": "HEALTH_FIX_LAYER",
        "id": "id_health_fix_layer",
        "defaultValue": 0,
        "label": "Which Layer to show always",
        "options": [
          { 
            "label": "Steps",
            "value": 0 
          },
          { 
            "label": "Calories",
            "value": 1 
          },
          { 
            "label": "Sleep",
            "value": 2
          }
        ]
      },
      {
        "type": "toggle",
        "messageKey": "HEALTH_SHAKE",
        "label": "Change layer on flick of wrist",
        "defaultValue": false
      },    
      
      {
        "type": "toggle",
        "messageKey": "HEALTH_REALTIME",
        "label": "Update Steps count in realtime",
        "description": "If ON, health data will be updated in realtime instead of every minute (consumes more battery)",
        "defaultValue": false
      },   
    ]
  },  
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Steps Layer"
      },
      {
        "type": "color",
        "messageKey": "UPPER_COLOR[0]",
        "defaultValue": "0x0055AA",
        "label": "Background Color of Upper Layer"
      },
      {
        "type": "color",
        "messageKey": "LOWER_COLOR[0]",
        "defaultValue": "0x555555",
        "label": "Background Color of Lower Layer"
      },
      {
        "type": "color",
        "messageKey": "TEXT_COLOR[0]",
        "defaultValue": "0xFFFFFF",
        "label": "Text Color"
      },
      {
        "type": "color",
        "messageKey": "SEP_COLOR[0]",
        "defaultValue": "0xFFFFFF",
        "label": "Separator Color"
      },
      {
        "type": "select",
        "messageKey": "ICON_COLOR[0]",
        "defaultValue": 1,
        "label": "Icons Color",
        "options": [
          { 
            "label": "Black",
            "value": 0 
          },
          { 
            "label": "White",
            "value": 1 
          }
        ]
      },     
    ]
  },  
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Calories Layer"
      },
      {
        "type": "color",
        "messageKey": "UPPER_COLOR[1]",
        "defaultValue": "0xFFAA00",
        "label": "Background Color of Upper Layer"
      },
      {
        "type": "color",
        "messageKey": "LOWER_COLOR[1]",
        "defaultValue": "0xFFFFFF",
        "label": "Background Color of Lower Layer"
      },
      {
        "type": "color",
        "messageKey": "TEXT_COLOR[1]",
        "defaultValue": "0x000000",
        "label": "Text Color"
      },
      {
        "type": "color",
        "messageKey": "SEP_COLOR[1]",
        "defaultValue": "0xFF5500",
        "label": "Separator Color"
      },
      {
        "type": "select",
        "messageKey": "ICON_COLOR[1]",
        "defaultValue": 0,
        "label": "Icons Color",
        "options": [
          { 
            "label": "Black",
            "value": 0 
          },
          { 
            "label": "White",
            "value": 1 
          }
        ]
      },      
    ]
  },  
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Sleep Layer"
      },
      {
        "type": "color",
        "messageKey": "UPPER_COLOR[2]",
        "defaultValue": "0xFFFFFF",
        "label": "Background Color of Upper Layer"
      },
      {
        "type": "color",
        "messageKey": "LOWER_COLOR[2]",
        "defaultValue": "0x00AAFF",
        "label": "Background Color of Lower Layer"
      },
      {
        "type": "color",
        "messageKey": "TEXT_COLOR[2]",
        "defaultValue": "0x000000",
        "label": "Text Color"
      },
      {
        "type": "color",
        "messageKey": "SEP_COLOR[2]",
        "defaultValue": "0x000000",
        "label": "Separator Color"
      },
      {
        "type": "select",
        "messageKey": "ICON_COLOR[2]",
        "defaultValue": 0,
        "label": "Icons Color",
        "options": [
          { 
            "label": "Black",
            "value": 0 
          },
          { 
            "label": "White",
            "value": 1 
          }
        ]
      }
    ]
  },      
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  },
  {
    "type": "button",   
    "id": "id_donate",
    "defaultValue": "Donate",
    "description": "Kindly donate if you liked my work. This inspires me to keep working on my watchfaces :)"
  }
];