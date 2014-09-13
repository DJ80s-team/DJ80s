//const int outputPin = 12;
int potPin = 0;
int sensorVal = 0;
int prevVal = 0;
String inputString = "";

int soundPin = 12;
int ledPin [] = {8,9,10,11};
int buttons [] = {4,5,6,7};
int buttonState [4];


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
  
}
 
void loop()
{
  
  sensorVal = analogRead(potPin);
  
//  if(abs(sensorVal-prevVal) > 5){
//    Serial.println(sensorVal);
//  }
   //noTone(soundPin);
  for(int i=0; i<4; i++)
    buttonState[i] = digitalRead(buttons[i]);
  
  
   if(buttonState[0] == HIGH){ //red
    Serial.print('S');
    Serial.print('red');
    Serial.print('F');
    //tone(soundPin, 100);
    digitalWrite(ledPin[0], LOW);
  }else if(buttonState[1] == HIGH){ //yellow
    Serial.print('S');
    Serial.print('yellow');
    Serial.print('F');
    //tone(soundPin, 200);
    digitalWrite(ledPin[1], LOW);
    //toneEffect();
  }else if(buttonState[2] == HIGH){ //green
    Serial.print('S');
    Serial.print('green');
    Serial.print('F');
    //tone(soundPin, 300);
    digitalWrite(ledPin[2], LOW);
    //toneEffect();
  }else if(buttonState[3] == HIGH){ //blue
    Serial.print('S');
    Serial.print('blue');
    Serial.print('F');
    //tone(soundPin, 400);
    digitalWrite(ledPin[3], LOW);
    //toneEffect();
  }else{
    for(int i=0; i<4; i++) 
      digitalWrite(ledPin[i], HIGH);
//      Serial.print('S');
//      Serial.print('none');
//      Serial.print('F');
  }
  
}

