#include <Arduino.h>
#include <SSD1306Brzo.h>
#include <brzo_i2c.h>

#define SSD1306_ADDRESS 0x3C

SSD1306Brzo display(SSD1306_ADDRESS, D1, D2);

volatile uint8_t state;
volatile bool needClear;
volatile uint32_t lastPressMs = 0;

void isr() {
  // Check that this interrupt is not called too soon after
  // previous call. Helps with button contact jitter.
  uint32_t ms = millis();
  if (ms - lastPressMs > 500) {
    state = (state + 1) % 4;
    needClear = true;
    lastPressMs = ms;
  }
}

void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println();
  attachInterrupt(D3, &isr, FALLING);
  display.init();
  display.display();
}

uint8_t sz = 2;
uint8_t iteration = 0;
uint8_t x, y, w, h;

void drawRectangle() {
  x = random(128);
  y = random(64);
  w = random(min(x, 128 - x));
  h = random(min(y, 64 - y));
  display.drawRect(x - w, y - h, w + w, h + h);
}

void drawCircle() {
  x = random(128);
  y = random(64);
  w = random(min(min(x, 128 - x), min(y, 64 - y)));
  display.drawCircle(x, y, w);
}

void drawLine() {
  x = random(128);
  y = random(64);
  int x1 = random(128);
  int y1 = random(64);
  display.drawLine(x, y, x1, y1);
}

void drawSmiley() {
  bool kawaii = true;
  display.fillCircle(70, 32, 30);
  display.setColor(BLACK);
  display.fillCircle(70 - 11, 32 - 7, 6);
  display.fillCircle(70 + 11, 32 - 7, 6);
  display.drawLine(70 - 7, 37, 70 + 6, 37);
  display.drawLine(70 - 7, 37 - 2, 70 - 7, 37 + 2);
  display.drawLine(70 + 6, 37 - 2, 70 + 6, 37 + 2);
  if ((millis() / 1000) % 10 >= 8) {
    display.fillRect(70 - 3, 37, 6, 3);
    display.fillCircle(70, 37 + 3, 2);
    kawaii = false;
  }
  display.setColor(WHITE);
  display.fillCircle(70 - 11 + 2, 32 - 7 - 1, 3);
  display.fillCircle(70 + 11 + 2, 32 - 7 - 1, 3);
  display.drawString(0, (millis()/400)%56, (kawaii)?F("KAWAII"):F("NOPE"));
}

void loop() {
  if (sz == 30 || needClear) {
    needClear = false;
    display.clear();
    sz = 0;
  }
  switch (state) {
  case 0:
    drawRectangle();
    break;
  case 1:
    drawCircle();
    break;
  case 2:
    drawLine();
    break;
  case 3:
    drawSmiley();
    break;
  }
  display.display();
  sz++;
  delay(1);
}
