#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiSTA.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define GAS_SENSOR_PIN 32
#define BUZZER_PIN 2
#define Piezo_SENSOR_PIN 33 // Pin to which the Piezo sensor is connected

TinyGPSPlus gps;
bool gasDetected = false;

#define WLAN_SSID "Acer"
#define WLAN_PASS "a123456b"

// Adafruit IO Setup
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "flamerider12"
#define AIO_KEY "aio_ZbDC53ENPhEIwPrRxTZlT3f90V5r"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Adafruit IO Feeds
Adafruit_MQTT_Publish gasFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/gas");
Adafruit_MQTT_Publish PiezoFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/piezo");

void MQTT_connect();

void setup() {
  Serial.begin(115200);
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(Piezo_SENSOR_PIN, INPUT);

  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read gas sensor value
  MQTT_connect();

  int gasValue = analogRead(GAS_SENSOR_PIN);
  publishGasValue(gasValue);

  int PiezoValue = analogRead(Piezo_SENSOR_PIN);
  // Publish Piezo sensor value to Adafruit IO
  publishPiezoValue(PiezoValue);

  if (gasValue > 2000) {
    buzzerAlert();
  }

  readGPSLocation();
  printGPSLocation();

  delay(5000);

  // float latitude = gps.location.lat();
  // float longitude = gps.location.lng();
  // Serial.print("Latitude: ");
  // Serial.println(latitude, 6);
  // Serial.print("Longitude: ");
  // Serial.println(longitude, 6);
}

void buzzerAlert() {
  digitalWrite(BUZZER_PIN, HIGH); // Turn the buzzer on
  delay(500); // Buzz for 1 seconds
  digitalWrite(BUZZER_PIN, LOW); // Turn the buzzer off
}

bool readGPSLocation() {
  while (Serial.available() > 0) {
    if (gps.encode(Serial.read())) {
      return true;
    }
  }
  return false;
}

void printGPSLocation() {
  Serial.print("Location: ");
  if (gps.location.isValid()) {
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(", Long: ");
    Serial.print(gps.location.lng(), 6);
  } else {
    Serial.print("Lat: 0 ");
    Serial.print("Long: 0");
  }
  Serial.println();
}

void publishGasValue(int value) {
  Serial.print("Publishing gas value to Adafruit IO: ");
  Serial.println(value);
  gasFeed.publish((int32_t)value);
}

void publishPiezoValue(int value) {
  Serial.print("Publishing Piezo sensor value to Adafruit IO: ");
  Serial.println(value);
  PiezoFeed.publish((int32_t)value);
}


void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000); // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }

  Serial.println("MQTT Connected!");
}

