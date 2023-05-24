#include <PubSubClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include "config.h"

String mPubAddr = String(MQTT_PUB) + String(MQTT_USERID)+"/"+String(MQTT_DEVICEID);
String mSubAddr = String(MQTT_SUB) + String(MQTT_USERID)+"/"+String(MQTT_DEVICEID);

int  mRemote = 0;
int  mPumpStat = 0;
int  lstSwitchState;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

String getPubString(int remote, int stat) {
  // Create a DynamicJsonDocument
  DynamicJsonDocument doc(100);

  String strStatus = stat == 1 ? "on" : "off";  
  
  doc["remote"] = remote;
  doc["pump"] = strStatus;  
  
  // Serialize the document to a JSON string
  String jsonString;
  serializeJson(doc, jsonString);
  
  return jsonString;
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  if (payload[0] == '{') {  
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print("Failed to parse JSON: ");
      Serial.println(error.c_str());
    } else {
      if (doc.containsKey("pump")) {
        const char* pumpStatus = doc["pumps"];
        if (strcmp(pumpStatus, "on") == 0) {
          Serial.println("Pumps is ON");
          digitalWrite(WATER_PIN, HIGH);
          mRemote = 1;
          mPumpStat = 1;
          client.publish(mPubAddr.c_str(), getPubString(mRemote, mPumpStat).c_str());
        } else if (strcmp(pumpStatus, "off") == 0) {
          Serial.println("pump is OFF");          
          digitalWrite(WATER_PIN, LOW);
          mRemote = 1;
          mPumpStat = 0;
          client.publish(mPubAddr.c_str(), getPubString(mRemote, mPumpStat).c_str());
        } else {
          Serial.println("Invalid pump status");
        }
      } else if (doc.containsKey("status")) {
        int numStatus = doc["status"];
        if (numStatus == 1) {
          Serial.println("Status request");
          client.publish(mPubAddr.c_str(), getPubString(mRemote, mPumpStat).c_str());
        }
      }
    }
  } else {
    // Print the received message as a string to the serial monitor
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);      
    }    
    Serial.println();    
  }  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish(mPubAddr.c_str(), "connected");
      // ... and resubscribe
      client.subscribe(mSubAddr.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(WATER_PIN, OUTPUT);
  
  digitalWrite(WATER_PIN, LOW);  

  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_HOST, 8359);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    digitalWrite(BUILTIN_LED, LOW);
    reconnect();
  } else {    
    digitalWrite(BUILTIN_LED, LOW);
    delay(500);
    digitalWrite(BUILTIN_LED, HIGH);
    delay(500);
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 60000) {
    lastMsg = now;
    ++value;
    client.publish(mPubAddr.c_str(), getPubString(mRemote, mPumpStat).c_str());
  }
  
  int switchState = digitalRead(SWITCH_PIN);
  if (lstSwitchState != switchState) {
    Serial.print("Switch Status:");
    Serial.println(switchState);
    lstSwitchState = switchState;
    mRemote = 0;    
    if (switchState == 0){
      mPumpStat = 1;
      digitalWrite(WATER_PIN, HIGH);
    } else {
      mPumpStat = 0;
      digitalWrite(WATER_PIN, LOW);
    }
    if (client.connected()) {
      client.publish(mPubAddr.c_str(), getPubString(mRemote, mPumpStat).c_str());    
    }
  }
}