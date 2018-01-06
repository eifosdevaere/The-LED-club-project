#include <SoftwareSerial.h>

SoftwareSerial BLU(3,4);

#define redPin 11
#define greenPin 10
#define bluePin 9

#define STATE_RED 0
#define STATE_GREEN 1
#define STATE_BLUE 2

int state = STATE_RED;
int red_val = 0;
int green_val = 0;
int blue_val = 0;

void setup() {
  //Serial setup
  Serial.begin(9600);
  Serial.println("-= HC-05 Bluetooth RGB LED =-");
  BLU.begin(9600);
  BLU.println("-= HC-05 Bluetooth RGB LED =-");
 
  pinMode(4, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  digitalWrite(4,HIGH);
//  setColor(255, 0, 0);
//  delay(500);
//  setColor(0, 255, 0);
//  delay(500);
//  setColor(0, 0, 255);
//  delay(500);
  setColor(255, 255, 255);
}

void loop(){
  while (BLU.available() == 0);
  
  char inChar = BLU.read();
  
  //Serial.print("Read char: ");
  //Serial.println(inChar);
  
  switch (state) {
    case STATE_RED:
      /* if we receive a digit */
      if (inChar >= '0' && inChar <= '9'){
        int inInt = inChar - '0';
        red_val = red_val * 10 + inInt;
      }
      
      /* if we receive a dot */
      else if (inChar == '.'){
        state = STATE_GREEN;
      }
      
      /* if we receive something unexpected, reset everything */
      else{
        red_val = 0;
        blue_val = 0;
        green_val = 0;
        state = STATE_RED;
      }
      
      break;
      
    case STATE_GREEN:
      /* if we receive a digit */
      if (inChar >= '0' && inChar <= '9'){
        int inInt = inChar - '0';
        green_val = green_val * 10 + inInt;
      }
      
      /* if we receive a dot */
      else if (inChar == '.'){
        state = STATE_BLUE;
      }
      
      /* if we receive something unexpected, reset everything */
      else{
        red_val = 0;
        blue_val = 0;
        green_val = 0;
        state = STATE_RED;
      }
      
      break;
      
    case STATE_BLUE:
      /* if we receive a digit */
      if (inChar >= '0' && inChar <= '9'){
        int inInt = inChar - '0';
        blue_val = blue_val * 10 + inInt;
      }
      
      /* if we receive a dot */
      else if (inChar == ')'){
        setColor(red_val, green_val, blue_val);
        red_val = 0;
        blue_val = 0;
        green_val = 0;
        state = STATE_RED;
      }
      
      /* if we receive something unexpected, reset everything */
      else{
        red_val = 0;
        blue_val = 0;
        green_val = 0;
        state = STATE_RED;
      }
      
      break;
      
    default:
        red_val = 0;
        blue_val = 0;
        green_val = 0;
        state = STATE_RED;
  }
}

void setColor(int red, int green, int blue)
{
  Serial.print("New Color: ");
  Serial.print(red);
  Serial.print(' ');
  Serial.print(green);
  Serial.print(' ');
  Serial.println(blue);
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
