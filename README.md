Cloud-Enabled IoT Thermal Alert and Logging System:
Project Overview:

The Cloud-Enabled IoT Thermal Alert and Logging System is an embedded IoT project designed to continuously monitor temperature using an LM35 sensor, transmit real-time temperature data to the cloud, and generate alerts when the temperature exceeds a predefined threshold. The system provides both local and remote configuration of temperature set points, ensuring reliable thermal monitoring and safety.

Objective:

To design and implement a cloud-enabled IoT thermal alert and logging system that:

Continuously monitors temperature using embedded sensors.
Transmits real-time data to the cloud for secure logging and visualization.
Generates timely alerts when predefined thermal thresholds are exceeded.
Ensures safety and prevents overheating conditions.

Features:

1.Real-time temperature monitoring using the LM35 sensor.
2.Cloud-based data logging and visualization using ThingSpeak.
3.Configurable temperature set point.
4.Automatic alert generation when temperature exceeds the threshold.
5.Local set point modification using a 4x4 matrix keypad.
6.Remote set point modification through the cloud interface.
7.EEPROM storage for retaining set point values during power failures.
8.LCD display for current temperature and system status.
9.Buzzer alert for nearby personnel during overheating conditions.

Hardware Requirements:

LPC2148 Microcontroller
LM35 Temperature Sensor
AT24C256 EEPROM
4x4 Matrix Keypad
Switch (External Interrupt)
LCD Display
Buzzer
ESP01 Wi-Fi Module
DB-9 Cable / USB-UART Converter

Software Requirements:

Keil C Compiler
Embedded C Programming
Flash Magic
ThingSpeak Cloud Platform

Block Diagram:
## Block Diagram
      +-------------------+
      |  LM35 Temperature |
      |      Sensor       |
      +---------+---------+
                | ADC
                v
      +-----------------------------------+
      |             LPC2148               |
      |         Microcontroller            |
      |                                   |
      |  +------+  +------+  +------+     |
      |  | ADC |  | RTC |  |UART |     |
      |  +------+  +------+  +------+     |
      |                                   |
      |  +------+  +------+  +------+     |
      |  |EINT|  | I/O |  | I2C |     |
      |  +------+  +------+  +------+     |
      +---+--------+--------+-----------+
          |        |        |
          |        |        |
          |        |        +-------------------+
          |        |                            |
          |        v                            v
          |   +-----------+          +----------------+
          |   | Keypad    |          | EEPROM         |
          |   | (4x4)      |          | (AT24C256)     |
          |   +-----------+          +----------------+
          |
          +--------------------+
          | Switch / EINT |
          +----------------+

      +-------------------+       +-------------------+
      | LCD Display       |       | Buzzer / LED     |
      +---------^---------+       +---------^---------+
                | I/O                         | I/O
                +------------+-------------+
                             |
                             v
                   +-------------------+
                   | ESP01 Wi-Fi      |
                   | Module (UART)    |
                   +---------+---------+
                             |
                             v
                   +-------------------+
                   | ThingSpeak Cloud |
                   +---------+---------+
                             |
                             v
                   +-------------------+
                   | Laptop / PC /    |
                   | Mobile           |
                   +-------------------+

Cloud Integration:

The project uses ThingSpeak as the IoT cloud platform for:

1.Real-time temperature data logging.
2.Data visualization through graphs and charts.
3.Remote monitoring of temperature values.
4.Remote updating of temperature set points.
5.Alert notifications when overheating occurs.

Project Workflow:

The LM35 sensor measures temperature and sends the data to the LPC2148 through the ADC. The temperature is displayed on the LCD and uploaded to ThingSpeak at regular intervals. If the temperature exceeds the predefined set point, the system activates the buzzer and sends an alert to the cloud. The set point can be changed locally via keypad or remotely through ThingSpeak, and is stored in EEPROM for reliability during power failures.

Applications:

1.Industrial equipment monitoring.
2.Server room temperature monitoring.
3.Home automation and safety systems.
4.Laboratory temperature monitoring.
5.Cold storage and warehouse monitoring.
