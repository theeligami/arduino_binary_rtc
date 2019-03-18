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
 * D11 - D12: first hour digit, first column from the left, numbered bottom to top
 * D21 - D24: second hour digit, second column from the left, numbered bottom to top
 * D31 - D33: first minute digit, third column from the left, numbered bottom to top
 * D41 - D44: second minute digit, fourth column from the left, numbered bottom to top
 */

#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

// First hour digit
#define D11 0
#define D12 1
// Second hour digit
#define D21 2
#define D22 3
#define D23 4
#define D24 5
// First minute digit
#define D31 6
#define D32 7
#define D33 8
// Second minute digit
#define D41 9
#define D42 10
#define D43 11
#define D44 12

const int hourPins[6] = {D11, D12, D21, D22, D23, D24};
const int minutePins[7] = {D31, D32, D33, D41, D42, D43, D44};

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

  int hour1 = now.hour() / 10;      // D1X
  int hour2 = now.hour() % 10;      // D2X
  int minute1 = now.minute() / 10;  // D3X
  int minute2 = now.minute() % 10;  // D4X
  
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

