#define echoPin 11
#define trigPin 12

double Duration = 0;
double Distance = 0;

void setup() {
	Serial.begin(9600);
	pinMode(6, OUTPUT);
	pinMode(5, INPUT);
	pinMode(4, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(trigPin, OUTPUT);
}

static int prev_x;
static int x;

void loop() {
	digitalWrite(6, HIGH);
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	Duration = pulseIn(echoPin, HIGH);
	if (Duration > 0) {
		Duration = Duration/2;
		Distance = Duration*340*100/1000000;
		// Serial.print("Distance:");
		// Serial.print(Distance);
		// Serial.println(" cm");
	}

	double cm = Distance;
	switch ((int)floor(cm / 3.7)) {
		case 0:
			x = 3;
			Serial.println("C");
			break;
		case 1:
			x = 5;
			Serial.println("D");
			break;
		case 2:
			x = 7;
			Serial.println("E");
			break;
		case 3:
			x = 8;
			Serial.println("F");
			break;
		case 4:
			x = 10;
			Serial.println("G");
			break;
		case 5:
			x = 12;
			Serial.println("A");
			break;
		case 6:
			x = 14;
			Serial.println("B");
			break;
		case 7:
			x = 15;
			Serial.println("C");
			break;
		default:
			x = -1;
			noTone(5);
	}
	if (x > 0 && x != prev_x) {
		double note = 440 * pow(2, x / 12.);
		tone(5, round(note));
	}
	prev_x = x;
	return;
}
