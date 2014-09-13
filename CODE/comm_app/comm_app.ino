//const int outputPin = 12;
int potPin = 0;
int sensorVal = 0;
int prevVal = 0;
String inputString = "";

int soundPin = 12;
int ledPin [] = {8,9,10,11};
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

void setup()
{
 
  for(int i=0; i<4; i++){
    pinMode(ledPin[i], OUTPUT);
  }
  
//  pinMode(outputPin, OUTPUT);
  Serial.begin(57600);
  
  for(int i=0; i<4; i++){
    pinMode(ledPin[i], OUTPUT);
    pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);
  }
  pinMode(soundPin, OUTPUT);
  
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
  
   Serial.print('B');
  Serial.print(encoderValue);
  Serial.print('E');
  
  delay(10);
  
   if(!buttonState[0] == HIGH){ //red
    Serial.print('S');
    Serial.print('red');
    Serial.print('F');
    //tone(soundPin, 100);
    digitalWrite(ledPin[0], LOW);
    //toneEffect();
    delay(10);
  }else if(!buttonState[1] == HIGH){ //yellow
    Serial.print('S');
    Serial.print('yellow');
    Serial.print('F');
    //tone(soundPin, 200);
    digitalWrite(ledPin[1], LOW);
    //toneEffect();
    delay(10);
  }else if(!buttonState[2] == HIGH){ //green
    Serial.print('S');
    Serial.print('green');
    Serial.print('F');
    //tone(soundPin, 300);
    digitalWrite(ledPin[2], LOW);
    //toneEffect();
    delay(10);
  }else if(!buttonState[3] == HIGH){ //blue
    Serial.print('S');
    Serial.print('blue');
    Serial.print('F');
    //tone(soundPin, 400);
    digitalWrite(ledPin[3], LOW);
    //toneEffect();
    delay(10);
  }else{
  for(int i=0; i<4; i++) 
    digitalWrite(ledPin[i], HIGH);
  }
  
  // arduino reads Serial
//  if (Serial.available() > 0) {
//    int incomingByte = Serial.read();
// 
//    if (incomingByte == 1) { // 0x01 = char 1
//      for(int i = 0; i <4; i++){
// //         tone(soundPin, 100+i*100);
//          delay(50);
//      }
// //     noTone(soundPin);
//    } 
//  }
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

void toneEffect(){
  
//  noTone(soundPin);
    
}
