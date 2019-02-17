
This project starts three FreeRTOS tasks:
* one task for for the LED3;
* one task for the the LED4;
* one task that dumps some memory content on USART1.

To compile it, just setup the libopencm3 and FreeRTOS paths in the makefile and:
`make flash`

To get the UART output, on linux you can start a terminal emulator as minicom:
`minicom -D /dev/ttyACM0 -b 19200` should work.

That is all !
;-)



