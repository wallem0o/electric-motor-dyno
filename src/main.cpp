#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <INA228.h>

const int ledPin = 48;
const int hallPin = 12;
const int tempPin = 10;
const int sdaPin = 3;
const int sclPin = 46;

Adafruit_NeoPixel boardLed(1, ledPin, NEO_GRB + NEO_KHZ800);
OneWire onewire(tempPin);
DallasTemperature tempSensors(&onewire);
INA228 currSensor(0x40);

void setup()
{
  Serial.begin(115200);
  tempSensors.begin();
  pinMode(hallPin, INPUT_PULLUP);
  bool success = Wire.begin(sdaPin, sclPin, 100000);

  if (success)
  {
    Serial.println("I2C bus successfullly connected");
    

    if (currSensor.begin())
    {
      Serial.println("Current sensor successfully connected.");
      currSensor.setMaxCurrentShunt(80, 0.002);
    }
    else {
      Serial.println("Failed to connect to current sensor.");
      while(1);
    }
  }

  else
  {
    Serial.println("I2C Connection Failed.");
  }

  boardLed.begin();
  boardLed.setPixelColor(0, 160, 32, 240);
  boardLed.setBrightness(100);
  boardLed.show();
  Serial.println("Program initialized");
}

void loop()
{

  int hallState = digitalRead(12);
  tempSensors.requestTemperatures();

  float tempC = tempSensors.getTempCByIndex(0);
  Serial.print("DS18B20 Temperature: ");
  Serial.print(tempC);
  Serial.println("°C");

  float busVoltage = currSensor.getBusVoltage();
  float current = currSensor.getCurrent();
  float inaTempC = currSensor.getTemperature();

  Serial.print("Bus Voltage: ");
  Serial.print(busVoltage, 3);
  Serial.println("V");

  Serial.print("Current: ");
  Serial.print(current, 3);
  Serial.println("A");

  Serial.print("INA228 Temperature: ");
  Serial.print(inaTempC, 3);
  Serial.println("°C");
}
