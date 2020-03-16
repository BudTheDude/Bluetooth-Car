// Pins of motor 1
#define mpin00 5
#define mpin01 6
// Pins of motor 2
#define mpin10 3
#define mpin11 11
Servo srv;
char c;
int p;
int r;
int lastP = 1;
int lastR = 1;
void setup() {
  // configuration of motor pins as output, initially 0
  digitalWrite(mpin00, 0);
  digitalWrite(mpin01, 0);
  digitalWrite(mpin10, 0);
  digitalWrite(mpin11, 0);
  pinMode (mpin00, OUTPUT);
  pinMode (mpin01, OUTPUT);
  pinMode (mpin10, OUTPUT);
  pinMode (mpin11, OUTPUT);
  // LED pin
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
void StartMotor (int m1, int m2, int forward, int speed)
{
  if (speed == 0) // stop
  {
    digitalWrite(m1, 0);
    digitalWrite(m2, 0);
  }
  else
  {
    if (forward)
    {
      digitalWrite(m2, 0);
      analogWrite(m1, speed); // use PWM
    }
    else
    {
      digitalWrite(m1, 0);
      analogWrite(m2, speed);
    }
  }
}
void delayStopped(int ms)
{
  StartMotor (mpin00, mpin01, 0, 0);
  StartMotor (mpin10, mpin11, 0, 0);
  delay(ms);
}
void loop() {
  if (Serial.available()) {
    p = Serial.parseInt();
    p = constrain(p, -47, 47);
    if (p > 15) {
      p = map(p, 15, 47, 100, 200);
    } else {
      if (p < -15) {
        p = map(p, -15, -47, -100, -200);
      } else
      {
        p = 0;
      }
    }
    if (Serial.available()) {
      r = Serial.parseInt();
      r = constrain(r, -65, 65);
      if (r > 15) {
        r = map(r, 15, 65, 0, 50);
      } else {
        if (r < -15) {
          r = map(r, -15, -65, 0, -50);
        } else
        {
          r = 0;
        }
      }
      if (abs(p - lastP) > 3) {
        if (p >= 0) {
          StartMotor (mpin00, mpin01, 0, p + r);
          StartMotor (mpin10, mpin11, 0, p - r);
        } else {
          if (p < 0) {
            StartMotor (mpin00, mpin01, 1, -p - r);
            StartMotor (mpin10, mpin11, 1, -p + r);
          }
          lastP = p;
        }
      }
    }
  }
}
