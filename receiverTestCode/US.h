#ifndef US_H
#define US_H

#define US_TRIG_1 A2
#define US_ECHO_1 A3

//VARIABLES
int distance_1 = 0;
unsigned long distance_millis_1 = 0;

int readDistance() {
  if ((distance_millis_1 + 500) < millis()) {
    int trigPin = US_TRIG_1;
    int echoPin = US_ECHO_1;
    long duration;
    int distance;
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
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
    distance_1 = constrain(distance, 0, 100);
    distance_millis_1 = millis();
  }
  return distance_1;
}

#endif
