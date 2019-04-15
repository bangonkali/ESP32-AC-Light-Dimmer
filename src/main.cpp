#include <Arduino.h>

#include <RBDdimmer.h> //

// pwm d23
// zero crossing d22
// monitor d21

//#define USE_SERIAL  SerialUSB //Serial for boards whith USB serial port
#define USE_SERIAL Serial
#define outputPin 23
#define zerocross 22 // for boards with CHANGEBLE input pins

dimmerLamp dimmer(outputPin, zerocross); //initialase port for dimmer for ESP8266, ESP32, Arduino due boards
// dimmerLamp dimmer(outputPin); //initialase port for dimmer for MEGA, Leonardo, UNO, Arduino M0, Arduino Zero

#define MONITOR_LED 21

int power = 0;
int direction = 1;
int buttonRed = 0;

int sensorValue = 0;
int interval = 0;
int lastValue = 0;

int serial_monitor_interval = 0;
int dimmer_refresh_interval = 0;

void setup()
{
  pinMode(MONITOR_LED, OUTPUT);
  pinMode(zerocross, INPUT);  // 36
  // pinMode(A0, INPUT);
  pinMode(outputPin, OUTPUT); // 37

  Serial.begin(115200);

  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE)
  // dimmer.setState(ON);
  // dimmer.toggleSettings(0, 100); //Name.toggleSettings(MIN, MAX);
  dimmer.setPower(power);
}

void loop()
{
  sensorValue = analogRead(36);

  dimmer.setPower(map(sensorValue, 0, 4095, 25, 100));

  // if (millis() - dimmer_refresh_interval > 83)
  // {
  //   if (direction == 1)
  //   {
  //     power += 1;
  //     if (power >= 100)
  //     {
  //       direction = 0;
  //     }
  //   }
  //   else
  //   {
  //     power -= 1;
  //     if (power <= 0)
  //     {
  //       direction = 1;
  //     }
  //   }
  //   dimmer.setPower(power);

  //   dimmer_refresh_interval = millis();
  // }

  if (millis() - interval > 300)
  {
    digitalWrite(MONITOR_LED, lastValue);
    lastValue = !lastValue;
    interval = millis();
  }

  if (millis() - serial_monitor_interval > 1000)
  {
    Serial.printf("Power Reading: %d\n", dimmer.getPower());
    Serial.printf("Sensor Reading: %d\n", sensorValue);
    serial_monitor_interval = millis();
  }
  // buttonRed = digitalRead(13);
  // if (buttonRed == 1)
  // {
  //   delay(10);
  //   dimmer.setState(ON); //name.setState(ON/OFF);
  // }
  // if (buttonRed == 0)
  // {
  //   delay(10);
  //   dimmer.setState(OFF); //name.setState(ON/OFF);
  // }
}
