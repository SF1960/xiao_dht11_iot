// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "a9ea85e0-a199-4816-aca4-a77a6ac14ddf";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password


String xiao_19_comfort;
float xiao_19_depoint;
float xiao_19_heatindex;
float xiao_19_humidity;
float xiao_19_temperature;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(xiao_19_comfort, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(xiao_19_depoint, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(xiao_19_heatindex, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(xiao_19_humidity, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(xiao_19_temperature, READ, ON_CHANGE, NULL);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);