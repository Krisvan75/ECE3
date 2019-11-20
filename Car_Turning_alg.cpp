
#include <ECE3.h>

uint16_t sensorValues[8];
const int left_nslp_pin=31;
const int left_dir_pin=29;
const int left_pwm_pin=40;
const int right_nslp_pin = 11;
const int right_dir_pin = 30;
const int right_pwm_pin = 39;

void Turn_Left(int sum);
void Turn_Right(int sum);

void setup() {
// put your setup code here, to run once:
  pinMode(left_nslp_pin,OUTPUT);
  pinMode(left_dir_pin,OUTPUT);
  pinMode(left_pwm_pin,OUTPUT);
  pinMode(right_nslp_pin,OUTPUT);
  pinMode(right_dir_pin,OUTPUT);
  pinMode(right_pwm_pin,OUTPUT);

  digitalWrite(left_dir_pin,LOW);
  digitalWrite(left_nslp_pin,HIGH);
  digitalWrite(right_dir_pin,LOW);
  digitalWrite(right_nslp_pin,HIGH);

  ECE3_Init();
  int SensorArr[8];
  Serial.begin(9600); 
  delay(2000); //Wait 2 seconds before starting 
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  int leftSpd = 130;
  int TestArr[] ={-8,-4,-2,-1,1,2,4,8};
  ECE3_read_IR(sensorValues);
  analogWrite(left_pwm_pin,leftSpd);
  analogWrite(right_pwm_pin,leftSpd);
  for (unsigned char i = 0; i < 8; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }

  int sum = ((TestArr[0]*sensorValues[0])+(TestArr[1]*sensorValues[1])+(TestArr[2]*sensorValues[2])+(TestArr[3]*sensorValues[3])+(TestArr[4]*sensorValues[4])+(TestArr[5]*sensorValues[5])+(TestArr[6]*sensorValues[6])+(TestArr[7]*sensorValues[7]));
  Serial.print(sum);
  Serial.print("\n");
  if(sum>150)
    Turn_Left(sum);
  if(sum<(-150))
    Turn_Right(sum);
  }
  
  void Turn_Left(int sum)
  {
    int LeftSpd=40;
    int RgtSpd=60; 
    int TestArr[] ={-8,-4,-2,-1,1,2,4,8};
    while(sum>150)
    {
      analogWrite(left_pwm_pin,LeftSpd);
      analogWrite(right_pwm_pin,RgtSpd);
      delay(500);
      ECE3_read_IR(sensorValues);
      sum = ((TestArr[0]*sensorValues[0])+(TestArr[1]*sensorValues[1])+(TestArr[2]*sensorValues[2])+(TestArr[3]*sensorValues[3])+(TestArr[4]*sensorValues[4])+(TestArr[5]*sensorValues[5])+(TestArr[6]*sensorValues[6])+(TestArr[7]*sensorValues[7]));
    }
    
  }
  void Turn_Right(int sum)
  {
    int LeftSpd=40;
    int RgtSpd=60; 
    int TestArr[] ={-8,-4,-2,-1,1,2,4,8};
    while(sum<-150)
    {
      analogWrite(left_pwm_pin,LeftSpd);
      analogWrite(right_pwm_pin,RgtSpd);
      delay(500);
      ECE3_read_IR(sensorValues);
      sum = ((TestArr[0]*sensorValues[0])+(TestArr[1]*sensorValues[1])+(TestArr[2]*sensorValues[2])+(TestArr[3]*sensorValues[3])+(TestArr[4]*sensorValues[4])+(TestArr[5]*sensorValues[5])+(TestArr[6]*sensorValues[6])+(TestArr[7]*sensorValues[7]));
    }
  }
