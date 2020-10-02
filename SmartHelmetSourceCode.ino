#include <IRremote.h>
const int pushbutton=2;   //act as self for bike
const int motor=13;// connected to 547npn base to control motor
const int buzzer=5;// buzzer sounds if helmet is not weared during riding of bike
const int RECV_PIN = 3;  //ir signal received             //declared for receiving pulses
int c=0;        //TO TURN ON OR OFF MOTOR 
int buttonstate=0; //to check self is clicked
int irstatus=0;  // to check ir received signal
int hr=0; // to count helmet removed status
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup()
{  Serial.begin(9600);
   pinMode(motor, OUTPUT);
   pinMode(buzzer,OUTPUT);
   pinMode(pushbutton,INPUT);
   pinMode(RECV_PIN,INPUT);
   //Serial.begin(9600);
   irrecv.enableIRIn();// Start the receiver
   while(irstatus!=HIGH)
    {if (irrecv.decode(&results))
     Serial.println(results.value);
     irrecv.resume();
     Serial.println("irstatus");
     if(digitalRead(RECV_PIN)==LOW)
      {
        Serial.println("ir detected");
        delay(100);
        irstatus=HIGH;
      }
     else
     {
      Serial.println("IR NOT DETECTED!");
      delay(100);
     }
    }
   if(irstatus)
   {
     while(buttonstate!=HIGH)
     {
      
       
       Serial.println(buttonstate);
      // c++;// increase c to know number of times switch is pressed
      // delay(200);
      if(digitalRead(pushbutton)==HIGH)
      { buttonstate=HIGH;
        c++;
        delay(300);
      }
     }
   }
   if(buttonstate==HIGH)
   {
      digitalWrite(motor,HIGH);
   }
  // delay(300);
}

void loop() {
   buttonstate=digitalRead(pushbutton);
  if(buttonstate==HIGH)
   {
     c++;
     
   if(c%2==0)
    {
    digitalWrite(motor,LOW);
    delay(200);
    }
   else if(c%2!=0)
   {
     digitalWrite(motor,HIGH);
     delay(200);
    }
    
   }
 
  while(digitalRead(RECV_PIN)==HIGH &&hr<=50)
   {  
      hr++;
     Serial.println("value of hr ");
     Serial.println(hr);
     if(digitalRead(pushbutton)==HIGH)
       {
        c++;
       // delay(200);
       
     if(c%2==0)
     {
      digitalWrite(motor,LOW);
      delay(100);
      hr=0;
     }
     else if(c%2!=0)
     {
      digitalWrite(motor,HIGH);
     }
      delay(100);
     }
     delay(100);
   }
  while(digitalRead(RECV_PIN)==LOW && hr>=50)
  {
    hr=0;
    delay(50);
    Serial.println("value of hr ");
    Serial.println(hr);
    if(digitalRead(pushbutton)==HIGH)
       {
        c++;
         if(c%2==0)
          {
           digitalWrite(motor,LOW);
            delay(200);
          }
           else if(c%2!=0)
          {
           digitalWrite(motor,HIGH);
           delay(200);
          }
     
           
       }
    
  }
  if(hr>=50 &&(c%2!=0))
  {
    digitalWrite(buzzer,HIGH);
    delay(50);
    digitalWrite(buzzer,LOW);
  }
  else if(hr<50)
  {
    digitalWrite(buzzer,LOW);
    //delay(500);
    hr=0;
  }

 Serial.println("value of hr ");
 Serial.println(hr);
 if(hr>50)
 {
   hr++;
 }
 delay(200);
 }
