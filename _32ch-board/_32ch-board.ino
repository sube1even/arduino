void setup() {
Serial.begin(115200);
}


void loop() {
move(5, 2400, 500);

move(5, 900, 500);

}

void move(int servo, int position, int time) {
Serial.print("#");
Serial.print(servo);
Serial.print("P");
Serial.print(position);
Serial.print("T");
Serial.print(time);
Serial.print("\r");
Serial.print("\n");

delay(time);

}

