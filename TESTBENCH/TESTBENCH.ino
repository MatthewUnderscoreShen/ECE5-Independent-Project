#define joyX A4
#define joyY A5
#define buttonJoy 11
#define buttonA 12
#define buttonB 13

double x, y; //joystick inputs
int a, b; //button inputs
int refresh = 250; //game refresh rate in milliseconds
int pieceNum = 0; //piece number
int lastPiece;
int t = 0;
bool gameState = false;
bool activePiece = false;

int board[40][20];

struct piece {
  int xOff; //offsets define what to add to the matrix
  int yOff; //to shift it to the board
  int xPos; //location
  int yPos;
  int ori[2][4];
};
typedef struct piece Piece;

//Initializing pieces.
// 0:I  1:O  2:T  3:J  4:L  5:S  6:Z
Piece pieces[] = {
      (Piece){-1, 1, 8, 40, {
                {-3, -1, 1, 3}, //x
                { 1,  1, 1, 1}  //y
             }}, //I piece
      (Piece){1, 1 , 8, 38, { 
                {-1, -1,  1, 1},
                {-1,  1, -1, 1} 
             }}, //O piece
      (Piece){0, 0, 8, 38, {
                {0, -2, 0, 2},
                {0,  0, 2, 0}
             }}, //T piece
      (Piece){0, 0, 8, 38, {
                {0, -2, -2, 2},
                {0,  2,  0, 0}
             }}, //J piece
      (Piece){0, 0, 8, 38, {
                {0, -2, 2, 2},
                {0,  0, 0, 2}
             }}, //L piece
      (Piece){0, -1, 8, 38, {
                {-2,    0,   0,   2},
                {-0.5, -0.5, 0.5, 0.5}
             }}, //S piece
      (Piece){0, -1, 8, 38, {
                {-2,   0,    0,    2},
                { 0.5, 0.5, -0.5, -0.5}
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
    for (int i = 0; i < 800; i++) { //initalizes the board
      board[i / 20][i % 20] = 0;
    }
  }

  void loop() {
    // put your main code here, to run repeatedly:
    t = millis();
    x = analogRead(joyX);
    y = analogRead(joyY);
    a = digitalRead(buttonA);
    b = digitalRead(buttonB);

    if (gameState == false) {
      if (t % 5000 == 0) {
        Serial.println("Game currently inactive");
      }
    }
    if (t % refresh == 0) {
      setPiece();
      movePiece();
    }
    setPiece(); //Sets the piece if not already set
    //At this point the piece should be active and initial position set

    if (gameState == false) { //Check for game over
      return;
    }
    
    //movePiece(); //Moves and/or rotates the piece.

    /*
    for (int i = 0; i < 8; i++) {
      if (i%4 == 0) { Serial.println(""); }
      Serial.print(currentPiece.ori[i/4][i%4]);
      Serial.print("  ");
    }
    Serial.println("");
    */
    Serial.println(t);

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

  void setPiece() { //this function chooses and sets the piece
    if (activePiece) { return; }
    pieceNum = 1;
    currentPiece.xOff = pieces[pieceNum].xOff;
    currentPiece.yOff = pieces[pieceNum].yOff;
    currentPiece.xPos = pieces[pieceNum].xPos;
    currentPiece.yPos = pieces[pieceNum].yPos;
    for (int i = 0; i < 8; i++) {
      currentPiece.ori[i/4][i%4] = pieces[pieceNum].ori[i/4][i%4];
    }

    if (checkCollision) {
      Serial.println("Game Over");
      gameState = false;
      return;
    }

    activePiece = true;
  }

  void movePiece() {
    //currentPiece
  }

  bool checkCollision() { //Checks to see if the current block is colliding with a placed block
    for (int i = 0; i < 4; i++) {
      if (board[ currentPiece.xPos + currentPiece.xOff + currentPiece.ori[0][i] ][ currentPiece.yPos + currentPiece.yOff + currentPiece.ori[1][i] ] == 1) {
        return false;
      }
    }
    return true;
  }
