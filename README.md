# SOS-helmet-alert-system

An emergency-response system built into a smart helmet. It uses GPS and GSM modules to send real-time location via SMS and initiate a call when an SOS button is pressed.

--- 

## SOS Emergency Alert (Arduino-GPS-GSM System)
- In the event of an accident or emergency, the user presses the SOS button mounted on the helmet.
- The Arduino Nano reads this input and wakes the GPS module.
- The GPS module fetches the latitude and longitude of the current location.
- These coordinates are processed into a Google Maps link.
- The GSM module sends an SMS containing this link to pre-saved emergency contact numbers.
- It can also initiate a phone call as an additional alert mechanism.
- The program includes smart delay functions for GPS data retrieval and ensures the alert is sent only once per press.

---


## Tech Stack

- **Microcontroller**: Arduino Nano
- **GSM Module**: SIM800L
- **GPS Module**: NEO-6M
- **Libraries**: TinyGPSPlus, SoftwareSerial

---

## Features

- Sends SMS with live GPS coordinates using SIM800L and NEO-6M
- Makes a follow-up emergency call after SMS
- Compact, wearable and ideal for bike riders
- Simple button-based SOS trigger
- Built using Arduino Nano

This Arduino sketch implements the SOS alert mechanism in the smart helmet system. It enables the rider to send their real-time GPS location to emergency contacts through an SMS using the SIM800L GSM module. The system supports both manual and remote activation.

---

## Key Functional Features: 

- **GPS Location Tracking:** Continuously reads data from a GPS module (e.g., NEO-6M). Extracts valid latitude and longitude coordinates using the TinyGPSPlus library.
- **Manual SOS via Long-Press Button:** A physical button is connected to the helmet. When pressed and held for 10 seconds, it triggers the emergency response. This prevents accidental alerts from short presses (debounce + long-press logic).
- **Remote SOS Activation via SMS:** The SIM800L module listens for incoming messages. If the incoming message contains the keyword "GETLOC", the system replies with a Google Maps link to the rider’s current location.
- **Dynamic Message Generation:** The location is formatted into a Google Maps URL. This message is then sent via SMS to the pre-saved emergency contact.
- **Reliable SMS Transmission:** After sending the message using AT commands, the code waits for a delivery confirmation (+CMGS: response). Prints success/failure status to the Serial Monitor for debugging and reliability tracking.
- **Debouncing and Error Handling:** Incorporates a wait loop to detect when the button is released after a long press. Provides fallback values (0.00000000) when GPS location is not yet available.


---

## Files Included

| File                | Description                            |
|---------------------|----------------------------------------|
| `sos_helmet.ino`    | Arduino source code                    |
| `README.md`         | This project overview                  |
| `images/`           | Circuit diagram, prototype photos      |

---

## Hardware Setup

![Circuit Diagram](images/circuit_diagram.png)
![Prototype image](images/Circuit_prototype.jpg)
![The project image](images/SOS_device.jpg)

---

##  Author

Piyush Samuel M
