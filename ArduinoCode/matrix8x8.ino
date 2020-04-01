#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 50 

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 14
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
  Serial.begin(57600);
  Serial.println("resetting");
  LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(84);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }


uint16_t A[] = {0b0000000111,0b0000000101, 0b0000000111, 0b0000000101, 0b0000000101 };
uint16_t B[] = {0b0000000111,0b0000000101, 0b0000000011, 0b0000000101, 0b0000000111 };
uint16_t C[] = {0b0000000111,0b0000000001, 0b0000000001, 0b0000000001, 0b0000000111 };
uint16_t D[] = {0b0000000011,0b0000000101, 0b0000000101, 0b0000000101, 0b0000000011 };
uint16_t E[] = {0b0000000111,0b0000000001, 0b0000000111, 0b0000000001, 0b0000000111 };
uint16_t F[] = {0b0000000111,0b0000000001, 0b0000000111, 0b0000000101, 0b0000000001 };
uint16_t G[] = {0b0000000111,0b0000000001, 0b0000000101, 0b0000000101, 0b0000000111 };
uint16_t H[] = {0b0000000101,0b0000000101, 0b0000000111, 0b0000000101, 0b0000000101 };
uint16_t I[] = {0b0000000111,0b0000000010, 0b0000000010, 0b0000000010, 0b0000000111 };
uint16_t J[] = {0b0000000011,0b0000000001, 0b0000000001, 0b0000000101, 0b0000000111 };
uint16_t K[] = {0b0000000101,0b0000000101, 0b0000000011, 0b0000000101, 0b0000000101 };
uint16_t L[] = {0b0000000001,0b0000000001, 0b0000000001, 0b0000000001, 0b0000000111 };

void writeLetter(uint16_t letter[] )
{
  for(int i = 0; i < 5; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      if(i % 2 == 0)
      {
         
        if(letter[i] & (1 << j))
        {
          leds[i * 10 + j] = CHSV(0, 255, 255);
        }
        else
        {
          leds[i * 10 + j] = CRGB::Black;
        }
        
      }
      else
      {
      // = CHSV(0, letter[i] & (1 << j) ? 0 : 255, letter[i] & (1 << j)? 0 : 255);
      if(letter[i] & (1 << j))
        {
          leds[i * 10 + (9 - j)] = CHSV(0, 255, 255);
        }
        else
        {
          leds[i * 10 + (9 - j)] = CRGB::Black;
        }
      }
    }
  }
  FastLED.show();
  
}

void slideLetter(uint16_t letter[])
{
  for(int k = 0; k < 10; k++)
  {
  for(int i = 0; i < 5; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      if(i % 2 == 0)
      {
         
        if(letter[i] & (1 << j))
        {
          leds[i * 10 + ((j + k) % 10)] = CHSV(0, 255, 255);
        }
        else
        {
          leds[i * 10 + ((j + k) % 10)] = CRGB::Black;
        }
        
      }
      else
      {
      // = CHSV(0, letter[i] & (1 << j) ? 0 : 255, letter[i] & (1 << j)? 0 : 255);
      if(letter[i] & (1 << j))
        {
          leds[i * 10 + (9 - ((j + k) % 10))] = CHSV(0, 255, 255);
        }
        else
        {
          leds[i * 10 + (9 - ((j + k) % 10))] = CRGB::Black;
        }
      }
    }
  }
  FastLED.show();
  delay(750);
  }
}

void colourswapsnake()
{
  static uint8_t hue = 0;
  Serial.print("x");
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  Serial.print("x");

  // Now go in the other direction.  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
}

void colourswap()
{
  static uint8_t hue = 0;
  Serial.print("x");
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    
  }
  hue += 10;//change the colour every loop to a different colour
  delay(500);
}

void instantrandom()
{
  static uint8_t hue = 0;
  Serial.print("x");
  
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    hue = random(255);//set every pixel the colour to a different value
    
    leds[i] = CHSV(hue, 255, 255);
    // Show the leds
    FastLED.show(); 
    fadeall();
    // Wait a little bit before we loop around and do it again
    
  }
  delay(10);  
}

void intertwine(uint8_t colour)
{
 
    for (int i = 0; i < 10; i++)
    {
      leds[i] = CHSV(colour, 255, 255);
      leds[i + 10] = CHSV(colour, 255, 255);
      leds[i + 20] = CHSV(colour, 255, 255);
      leds[i + 30] = CHSV(colour, 255, 255);
      leds[i + 40] = CHSV(colour, 255, 255);
      FastLED.show();
      fadeall();
      delay(100);
    }
  
}

void intertwineclear()
{
  for (int i = 0; i < 10; i++)
    {
      leds[i] = CHSV(0, 0, 0);
      leds[i + 10] = CHSV(0, 0, 0);
      leds[i + 20] = CHSV(0, 0, 0);
      leds[i + 30] = CHSV(0, 0, 0);
      leds[i + 40] = CHSV(0, 0, 0);
      FastLED.show();
      fadeall();
      delay(100);
    }
}

void interTwineColourChange()
{
  int hue = 0;
  while(hue < 255)
  {
    intertwine(hue%255);
    hue+=20;
    intertwineclear();
  }
    
}

void loop() { 
  interTwineColourChange();
  delay(1000);
  instantrandom();
  delay(1000);
  colourswap();
  delay(1000);
  colourswapsnake();
  writeLetter(H);
  delay(750);
  writeLetter(A);
  delay(750);
  writeLetter(I);
  delay(1000);
  slideLetter(A);
}
