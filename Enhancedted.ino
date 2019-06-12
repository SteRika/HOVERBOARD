#include <ArduinoJson.h>
//########################################################################################
//########################################################################################
//                          GPIO mappings for Arduino Mega 2560
//########################################################################################
//########################################################################################
int m1_EL_Start_Stop=5;  //EL 
int m1_Signal_hall=3;   // Signal - Hall sensor
int m1_ZF_Direction=4;  // ZF 
int m1_VR_speed=2;    //VR 
int m2_EL_Start_Stop=9;  //EL 
int m2_Signal_hall=7;   // Signal - Hall sensor
int m2_ZF_Direction=8;  // ZF 
int m2_VR_speed=6;    //VR 
//#######################################################################################
//#######################################################################################
int pos=0; int pos2 =0 ;int steps=0;int speed1=0;int speed2=0;
String direction1;
//#######################################################################################
//#######################################################################################
void plus() {
  pos++; //count steps
  //Serial.println(pos);
    if(pos>=steps){
    wheelStop();
    pos=0;
    pos2=0;
   Serial.println("STOP");
  }
}

void plus2() {
  pos2++; //count steps
  //Serial.println(pos2);
    if(pos2>=steps){
    wheelStop();
    pos=0;
    pos2=0;
    Serial.println("STOP");
  }
}

void setup() {

// put your setup code here, to run once:
Serial.begin(115200);
Serial.println ("Hello , Please Choose the Command");
//wheel 1 - Setup pin mode
pinMode(m1_EL_Start_Stop, OUTPUT);//stop/start - EL 
pinMode(m1_Signal_hall, INPUT);   //plus       - Signal  
pinMode(m1_ZF_Direction, OUTPUT); //direction  - ZF 
pinMode(m2_EL_Start_Stop, OUTPUT);//stop/start - EL 
pinMode(m2_Signal_hall, INPUT);   //plus       - Signal  
pinMode(m2_ZF_Direction, OUTPUT); //direction  - ZF 
    
    //Hall sensor detection - Count steps
    attachInterrupt(digitalPinToInterrupt(m1_Signal_hall), plus, CHANGE);
    attachInterrupt(digitalPinToInterrupt(m2_Signal_hall), plus2, CHANGE);
}


void drive(){
// {"direction":"forward","steps":"30","speed":"50"}
// {"direction":"backward","steps":"30","speed":"50"}
// {"direction":"stop","steps":"0","speed":"0"}--
 
      if(direction1=="forward" && pos < steps)
      {
        Serial.println("Command Accepted");
        Forward();
      }
      else if(direction1=="backward" && pos < steps)
      {
        Serial.println("Command Accepted");
        Backward();
      }
      else if(direction1=="right" && pos < steps)
      {
        Serial.println("Command Accepted");
        wheelMoveRight();
      }

      else if(direction1=="left" && pos2 < steps)
      {
        Serial.println("Command Accepted");
        wheelMoveLeft();
      }
      else{
        Serial.println("Wrong Command");
        wheelStop();
        pos=0;
        pos2=0;
        Serial.println("ALL STOP");
      }        
 }


void loop() {

  if (Serial.available()>0) {
    String command=Serial.readString();
    
      DynamicJsonBuffer jsonBuffer;
      JsonObject& root= jsonBuffer.parseObject(command);
      
       if (root.success()) {
          direction1 = root["direction"].asString();
          //Serial.println(direction1);
          steps = atoi(root["steps"]);
          //Serial.println(steps);
          speed1 = atoi(root["speed"]);
         //Serial.println(speed1);
          drive();
       }
}
}


void wheelStop()
{
  digitalWrite(m1_EL_Start_Stop,LOW);
  digitalWrite(m2_EL_Start_Stop,LOW);
}

void Forward()
{
  analogWrite(m1_VR_speed, speed1);
  analogWrite(m2_VR_speed, speed1);
  Serial.println("2 Motor Ready");
  digitalWrite(m1_EL_Start_Stop, LOW);  
  Serial.println("m1 is now moving");
  digitalWrite(m2_EL_Start_Stop, LOW);
  Serial.println("m2 is now moving");
  delay(1000);
  digitalWrite(m1_ZF_Direction, HIGH);
  Serial.println("m1 is forward");
  digitalWrite(m2_ZF_Direction, HIGH);
  Serial.println("m2 is forward");
  delay(1000);
  digitalWrite(m1_EL_Start_Stop,HIGH);
  digitalWrite(m2_EL_Start_Stop,HIGH);
}

void Backward()
{
  analogWrite(m1_VR_speed, speed1);
  analogWrite(m2_VR_speed, speed1);
  Serial.println("2 Motor Ready");
  digitalWrite(m1_EL_Start_Stop, LOW);
  Serial.println("m1 is now moving");
  digitalWrite(m2_EL_Start_Stop, LOW);
  Serial.println("m2 is now moving");
  delay(1000);
  digitalWrite(m1_ZF_Direction, LOW);
  Serial.println("m1 is backward");
  digitalWrite(m2_ZF_Direction , LOW);
  Serial.println("m2 is backward");
  delay(1000);
  digitalWrite(m1_EL_Start_Stop, HIGH);
  digitalWrite(m2_EL_Start_Stop, HIGH);
}

void wheelMoveRight(){
      analogWrite(m1_VR_speed, speed1);
      Serial.println("Motor is Ready");
      digitalWrite(m1_EL_Start_Stop,LOW);
      Serial.println("Motor is Moving");
      delay(1000);
      digitalWrite(m1_ZF_Direction,HIGH);
      Serial.println("Motor Turning Right");
      delay(1000);
      digitalWrite(m1_EL_Start_Stop,HIGH);
}

void wheelMoveLeft(){
      analogWrite(m2_VR_speed, speed1);
      Serial.println("Motor is Ready");
      digitalWrite(m2_EL_Start_Stop,LOW);
      Serial.println("Motor is Moving");
      delay(1000);
      digitalWrite(m2_ZF_Direction,LOW);
      Serial.println("Motor Turning Left");
      delay(1000);
      digitalWrite(m2_EL_Start_Stop,HIGH);
}
