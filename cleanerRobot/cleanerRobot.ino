
/* rightWheel connect to pin3 pin5
 * leftWheel connect to pin6 pin9 
 * cleaner connect to pin12 pin13
 * pump connect to pin10 pin11
 * 15 is sensor no1
 * (sensor) found 0 , not found 1
 * CW ตามเข็ม CCW ทวนเข็ม
 * analogWrite(ที่มีรูปคลื่น)ปรับกำลังได้ 
 *
 */


#define reverse   0
#define forward   1
#define motorstop 2

#define sensorL 15
#define sensorR 16

#define cleanerCW   1
#define cleanerCCW  2
#define STOP 3 

#define pumpON  1
#define pumpOFF 0


void setup() {
   // leftWheel
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);

   // rightWheel
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);

   // sensor
    pinMode(15, INPUT);
    pinMode(16, INPUT);

   // water pump
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);

   // cleaner
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    
    Serial.begin(9600);
}


int getSensorvalue(int sensornumber)
{
   int result;
   result = digitalRead(sensornumber);
   return result;    
}   


// direction = forward or reverse
// power is value 0-255
void leftWheel(int direction, int power ) 
{
   if(direction == forward)
   {
      Serial.print("leftWheel is forward, power = ");
      Serial.println(power, DEC);
      analogWrite(6, 0);
      analogWrite(9, power);
   } 
   else if(direction == reverse)
   {
      Serial.print("leftWheel is reverse, power = ");
      Serial.println(power, DEC);
      analogWrite(6, power);
      analogWrite(9, 0);  
   }
   else
   {
      Serial.println("leftWheel is stop");
      analogWrite(6, 0);
      analogWrite(9, 0);
   }
}

void rightWheel(int direction, int power ) 
{
   if(direction == forward)
   {
      Serial.print("rightWheel is forward, power = ");
      Serial.println(power, DEC);
      analogWrite(3, 0);
      analogWrite(5, power);
   } 
   else if(direction == reverse)
   {
      Serial.print("rightWheel is reverse, power = ");
      Serial.println(power, DEC);
      analogWrite(3, power);
      analogWrite(5, 0);  
   }
   else
   {
      Serial.println("rightWheel is stop");
      analogWrite(3, 0);
      analogWrite(5, 0);
   }
}

void pump(int direction, int power)
{
  if(direction == pumpON)
  {
    analogWrite(10, power);
    analogWrite(11, 0);
  }
  else
  {
    analogWrite(10, 0);
    analogWrite(11, 0);
  }
}

void cleaner(int state)
{
  if(state == cleanerCW)
  {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }
  else
  {
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
  }

}

int sensorL_value;
int sensorR_value;  
void loop() 
{
  // sensorL left
     sensorL_value = getSensorvalue(sensorL);

  // sensorR right
     sensorR_value = getSensorvalue(sensorR);

    Serial.print("sensorLvalue ");
    Serial.println(sensorL_value, DEC);
    Serial.print("sensorRvalue ");
    Serial.println(sensorR_value, DEC); 

if((sensorL_value == 1)&&(sensorR_value == 1))
  { 
    leftWheel(reverse, 130);
    rightWheel(reverse, 130);
    delay(700);
    leftWheel(reverse, 130);
    rightWheel(forward, 130);
    delay(200);
  }

else if(sensorL_value == 1)
  {
    leftWheel(reverse, 130);
    rightWheel(reverse, 130);
    delay(700);
    leftWheel(forward, 130);
    rightWheel(reverse, 130);
    delay(200);
  }

else if(sensorR_value == 1)
  { 
    leftWheel(reverse, 130);
    rightWheel(reverse, 130);
    delay(700);
    leftWheel(reverse, 130);
    rightWheel(forward, 130);
    delay(200);
  }

else{
    leftWheel(forward, 130);
    rightWheel(forward, 130);
    delay(100);
    }
  
    cleaner(cleanerCW);
    delay(100);
    cleaner(cleanerCCW);
    delay(100);
    
  
 //   pump(pumpON, 100);
 //   delay(80);
 //   pump(pumpOFF);
  

}
