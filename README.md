# 🔧 Sensors & Transducers Lab – ESP32

This repository contains code, circuits, and documentation for my **Sensors and Transducers Lab** experiments.  
All experiments are implemented on the **ESP32** microcontroller, using **Embedded C** and the **Arduino IDE**.

---

## 📌 About

In this lab, I interfaced various sensors and transducers with the ESP32 to understand:
- Data acquisition
- Signal conditioning
- Analog & digital sensing
- Sensor calibration
- Practical integration of sensors with microcontrollers

The code is written in Embedded C style (using Arduino APIs) and organized by experiment.


---

## 🛠️ Tools & Technologies

- **Microcontroller**: ESP32 (e.g., ESP32-DevKitC, WROOM)
- **Language**: Embedded C (Arduino-style)
- **IDE**: Arduino IDE (with ESP32 board support)
- **Libraries**: Standard Arduino + sensor-specific libraries

---

Install Arduino IDE (if not already):
👉 Download Arduino IDE

Add ESP32 support in Arduino IDE:

Open Arduino IDE

Go to File > Preferences

Add this URL to Additional Boards Manager URLs:

bash
Copy
Edit
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
Go to Tools > Board > Boards Manager and install esp32 by Espressif Systems.

Install required libraries (listed in requirements.txt).

Open any .ino file from the experiments folder in Arduino IDE, select your ESP32 board, and upload.

