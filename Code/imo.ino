
#include <Servo.h>

int motorpin=10;
int counter;
int baselineTemp = 0;
int celsius = 0;
int fahrenheit = 0;
int angle;
Servo servoBase;

void setup() {
  servoBase.attach(A1);
  servoBase.write(0);
  pinMode(motorpin, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(A1,OUTPUT);
  pinMode(A0, INPUT); //sensor temperature
  pinMode(11, OUTPUT); //blue
  pinMode(12, OUTPUT); //yellow
  pinMode(13, OUTPUT); //red
  Serial.begin(9600);
  while (! Serial);
  
}

void loop() {
    // //light sensor
    // int lightsensitivity =   analogRead(A2);
    // Serial.println("Light sensitivity");
    // Serial.println(lightsensitivity);
    // delay(1000);
    // //servo vontrolled by light sensitivity
    // angle=lightsensitivity/5;
    // servoBase.write(angle);
    // Serial.println("angle is");
    // Serial.println(angle);
    // delay(1000);

    //temperature sensor
    int sensor = analogRead(A0);
    baselineTemp = 40;
    
    celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
    
    fahrenheit = ((celsius * 9) / 5 + 32);
    // Serial.println(celsius);

    if (celsius < baselineTemp) {
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
    }
    
    if (celsius >= baselineTemp && celsius < baselineTemp + 10) { //cold
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
    // Serial.println(" Temperature");
        //Serial.println(celsius);
    }
    if (celsius >= baselineTemp + 10 && celsius < baselineTemp + 20) { //hot
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);
        //Serial.println(" Temperature");
        //Serial.println(celsius);
    }
    else { //fine
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
        digitalWrite(13, LOW);
    // Serial.println(" Temperature");
        //Serial.println(celsius);
    }
    delay(1000);
    //motor controlled by temperature
    if (Serial.available()) {
        int speed = Serial.parseInt();
        if (speed >= 0 && speed <= 255)
        {
    //   analogWrite(motorPin, 255 - speed);
        // 
            Serial.println("Speed 0 to 255");
            Serial.println(speed); // !!!!!!

            if (celsius < baselineTemp)
            {
            analogWrite(motorpin,50);
            Serial.println(" Temperature"); 
            Serial.println(celsius);  // !!!!!!
            Serial.println("speed");
            Serial.println(speed); 
            }
            //if (celsius >= baselineTemp && celsius < baselineTemp + 10 && speed<100)
            if (celsius >= baselineTemp && celsius < baselineTemp + 10)
            // we were missing the edgecase of Temp between baseline,baseline+10 and speed>=100
            {
                analogWrite(motorpin,100);
                Serial.println(" Temperature");
                Serial.println(celsius);
                Serial.println("speed"); 
                Serial.println(speed);
            }
            if (celsius >= baselineTemp + 10 && celsius < baselineTemp + 20 ) 
            {
                analogWrite(motorpin,180); ///full max? what happens at {>=  baselineTemp + 20}?
                Serial.println(" Temperature");
                Serial.println(celsius);
                Serial.println("speed");
                Serial.println(speed);
            }
            if (celsius >=  baselineTemp + 20 )
            {
                analogWrite(motorpin,255);
                Serial.println(" Temperature");
                Serial.println(celsius);
                Serial.println("speed");
                Serial.println(speed);
            }
    
        }
        } 
}




