
//基板上のボタンのpin設定
int button_left = 10;
int button_right = 11;

//リミットスイッチのpin設定
int button_wire_left = 12;
int button_wire_right = 13;

//tweliteのpin設定
int twelite_up = 7;
int twelite_down = 8;

//基板上のボタンの状態を格納する変数
int button_left_state = 0;
int button_right_state = 0;

//リミットスイッチの状態を格納する変数
int button_wire_left_state = 0;
int button_wire_right_state = 0;

//tweliteの状態を格納する変数
int twelite_up_state = 0;
int twelite_down_state = 0;

//モータドライバのpin設定
int motor1_A = 5;
int motor1_B = 3;

//tweliteが反応したら1にするフラグ
int twe_flag = 0;

void setup() {
  pinMode(button_left,INPUT);
  pinMode(button_right,INPUT);

  pinMode(button_wire_left,INPUT);
  pinMode(button_wire_right,INPUT);

  pinMode(twelite_up,INPUT);
  pinMode(twelite_down,INPUT);
  
  pinMode(motor1_A,OUTPUT);
  pinMode(motor1_B,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  button_left_state = digitalRead(button_left);
  button_right_state = digitalRead(button_right);

  button_wire_left_state = digitalRead(button_wire_left);
  button_wire_right_state = digitalRead(button_wire_right);

  twelite_up_state = digitalRead(twelite_up);
  twelite_down_state = digitalRead(twelite_down);

  Serial.print(button_left_state);
  Serial.print(button_right_state);
  Serial.print(button_wire_left_state);
  Serial.print(button_wire_right_state);
  Serial.print(twelite_up_state);
  Serial.println(twelite_down_state);

  //基板上テスト用　押している間モータが回る
  if(button_left_state == 0)
  {
    digitalWrite(motor1_A,1);
    digitalWrite(motor1_B,0);
  }
  else if(button_right_state == 0)
  {
    digitalWrite(motor1_A,0);
    digitalWrite(motor1_B,1);
  }
  else
  {
    analogWrite(motor1_A,0);
    analogWrite(motor1_B,0);
  }


  //twelite用　downが押されたらリミットスイッチが反応するまでモータを回す
  if(twelite_up_state == 0)
  {
    digitalWrite(motor1_A,0);
    digitalWrite(motor1_B,1);
  }
  else if(twelite_down_state == 0)
  {
    twe_flag = 1;
    while(digitalRead(button_wire_right)==0)
    {
      digitalWrite(motor1_A,1);
      digitalWrite(motor1_B,0);
    }
  }
  else
  {
    analogWrite(motor1_A,0);
    analogWrite(motor1_B,0);
  }

  //リミットスイッチが反応してtwe_flagが1の時に実行
  //一定時間逆回転させて紐のテンションを開放する
  if(twe_flag == 1)
  {
      digitalWrite(motor1_A,0);
      digitalWrite(motor1_B,1);

      twe_flag = 0;
      delay(2000);
  }
  
  delay(100);
}
