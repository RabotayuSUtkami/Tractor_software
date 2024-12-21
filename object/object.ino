#include <AESLib.h>
#include <string.h>
#include <Servo.h>

#include <iarduino_VCC.h>



Servo servo1;
char rx_data;
const int FwdPin_A = 3; 
const int BwdPin_A = 4; 
const int FwdPin_B = 5; 
const int BwdPin_B = 6; 
int MaxSpd = 250; 
int roll = 90;
int angle = 15;

bool first = 1;
String data = "";

uint8_t key[] = {"a"};
//char data[] = "123456789abc"; //16 chars == 16 bytes



void setup(){
 
  Serial.begin(9600);
  servo1.attach(11);
  servo1.write(roll);

  pinMode(FwdPin_A, OUTPUT);    // Устанавливаем FwdPin_A как выход
  pinMode(BwdPin_A, OUTPUT);    // Устанавливаем BwdPin_A как выход
  pinMode(FwdPin_B, OUTPUT);    // Устанавливаем FwdPin_A как выход
  pinMode(BwdPin_B, OUTPUT);    // Устанавливаем BwdPin_A как выход
  

  
}

void loop(){


   // Serial.println( data );  
    //float i = analogRead_VCC();       // Читаем напряжение питания Arduino.
    //Serial.println( i );   

    //String rx_data = Serial.readString();
    //char rx_data = Serial.read();

    //const void *a = rx_data.c_str();//buffer.c_str();
   
    //Serial.println(rx_data);
    //Serial.print("I received: ");
    //aes128_dec_single(key, incomingByte);


if (Serial.available() > 0) {
   rx_data  = Serial.read();
   //Serial.println( rx_data );  

  if (rx_data == '$'){
    if (first == 1){
      data = "";
      first = 0;
    }
    else{
      processing(data);
      data = "";
    }
  }
  else{
    data += rx_data;
  }
}


//const int FwdPin_A = 10; 
//const int BwdPin_A = 9; 

    // if (rx_data == 'w'){
    //   //analogWrite(BwdPin_A,MaxSpd);  
    //   digitalWrite(BwdPin_A, HIGH); // включаю мотор вперед
    //   delay(40);
    // }
    // else if(rx_data == 's'){
    //   //analogWrite(FwdPin_A,MaxSpd);   
    //   digitalWrite(FwdPin_A, HIGH); // включаю мотор назад

    //   delay(40);
    // }
    // else if(rx_data == 'd'){
    //   servo1.write(100);
    //    delay(40);
    // }
    // else if(rx_data == 'a'){
    //   servo1.write(80);   
    //   delay(40);
    // }
    // else{
    //   digitalWrite(BwdPin_A,LOW); 
    //   digitalWrite(FwdPin_A,LOW); 
    //   servo1.write(90);
    // }
    
  
}

void processing(String data){
  if (data == "forw"){
    digitalWrite(FwdPin_A, HIGH); // включаем мотор
    digitalWrite(BwdPin_B, HIGH); // включаем мотор
  }
  else if (data == "back"){
    digitalWrite(BwdPin_A, HIGH); // включаем мотор
    digitalWrite(FwdPin_B, HIGH); // включаем мотор
  } 
  else if (data == "left"){
    servo1.write(roll - angle); 
    //Serial.println("the end");
  } 
  else if (data == "right"){
    servo1.write(roll + angle); 
    //Serial.println("the end");
  } 
  else if (data == "noroute"){
    servo1.write(roll); 
  } 
  else if (data == "nomove"){
    digitalWrite(FwdPin_A, LOW); // включаем мотор
    digitalWrite(BwdPin_A, LOW); // включаем мотор
    digitalWrite(FwdPin_B, LOW); // включаем мотор
    digitalWrite(BwdPin_B, LOW); // включаем мотор
  } 
  else if (data == "pdl"){
    Serial.write("$pdl,1111111111$");
    //Serial.println("pdl send");
  } 
  else if (data == "volt"){
    float i = analogRead_VCC();
    String stringOne = "$volt," + String(i, 2) + "$";
    Serial.write (stringOne.c_str());
    //Serial.println(stringOne);
    //Serial.println("");
  } 
  else if (data == "getroll"){
    String rollval = "$roll," + String(roll) + "$";
    Serial.write(rollval.c_str());
    //Serial.println("the end");
  } 
  else if (data == "getangle"){   
    String angleval = "$angle," + String(angle) + "$";
     Serial.write(angleval.c_str());
    //Serial.println("the end");
  } 

  int index = data.indexOf("setroll");
  if (index != -1){
    data.remove(0, 7);
    roll = data.toInt();
    servo1.write(roll);
  }
  else{
    index = data.indexOf("setangle");
    if (index != -1){
      data.remove(0, 8);
      angle = data.toInt();
    
    }
  }    
}

