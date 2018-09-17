int leftMotor  = 11;
int rightMotor = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);
  analogWrite(leftMotor, 128);
  analogWrite(rightMotor, 128);
}

void loop() {
  // put your main code here, to run repeatedly:
  forward(75, 2000);
  //delay(2000);
  turn(75, 25, 2000, 1);
  delay(2000);
  turn(25, 75, 2000, 1);
  delay(2000);
}

void stahp(){
  analogWrite(leftMotor, 127);
  analogWrite(rightMotor, 127);
}

void stahp_slow(){
  analogWrite(leftMotor, 128);
  analogWrite(rightMotor, 128);
}

void forward(int spd, int dur){
  analogWrite(leftMotor, 128+spd);
  analogWrite(rightMotor, 128+spd);
  delay(dur);
  stahp();
}

void turn(int lspd, int rspd, int dur, int dir) {
  analogWrite(leftMotor, 128+(dir*lspd));
  analogWrite(rightMotor, 128+(dir*rspd));
  delay(dur);
  stahp();
}

void backward(int spd, int dur){
  analogWrite(leftMotor, 128-spd);
  analogWrite(rightMotor, 128-spd);
  delay(dur);
  stahp();
}
