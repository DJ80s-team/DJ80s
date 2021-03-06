#include <Adafruit_NeoPixel.h>

#define PIN_R 8
#define PIN_Y 9
#define PIN_G 10
#define PIN_B 11

Adafruit_NeoPixel neon_r = Adafruit_NeoPixel(60, PIN_R, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neon_b = Adafruit_NeoPixel(60, PIN_B, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neon_y = Adafruit_NeoPixel(60, PIN_Y, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neon_g = Adafruit_NeoPixel(60, PIN_G, NEO_GRB + NEO_KHZ800);


//const int outputPin = 12;
int potPin = 0;
int sensorVal = 0;
int prevVal = 0;
String inputString = "";

//int ledPin [] = {8,9,10,11};
int buttons [] = {4,5,6,7};
int buttonState [4];

//these pins can not be changed 2/3 are special pins
int encoderPin1 = 2;
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

boolean pushed [] = {false,false,false,false};

void setup()
{
  
  neon_r.begin();
  neon_r.setPixelColor(0,neon_r.Color(255, 23, 107));
  neon_r.show();
  pinMode(PIN_R, OUTPUT);
  
  neon_b.begin();
  neon_b.setPixelColor(0,neon_b.Color(26, 130, 255));
  neon_b.show();
  pinMode(PIN_B, OUTPUT);
  
  neon_y.begin();
  neon_y.setPixelColor(0,neon_y.Color(255, 222, 29));
  neon_y.show();
  pinMode(PIN_Y, OUTPUT);
  
  neon_g.begin();
  neon_g.setPixelColor(0,neon_g.Color(33, 237, 112));
  neon_g.show();
  pinMode(PIN_G, OUTPUT);
  
// 
//  for(int i=0; i<4; i++){
//    pinMode(ledPin[i], OUTPUT);
//  }
  
//  pinMode(outputPin, OUTPUT);
  Serial.begin(57600);
  
  for(int i=0; i<4; i++){
//    pinMode(ledPin[i], OUTPUT);
    pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);
  }
//  pinMode(soundPin, OUTPUT);
  
  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
}
 
void loop()
{
   //noTone(soundPin);
  for(int i=0; i<4; i++)
    buttonState[i] = digitalRead(buttons[i]);
    
    if((encoderValue - prevVal)>0){
      if(abs((encoderValue - prevVal))>15){
        Serial.print('B');
        Serial.print("left");
        Serial.print('E');
        
        prevVal = encoderValue;
      }
    }else if((encoderValue - prevVal)<0){
      if(abs((encoderValue - prevVal))>15){
        Serial.print('B');
        Serial.print("right");
        Serial.print('E');
        
        prevVal = encoderValue;
      }
    }
  
  
  delay(10);
  
   if(!buttonState[0] == HIGH){ //red
    pushed[0] = true;
    Serial.print('S');
    Serial.print("red");
    Serial.print('F');
    neon_r.setPixelColor(0,neon_r.Color(255, 255, 255));
    neon_r.show();
  }else if(!buttonState[0] == LOW){
    if(pushed[0] == true){
      pushed[0] = false;
      Serial.print('S');
      Serial.print("r_released");
      Serial.print('F');
    }
    neon_r.setPixelColor(0,neon_r.Color(255, 23, 107));
    neon_r.show();
  }
  
   if(!buttonState[1] == HIGH){ //yellow
    pushed[1] = true;
    Serial.print('S');
    Serial.print("yellow");
    Serial.print('F');
    neon_y.setPixelColor(0,neon_r.Color(255, 255, 255));
    neon_y.show();
  }else if(!buttonState[1] == LOW){
    if(pushed[1] == true){
      pushed[2] = false;
      Serial.print('S');
      Serial.print("y_released");
      Serial.print('F');
    }
    neon_y.setPixelColor(0,neon_y.Color(255, 222, 29));
    neon_y.show();
  }
 
  if(!buttonState[2] == HIGH){ //green
   pushed[2] = true;
    Serial.print('S');
    Serial.print("green");
    Serial.print('F');
    neon_g.setPixelColor(0,neon_r.Color(255, 255, 255));
    neon_g.show();
  }else if(!buttonState[2] == LOW){
    if(pushed[2] == true){
      pushed[2] = false;
      Serial.print('S');
      Serial.print("g_released");
      Serial.print('F');
    }
    neon_g.setPixelColor(0,neon_g.Color(33, 237, 112));
    neon_g.show();
  }
 
 if(!buttonState[3] == HIGH){ //blue
  pushed[3] = true;
    Serial.print('S');
    Serial.print("blue");
    Serial.print('F');
    neon_b.setPixelColor(0,neon_r.Color(255, 255, 255));
    neon_b.show();
  }else if(!buttonState[3] == LOW){
    if(pushed[3] == true){
      pushed[3] = false;
      Serial.print('S');
      Serial.print("b_released");
      Serial.print('F');
    }
    neon_b.setPixelColor(0,neon_b.Color(26, 130, 255));
    neon_b.show();
  }
  
}

void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}

