class MotionDetector {
public:
  virtual void handleMotion() = 0;
  virtual void handleNoMotion() = 0;
};

class SimpleMotionDetector : public MotionDetector {
private:
  int statusIndicatorPin;
  volatile int* detectionStatus;

public:
  SimpleMotionDetector(int indicatorPin, volatile int* status)
      : statusIndicatorPin(indicatorPin), detectionStatus(status) {}

  void handleMotion() override {
    digitalWrite(statusIndicatorPin, HIGH);
    Serial.println("Motion detected!");
    delay(1000);  // Adjust this delay cautiously; it may affect interrupt responsiveness
    digitalWrite(statusIndicatorPin, LOW);
    *detectionStatus = 1;
  }

  void handleNoMotion() override {
    Serial.println("No motion detected");
    // Consider whether you want to reset detectionStatus to 0 here
    // Depending on your application, you may want to keep the last status until a new motion event occurs.
    // *detectionStatus = 0;
  }
};

const int motionSensorInterrupt = 2;
const int statusIndicatorPin = 6;
volatile int detectionStatus = 0;

MotionDetector* motionDetector;

void setup() {
  Serial.begin(9600);
  Serial.println("Motion Detection System Initialized");

  pinMode(statusIndicatorPin, OUTPUT);
  motionDetector = new SimpleMotionDetector(statusIndicatorPin, &detectionStatus);
  attachInterrupt(digitalPinToInterrupt(motionSensorInterrupt), handleMotionInterrupt, HIGH);
}

void loop() {
  // The loop is intentionally left empty
  // All logic is moved to the handleMotionInterrupt function
}

void handleMotionInterrupt() {
  int sensorValue = digitalRead(motionSensorInterrupt);

  if (sensorValue == HIGH) {
    motionDetector->handleMotion();
  } else {
    motionDetector->handleNoMotion();
  }
}
