#include <Servo.h>
int redPin = 3;
int bluePin = 5;
int greenPin = 6;
int MQ3 = A0;
int value;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /* Controls the servo */
    Servo myServo;
    myServo.attach(9);
    myServo.write(10);

      /* This is the Alcohol sensor*/

    pinMode(MQ3, INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
    
    
    // This is the amount of alcohol detected from the sensor
  value = analogRead(MQ3);

   // This will light the led if alcohol is present
    Serial.println(value);
   while(value>0) //may remove
    {
      if(value > 400)
      {
        analogWrite(redPin,100);
        analogWrite(bluePin,100);
        analogWrite(greenPin,100);
      }
      else{
         analogWrite(redPin,0);
        analogWrite(bluePin,0);
        analogWrite(greenPin,0);    
        }
    delay(100);
     
    }
    

}
