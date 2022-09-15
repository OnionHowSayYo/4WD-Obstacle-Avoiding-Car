#include <Servo.h>

// Microservo Pin
int servoPin = 3;

// DC Motor Pin
int in1 = 8;
int in2 = 7;
int enA = 6;

int in3 = 4;
int in4 = 2;
int enB = 5;

// Ultrasonic Sensor Pin
int trigPin = 9;
int echoPin = 10;

// Variables for Ultrasonic Sensor
long duration;
long durationL;
long durationR;
int distance;
int distanceL;
int distanceR;

// Define servo name
Servo servo;

// Some variables
boolean turning = false;
boolean turningL = false;
boolean turningR = false;
boolean scanning = false;
boolean checking = false;




void setup() {
  
  // Setup for Microservo
  servo.attach(servoPin);

  // Setup for DC Motor
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Setup for Ultrasonic Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  Serial.begin(9600);





}

void loop() {

  servo.write(90);

duration = 0;
durationL = 0;
durationR = 0;
distance = 0;
distanceL = 0;
distanceR = 0;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 15){
    
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(enA, HIGH);
    digitalWrite(enB, HIGH);


  }

  else if (distance <= 15){
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(enA, HIGH);
    digitalWrite(enB, HIGH);

    checking = true;

    while (checking == true) {
      scanning = true;
  
      while (scanning == true) {
        servo.write(180);
        
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        durationL = pulseIn(echoPin, HIGH);
        distanceL = durationL * 0.034 / 2;
      
        Serial.print("Distance: ");
        Serial.println(distanceL);
  
        delay(1000);
  
        servo.write(0);
        
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        durationR = pulseIn(echoPin, HIGH);
        distanceR = durationR * 0.034 / 2;
      
        Serial.print("Distance: ");
        Serial.println(distanceR);
  
        delay(1000);

        servo.write(90);
  
        scanning = false;
        
      }
  
      turning = true;
  
      while (turning == true) {
          if (distanceL >= distanceR) {
            turningL = true;
        
            while (turningL == true) {
        
              for (int i = 0; i < 1500; i++) {
                digitalWrite(in1, HIGH);
                digitalWrite(in2, LOW);
                digitalWrite(in3, HIGH);
                digitalWrite(in4, LOW);
                digitalWrite(enA, HIGH);
                digitalWrite(enB, HIGH);
        
                delay(1);
              }
              digitalWrite(in1, LOW);
              digitalWrite(in2, LOW);
              digitalWrite(in3, LOW);
              digitalWrite(in4, LOW);
              digitalWrite(enA, HIGH);
              digitalWrite(enB, HIGH);
              turningL = false;
            }
            
          }
  
          else if (distanceR > distanceL) {
            turningR = true;
        
            while (turningR == true) {
        
              for (int j = 0; j < 1500; j++) {
                digitalWrite(in1, LOW);
                digitalWrite(in2, HIGH);
                digitalWrite(in3, LOW);
                digitalWrite(in4, HIGH);
                digitalWrite(enA, HIGH);
                digitalWrite(enB, HIGH);
        
                delay(1);
              }
              digitalWrite(in1, LOW);
              digitalWrite(in2, LOW);
              digitalWrite(in3, LOW);
              digitalWrite(in4, LOW);
              digitalWrite(enA, HIGH);
              digitalWrite(enB, HIGH);
              turningR = false;
            }
            
          }
  
          delay(500);
          turning = false;
      }

      checking = false;
    
    }

  }











}
