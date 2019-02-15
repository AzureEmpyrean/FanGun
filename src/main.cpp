#include <Arduino.h>
#include <FastLED.h> 



#define NUM_LEDS 16         // number of leds
#define modeCt 5
#define upper_TIMEOUT 150

#define LED_PIN           16          //upper
#define LED_PIN2          17         //lower

#define upper             21         // dac1
#define lower             22       // A1
#define thumb             20         // dac1
#define fans              23

uint8_t gHue = 0;
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB dupe[NUM_LEDS];
String string;
boolean upperState, upper_flag, upper_hold_flag, lowerState, lower_flag, lower_hold_flag, thumbState, thumb_flag, thumb_hold_flag;
byte upper_counter, lower_counter;
unsigned long upper_timer, lower_timer, thumb_timer;
int mode = 4;
int btn=0, rgb=0;

void setup() {
  delay(1000);


  FastLED.addLeds<WS2812B, LED_PIN2, RGB>(leds2, 0,NUM_LEDS).setCorrection(TypicalLEDStrip);
  //  FastLED.addLeds<WS2812B, 18, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds1, 0, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(96);  // ~40% of LED strip brightness
  pinMode(fans, OUTPUT);
  pinMode(upper, INPUT_PULLUP);
  pinMode(lower, INPUT_PULLUP);
  pinMode(thumb, INPUT_PULLUP);
  digitalWrite(fans, LOW);
  //digitalWrite(fans, HIGH);

 // fill_solid(leds1, NUM_LEDS, CRGB::White);
 // FastLED.show();

}

void upperTick();
void lowerTick();
void thumbTick(); 
void juggle();
void sinelon();
void bpm();
void Fans();

void loop() {
  EVERY_N_MILLISECONDS( 20 ) { gHue++; }
  // put your main code here, to run repeatedly:
  // sinelon();
  //juggle();
  bpm();
  upperTick(); 
  //lowerTick();
  //thumbTick();  
  Fans();
  FastLED.show();
  //digitalWrite(fans, HIGH);
  //delay(2000);
  //digitalWrite(fans, LOW);
  //delay(2000);
}

void Fans() {
  if(upper_hold_flag == 1){
    digitalWrite(fans, HIGH);
    Serial.println("fanning");
  }
  if(upper_hold_flag == 0)
    digitalWrite(fans, LOW);
}

void upperTick() {
  upperState = !digitalRead(upper);
  if ( (upperState && !upper_flag) || (string == "upperx1") ){
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
    Serial.println("holding");
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

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds1, NUM_LEDS, 20);
  fadeToBlackBy( leds2, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds1[pos] += CHSV( gHue, 255, 192);
  leds2[pos] += CHSV( gHue, 255, 192);
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds1, NUM_LEDS, 20);
  fadeToBlackBy( leds2, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds1[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    leds2[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}


void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds1[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    leds2[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}



