
// Libraries
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "DHT.h"

// DHT 11 sensor
#define DHTPIN D5
#define DHTTYPE DHT11

// WiFi parameters
const char* ssid          = "youseewifi";
const char* password      = "youseewifi1";
//#define WLAN_SSID       "Filip"
//#define WLAN_PASS       "PasswordIsFilip"
//#define WLAN_SSID       "SpaceExtremeDownstairs"
//#define WLAN_PASS       "iskagehuset"
// Adafruit IO
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "filipgermanek"
#define AIO_KEY         "18437194c3b845eb814a1831b140e62e"  // Obtained from account info on io.adafruit.com

// DHT sensor
DHT dht(DHTPIN, DHTTYPE, 15);

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Setup feeds for temperature & humidity
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");

/*************************** Sketch Code ************************************/

void setup() {

  // Init sensor
  dht.begin();
  Serial.begin(115200);
  delay(5000);
  Serial.println('\n');
  // Connect to WiFi access point.
   Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  //WiFi.mode(WIFI_STA); // SETS TO STATION MODE!
  WiFi.begin(ssid, password);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());

  // connect to adafruit io
  connect();

}

void loop() {

  // ping adafruit io a few times to make sure we remain connected
  if(! mqtt.ping(3)) {
    // reconnect to adafruit io
    if(! mqtt.connected())
      connect();
  }

  // Grab the current state of the sensor
  //int humidity_data = (int)dht.readHumidity();
  int temperature_data = (int)dht.readTemperature();

  // By default, the temperature report is in Celsius, for Fahrenheit uncomment
  //    following line.
  // temperature_data = temperature_data*(9.0/5.0) + 32.0;

  // Publish data
  if (! temperature.publish(temperature_data))
    Serial.println(F("Failed to publish temperature"));
  else
    Serial.println(F("Temperature published!"));

  //if (! humidity.publish(humidity_data))
  //  Serial.println(F("Failed to publish humidity"));
  //else
  //  Serial.println(F("Humidity published!"));

  // Repeat every 10 seconds
  delay(10000);

}

// connect to adafruit io via MQTT
void connect() {

  Serial.print(F("Connecting to Adafruit IO... "));

  int8_t ret;

  while ((ret = mqtt.connect()) != 0) {

    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(5000);

  }

  Serial.println(F("Adafruit IO Connected!"));

}
