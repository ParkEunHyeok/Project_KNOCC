#include "Keyboard.h"

bool a_toggle = false;
bool b_toggle = false;

char* secretCode = "1111";  // 비밀번호를 설정(여기선 1234)
int count = 0; 
int wrong = 0;
// 비밀번호 비교시 쓸 변수 선언(맞는 경우와 틀린경우 2가지)

const int redPin = 8;
const int greenPin = 9;

char keys[3] = {'1', '2', '3'};

void setup()
{
  Keyboard.begin();
  Serial.begin(115200);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  setLocked(true);
}

void loop()
{
  char key;
  /*
  if(digitalRead(4)==1) key = '1';
  else if(digitalRead(5)==1) key = '2';
  else if(digitalRead(3)==1) key = '3';
  */
  if(digitalRead(4) && a_toggle==false) {
    key = '1';
    a_toggle = true;
    //Keyboard.write('a');
  }
  else if(digitalRead(5) && b_toggle==false) {
    key = '2';
    b_toggle = true;
    //Keyboard.write('b');
  }
  else if(digitalRead(3)==1) key = '3';


  if(key=='1') Keyboard.write('a');
  if(key=='2') Keyboard.write('b');
  
  if(key == '3'){ // *, # 버튼을 눌렀을 경우
    count = 0; 
    wrong = 0; // 입력 초기화
    setLocked(true); // 잠금상태로 세팅
  } 
  else if(key == secretCode[count])
  { // 해당 자리에 맞는 비밀번호가 입력됬을 경우
    count++; // 다음 자리로 넘어 감
    wrong = 0; // 비밀번호 오류 값을 0으로 만듬
  }
  else if(key != secretCode[count])
  { // 해당 자리에 맞지 않는 비밀번호가 입력됬을 경우
    count = 0; // 비밀번호를 맞았을 경우를 0으로 만듬
    setLocked(true); // 잠금상태로 세팅
    wrong++; // 비밀번호 오류 값을 늘려준다
  }

  if(count == 4)
  { // 4자리 비밀번호가 모두 맞았을 경우
    setLocked(false); // 잠금상태를 해제 함
    delay(1000);
  }
  if(wrong == 4)
  { // 비밀번호 오류를 4번 했을 경우
    blink(); // Red LED를 깜빡여 준다.
    wrong = 0; // 비밀번호 오류 값을 0으로 만들어 준다.
  }

  if(!digitalRead(4)) a_toggle = false;
  if(!digitalRead(5)) b_toggle = false;

  delay(10);
}

void setLocked(int locked){ // 잠금시와 해제시에 맞는 LED를 세팅해 주는 함수
  if(locked) { // 잠금시 Red LED를 켜주고, Green LED를 꺼준다.
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW); 
  }
  else{ // 해제시 Red LED를 꺼주고, Green LED를 켜준다.
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  } 
}

void blink(){ // 비밀번호 4번 오류시 Red LED를 깜빡여 주는 함수.
  for(int i = 0; i < 4; i++){ // 딜레이 만큼 Red LED를 껐다 켰다 해준다. 총 8회
    digitalWrite(redPin, LOW);
    delay(500);
    digitalWrite(redPin, HIGH);
    delay(500);
  }
}
