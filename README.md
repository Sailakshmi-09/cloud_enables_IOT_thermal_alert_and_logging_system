## 🌡️ Cloud-Enabled IoT Thermal Alert and Logging System:

# 🌡️ Cloud-Enabled IoT Thermal Alert and Logging System

## 📖 Overview

## 🎯 Aim

## 🔄 Flow Diagram

## ✨ Features

## 🛠️ Hardware Requirements

## 💻 Software Requirements

## 🏗️ System Architecture

## 🖼️ Block Diagram

## ⚙️ Working Principle

## 📂 Project Structure

## 🚀 Implementation Steps

## 🎓 Learning Outcomes

## 🔮 Future Enhancements

## 🚀 Applications

## 👨‍💻 Author

## 📄 License

## 📖 Overview

The **Cloud-Enabled IoT Thermal Alert and Logging System** is an embedded IoT project based on the **LPC2148 ARM7 microcontroller** that continuously monitors ambient temperature using an **LM35 sensor**. The measured temperature is displayed on an LCD and transmitted to the **ThingSpeak Cloud** via the **ESP01 Wi-Fi module** for real-time monitoring and data logging. The system supports configurable temperature thresholds, automatic overheat alerts, and both local and remote set-point configuration, providing a reliable solution for intelligent thermal monitoring.

## 🎯 Aim:

To design and implement an IoT-based thermal monitoring system capable of continuously measuring temperature, storing real-time data on the cloud, generating alerts when the temperature exceeds a predefined threshold, and allowing both local and remote configuration of temperature set points.

## Flow diagram:

<img width="1024" height="1536" alt="image" src="https://github.com/user-attachments/assets/52b6c3a6-0e6d-4ee8-99d4-7ae08693fd32" />



 ## ✨ Features

- 🌡️ Real-time temperature monitoring using the LM35 sensor.
- ☁️ Cloud-based temperature logging using ThingSpeak.
- 📈 Live data visualization through graphs.
- 🔔 Automatic buzzer alert during overheating.
- 📟 LCD display for temperature and system status.
- ⌨️ Local set-point configuration using a 4×4 matrix keypad.
- 🌐 Remote set-point modification via the cloud.
- 💾 EEPROM storage for retaining set-point values after power failure.
- 📶 Wireless communication using the ESP01 Wi-Fi module.
- ⚡ Reliable and continuous thermal monitoring.
 
 ## 🛠️ Hardware Requirements

- 🖥️ LPC2148 ARM7 Microcontroller
- 🌡️ LM35 Temperature Sensor
- 💾 AT24C256 EEPROM
- ⌨️ 4×4 Matrix Keypad
- 🔘 External Interrupt Switch
- 📟 16×2 LCD Display
- 🔊 Buzzer
- 📶 ESP01 Wi-Fi Module
- 🔌 DB-9 Cable / USB-UART Converter
- 🔋 5V DC Power Supply

 ## 💻 Software Requirements

- 💻 Keil µVision IDE
- ⚙️ Embedded C Programming
- ⚡ Flash Magic
- ☁️ ThingSpeak Cloud Platform
- 🪟 Windows Operating System

## 🏗️ System Architecture

The **LPC2148 ARM7 microcontroller** acts as the central controller of the system. The **LM35 sensor** measures the ambient temperature and sends analog data to the LPC2148's ADC. The processed temperature is displayed on the **16×2 LCD** and uploaded to the **ThingSpeak Cloud** via the **ESP01 Wi-Fi module** using UART communication. The **AT24C256 EEPROM** stores the temperature set-point, while the **4×4 keypad** and **external interrupt switch** allow local configuration. If the temperature exceeds the set threshold, the system activates the **buzzer** and sends an alert to the cloud.

## Block Diagram:

<img width="1515" height="1038" alt="ChatGPT Image Jul 24, 2026, 05_32_37 PM" src="https://github.com/user-attachments/assets/b619456d-1694-4d57-a061-9a5eeeb327ca" />



## ⚙️ Working Principle

- The **LPC2148 ARM7 microcontroller** initializes all connected peripherals, including the ADC, UART, I²C, LCD, EEPROM, and ESP01 Wi-Fi module.
- The previously stored **temperature set point** is retrieved from the **AT24C256 EEPROM** during system startup.
- The **LM35 temperature sensor** continuously measures the ambient temperature and sends an analog voltage to the LPC2148.
- The built-in **ADC (Analog-to-Digital Converter)** converts the analog temperature signal into digital data for processing.
- The measured temperature is displayed on the **16×2 LCD** in real time.
- The **ESP01 Wi-Fi module** transmits the temperature data to the **ThingSpeak Cloud** at regular intervals.
- The microcontroller compares the current temperature with the configured **set-point value**.
- If the measured temperature exceeds the predefined threshold:
  - 🔔 The **buzzer** is activated to provide a local alert.
  - ☁️ An **alert notification** is sent to the ThingSpeak Cloud.
