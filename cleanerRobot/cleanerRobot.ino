/* IO Define */
#define rightWheel_A     3
#define rightWheel_B     5

#define leftWheel_A      6
#define leftWheel_B      9

#define waterPump_A     10
#define waterPump_B     11

#define cleaner_A       12
#define cleaner_B       13

#define lightSensor1    15
#define lightSensor2    16
#define lightSensor3    17
#define lightSensor4    18

/* Motor State and Direction */
#define Reverse        0
#define Forward        1
#define STOP           2
#define ON             3
#define OFF            4

/*
 *   Light Sensor Value
 *   Value = 1 when reach edge of the table
 */
unsigned char lightSensor1_value;
unsigned char lightSensor2_value;
unsigned char lightSensor3_value;
unsigned char lightSensor4_value;


unsigned int  cleanerCyclic_SET       = 100;      /* set cleaner period here */
unsigned char cleanerState            = Forward;
unsigned int  cleanerCyclic_COUNT     = 0;

void loop() {
  
  lightSensor1_value = getSensorvalue(lightSensor1);
  lightSensor2_value = getSensorvalue(lightSensor2);
  lightSensor3_value = getSensorvalue(lightSensor3);
  lightSensor4_value = getSensorvalue(lightSensor4);

  if (cleanerCyclic_COUNT >= cleanerCyclic_SET) {
    cleanerCyclic_COUNT = 0;
    (cleanerState == Forward) ? (cleanerState = Reverse) : (cleanerState = Forward);
    cleaner(cleanerState)
  }
  
  cleanerCyclic_COUNT++;  
  delay(1);
}

void leftWheel(unsigned char Direction, unsigned char Power){
   if(Direction == Forward) {
      Serial.print("leftWheel is forward, power = ");
      Serial.println(Power, DEC);
      analogWrite(leftWheel_A, 0);
      analogWrite(leftWheel_B, Power);
   } 
   else if(Direction == Reverse) {
      Serial.print("leftWheel is reverse, power = ");
      Serial.println(Power, DEC);
      analogWrite(leftWheel_A, Power);
      analogWrite(leftWheel_B, 0);  
   }
   else {
      Serial.println("leftWheel is stop");
      analogWrite(leftWheel_A, 0);
      analogWrite(leftWheel_A, 0);
   }
}

void rightWheel(unsigned char Direction, unsigned char Power) {
   if(Direction == Forward) {
      Serial.print("rightWheel is forward, power = ");
      Serial.println(Power, DEC);
      analogWrite(rightWheel_A, 0);
      analogWrite(rightWheel_B, Power);
   } 
   else if(Direction == Reverse) {
      Serial.print("rightWheel is reverse, power = ");
      Serial.println(Power, DEC);
      analogWrite(rightWheel_A, Power);
      analogWrite(rightWheel_B, 0);  
   }
   else {
      Serial.println("rightWheel is stop");
      analogWrite(rightWheel_A, 0);
      analogWrite(rightWheel_B, 0);
   }
}

void waterPump(unsigned char State, unsigned char Power) {
  if(State == ON) {
    analogWrite(waterPump_A, Power);
    analogWrite(waterPump_B, 0);
  }
  else {
    analogWrite(waterPump_A, 0);
    analogWrite(waterPump_B, 0);
  }
}

void cleaner(unsigned char Direction) {
  if(Direction == Forward) {
    digitalWrite(cleaner_A, HIGH);
    digitalWrite(cleaner_B, LOW);
  }
  else if (Direction == Reverse){
    digitalWrite(cleaner_A, LOW);
    digitalWrite(cleaner_B, HIGH);
  }
  else {
    digitalWrite(cleaner_A, LOW);
    digitalWrite(cleaner_B, LOW);
  }
}

unsigned char getSensorvalue(unsigned char sensornumber) {
   int result;
   result = digitalRead(sensornumber);
   return result;    
}

void setup() {
   pinMode(leftWheel_A, OUTPUT);
   pinMode(leftWheel_B, OUTPUT);

   pinMode(rightWheel_A, OUTPUT);
   pinMode(rightWheel_B, OUTPUT);

   pinMode(lightSensor1, INPUT);
   pinMode(lightSensor2, INPUT);
   pinMode(lightSensor3, INPUT);
   pinMode(lightSensor4, INPUT);

   pinMode(waterPump_A, OUTPUT);
   pinMode(waterPump_B, OUTPUT);

   pinMode(cleaner_A, OUTPUT);
   pinMode(cleaner_B, OUTPUT);
    
   Serial.begin(9600);

   cleaner(Forward);
}
