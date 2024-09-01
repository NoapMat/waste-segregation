#define RELAY1 7
#define RELAY2 6

// Initializations
int val1 = 0;
int val2 = 0;

int soilPin1 = A0;
int soilPin2 = A1;

int soilPower1 = 8;
int soilPower2 = 9;

void setup() {
    Serial.begin(9600);
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(soilPower1, OUTPUT);
    pinMode(soilPower2, OUTPUT);
    digitalWrite(soilPower1, LOW);
    digitalWrite(soilPower2, LOW);
}

void loop() {
    int switchval = digitalRead(3);
    if (switchval == 1) {
        digitalWrite(RELAY2, 0);
        Serial.println("Lamp OFF");
    } else {
        digitalWrite(RELAY2, 1);
        Serial.println("Lamp ON");
    }
    Serial.print("Soil Moisture 1 = ");
    Serial.println(readSoil1());

    Serial.print("Soil Moisture 2 = ");
    Serial.println(readSoil2());

    // take a reading every second
    delay(1000);
}

int readSoil1() {
    digitalWrite(soilPower1, HIGH);
    delay(10);
    val1 = analogRead(soilPin1);
    if (val1 <= 350) {
        digitalWrite(RELAY1, 0);
        Serial.println("Pump OFF");
        delay(1000);
    } else {
        digitalWrite(RELAY1, 1);
        Serial.println("Pump ON");
        delay(1000);
    }
    digitalWrite(soilPower1, LOW);
    return val1;
}

int readSoil2() {
    digitalWrite(soilPower2, HIGH);
    delay(10);
    val2 = analogRead(soilPin2);
    if (val2 <= 400) {
        digitalWrite(RELAY1, 0);
        Serial.println("Pump OFF");
        delay(1000);
    } else {
        digitalWrite(RELAY1, 1);
        Serial.println("Pump ON");
        delay(1000);
    }
    digitalWrite(soilPower2, LOW);
    return val2;
}
