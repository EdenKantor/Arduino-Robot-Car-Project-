
//===============================================
 #define PinDirectionr 12// H-bridge Pin 2 
 #define PinMotorr 10    // H-bridge Pin 7(PWM)
 #define PinDirectionl 13// H-bridge Pin 2 
 #define PinMotorl 9//11
 #define Vleft 5
 #define Rleft 6
 #include <LiquidCrystal.h>
 #define echoPin 7
 #define trigPin 4
 #define SpeakerPin 8
  int x[3]={130,190,250};
  int mone=0; 
 byte SBUF; 
 LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
 long duration, distance;
 void setup() {
     Serial.begin(9600);
     pinMode(PinDirectionr, OUTPUT);
     pinMode(PinDirectionl, OUTPUT);
     pinMode(Vleft,OUTPUT);
     pinMode(Rleft,OUTPUT);
     //=================================
   lcd.begin(16,2);
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(SpeakerPin, OUTPUT);
   digitalWrite(trigPin, LOW);
  lcd.setCursor(0,0);
  lcd.print("Distance = ");
  }//End of setup function
 void loop() { 
   noTone (SpeakerPin);
   motor(0,0);
   while(1){
  SBUF=Serial.read();
  if(SBUF=='+')
       motor(x[mone],x[mone]);
  if(SBUF=='+'&&mone!=3)
       mone++;
  if(SBUF=='+'&&mone==3)
       mone=0;
       digitalWrite(Vleft,0);
         digitalWrite(Rleft,0);
  
  if(SBUF=='-')
   {
       motor(-200,-200);
        while(SBUF!='+'&& SBUF!='>'&& SBUF!='<'&& SBUF!='$')
       {
         digitalWrite(Vleft,1);
         digitalWrite(Rleft,1);
         //delay(250);
        // digitalWrite(Vleft,0);
         //digitalWrite(Rleft,0);
         //delay(250);
         //===========================================
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 // Serial.print("Distance = ");
  
  lcd.setCursor(10,0);
  lcd.print("     ");
 // delay(20);
  lcd.setCursor(10,0);
  distance = duration/58;
  //Serial.println(distance);
  lcd.print(distance);
  
  if (distance<40)
  {
  
  tone(SpeakerPin,526);
  delay(distance*8);
  noTone(SpeakerPin);
  delay(distance*8);
  }
  else
     noTone(SpeakerPin);
     if (distance<10){
   motor(0,0);
   tone(SpeakerPin,526);
     }
     
     if (distance>10)
     motor(-200,-200);
     
       
   //End LCD+SPEAKER+HC
         //==========================================
         SBUF=Serial.read();
       } 
     }
  if(SBUF=='>')
   {
       motor(150,250);
        while(SBUF!='+'&& SBUF!='-'&& SBUF!='<'&& SBUF!='$')
       {
         digitalWrite(Vleft,0);
         digitalWrite(Rleft,0);
         
         digitalWrite(Rleft,1);
         delay(250);
         digitalWrite(Rleft,0);
         delay(250);
       SBUF=Serial.read();
       }  }
  if(SBUF=='<')
  {
       motor(250,150);
          while(SBUF!='+'&& SBUF!='-'&& SBUF!='>'&& SBUF!='$')
        { 
          digitalWrite(Vleft,0);
         digitalWrite(Rleft,0);
         
          digitalWrite(Vleft,1);
          delay(250);
          digitalWrite(Vleft,0);
          delay(250);
        SBUF=Serial.read();
     }  }
       
  if(SBUF=='$')
  {
       motor(0,0);
       while(SBUF!='+'&& SBUF!='>'&& SBUF!='<'&& SBUF!='-')
       {
        digitalWrite(Vleft,0);
        digitalWrite(Rleft,0);
        SBUF=Serial.read();
       }}
 }
  }//End of loop function
 void motor(int Speedl,int Speedr){
    Speedl=Speedl*-1; 
    Speedr=Speedr*-1;      
  	 analogWrite(PinMotorr, Speedr);
          analogWrite(PinMotorl, Speedl);
   if(Speedr >= 0)
    	 digitalWrite(PinDirectionr,LOW);
   else
	 digitalWrite(PinDirectionr,HIGH);
   if(Speedl >= 0)
    	 digitalWrite(PinDirectionl,LOW);
   else
	 digitalWrite(PinDirectionl,HIGH);
 }
//===============================================

