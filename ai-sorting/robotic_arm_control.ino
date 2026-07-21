#include <Servo.h>

Servo servo1;
Servo servo2; 
Servo servo3; 
Servo servo6; 

int pos1 = 90;   
int pos2 = 100;
int pos3 = 80;
int pos6 = 0;

void setup() {
  Serial.begin(9600);

  Serial.println("=== CONTROL PANEL ===");
  Serial.println("o/c -> Gripper");
  Serial.println("j/k -> Servo3 (pin 7)");
  Serial.println("n/m -> Servo2 (pin 6)");
  Serial.println("0/1 -> AUTO MODE");
  Serial.println("=====================");

  servo1.attach(4);
  servo1.write(pos1);

  servo2.attach(6);
  servo2.write(pos2);

  servo3.attach(7);
  servo3.write(pos3);

  servo6.attach(8);
  servo6.write(pos6);

  delay(500); 
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input == '\n' || input == '\r') return;

    if (input == '1') {
      Serial.println("AUTO: BOLT");

      do_o(); delay(400);
      do_j(); delay(400);
      do_n(); delay(400);
      do_c(); delay(400);
      do_m(); delay(400);
      do_k(); delay(400);
      bolts(); delay(500);
      do_j(); delay(400);
      do_o(); delay(400);
      do_k(); delay(400);
      boltsr(); delay(400);
    }

    else if (input == '0') {
      Serial.println("AUTO: NUT");

      do_o(); delay(400);
      do_j(); delay(400);
      do_n(); delay(400);
      do_c(); delay(400);
      do_m(); delay(400);
      do_k(); delay(400);
      nuts(); delay(500);
      do_j(); delay(400);
      do_o(); delay(400);
      do_k(); delay(400);
      nutsr(); delay(400);
    }

    else if (input == 'o') do_o();
    else if (input == 'c') do_c();
    else if (input == 'j') do_j();
    else if (input == 'k') do_k();
    else if (input == 'n') do_n();
    else if (input == 'm') do_m();
    else if (input == 'a') bolts();     
    else if (input == 's') boltsr();    
    else if (input == 'd') nuts();      
    else if (input == 'f') nutsr();    

    else {
      Serial.println("Invalid command");
    }
  }
}

void do_o() {
  Serial.println("Opening gripper...");
  moveServoSlow(servo6, pos6, 35);
  pos6 = 35;
  delay(200);
}

void do_c() {
  Serial.println("Closing gripper...");
  moveServoSlow(servo6, pos6, 0);
  pos6 = 0;
  delay(200);
}

void do_j() {
  Serial.println("Servo3 -> 10 deg");
  moveServoSlow(servo3, pos3, 10);
  pos3 = 10;
  delay(200);
}

void do_k() {
  Serial.println("Servo3 -> back to 80 deg");
  moveServoSlow(servo3, pos3, 80);
  pos3 = 80;
  delay(200);
}

void do_n() {
  Serial.println("Servo2 -> 139 deg");
  moveServoSlow(servo2, pos2, 142);
  pos2 = 142;
  delay(200);
}

void do_m() {
  Serial.println("Servo2 -> back to 100 deg");
  moveServoSlow(servo2, pos2, 100);
  pos2 = 100;
  delay(200);
}

void bolts() {
  Serial.println("Servo1 -> BOLT");
  moveServoSlow(servo1, pos1, 30);
  pos1 = 30;
  delay(300);
}

void boltsr() {
  moveServoSlow(servo1, pos1, 90);
  pos1 = 90;
  delay(200);
}

void nuts() {
  Serial.println("Servo1 -> NUT");
  moveServoSlow(servo1, pos1, 150);
  pos1 = 150;
  delay(300);
}

void nutsr() {
  moveServoSlow(servo1, pos1, 90);
  pos1 = 90;
  delay(200);
}

void moveServoSlow(Servo &s, int startAngle, int endAngle) {

  if (startAngle < endAngle) {
    for (int pos = startAngle; pos <= endAngle; pos += 2) {
      s.write(pos);
      delay(25);  
    }
  } 
  else {
    for (int pos = startAngle; pos >= endAngle; pos -= 2) {
      s.write(pos);
      delay(25);
    }
  }
}