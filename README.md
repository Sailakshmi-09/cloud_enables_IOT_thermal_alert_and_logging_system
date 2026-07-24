Cloud-Enabled IoT Thermal Alert and Logging System:
Project Overview:

The Cloud-Enabled IoT Thermal Alert and Logging System is an embedded IoT project designed to continuously monitor temperature using an LM35 sensor, transmit
real-time temperature data to the cloud, and generate alerts when the temperature exceeds a predefined threshold. The system provides both local and remote configuration of temperature set points, ensuring reliable thermal monitoring and safety.

Objective:

To design and implement a cloud-enabled IoT thermal alert and logging system that:

Continuously monitors temperature using embedded sensors.
Transmits real-time data to the cloud for secure logging and visualization.
Generates timely alerts when predefined thermal thresholds are exceeded.
Ensures safety and prevents overheating conditions.

Flow diagram:

<img width="1024" height="1536" alt="image" src="https://github.com/user-attachments/assets/52b6c3a6-0e6d-4ee8-99d4-7ae08693fd32" />


Features:

* Real-time temperature monitoring using the LM35 sensor.
* Cloud-based data logging and visualization using ThingSpeak.
* Configurable temperature set point.
* Automatic alert generation when temperature exceeds the threshold.
* Local set point modification using a 4x4 matrix keypad.
* Remote set point modification through the cloud interface.
* EEPROM storage for retaining set point values during power failures.
* LCD display for current temperature and system status.
* Buzzer alert for nearby personnel during overheating conditions.

Hardware Requirements:

🖥️ LPC2148 Microcontroller

🌡️ LM35 Temperature Sensor

💾 AT24C256 EEPROM

⌨️ 4×4 Matrix Keypad

🔘 Switch (External Interrupt)

📟 LCD Display

🔊 Buzzer

📶 ESP01 Wi-Fi Module

🔌 DB-9 Cable / USB-UART Converter

Software Requirements:

💻 Keil C Compiler

⚙️ Embedded C Programming

⚡ Flash Magic

☁️ ThingSpeak Cloud Platform

Block Diagram:

<img width="1515" height="1038" alt="ChatGPT Image Jul 24, 2026, 05_32_37 PM" src="https://github.com/user-attachments/assets/b619456d-1694-4d57-a061-9a5eeeb327ca" />


                   

Cloud Integration:

The project uses ThingSpeak as the IoT cloud platform for:

* Real-time temperature data logging.
* Data visualization through graphs and charts.
* Remote monitoring of temperature values.
* Remote updating of temperature set points.
* Alert notifications when overheating occurs.

Project Workflow:

The LM35 sensor measures temperature and sends the data to the LPC2148 through the ADC. The temperature is displayed on the LCD and uploaded to ThingSpeak at regular intervals. If the temperature exceeds the predefined set point, the system activates the buzzer and sends an alert to the cloud. The set point can be changed locally via keypad or remotely through ThingSpeak, and is stored in EEPROM for reliability during power failures.

Applications:

* Industrial equipment monitoring
* Server room temperature monitoring.
* Home automation and safety systems.
* Laboratory temperature monitoring.
* Cold storage and warehouse monitoring.
