/*
<A binary realtime clock using a DST3231_RTC-chip>
Copyright (C) <2019>  <Elias Kleimeier>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/*
 * Pins connections:
 * LED11 - LED12: first hour digit, first column from the left, numbered bottom to top
 * LED21 - LED24: second hour digit, second column from the left, numbered bottom to top
 * LED31 - LED33: first minute digit, third column from the left, numbered bottom to top
 * LED41 - LED44: second minute digit, fourth column from the left, numbered bottom to top
 */

#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

// First hour digit
#define LED11 0
#define LED12 1
// Second hour digit
#define LED21 2
#define LED22 3
#define LED23 4
#define LED24 5
// First minute digit
#define LED31 6
#define LED32 7
#define LED33 8
// Second minute digit
#define LED41 9
#define LED42 10
#define LED43 11
#define LED44 12

const int hourPins[6] = {LED11, LED12, LED21, LED22, LED23, LED24};
const int minutePins[7] = {LED31, LED32, LED33, LED41, LED42, LED43, LED44};

void setup() 
{
  Serial.begin(9600);
  delay(3000); // Wait for console opening

  if (! rtc.begin()) 
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
    
  // Set LED pins to OUTPUT
  for (int i = 0; i < 13; i++)
  {
    pinMode(i, OUTPUT);
  }
  Serial.end(); // RX and TX needed for LEDs instead of serial
}

void loop()
{
  DateTime now = rtc.now();

  int hour1 = now.hour() / 10;      // LED1X
  int hour2 = now.hour() % 10;      // LED2X
  int minute1 = now.minute() / 10;  // LED3X
  int minute2 = now.minute() % 10;  // LED4X
  // First hour digit
  for (int c = 1, k = 0; c >= 0; c--) 
  {
    k = hour1 >> c;

    if (k & 1) 
    {
      digitalWrite(hourPins[c], HIGH);
    }
    else 
    {
      digitalWrite(hourPins[c], LOW);
    }
  }

  // Second hour digit
  for (int c = 3, k = 0; c >= 0; c--) 
  {
    k = hour2 >> c;

    if (k & 1) 
    {
      digitalWrite(hourPins[c + 2], HIGH);
    }
    else 
    {
      digitalWrite(hourPins[c + 2], LOW);
    }
  }
  
  // First minute digit
  for (int c = 2, k = 0; c >= 0; c--) 
  {
    k = minute1 >> c;

    if (k & 1) 
    {
      digitalWrite(minutePins[c], HIGH);
    }
    else 
    {
      digitalWrite(minutePins[c], LOW);
    }
  }
  
  // Second minute digit
  for (int c = 3, k = 0; c >= 0; c--) 
  {
    k = minute2 >> c;

    if (k & 1) 
    {
      digitalWrite(minutePins[c + 3], HIGH);
    }
    else 
    {
      digitalWrite(minutePins[c + 3], LOW);
    }
  }
}

