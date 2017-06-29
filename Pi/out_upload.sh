sudo avrdude -p t44 -C /home/pi/avrdude_gpio.conf -c pi_1 -B 5 -u -Uflash:w:Out.hex:a -Ulfuse:w:0xe2:m -Uhfuse:w:0xdf:m -Uefuse:w:0xff:m

