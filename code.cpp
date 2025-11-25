#define TRIG 5
#define ECHO 6

long duration;
int distance;
int count = 0;
int thresholdDistance = 15;  // Detect objects within 15 cm
bool objectDetected = false;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {

  // Trigger ultrasonic pulse
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Read echo time
  duration = pulseIn(ECHO, HIGH, 30000); // timeout added

  // Convert to distance (cm)
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Object detected
  if (distance > 0 && distance < thresholdDistance && !objectDetected) {
    count++;
    objectDetected = true;

    Serial.print("Object Count = ");
    Serial.println(count);
  }

  // Reset detection when object goes away
  if (distance >= thresholdDistance) {
    objectDetected = false;
  }

  delay(100);
}
