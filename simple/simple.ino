/**
 * Simple example using the mqtt protocol on
 * a adafruit huzzah board to connect to
 * https://shiftr.io/
 *
 * based on sketches by Joël Gähwiler @256dpi
 * https://github.com/IAD-ZHDK/ShifterBit
 *
 * huzzah board: http://www.adafruit.com/products/2471
 * mqtt lib: https://github.com/256dpi/arduino-mqtt
 * esp8266 lib: https://github.com/esp8266/Arduino
 * tutorial: https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/overview
 * @author: Fabian @fabiantheblind  Morón Zirfas
 * @license: MIT
 *
 *
 */

// include the libs
#include <ESP8266WiFi.h>
#include <MQTTClient.h>

MQTTClient mqtt_client;
WiFiClient wifi_client;

// some globals like
// your ssid and the adress of the server
// your topics and so on
int count = 0;
const char* ssid = "YOUR WIFI NAME";
const char* wifi_key = "YOUR WIFI PASSWORD";
const char* mqtt_broker = "broker.shiftr.io";
const char* mqtt_pw = "try";
const char* mqtt_client_id = "Huzzah";
const char* mqtt_user = "try";
const char* subscribe_topic = "hello";
const char* publish_topic = "world";


void setup() {
  // first we need to connect to the wifi
  Serial.begin(115200);
  Serial.print("Joining WiFi...");
  WiFi.begin(ssid, wifi_key);
  Serial.setDebugOutput(true);

  // we go on as soon as we are connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // if we joind the wifi
  // we get some messages
  Serial.print("\nJoined with IP Address: ");
  Serial.println(WiFi.localIP()); // print your ip

  // now lets connect to the broker
  mqtt_client.begin(mqtt_broker, wifi_client);
  Serial.print("Connecting to shiftr.io...");
  // also we wait until we are connected
  while (!mqtt_client.connect(mqtt_client_id, mqtt_user, mqtt_pw)) {
    Serial.println(".");
  }
  // huzzah we are connected to the broker on shiftr
  Serial.println("\nConnected!");
  
  // if you also want to subscribe to something to it like this
  //  mqtt_client.subscribe(subscribe_topic);

}

void loop() {
  // loop the client and listen to what 
  mqtt_client.loop(); 
  delay(10); // make it a bit slower

  // now we publish someting every 1000 ticks
  if (count % 1000 == 0) {
    mqtt_client.publish(publish_topic, "1");
  }
  count++;// increase our tick
}

// if you subscribe to something it
// will come in here
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {

  Serial.println(payload.toInt());

}
