# Electric RC Motor Dynamometer
By Josh Wall

**Project Version:** `v0.1.0`

## CURRENT STATUS 09-10-2026
All sensors are online and working as intended. 
Currently configuring RC motor to receive signals from ESP32.

## Overview
This is my second portfolio project, following my high voltage fly swatter.
The goal of this project is to characterize an electric RC powertrain by measuring electrical input power, rotational speed, temperature, generator output power, and overall drivetrain efficiency.
Components used in this project include, but are not limited to:
1. 1x BLDC 3650 2300KV RC MOTOR + 80A ESC
2. 1x BRUSHED 775 DC MOTOR as GENERATOR
3. 1x 3:1 GT2 BELT TRANSMISSION
4. 1x ESP32-S3 N16R8
5. 4x 50W RESISTORS (2x 20OHM, 2x 10OHM)
6. 2x INA228 R002 VOLTAGE/CURRENT SENSOR
7. 3x DS18B20 TEMP SENSOR
8. 1x HALL EFFECT SENSOR
9. 18AWG WIRE
10. 22AWG WIRE

## System Architecture
Battery → current sensor → ESC → RC motor → transmission reduction → 775 motor → current sensor → load bank 
With temperature sensors on both motors and esc.
With hall effect sensor on 775 motor side of the transmission.

## Development Status

- [x] ESP32-S3 firmware environment
- [x] DS18B20 temperature sensing
- [x] Hall-effect sensor detection
- [x] INA228 voltage/current measurement
- [x] INA228 measurements verified against Ohm's law
- [x] Dual INA228 integration
- [x] Hall-effect RPM measurement using interrupts
- [X] Three-sensor OneWire temperature bus
- [ ] RC motor control functions programmed
- [ ] OLED interface
- [ ] Data logging
- [ ] Mechanical assembly
- [ ] Full dynamometer testing

## Engineering Goals
This project was designed to develop practical skills in embedded C++, control systems, different communication protocols, powertrain instrumentation, and SolidWorks.

Specific learning goals include:

- Designing and debugging multi-sensor embedded systems using I2C and OneWire communication.
- Measuring voltage, current, temperature, and rotational speed from physical hardware.
- Using interrupts and timing methods for real-time RPM measurement.
- Validating sensor measurements against theoretical calculations and external measurements.
- Integrating electrical, firmware, and mechanical subsystems into a complete test platform.
- Using collected data to characterize motor performance and drivetrain efficiency.

Ironically as a mechanical major, I'm more inclined towards mechatronics and electrical control systems after working on this project for a while. 
