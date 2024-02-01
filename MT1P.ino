#define pirPin 5
#define ledPin 6

volatile bool ismotionDetected = false;

void interruptPIR() {
    ismotionDetected = true;
}

void setup() {
    pinMode(pirPin, INPUT);
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);

    attachInterrupt(digitalPinToInterrupt(pirPin), interruptPIR, RISING);
}

void loop() {

    if(ismotionDetected){
        digitalWrite(ledPin, HIGH);
        Serial.println("Motion detected! Turning on LED.");
        ismotionDetected = false;
    }
    else{
        digitalWrite(ledPin, LOW);
        Serial.println("No motion detected. Turning off LED.");
    }
   
    delay(1000);
}

