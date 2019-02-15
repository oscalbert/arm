With this tiny project, you can make blinking the 3 user leds of your nucleo-f729zg board.
It only uses the libopencm3 library.
It is a copy of nucleo-429zi/blink1 project.


There are some details in clock setup and in the link phase to fix, but it blinks !

To build it:

`make CM3_DIR=your_libopencm3_location_path`

To flash it:

`make flash`
