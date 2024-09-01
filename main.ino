#include <Servo.h>
#include <AFMotor.h>

AF_DCMotor motor1(4);
int ir_sen = 3;
float metal;
int reading;
int metalPin = A3;
uint8_t i;
int senVal1, senVal2, senVal3;
Servo servo2;
int pos1 = 0;

void setup() {
    Serial.begin(9600);
    servo2.attach(9);
    motor1.setSpeed(25);
    motor1.run(RELEASE);
    delay(1000);
}

void loop() {
    pinMode(ir_sen, INPUT);
    delay(1000);
    int digValue = digitalRead(ir_sen);
    if (digValue == HIGH) {
        Serial.println("Waste In");
        // dry or wet compartment
        int cap_one = A0;
        int cap_two = A1;
        int cap_three = A2;
        senVal1 = analogRead(cap_one);
        senVal2 = analogRead(cap_two);
        senVal3 = analogRead(cap_three);
        if (senVal1 < 700 || senVal2 < 700 || senVal3 < 700) {
            Serial.println("Wet waste detected. OpenFLAP2");
            Serial.println(senVal1);
            Serial.println(senVal2);
            Serial.println(senVal3);
            for (pos1 = 0; pos1 <= 75; pos1 += 1) {
                servo2.write(pos1);
                delay(15);
            }
            delay(5000);
            for (pos1 = 75; pos1 >= 0; pos1 -= 1) {
                servo2.write(pos1);
                delay(10);
            }
            Serial.println("close flap");
        } else {
            reading = analogRead(metalPin);
            Serial.println(reading);
            metal = (float) reading * 100 / 1024.0;
            Serial.print("Metal in Proximity = ");
            Serial.print(metal);
            Serial.println(" %");

            if (reading < 500) {
                Serial.println("Metal Detected");
                Serial.println("Rotate Motor clockwise and stop");
                motor1.run(FORWARD);
                for (i = 180; i < 130; i++) {
                    motor1.setSpeed(i);
                    delay(5);
                }

                for (i = 130; i != 180; i--) {
                    motor1.setSpeed(i);
                    delay(5);
                }
                Serial.println("Metal bin in position. Stop Motor.");
                motor1.run(RELEASE);
                delay(5000);
                Serial.println("FLAP open");
                for (pos1 = 0; pos1 <= 75; pos1 += 1) {
                    servo2.write(pos1);
                    delay(15);
                }
                delay(5000);
                for (pos1 = 75; pos1 >= 0; pos1 -= 1) {
                    servo2.write(pos1);
                    delay(15);

                }
                Serial.println("Close FLAP");
                delay(5000);

                motor1.run(BACKWARD);
                for (i = 130; i < 180; i++) {
                    motor1.setSpeed(i);
                    delay(5);
                }

                for (i = 180; i != 130; i--) {
                    motor1.setSpeed(i);
                    delay(5);
                }
                motor1.run(RELEASE);
                delay(5000);
            } else {
                Serial.println("Dry waste Detected");
                Serial.println("Rotate motor counterclockwise");
                
                // debug
                // motor1.setSpeed();
                
                motor1.run(BACKWARD);
                for (i = 130; i < 180; i++) {
                    motor1.setSpeed(i);
                    delay(5);
                }

                for (i = 180; i != 130; i--) {
                    motor1.setSpeed(i);
                    delay(5);
                }
                Serial.println("Dry bin in position. Stop Motor.");

                motor1.run(RELEASE);
                delay(5000);
                Serial.println("Open FLAP");
                for (pos1 = 0; pos1 <= 75; pos1 += 1) {
                    servo2.write(pos1);
                    delay(15);
                }
                delay(5000);
                for (pos1 = 75; pos1 >= 0; pos1 -= 1) {
                    servo2.write(pos1);
                    delay(15);
                }

                Serial.println("Close Flap");
                Serial.println("Back to Position");
                motor1.run(FORWARD);
                for (i = 180; i < 130; i++) {
                    motor1.setSpeed(i);
                    delay(5);
                }

                for (i = 130; i != 180; i--) {
                    motor1.setSpeed(i);
                    delay(5);
                }
                motor1.run(RELEASE);
                delay(5000);
            }
        }
    }
    delay(6000);
}
