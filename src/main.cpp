#include <Arduino.h>
#include <FastLED.h> 



#define NUM_LEDS 30         // number of leds
#define modeCt 5
#define upper_TIMEOUT 150

#define LED_PIN           9          //upper
#define LED_PIN2          10         //lower

#define upper             20         // dac1
#define lower             21       // A1
#define thumb             22         // dac1

CRGB leds[NUM_LEDS];
CRGB dupe[NUM_LEDS];
String string;
boolean upperState, upper_flag, upper_hold_flag, lowerState, lower_flag, lower_hold_flag, thumbState, thumb_flag, thumb_hold_flag;
byte upper_counter, lower_counter;
unsigned long upper_timer, lower_timer, thumb_timer;
int mode = 4;
int btn=0, rgb=0;

void setup() {
  delay(1000);
  FastLED.addLeds<WS2812B, LED_PIN2, RGB>(leds, 0,(NUM_LEDS/2)).setCorrection(TypicalLEDStrip);
  //  FastLED.addLeds<WS2812B, 18, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, (NUM_LEDS/2)-1, NUM_LEDS/2).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(96);  // ~40% of LED strip brightness
  
  pinMode(upper, INPUT_PULLUP);
  pinMode(lower, INPUT_PULLUP);
  pinMode(thumb, INPUT_PULLUP);


}

void loop() {
  // put your main code here, to run repeatedly:
  upperTick();
  //lowerTick();
  //thumbTick();  
  
}


void upperTick() {
  upperState = !digitalRead(upper);
  if ( (upperState && !upper_flag) || (string == "rgbx1") ){
    //if (DEBUG) Serial.println(F("RGB BTN PRESS"));
    upper_flag = 1;
    upper_counter++;
    upper_timer = millis();

  }

  if ((!upperState && upper_flag)){
    upper_flag = 0;
    upper_hold_flag = 0;
    
  }

   if ( (upper_flag && upperState && (millis() - upper_timer > upper_TIMEOUT) && !upper_hold_flag)) {
    upper_hold_flag = 1;
    upper_counter = 0;
    //Serial.println("holding");

  }

  if ( ((millis() - upper_timer > upper_TIMEOUT) && (upper_counter != 0)) || (string == "rgbx3") || (string == "rgbx5") ) {
    if (upper_counter == 1) {               // 3 press count
        Serial.println("RGB BTN");
      }
      if (upper_counter == 3) {               // 3 press count

      }
      if ( upper_counter == 5){

          }
        upper_counter = 0;
      }

  }