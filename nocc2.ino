#include "Keyboard.h"

char* secretCode = "1234";  // set password
int secretCodeLen = 4;
bool a_toggle = false, b_toggle = false, passwd_toggle = false;
bool c_toggle = false, d_toggle = false, pushbtn_toggle = false;
int count = 0, wrong = 0, button_mode = 0;

// touch sensor
const int key_one_pin = 3;
const int key_two_pin = 15;
const int key_three_pin = 4;
const int key_four_pin = 14;
// push button
const int push_button = 2;
// rgb led
const int redPin = 6;
const int greenPin = 7;
const int bluePin = 8;
// red led
const int led_pin = 9;

void setup()
{
  Serial.begin(9600);
  Keyboard.begin();
  Serial.begin(115200);
  pinMode(push_button, INPUT_PULLUP);
  pinMode(key_one_pin, INPUT);
  pinMode(key_two_pin, INPUT);
  pinMode(key_three_pin, INPUT);
  pinMode(key_four_pin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(led_pin, OUTPUT);
  
  setLocked(true);
}

void loop()
{
  char key;
  
  if(digitalRead(key_one_pin)==1 && a_toggle==false) {
    key = '1';
    a_toggle = true;
    Serial.println('a');
    passwd_toggle = true;
    if(button_mode==2) {
      Keyboard.write('a');
    }
  }
  else if(digitalRead(key_two_pin)==1 && b_toggle==false) {
    key = '2';
    b_toggle = true;
    Serial.println('b');
    passwd_toggle = true;
    if(button_mode==2) {
      Keyboard.write('b');
    }
  }
  else if(digitalRead(key_three_pin)==1 && c_toggle==false) {
    key = '3';
    c_toggle = true;
    Serial.println('c');
    passwd_toggle = true;
    if(button_mode==2) {
      Keyboard.write('c');
    }
  }
  else if(digitalRead(key_four_pin)==1 && d_toggle==false) {
    key = '4';
    d_toggle = true;
    Serial.println('d');
    passwd_toggle = true;
    if(button_mode==2) {
      Keyboard.write('d');
    }
  }
  else if(!digitalRead(push_button) && pushbtn_toggle==false) {
    passwd_toggle = true;
    pushbtn_toggle = true;
    
    button_mode++;
    if(button_mode>=3) button_mode = 0;
  }

  // button mode -> change led
  if(button_mode==0) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  }
  else if(button_mode==1) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
  }
  else {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }

  // input password
  if(passwd_toggle && button_mode!=2)
  {
    if(key==secretCode[count]) {
      count++;
    }
    else if(key!=secretCode[count])
    {
      count++;
      wrong++;  
    }

    if(count==secretCodeLen) {
      if(wrong==0) {
        setLocked(false);
        setLocked(true);
      }
      else {
        setLocked(true);
        led_blink();
      }
      wrong = 0;
      count = 0;
    }
    passwd_toggle = false;
  }

  if(!digitalRead(key_one_pin)) a_toggle = false;
  if(!digitalRead(key_two_pin)) b_toggle = false;
  if(!digitalRead(key_three_pin)) c_toggle = false;
  if(!digitalRead(key_four_pin)) d_toggle = false;
  if(digitalRead(push_button)) pushbtn_toggle = false;
  delay(10);
}

void setLocked(int locked)
{
  if(locked)
  {
    digitalWrite(led_pin, LOW);
  }
  else
  {
    // button mode -> keyboard write
    if(button_mode==0) {
      Keyboard.println("3630");
    }
    else if(button_mode==1) {
      Keyboard.println("3630");
    }
    
    digitalWrite(led_pin, HIGH);
    delay(2000);
  } 
}

void led_blink()
{
  for(int i=0; i<4; i++) {
    digitalWrite(led_pin, HIGH);
    delay(300);
    digitalWrite(led_pin, LOW);
    delay(300);
  }
}
