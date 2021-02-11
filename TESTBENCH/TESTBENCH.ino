#define joyX A4
#define joyY A5
#define buttonJoy 11
#define buttonA 12
#define buttonB 13

double x, y; //joystick inputs
int a, b; //button inputs
int refresh = 2000; //game refresh rate in milliseconds
int pieceNum = 0; //piece number
bool gameState = false;
bool activePiece = false;

int board[20][10];

struct piece {
  int xOff; //offsets define what to add to the matrix
  int yOff; //to shift it to the board
  int x; //location
  int ori[2][4];
};
typedef struct piece Piece;

//Initializing pieces.
// 0:I  1:O  2:T  3:J  4:L  5:S  6:Z
Piece pieces[] = {
      (Piece){-0.5, 0.5, 4, 20, {
                {-1.5, -0.5, 0.5, 1.5},
                { 0.5,  0.5, 0.5, 0.5}
             }}, //I piece
      (Piece){0.5, 0.5 , 4, 19, { 
                {-0.5, -0.5,  0.5, 0.5},
                {-0.5,  0.5, -0.5, 0.5} 
             }}, //O piece
      (Piece){0, 0, 4, 19, {
                {0, -1, 0, 1},
                {0,  0, 1, 0}
             }}, //T piece
      (Piece){0, 0, 4, 19, {
                {0, -1, -1, 1},
                {0,  1,  0, 0}
             }}, //J piece
      (Piece){0, 0, 4, 19, {
                {0, -1, 1, 1},
                {0,  0, 0, 1}
             }}, //L piece
      (Piece){0, 0, 4, 19, {
                {0, -1, 0, 1},
                {0,  0, 1, 1}
             }}, //S piece
      (Piece){0, 0, 4, 19, {
                {0, -1, 0, 1},
                {0,  1, 1, 0}
             }}  //Z piece
  };

Piece currentPiece;

int rots[][2][2] = 
  { //Rotation matricies
    { {0, -1},  {1, 0} }, //90deg ccw around origin
    { {0,  1}, {-1, 0} }  //90deg cw around origin
  };

  
  void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(buttonA, INPUT);
    pinMode(buttonB, INPUT);
    for (int i = 0; i < 200; i++) { //
      board[i / 10][i % 10] = 0;
    }
  }

  void loop() {
    // put your main code here, to run repeatedly:
    x = analogRead(joyX);
    y = analogRead(joyY);
    a = digitalRead(buttonA);
    b = digitalRead(buttonB);

    setPiece(); //Sets the piece if not already set
    //At this point the piece should be active and initial position set

    for (int i = 0; i < 8; i++) {
      if (i%4 == 0) { Serial.println(""); }
      Serial.print(currentPiece.ori[i/4][i%4]);
      Serial.print("  ");
    }
    Serial.println("");

    delay(refresh);
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

  void setPiece() {
    if (activePiece) { return; }
    pieceNum = 1;
    currentPiece.xOff = pieces[pieceNum].xOff;
    currentPiece.yOff = pieces[pieceNum].yOff;
    currentPiece.x = pieces[pieceNum].x;
    currentPiece.y = pieces[pieceNum].y;
    for (int i = 0; i < 8; i++) {
      currentPiece.ori[i/4][i%4] = pieces[pieceNum].ori[i/4][i%4];
    }

    activePiece = true;
  }
