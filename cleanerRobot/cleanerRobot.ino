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

#define onTable        0
#define offTable       1

#define False          0
#define True           1

/*
 *   Light Sensor Value
 *   Value = 1 when reach edge of the table
 *   
 */
unsigned char lsFrontLeft;            /* front left  */
unsigned char lsFrontRight;           /* front right */
unsigned char lightSensor3_value;     /* Not used, for now */
unsigned char lightSensor4_value;     /* Not used, for now */
unsigned char lightSentorEvent = 0;   /* Light Sensor event flag */

/* Cleaner config */
unsigned int  cleanerCyclic_SET       = 500;         /* set cleaner period here */
unsigned char cleanerState            = Forward;
unsigned int  cleanerCyclic_COUNT     = 0;

/* pump Config */
unsigned int  pumpCyclic_SET       = 1500;           /* set pump period here  */
unsigned int  pumpCyclic_NO        = 20;             /* set pump ON time here */
unsigned char pumpPower            = 200;            /* Not used, for now */
unsigned int  pumpCyclic_COUNT     = 0;

/*
 *          Moving config
 *   Delay1 for Backward Delay Time
 *   Delay2 for Turn     Delay Time
 *   ***must be config for appropriate surface friction
 */
unsigned char ForwardPower     = 150;
unsigned char RewardPower      = 150;
unsigned char TurnRightPower   = 150;
unsigned char TurnLeftPower    = 150;

unsigned int bothSensorDelay1  = 500;
unsigned int bothSensorDelay2  = 500;

unsigned int leftSensorDelay1  = 500;
unsigned int leftSensorDelay2  = 500;

unsigned int rightSensorDelay1 = 500;
unsigned int rightSensorDelay2 = 300;

void loop() {
  
  while(1) {
      readAllLightSensor();
    
      while (lightSentorEvent == 1) {
        leftWheel(STOP,  0);
        rightWheel(STOP, 0);
    
        /* Both front sensor are off the table, try to turn around and continue moving */
        if((lsFrontLeft == offTable) && (lsFrontRight == offTable)) {
          //Serial.println("Both Sensor");
          leftWheel(Reverse,  RewardPower);
          rightWheel(Reverse, RewardPower);
          delay(bothSensorDelay1);
          leftWheel(Forward,  TurnLeftPower);
          rightWheel(Reverse, TurnLeftPower);
          delay(bothSensorDelay2);
        }
        /* Light sensor at front left is off the table */
        else if (lsFrontLeft == offTable) {
          //Serial.println("Left Sensor");
          leftWheel(Reverse,  RewardPower);
          rightWheel(Reverse, RewardPower);
          delay(leftSensorDelay1);
          leftWheel(Forward,  TurnRightPower);
          rightWheel(Reverse, TurnRightPower);
          delay(leftSensorDelay2);    
        }
        /* Light sensor at front right is off the table */
        else{
          //Serial.println("Right Sensor");
          leftWheel(Reverse,  RewardPower);
          rightWheel(Reverse, RewardPower);
          delay(rightSensorDelay1);
          leftWheel(Reverse,  TurnLeftPower);
          rightWheel(Forward, TurnLeftPower);
          delay(rightSensorDelay2);    
        }
        readAllLightSensor();
      }
    
      /*Normal operation, keep fowarding*/
      leftWheel(Forward,  ForwardPower);
      rightWheel(Forward, ForwardPower);
      
      delay(1);
  }
  delay(1);
}

void readAllLightSensor(void) {
  lsFrontLeft        = getSensorvalue(lightSensor1);
  lsFrontRight       = getSensorvalue(lightSensor2);
  lightSensor3_value = getSensorvalue(lightSensor3);
  lightSensor4_value = getSensorvalue(lightSensor4);

  /* all sensors are on the table */
  if ((lsFrontLeft == onTable)&&(lsFrontRight == onTable)) {
    lightSentorEvent = 0;
  }

  /* there is some sonsor is off the table */
  else if ((lsFrontLeft == offTable)||(lsFrontRight == offTable)) {
    lightSentorEvent = 1;
  }
}

void leftWheel(unsigned char Direction, unsigned char Power){
   if(Direction == Forward) {
      //Serial.print("leftWheel is forward, power = ");
      //Serial.println(Power, DEC);
      analogWrite(leftWheel_A, 0);
      analogWrite(leftWheel_B, Power);
   } 
   else if(Direction == Reverse) {
      //Serial.print("leftWheel is reverse, power = ");
      //Serial.println(Power, DEC);
      analogWrite(leftWheel_A, Power);
      analogWrite(leftWheel_B, 0);  
   }
   else {
      //Serial.println("leftWheel is stop");
      analogWrite(leftWheel_A, 0);
      analogWrite(leftWheel_A, 0);
   }
}

void rightWheel(unsigned char Direction, unsigned char Power) {
   if(Direction == Forward) {
      //Serial.print("rightWheel is forward, power = ");
      //Serial.println(Power, DEC);
      analogWrite(rightWheel_A, 0);
      analogWrite(rightWheel_B, Power);
   } 
   else if(Direction == Reverse) {
      //Serial.print("rightWheel is reverse, power = ");
      //Serial.println(Power, DEC);
      analogWrite(rightWheel_A, Power);
      analogWrite(rightWheel_B, 0);  
   }
   else {
      //Serial.println("rightWheel is stop");
      analogWrite(rightWheel_A, 0);
      analogWrite(rightWheel_B, 0);
   }
}

void waterPump(unsigned char State, unsigned char Power) {
  if(State == ON) {
    //analogWrite(waterPump_A, Power);
    //analogWrite(waterPump_B, 0);
    digitalWrite(waterPump_A, HIGH);
    digitalWrite(waterPump_B, LOW);
  }
  else {
    //analogWrite(waterPump_A, 0);
    //analogWrite(waterPump_B, 0);
    digitalWrite(waterPump_A, LOW);
    digitalWrite(waterPump_B, LOW);
    
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

   // Timer0 is already used for millis() - we'll just interrupt somewhere
   // in the middle and call the "Compare A" function below
   OCR0A = 0xAF;
   TIMSK0 |= _BV(OCIE0A);
  
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

// Interrupt is called once a millisecond, 
SIGNAL(TIMER0_COMPA_vect) 
{
  static unsigned char pumpIsFirstTime1 = True;
  static unsigned char pumpIsFirstTime2 = True;
  /* Moving a cleaner periodically */
  if (cleanerCyclic_COUNT >= cleanerCyclic_SET) {
    cleanerCyclic_COUNT = 0;
    (cleanerState == Forward) ? (cleanerState = Reverse) : (cleanerState = Forward);
    cleaner(cleanerState);
  }

  if(pumpCyclic_COUNT <= pumpCyclic_SET) {
    if (pumpIsFirstTime1 == True) {
        //Serial.println("pump off");
        pumpIsFirstTime1 = False;
        waterPump(OFF, 0);  
    }
  }
  else if (pumpCyclic_COUNT <= pumpCyclic_SET + pumpCyclic_NO) {
    if (pumpIsFirstTime2 == True) {
        //Serial.println("pump on");
        pumpIsFirstTime2 = False;
        waterPump(ON, pumpPower); 
    }
 }
 else if (pumpCyclic_COUNT >= pumpCyclic_SET + pumpCyclic_NO){
    pumpCyclic_COUNT = 0;
    pumpIsFirstTime1 = True;
    pumpIsFirstTime2 = True;
 }

  cleanerCyclic_COUNT++;  
  pumpCyclic_COUNT++;
}
