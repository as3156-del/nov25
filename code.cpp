#define TRIG 5
#define ECHO 18

long duration;
int distance;
int count = 0;

// distance threshold (in cm) to detect an object
int thresholdDistance = 15;

// flag to avoid multiple counts for one object
bool objectDetected = false;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {

  // --- Trigger the sensor ---
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // --- Read echo ---
  duration = pulseIn(ECHO, HIGH);
  
  // convert to distance (cm)
  distance = duration * 0.034 / 2;

  // print distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // --- Object detection logic ---
  if (distance > 0 && distance < thresholdDistance && !objectDetected) {
    count++;
    objectDetected = true;

    Serial.print("Object Count = ");
    Serial.println(count);
  }

  // reset detection once object moves away
  if (distance >= thresholdDistance) {
    objectDetected = false;
  }

  delay(100);
}
