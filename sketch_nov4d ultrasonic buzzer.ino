#define trigPin 9
#define echoPin 10

const int buzzerPin = 6;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  long duration, distance;
  
  // Trigger the ultrasonic sensor to send a pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time it takes for the echo to return
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration / 58.2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Play an "echo" sound based on the distance
  if (distance <= 10) {
    playEchoSound(3); // Play 3 "echoes" when an object is detected within 100 cm
  } else if (distance <= 15) {
    playEchoSound(2); // Play 2 "echoes" when an object is detected between 100 and 150 cm
  } else {
    noTone(buzzerPin); // Stop playing sound when no object is detected
  }

  delay(1000); // Delay before taking the next reading
}

void playEchoSound(int numEchoes) {
  for (int i = 0; i < numEchoes; i++) {
    tone(buzzerPin, 1000, 100); // Play a 1 kHz tone for 100 ms
    delay(200); // Delay between "echoes"
  }
  noTone(buzzerPin); // Stop playing sound after all "echoes"
}
