#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <Tone.h>
#define PIN 9
Tone freq1;

int d = 20;
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(135, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
bool blue = false;
int counter = 0;
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  Serial.begin(9600);
  freq1.begin(11);
  pinMode(7, OUTPUT);
  pinMode(4, INPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  while (!digitalRead(4)) {
    rest();
  }
  d = 100;
  while (digitalRead(4)) {
    charging();
  }
  fire();
}
void fire(){
   for (uint16_t i = 0; i < 135; i += 1) {
    strip.setPixelColor(i, strip.Color(150, 0, 255));
  }
  strip.show();
  digitalWrite(7,HIGH); 
freq1.play(250, map(d, 100,10,100,1000));

  delay(map(d, 100,10,100,1000));
  digitalWrite(7,LOW); 

}
void ring1(bool state) {
  if (state) {
    for (uint16_t i = 7; i < 25; i += 1) {
      strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
  }
  else {
    for (uint16_t i = 7; i < 25; i += 1) {
      strip.setPixelColor(i, strip.Color(0, 0, 255));
    }
  }
}
void ring2(bool state) {
  if (state) {
    for (uint16_t i = 50; i < 68; i += 1) {
      strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
  }
  else {
    for (uint16_t i = 50; i < 68; i += 1) {
      strip.setPixelColor(i, strip.Color(0, 0, 255));
    }
  }
}

void ring3(bool state) {
  if (state) {
    for (uint16_t i = 68; i < 86; i += 1) {
      strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
  }
  else {
    for (uint16_t i = 68; i < 86; i += 1) {
      strip.setPixelColor(i, strip.Color(0, 0, 255));
    }
  }
}
void ring4(bool state) {
  if (state) {
    for (uint16_t i = 86; i < 104; i += 1) {
      strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
  }
  else {
    for (uint16_t i = 86; i < 104; i += 1) {
      strip.setPixelColor(i, strip.Color(0, 0, 255));
    }
  }
}
void all_blue() {
  for (uint16_t i = 0; i < 7; i += 1) {
    strip.setPixelColor(i, strip.Color(0, 0, 255));
  }
  for (uint16_t i = 25; i < 50; i += 1) {
    strip.setPixelColor(i, strip.Color(0, 0, 255));
  }
  for (uint16_t i = 104; i < 135; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 255));
  }
}

void charging() {
  ring1(true);
  ring2(false);
  ring3(false);
  ring4(false);
  bottom();
  strip.show();
  freq1.play(map(d,100,10,800,1500), d);
  delay(d);
  ring1(false);
  ring2(true);
  ring3(false);
  ring4(false);
  bottom();
  strip.show();
   freq1.play(map(d,100,10,800,1500), d);
     delay(d);
  ring1(false);
  ring2(false);
  ring3(true);
  ring4(false);
  bottom();
  strip.show();
  freq1.play(map(d,100,10,800,1500), d);
    delay(d);

  ring1(false);
  ring2(false);
  ring3(false);
  ring4(true);
  bottom();
  strip.show();
  freq1.play(map(d,100,10,800,1500), d);
    delay(d);

  d -= 10;
  if (d < 10) d = 10;
}

void bottom() {
  all_blue();
  first();
  second();
  third();
  fourth();
  ring();
  counter++;
  if (counter == 5) counter = 0;
}

void first() {
  for (uint16_t i = 0; i < 7; i ++) {
    if (((counter - i) % 4) == 0) strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
}
void second() {
  for (uint16_t i = 34; i > 24; i--) {
    if (((counter + i) % 4) == 0) strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
}
void third() {
  for (uint16_t i = 34; i < 43; i ++) {
    if (((counter - i) % 4) == 0) strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
}
void fourth() {
  for (uint16_t i = 49; i > 42; i--) {
    if (((counter + i) % 4) == 0) strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
}
void ring() {
  for (uint16_t i = 104; i < 135; i++) {
    if (((counter + i) % 4) == 0) strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
}
void rest() {
  for (uint16_t i = 0; i < 104; i += 1) {
    strip.setPixelColor(i, strip.Color(0, 10, 50));
  }
  for (uint16_t i = 104; i < 135; i += 1) {
    strip.setPixelColor(i, strip.Color(0, 10, 50));

  }
  strip.show();
}

