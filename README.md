# Kawaii esp8266 oled test

This is a simple project that I built just to learn how to use PlatformIO and
how to make ESP8266 (NodeMCU dev board in my case) work with SSD1306 powered
OLED screen module using I2C bus.

Dependencies:
* Brzo I2C: `platformio lib install 335`
* ESP8266_SSD1306 driver: `platformio lib install 562`

Note that as of this writing (11/19/2016) latest published version of SSD1306
driver lib has annoying bugs with drawing rectangles that are fixed in trunc [here](https://github.com/squix78/esp8266-oled-ssd1306/commit/3759e51365fadb78955811457295d8b82f90680a)
and [here](https://github.com/squix78/esp8266-oled-ssd1306/commit/abd5e8e57f1b57e43074e44e9ec34a7585d97f15).
You may want to patch those in.

To make it work connect SDA and SCL to D1 and D2 respectively, hook up a button
to pull D3 to the ground and upload the firmware.

On a press of a button the programm will circulate between following modes:
* Draw random rectangles
* Draw random circles
* Draw random lines
* Draw a kawaii face (with a trick)

ESP8266 is fast enough to provide very decent fps. The screen driver lib is also
quite optimized so the first 3 modes will be very fast.

![Picture of a kawaii face](https://raw.githubusercontent.com/qu1ck/nodemcu_kawaii_oled_test/master/resources/demo1.jpg)
