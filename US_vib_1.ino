oh
//Program to run US distance measure and a small vibration motor off an ESP8266

#include <Arduino.h>

//Define pins
const int trigPin = 4;
const int echoPin = 5;
int motor_pin = 12;

//US variables
long duration;
int distance;

int dist2vibe = 0;

//averaging
float Av = 10;
float K = 0.4;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(motor_pin, OUTPUT);
analogWrite(motor_pin,0);
Serial.begin(9600); 


}

void loop() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
//Calculate the distance (in cm) based on the speed of sound.
distance = duration/58.2;
Serial.print(distance);

//running average for smoothing
Av = Av + ((distance - (Av-1))*K);
Serial.print(",");
Serial.println(Av);

//maps distance MIN,MAX to motor MAX,MIN
dist2vibe= map(Av, 0,80,1000,70);
analogWrite(motor_pin,dist2vibe);
//Delay 50ms before next reading.
delay(30);

}
