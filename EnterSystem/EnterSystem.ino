#include <Servo.h>

#define echoPin 3
#define trigPin 2
#define ledPin 9
#define pwmPin 10
#define speakerPin 8
Servo servo;

int intruderDetectionRate = 100;

float Duration = 0;
float Distance = 0;
bool isContinues = false;

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  servo.attach(10, 500, 2400);

  
}

void loop() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH );
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  Duration = pulseIn(echoPin, HIGH);
  Duration = Duration / 2;
  Distance = Duration * 340 * 100 / 1000000;
  if (Distance < 160) {
    if (isContinues == false) {
      runRundom();
      isContinues = true;
      digitalWrite(ledPin, HIGH);
      playMusic();
    }
    // Serial.print(Distance);
    // Serial.println(" cm");
  } else {
    digitalWrite(ledPin, LOW);
    servo.write(90);
    isContinues = false;
  }
  delay(500);
}

void runRundom() {
  int randomNumber;
  randomNumber = random(0, intruderDetectionRate + 1);
  if (randomNumber == 0) {
    servo.write(0);
    Serial.println("不審者発見！！！");
  } else {
    Serial.println("異常なし");
  }
}

inline double freq(int x) {
  return 440 * pow(2, x / 12.);
}

float c = 523;
float d = 587;
float e = 659;
float f = 698;
float g = 784;
float a = 880;
float b = 988;

void playMusic() {
  static const int xs[][2] = {
    {11, 400}, {7, 400}, {2, 400}, {7, 400}, {9, 400}, {14, 800}, {2, 400}, {9, 400}, {11, 400}, {9, 400}, {2, 400}, {7, 400}
  };
  for (int i = 0; i < sizeof(xs); ++i) {
    tone(speakerPin, 	freq(xs[i][0]));
    delay(xs[i][1]);
  }
  noTone(speakerPin);
}


// 167
