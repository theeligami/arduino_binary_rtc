## A binary real-time-clock using an Arduino Uno and a RTC_DS3231

This clock will display the time on some LEDs in binary format.
For the best results, please make sure to follow the layout plan and the schematic.

__This is a work in progress! I am not responsible for any damages to you or your property if you attempt to build this project yourself!__

____

### Requirements:
For the code to work you will need adafruit's [RTClib](https://github.com/adafruit/RTClib). Just follow their instructions to install it and you're good to go.

___

### Note:
I am also working on a wall-mount version of the clock as well as a custom pcb. Instead of a DS3231 a DCF-77 time signal receiver will be used by the new circuit.
The project will also be ported to pure C instead of Arduino C++ in the future. For more information check out the "kicad" directory.

___

### Known Issues:
__The time displayed on the clock is off or from the wrong time zone:__

This is due to the \__DATE__ variable (which is used by the DS3231) in your system being wrong. Check if your UEFI/BIOS time is set correctly.
You can set you timezone with the help of the TIMEZONE macro. TIMEZONE will be added to the hours variable.


_Feel free to report errors and bugs or give input on possible optimizations!_
