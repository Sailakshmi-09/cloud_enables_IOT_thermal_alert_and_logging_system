Cloud-Enabled IoT Thermal Alert and Logging System:
Project Overview:

The Cloud-Enabled IoT Thermal Alert and Logging System is an embedded IoT project designed to continuously monitor temperature using an LM35 sensor, transmit real-time temperature data to the cloud, and generate alerts when the temperature exceeds a predefined threshold. The system provides both local and remote configuration of temperature set points, ensuring reliable thermal monitoring and safety.

Objective:

To design and implement a cloud-enabled IoT thermal alert and logging system that:

Continuously monitors temperature using embedded sensors.
Transmits real-time data to the cloud for secure logging and visualization.
Generates timely alerts when predefined thermal thresholds are exceeded.
Ensures safety and prevents overheating conditions.
Features
Real-time temperature monitoring using the LM35 sensor.
Cloud-based data logging and visualization using ThingSpeak.
Configurable temperature set point.
Automatic alert generation when temperature exceeds the threshold.
Local set point modification using a 4x4 matrix keypad.
Remote set point modification through the cloud interface.
EEPROM storage for retaining set point values during power failures.
LCD display for current temperature and system status.
Buzzer alert for nearby personnel during overheating conditions.

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
System Working:
1.The LM35 sensor continuously measures the ambient temperature.
2.The LPC2148 reads the analog temperature value through its inbuilt ADC.
3.The measured temperature is displayed on the LCD.
4.At predefined intervals, the temperature data is transmitted to the ThingSpeak cloud.
5.The system compares the current temperature with the stored set point.
6.If the temperature exceeds the set point:
An alert is sent to the cloud through a dedicated alert field.
The buzzer is activated locally to warn nearby personnel.
7.The set point can be updated:
Locally using the keypad and external interrupt.
Remotely through a dedicated ThingSpeak channel.
8.Updated set points are stored in EEPROM to retain configuration during power loss.

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

Real-time temperature data logging.
Data visualization through graphs and charts.
Remote monitoring of temperature values.
Remote updating of temperature set points.
Alert notifications when overheating occurs.

Project Workflow:

Initialize all peripherals (LCD, Keypad, UART, ADC, EEPROM, ESP01).
Read the initial set point from EEPROM.
Continuously monitor temperature using the LM35 sensor.
Display the current temperature on the LCD.
Send temperature data to ThingSpeak at regular intervals.
Compare the current temperature with the set point.
Trigger cloud and local alerts if overheating is detected.
Periodically check for remote set point updates from ThingSpeak.
Update EEPROM whenever the set point is changed.

Future Enhancements:

Add SMS or email alert notifications.
Integrate a mobile application for monitoring and control.
Support multiple temperature sensors for zone-based monitoring.
Implement data analytics for predictive maintenance.
Add battery backup for uninterrupted operation.

Applications:

Industrial equipment monitoring.
Server room temperature monitoring.
Home automation and safety systems.
Laboratory temperature monitoring.
Cold storage and warehouse monitoring.