- Users can update the temperature set point:
  - ⌨️ **Locally** using the 4×4 matrix keypad.
  - 🌐 **Remotely** through the ThingSpeak Cloud.
- Any updated set-point value is saved in the **EEPROM**, ensuring it is retained even after a power failure.
- The entire process repeats continuously, providing reliable **real-time temperature monitoring, cloud logging, and thermal alert generation**.

## 📂 Project Structure

```text
Cloud-Enabled-IoT-Thermal-Alert-System/
│
├── README.md
├── main.c
├── adc.c
├── adc.h
├── lcd.c
├── lcd.h
├── uart.c
├── uart.h
├── esp01.c
├── esp01.h
├── rtc.c
├── rtc.h
├── i2c.c
├── i2c.h
├── eeprom.c
├── eeprom.h
├── keypad.c
├── keypad.h
├── interrupt.c
├── interrupt.h
├── delay.c
├── delay.h
├── headers/
├── images/
└── docs/
```
## 🚀 Implementation Steps

1. 📝 Design the hardware circuit and identify all required components.
2. 🔌 Interface the **LM35 sensor, LCD, EEPROM, ESP01, Keypad, and Buzzer** with the **LPC2148 ARM7 microcontroller**.
3. 🌡️ Configure the **ADC** to acquire temperature data from the LM35 sensor.
4. 📟 Interface and test the **16×2 LCD** to display temperature readings and system status.
5. 📡 Configure **UART communication** for data exchange between the LPC2148 and the ESP01 Wi-Fi module.
6. 💾 Implement **I²C communication** to read and write temperature set-point values in the **AT24C256 EEPROM**.
7. ⌨️ Develop the **4×4 matrix keypad** and **external interrupt** routines for local set-point configuration.
8. ☁️ Configure the **ThingSpeak Cloud** to receive, store, and visualize real-time temperature data.
9. ⚙️ Implement the main application logic for **temperature monitoring, threshold comparison, cloud communication, and alert generation**.
10. 🧪 Test, debug, and validate the complete system to ensure reliable real-time monitoring and cloud connectivity.

 ## 🎓 Learning Outcomes

- 🖥️ Gained hands-on experience in programming the **LPC2148 ARM7 microcontroller** using Embedded C.
- ⚙️ Developed practical skills in **Embedded C programming** for real-time applications.
- 🌡️ Learned **ADC interfacing** for acquiring temperature data from the **LM35 sensor**.
- 📡 Understood **UART communication** by interfacing the ESP01 Wi-Fi module with the microcontroller.
- 💾 Implemented **I²C communication** to read from and write data to the **AT24C256 EEPROM**.
- 📟 Acquired knowledge of **LCD interfacing** and **4×4 matrix keypad programming** for user interaction.
- ☁️ Explored **IoT cloud integration** using the **ThingSpeak platform** for real-time data logging and visualization.
- 🔄 Learned the design and implementation of **real-time embedded systems** for continuous monitoring applications.
- 🚨 Developed an understanding of **IoT-based thermal monitoring and alert systems** with automatic threshold detection.
- 🔒 Gained experience in **EEPROM data management**, ensuring persistent storage of configuration parameters during power failures.
  
## 🔮 Future Enhancements

- 📱 Develop a **mobile application** for real-time temperature monitoring and remote control.
- 📩 Integrate **SMS, Email, and Push Notifications** for instant thermal alerts.
- 🔥 Support **multi-sensor temperature monitoring** for larger industrial and commercial environments.
- 🌡️ Extend the system to monitor **temperature and humidity** using sensors such as **DHT22**.
- 📊 Implement an **advanced analytics dashboard** with historical trends, reports, and performance insights.
- 🤖 Incorporate **AI and Machine Learning** for predictive thermal analysis and anomaly detection.
- 🔐 Enhance system security with **user authentication**, encrypted communication, and secure cloud access.
- ☀️ Enable **solar-powered deployment** for remote and off-grid monitoring applications.
- 🌍 Support multiple IoT cloud platforms such as **AWS IoT, Azure IoT Hub, and Blynk**.
- 📡 Add **OTA (Over-the-Air) firmware updates** for remote software maintenance and upgrades.

## 👨‍💻 Author

Kuppireddy Sailakshmi

## 📄 License

This project is licensed. You are free to use, modify, and distribute this project for educational and personal purposes.
