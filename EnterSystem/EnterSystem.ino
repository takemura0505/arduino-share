#include <Servo.h>

#define echoPin 3
#define trigPin 2
#define ledPin 9
#define pwmPin 10
#define speakerPin 8
#define numberof(x) (sizeof(x) / sizeof(x[0]))
Servo servo;

#define LO (-12) +
#define HI (+12) +

#define A 0
#define B 2
#define C 3
#define D 5
#define E 7
#define F 8
#define G 10
#define FL + (-1)
#define SH + (+1)

int intruderDetectionRate = 1;

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
      isContinues = true;
      digitalWrite(ledPin, HIGH);
      runRundom();
    }
    Serial.print(Distance);
    Serial.println(" cm");
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
    playLuckyMusic();
  } else {
    Serial.println("異常なし");
    playDefaultMusic();
  }
}

inline double freq(int x) {
  return 440 * pow(2, x / 12.);
}

void playDefaultMusic() {
  static const int music[][2] = {
    {G, 1},
    {D SH, 1},
    {B FL, 1},
    {D SH, 1},
    {F, 1},
    {HI B FL, 2},
    {LO F, 1},
    {F, 1},
    {G, 1},
    {F, 1},
    {A SH, 1},
    {D SH, 2}
  };
  for (int i = 0, n = numberof(music); i < n; ++i) {
    tone(speakerPin, 	freq(music[i][0]));
    delay(music[i][1] * 400);
  }
  noTone(speakerPin);
}

void playLuckyMusic() {
  static const int music[][2] = {
    {F, 1},
    {F, 1},
    {F, 1},
    {F, 1},
    {HI HI HI HI HI HI F, 1},
    {E FL, 1},
    {HI HI HI HI HI HI F, 1},
    {G, 1},
    {HI HI HI HI HI HI F, 1},
    {F, 8}
  };
  for (int i = 0, n = numberof(music); i < n; ++i) {
    tone(speakerPin, 	freq(music[i][0]));
    delay(music[i][1] * 80);
    noTone(speakerPin);
    delay(80);
  }
  noTone(speakerPin);
}
