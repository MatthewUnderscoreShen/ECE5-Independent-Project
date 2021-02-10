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
int board[20][10];
int pieces[][4][2] = 
  { { {0, 0}, { -1, 0}, {1, 0},   {2, 0} }, //I piece
    { {0, 0}, {1, 0},   {0, 1},   {1, 1} }, //O piece
    { {0, 0}, { -1, 0}, {0, 1},   {1, 0} }, //T piece
    { {0, 0}, { -1, 1}, { -1, 0}, {1, 0} }, //J piece
    { {0, 0}, { -1, 0}, {1, 0},   {1, 1} }, //L piece
    { {0, 0}, { -1, 0}, {0, 1},   {1, 1} }, //S piece
    { {0, 0}, { -1, 1}, {0, 1},   {1, 0} }  //Z piece
  };
/*
int rots[][2][2] = 
  { { {0, 1},  {-1, 0} }, //90deg ccw around origin
    { {0, -1}, {1, 0}  }, //90deg cw around origin
    { 
*/
  void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(buttonA, INPUT);
    pinMode(buttonB, INPUT);
    for (int i = 0; i < 200; i++) {
      board[i / 10][i % 10] = 0;
    }
  }

  void loop() {
    // put your main code here, to run repeatedly:
    x = analogRead(joyX);
    y = analogRead(joyY);
    a = digitalRead(buttonA);
    b = digitalRead(buttonB);

    
    
    /*
    Serial.print(a);
    Serial.print("\t");
    Serial.print(b);
    Serial.print("\t");
    Serial.print(x);
    Serial.print("\t");
    Serial.println(y);
    */
  }
