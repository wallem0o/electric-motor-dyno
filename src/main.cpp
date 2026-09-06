#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <INA228.h>

const int LED_PIN = 48;
const int HALL_PIN = 12;
const int ONE_WIRE_BUS = 9;
const int SDA_PIN = 3;
const int SCL_PIN = 46;

Adafruit_NeoPixel boardLed(1, LED_PIN, NEO_GRB + NEO_KHZ800);
OneWire onewire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&onewire);
INA228 ina228_1(0x40);
INA228 ina228_2(0x41);
DeviceAddress thermom_1, thermom_2, thermom_3;

void setup()
{
  Serial.begin(115200);

  boardLed.begin();
  boardLed.setBrightness(100);
  boardLed.setPixelColor(0, 255, 165, 0);
  boardLed.show();

  Serial.println();
  Serial.println("Program initialized...");

  tempSensors.begin();
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(tempSensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
  tempSensors.getAddress(thermom_1, 0);
  tempSensors.getAddress(thermom_2, 1);
  tempSensors.getAddress(thermom_3, 2);

  void printAddress(DeviceAddress deviceAddress);

  Serial.print("Device 0 Address: ");
  printAddress(thermom_1);
  Serial.println();

  Serial.print("Device 1 Address: ");
  printAddress(thermom_2);
  Serial.println();

  Serial.print("Device 2 Address: ");
  printAddress(thermom_3);
  Serial.println();

  pinMode(HALL_PIN, INPUT_PULLUP);

  Wire.setPins(SDA_PIN, SCL_PIN);
  bool success = Wire.begin();

  for (int i = 0; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.println(i, HEX);
    }
  }

  if (success)
  {
    Serial.println("I2C controller initialized.");

    if (ina228_1.begin())
    {
      Serial.println("INA228_1  successfully connected.");
      ina228_1.setMaxCurrentShunt(80, 0.002);
    }
    else
    {
      Serial.println("Failed to connect to INA228_1 sensor.");
    }

    if (ina228_2.begin())
    {
      Serial.println("INA228_2 successfully connected.");
      ina228_2.setMaxCurrentShunt(80, 0.002);
    }
    else
    {
      Serial.println("Failed to connect to INA228_2 sensor.");
      while (1);
    }
  }

  else
  {
    Serial.println("I2C Connection Failed.");
  }

  boardLed.setPixelColor(0, 125, 0, 255);
  boardLed.show();
  Serial.println("Program looping...");
}

void loop()
{
  int hallState = digitalRead(12);

  tempSensors.requestTemperatures();

  float tempC_1 = tempSensors.getTempCByIndex(0);
  Serial.print("DS18B20_1 Temperature: ");
  Serial.print(tempC_1);
  Serial.println("°C");

  float tempC_2 = tempSensors.getTempCByIndex(1);
  Serial.print("DS18B20_2 Temperature: ");
  Serial.print(tempC_2);
  Serial.println("°C");

  float tempC_3 = tempSensors.getTempCByIndex(2);
  Serial.print("DS18B20_3 Temperature: ");
  Serial.print(tempC_3);
  Serial.println("°C");

  Serial.println();

  float busVoltage1 = ina228_1.getBusVoltage();
  float current1 = ina228_1.getCurrent();
  float inaTempC1 = ina228_1.getTemperature();
  float busVoltage2 = ina228_2.getBusVoltage();
  float current2 = ina228_2.getCurrent();
  float inaTempC2 = ina228_2.getTemperature();

  Serial.println("INA 1:");
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER\tTEMP");
  Serial.print(ina228_1.getBusVoltage());
  Serial.print("\t");
  Serial.print(ina228_1.getShuntMilliVolt());
  Serial.print("\t");
  Serial.print(ina228_1.getMilliAmpere());
  Serial.print("\t");
  Serial.print(ina228_1.getMilliWatt());
  Serial.print("\t");
  Serial.print(ina228_1.getTemperature());
  Serial.println();
  Serial.println();

  Serial.println("INA 2:");
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER\tTEMP");
  Serial.print(ina228_2.getBusVoltage());
  Serial.print("\t");
  Serial.print(ina228_2.getShuntMilliVolt());
  Serial.print("\t");
  Serial.print(ina228_2.getMilliAmpere());
  Serial.print("\t");
  Serial.print(ina228_2.getMilliWatt());
  Serial.print("\t");
  Serial.print(ina228_2.getTemperature());
  Serial.println();
  Serial.println();

  delay(1000);
}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}