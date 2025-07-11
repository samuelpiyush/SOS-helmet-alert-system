#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// SIM800L GSM Module
SoftwareSerial sim800(2, 3);       // RX, TX
// NEO-6M GPS Module
SoftwareSerial gpsSerial(10, 11);  // TX, RX

TinyGPSPlus gps;

const int buttonPin = 8;
const unsigned long longPressDuration = 10000; // 10 seconds
const String emergencyNumber = "+91xxxxxxxxxx"; // <-- Update as needed
const unsigned long smsTimeout = 15000; // 15 seconds

bool buttonPressed = false;
unsigned long pressStartTime = 0;
String textMessage = "";

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  sim800.begin(9600);
  gpsSerial.begin(9600);

  delay(3000); 

  // Initialize GSM module
  sim800.println("AT");
  delay(1000);
  sim800.println("AT+CMGF=1");         // SMS text mode
  delay(1000);
  sim800.println("AT+CNMI=2,2,0,0,0"); // Show SMS in serial
  delay(1000);

  Serial.println("SOS Helmet System Ready");
}

void loop() {
  // --- Read GPS data ---
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  // --- Check for incoming SMS ---
  if (sim800.available()) {
    textMessage = sim800.readString();
    Serial.println("Incoming SMS: " + textMessage);
    if (textMessage.indexOf("GETLOC") >= 0) {
      sendLocationSMS();
    }
    textMessage = "";
  }

  // --- Handle long button press ---
  if (digitalRead(buttonPin) == LOW) {
    if (!buttonPressed) {
      pressStartTime = millis();
      buttonPressed = true;
    } else if (millis() - pressStartTime >= longPressDuration) {
      Serial.println("Long press detected! Sending SOS...");
      sendLocationSMS();
      while (digitalRead(buttonPin) == LOW); // Wait until button released
      buttonPressed = false;
    }
  } else {
    buttonPressed = false;
  }
}

void sendLocationSMS() {
  String lati = "0.00000000";
  String longi = "0.00000000";

  if (gps.location.isValid()) {
    lati = String(gps.location.lat(), 8);
    longi = String(gps.location.lng(), 8);
  }

  String mapsLink = "https://maps.google.com/?q=" + lati + "," + longi;
  Serial.println("Sending SMS with link: " + mapsLink);

  // Send SMS
  sim800.println("AT+CMGS=\"" + emergencyNumber + "\"");
  delay(1000);
  sim800.print("Emergency! Helmet SOS location:\n" + mapsLink);
  sim800.write(26); // CTRL+Z

  // Wait for +CMGS confirmation
  unsigned long startTime = millis();
  bool success = false;

  while (millis() - startTime < smsTimeout) {
    if (sim800.available()) {
      String response = sim800.readString();
      if (response.indexOf("+CMGS:") != -1) {
        Serial.println("SMS sent successfully!");
        success = true;
        break;
      }
    }
  }

  if (!success) {
    Serial.println("SMS failed or SIM800L not responding.");
  }
}


