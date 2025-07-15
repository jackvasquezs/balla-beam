#include <Wire.h>
#include <Servo.h>
#include <PID_v1.h>


/////////////////////// Inputs/outputs ///////////////////////
int Analog_in = A0;
Servo myservo;  // Create servo object to control a servo, later attached to D9
//////////////////////////////////////////////////////////////

//////////////////////// Variables ///////////////////////////
int Read = 0;

float elapsedTime, time, timePrev;  // Variables for time control

int period = 50;  // Refresh rate period of the loop is 50ms
double Setpoint, Input, Output;
//////////////////////////////////////////////////////////////

/////////////////// PID constants /////////////////////////////
float kp =2.2;         
float ki =0.5;        
float kd =0.5;       
float p1,p2,p3;
float PID_p, PID_i, PID_d, PID_total,adc,adcm;
//////////////////////////////////////////////////////////////
PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);  

void setup() {
  Serial.begin(115200);
  myservo.attach(9);  // Attaches the servo on pin 9 to the servo object
  myservo.write(80); // Put the servo at angle 80, so the balance is in the middle
  pinMode(Analog_in, INPUT);
  time = millis();
  myPID.SetMode(AUTOMATIC);                                          //Set PID object myPID to AUTOMATIC 
  myPID.SetOutputLimits(-50,50);    
  //delay(10000);
}


void loop() {
  if (millis() > time + period) {
    time = millis();
    Setpoint=12;
    Input= get_dist(100);  // Get distance from the sen
    myPID.Compute();     
    PID_total = map(Output, -50, 50, 50, 110);
    
    // Limit the PID output to within the servo's range
    if (PID_total < 50) {
      PID_total = 50;
    }
    if (PID_total > 110) {
      PID_total = 110;
    }
  
    // Move the servo to the calculated position
    myservo.write(PID_total);
    
  }
}

float get_dist(int n) {
   //float adc = analogRead(Analog_in);
   // Calculate distance using the sensor's formula
  float a = 90.63; 
  float b = -1.725;
  long sum = 0;
  
  for (int i=0; i<n;i++){
   sum = sum + analogRead(Analog_in);
  }
  float adc=sum/n;
 
  float vout= adc*0.0048828125;
  float distance_cm = a*exp(b*vout);
  Serial.println(distance_cm); 
  return distance_cm;
}