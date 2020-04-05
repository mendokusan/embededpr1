#include <Servo.h>
#include <Chrono.h>

int redPin = 3;
int bluePin = 5;
int greenPin = 6;
int MQ3 = A0;
int value;
int btnPin = 2;
Servo myServo;
Chrono timer(Chrono::SECONDS);

int buzzerPin = 11;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /* Controls the servo */
   
    myServo.attach(9);
    pinMode(btnPin,  INPUT_PULLUP);
    pinMode(MQ3, INPUT);
    pinMode(buzzerPin, OUTPUT);




}
void loop() {

  // put your main code here, to run repeatedly:    
    // This is the amount of alcohol detected from the sensor
   // This will light the led if alcohol is present
   DetectStart();
 
}
void DetectStart()
{
  if(digitalRead(btnPin) == LOW)
 {
     ClearLightColor();
     FirstTest();
 }
}

bool FirstTest()
{
  int result = DeteectAlcohol();
  if(result > 400){
    FailedState();
  }
  else{
    ClearLightColor();
    GreenLight();
    UnlockCar();
    PassedTone();
  }
 
}

int DeteectAlcohol(){
  int maxContent = 0;
  for(int i = 0; i < 10; i++)
  {
      Proccesing();
      value = analogRead(MQ3);
       Serial.println(value);
      delay(1000);
      if(value > maxContent )
      {
       maxContent = value;
      }
  }

  return maxContent;
}

void FailedState()
{
  timer.restart();
  LockCar();
  FailedTone();
  RedLight();
  while(timer.hasPassed(20) == false)
  {
    if(timer.elapsed() % 2 == 0)
    {
      analogWrite(redPin,255);
    }
      analogWrite(redPin,0);
  
}
    timer.stop();
    GreenLight();
    AzureLight();
    DetectStart();
}
void RedLight()
{
   analogWrite(redPin,80);
   analogWrite(bluePin,0);
   analogWrite(greenPin,0);
}

void GreenLight()
{

   analogWrite(greenPin,100);
}
void Proccesing()
{
    analogWrite(redPin,0);
    analogWrite(greenPin,0);
    delay(10);
    analogWrite(redPin,255);
    analogWrite(greenPin,100);
 

}
void AzureLight()
{
   analogWrite(redPin,255);
   analogWrite(bluePin,255);
   analogWrite(greenPin,255);
}
void ClearLightColor()
{
  analogWrite(redPin,0);
   analogWrite(bluePin,0);
   analogWrite(greenPin,0);
}

void FailedTone(){
  
    tone(buzzerPin, 200); 
    delay(150);
    tone(buzzerPin, 255); 
    delay(150);
    tone(buzzerPin, 200);
    delay(150);
    noTone(buzzerPin);
     
  }
void PassedTone(){
    tone(buzzerPin, 50); 
    delay(150);
    tone(buzzerPin, 100); 
    delay(150);
    tone(buzzerPin, 200);
    delay(150);
    noTone(buzzerPin);
}
void LockCar(){
    myServo.write(255);
}
void UnlockCar(){
  myServo.write(0);
}
