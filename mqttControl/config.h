  

//#define SLEEP_DURATION 30 * 60
#define SLEEP_DURATION 5 * 60
// emergency hibernate countdown in seconds
#define EMERGENCY_HIBERNATE 3 * 60
// how often should the battery be read - in run count
#define BATTERY_INTERVAL 6
// how often should a device be retried in a run when something fails
#define RETRY 3

// MQTT topic gets defined by "<MQTT_BASE_TOPIC>/<MAC_ADDRESS>/<property>"
// where MAC_ADDRESS is one of the values from FLORA_DEVICES array
// property is either temperature, moisture, conductivity, light or battery

const char*   MQTT_HOST       = "frogmon.synology.me"; // 원격컨트롤 서버 주소
const int     MQTT_PORT       = 8359;                  // 원격컨트롤 서버 포트
const char*   MQTT_USERID     = "등록한뚝딱이ID";         // 등록한뚝딱이ID
const char*   MQTT_DEVICEID   = "등록한장비ID";          // 등록한장비ID
const int     MQTT_RETRY_WAIT = 5000;
const char*   MQTT_PUB        = "FARMs/Status/";      // 변경 불필요
const char*   MQTT_SUB        = "FARMs/Control/";     // 뱐걍 븚필요

#define BUTTON_PIN  0   // Pin number for the button
#define BUILTIN_LED 2
#define WATER_PIN   15
#define SWITCH_PIN  13

