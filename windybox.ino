#include "DHT.h"
#include <IRremote.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

long previousMillis = 0;
long logInterval = 5000;

// pin 3
IRsend irsend;

unsigned int livingroomFAN[67] = {9050, 4450, 600, 500, 600, 500, 650, 500, 600, 550, 600, 500, 600, 1650, 600, 500, 650, 500, 600, 1650, 600, 1650, 600, 1650, 600, 1600, 650, 1650, 600, 500, 600, 1650, 600, 1650, 600, 500, 600, 1650, 600, 550, 600, 1650, 600, 1650, 600, 500, 600, 550, 600, 500, 600, 1650, 600, 500, 650, 1650, 550, 550, 600, 500, 600, 1650, 600, 1650, 600, 1650, 600};
unsigned int livingroomMODE[67] = {9050, 4450, 600, 500, 650, 500, 600, 500, 650, 500, 600, 500, 600, 1650, 600, 550, 600, 500, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 500, 600, 1650, 600, 1650, 600, 1650, 600, 500, 650, 500, 600, 1650, 600, 500, 600, 550, 600, 500, 600, 550, 600, 500, 600, 1650, 600, 1650, 600, 550, 550, 1650, 650, 1650, 550, 1650, 600, 1650, 600};
unsigned int livingroomPOWER[67] = {9050, 4400, 650, 500, 600, 500, 650, 500, 600, 500, 650, 500, 600, 1600, 650, 500, 600, 550, 600, 1600, 650, 1600, 650, 1650, 600, 1600, 600, 1650, 650, 500, 600, 1650, 600, 1650, 600, 500, 600, 1650, 600, 500, 650, 500, 600, 550, 600, 500, 600, 500, 600, 550, 600, 1650, 600, 500, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600};
unsigned int livingroomTEMPMINUS[67] = {9050, 4450, 600, 500, 650, 500, 600, 500, 650, 500, 600, 500, 600, 1650, 600, 550, 600, 500, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 500, 600, 1650, 600, 1650, 600, 1650, 600, 500, 650, 500, 600, 550, 600, 1600, 600, 550, 600, 500, 650, 500, 600, 500, 600, 1650, 600, 1650, 600, 1650, 600, 500, 650, 1650, 550, 1700, 550, 1650, 600};
unsigned int livingroomTEMPPLUS[67] = {9050, 4400, 650, 500, 600, 550, 600, 500, 600, 500, 650, 500, 600, 1650, 600, 500, 600, 550, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 550, 550, 600, 1650, 600, 1650, 600, 500, 600, 1650, 650, 500, 600, 1650, 600, 500, 600, 550, 600, 500, 600, 550, 550, 1650, 650, 500, 600, 1650, 600, 500, 600, 1650, 600, 1700, 550, 1650, 600, 1650, 600};
unsigned int livingroomTIMER[67] = {9050, 4450, 600, 500, 650, 500, 600, 550, 600, 500, 600, 500, 650, 1600, 650, 500, 600, 500, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 500, 600, 1650, 650, 1650, 550, 1650, 600, 550, 600, 500, 600, 1650, 600, 1650, 600, 550, 600, 500, 600, 550, 550, 550, 600, 1650, 600, 1650, 600, 500, 600, 550, 600, 1650, 600, 1650, 600, 1650, 550};

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  unsigned long currentMillis = millis();
  String cmd;
  
  if (currentMillis - previousMillis > logInterval) {
    previousMillis = currentMillis;
    logTemperature();
  }
  
  if (Serial.available() > 0) {
    cmd = Serial.readStringUntil('\n');
    cmd.trim();
    sendIr(cmd);
  }
}

void logTemperature() {
  float humidity = dht.readHumidity();
  float degrees_c = dht.readTemperature();
  
  if(!isnan(humidity) && !isnan(degrees_c)) {
    Serial.print("Humidity:");
    Serial.print(humidity);
    Serial.println(":%");
    Serial.print("Temperature:");
    Serial.print(degrees_c);
    Serial.println(":C");
  }
}

void sendIr(String cmd) {
  Serial.println(cmd);
  if (cmd == "POWER") {
    irsend.sendRaw(livingroomPOWER, 67, 38);
  } else if (cmd == "TEMPPLUS") {
    irsend.sendRaw(livingroomTEMPPLUS, 67, 38);
  } else if (cmd == "TEMPMINUS") {
    irsend.sendRaw(livingroomTEMPMINUS, 67, 38);
  } else if (cmd == "TIMER") {
    irsend.sendRaw(livingroomTIMER, 67, 38);
  } else if (cmd == "FAN") {
    irsend.sendRaw(livingroomFAN, 67, 38);
  } else if (cmd == "MODE") {
    irsend.sendRaw(livingroomMODE, 67, 38);
  }
}
