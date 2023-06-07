#include "arduino_secrets.h"

/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled 2"
  https://create.arduino.cc/cloud/things/8b2c66c8-a852-4a0b-8370-59ef00bcc282 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  String xiao_19_comfort;
  float xiao_19_depoint;
  float xiao_19_heatindex;
  float xiao_19_humidity;
  float xiao_19_temperature;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include "DHTesp.h"                                // Click here to get the library: http://librarymanager/All#DHTesp

DHTesp dht;                                        // Initialize the sensor

#define dhtPin A2                                  // pin for DHT
#define BAUD 9600                                  // serial monitor BAUD rate

int delay_time = 3000;

ComfortState cf;                                   // ComfortState is returned by the DHT11 sensor

bool getTemperature() {
  // Reading temperature for humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  TempAndHumidity newValues = dht.getTempAndHumidity();
  // Check if any reads failed and exit early (to try again).
  if (dht.getStatus() != 0) {
    Serial.println("DHT11 error status: " + String(dht.getStatusString()));

    delay(delay_time);

    return false;
  }

  // call functions from DHT11
  float heatindex = dht.computeHeatIndex(newValues.temperature, newValues.humidity);
  float dewpoint = dht.computeDewPoint(newValues.temperature, newValues.humidity);
  float cr = dht.getComfortRatio(cf, newValues.temperature, newValues.humidity);

  // get comfortStatus from DHT11 and use Select function to determine String
  String comfortStatus;
  switch(cf) {
    case Comfort_OK:
      comfortStatus = "       OK";
      break;
    case Comfort_TooHot:
      comfortStatus = "    Too Hot";
      break;
    case Comfort_TooCold:
      comfortStatus = "    Too Cold";
      break;
    case Comfort_TooDry:
      comfortStatus = "    Too Dry";
      break;
    case Comfort_TooHumid:
      comfortStatus = "   Too Humid";
      break;
    case Comfort_HotAndHumid:
      comfortStatus = "  Hot And Humid";
      break;
    case Comfort_HotAndDry:
      comfortStatus = "  Hot And Dry";
      break;
    case Comfort_ColdAndHumid:
      comfortStatus = " Cold And Humid";
      break;
    case Comfort_ColdAndDry:
      comfortStatus = " Cold And Dry";
      break;
    default:
      comfortStatus = "   Unknown:";
      break;
  };
 
  // print results to Monitor
  Serial.println(" TMP:" + String(newValues.temperature) + " HUM:" + String(newValues.humidity) + " HIX:" + String(heatindex) + " DEW:" + String(dewpoint) + " " + comfortStatus);
	
  // store results in IOT variables
	
  xiao_19_temperature = newValues.temperature;
  xiao_19_humidity = newValues.humidity;
  xiao_19_comfort = comfortStatus;
  xiao_19_depoint = dewpoint;
  xiao_19_heatindex = heatindex;
  
  return true;

}

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  dht.setup(dhtPin, DHTesp::DHT11);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  Serial.println("DHT ESP32 example with tasks");

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(delay_time);

}

void loop() {

  getTemperature();           // get data from DHT11

  ArduinoCloud.update();
  
  delay(delay_time);
  
}








