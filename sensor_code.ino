//base code credits to: https://www.hackster.io/331510/wash-a-lot-bot-a-diy-hand-washing-timer-2df500
//youtube tutorial: https://www.youtube.com/watch?v=X-3AoN8Subk

#include <Servo.h>
#include "pitches.h"

const int trigPin = 9;
const int echoPin = 10;
const int speaker = 4;

float duration, distance;

// threshold where the sensor will trigger the 
//countdown. 
int threshold = 20;
Servo countServo;

int melody[] = {
  
  NOTE_C5, NOTE_D5, 
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  0, NOTE_F5, NOTE_F5, NOTE_C5, NOTE_D5,
  NOTE_F5, NOTE_F5, NOTE_F5,NOTE_F5, NOTE_F5,
  0, NOTE_F5, NOTE_F5, NOTE_C5, NOTE_D5,
  NOTE_F5, NOTE_F5, NOTE_F5,NOTE_F5, NOTE_F5,
  0, NOTE_F5, NOTE_F5, NOTE_C5, NOTE_D5,
  NOTE_A5, NOTE_G5,
  NOTE_F5, NOTE_F5, NOTE_F5,NOTE_F5, NOTE_F5,
  0, NOTE_F5, NOTE_F5, NOTE_A5, NOTE_G5,
  NOTE_F5, NOTE_F5, NOTE_F5,NOTE_F5, NOTE_F5,
  NOTE_C5, NOTE_D5, 
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  0, NOTE_F5, NOTE_F5, NOTE_C5, NOTE_D5,
  NOTE_F5, NOTE_F5, NOTE_F5,NOTE_F5, NOTE_F5,
  0, NOTE_F5, NOTE_F5, NOTE_C5, NOTE_D5,
  NOTE_F5, NOTE_F5, NOTE_F5,NOTE_F5, NOTE_F5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  2,2, 
  4, 4, 4, 8, 8, 
  8,8, 4,4,4,
  8,8,8,4,4,
  4,4,8,8,8,
  8,8,8,4,4,
  4,4,8,8,8,
  2,2,
  8,8,8,4,4,
  4,4,8,8,8,
  8, 8, 8, 4, 4,
  2,2,4,4,4,8,8,8,8,4,4,4,8,8,8,4,4,4,4,8,8,8,8,8,8,4,
};

void setup() {
pinMode(trigPin,OUTPUT);
pinMode(echoPin, INPUT);
  Serial.begin(9600);
  
  //attach pin 7 to servo and sweep it to indicate that the timer is on
  countServo.attach(7);
  countServo.write(180);
  delay(700);
  countServo.write(0);
  delay(700);
  countServo.write(180);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  Serial.println(duration);
  distance = (duration * .0343) / 2;
  Serial.println(distance);

if (distance < threshold) {
    countdownServo();
  }
  delay(100);
}

//this moves the servo 4.5 degrees every half second
//to smooth out the movemnt (vs 9 degrees every second)
//for 20 seconds.
void countdownServo() {
  Serial.println("Counting down");
  int halfseconds = 40;

  for (int thisNote = 0; thisNote < 75; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(speaker, melody[thisNote], noteDuration);
    
    countServo.write((int)( (74-thisNote) * 2.4));
    
    int pauseBetweenNotes = noteDuration * 1.30;
    Serial.print("thisNote ");
    Serial.println(thisNote);
    delay(pauseBetweenNotes);
    
  }

  //reset the servo, clear the queue
  digitalWrite(13,HIGH);
  noTone(speaker);
  countServo.write(180);
  
  delay(700);
}
