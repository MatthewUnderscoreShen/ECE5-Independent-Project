#define joyX A4
#define joyY A5
#define buttonJoy 11
#define buttonA 12
#define buttonB 13

struct piece {
  int x, y;
  int ori[4][2];
  int rot[2][2];
};

double x, y;
int a, b;
int board[21][10];
int pieces[][4][2] = { {{0, 0}, {-1, 0}, {1, 0},  {2, 0} }, //I piece
                        {{0, 0}, {1, 0},  {0, -1}, {1, -1}}, //O piece
                        {{0, 0}, {-1, 0}, {0, 1},  {1, 0} }, //T piece
                        {{0, 0}, {

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  for (int i = 0; i < 210; i++) {
    board[i / 10][i % 10] = 0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  x = analogRead(joyX);
  y = analogRead(joyY);
  a = digitalRead(buttonA);
  b = digitalRead(buttonB);
  Serial.print(a);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.println(y);
}
