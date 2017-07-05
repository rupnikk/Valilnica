sudo avrdude -p t85 -C /home/pi/Valilnica/Software/Power_out/Debug/avrdude_gpio.conf -c pi_1 -B 5 -u -Uflash:w:Power_out.hex:a -Ulfuse:w:0xe2:m -Uhfuse:w:0xdf:m -Uefuse:w:0xff:m

