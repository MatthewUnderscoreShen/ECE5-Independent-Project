#define joyX A4
#define joyY A5
#define buttonJoy 11
#define buttonA 12
#define buttonB 13

double x, y; //joystick inputs
int a, b; //button inputs
int refresh = 1000; //game refresh rate in milliseconds
int fallSpeed = 2; //How many frames it takes to fall one block
int pieceNum = 0; //piece number
int lastPiece;
int t = 0;
int tLast = 0;
bool gameState = true;
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
      (Piece){-1, 1, 8, 0, {
                {-3, -1, 1, 3}, //x
                { 1,  1, 1, 1}  //y
             }}, //I piece
      (Piece){1, 1 , 8, 2, { 
                {-1, -1,  1, 1},
                {-1,  1, -1, 1} 
             }}, //O piece
      (Piece){0, 0, 8, 2, {
                {0, -2, 0, 2},
                {0,  0, 2, 0}
             }}, //T piece
      (Piece){0, 0, 8, 2, {
                {0, -2, -2, 2},
                {0,  2,  0, 0}
             }}, //J piece
      (Piece){0, 0, 8, 2, {
                {0, -2, 2, 2},
                {0,  0, 0, 2}
             }}, //L piece
      (Piece){0, -1, 8, 2, {
                {-2,    0,   0,   2},
                {-0.5, -0.5, 0.5, 0.5}
             }}, //S piece
      (Piece){0, -1, 8, 2, {
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

    if (checkCollision()) {
      Serial.println("Game Over");
      gameState = false;
      return;
    }

    activePiece = true;
  }

  void movePiece(int currentT, bool isOut) {
    if ((currentT / refresh % fallSpeed == 0) && !isOut) { //Fall
      currentPiece.yPos = currentPiece.yPos + 2;
    }
  }

  bool checkCollision() { //Checks to see if the current block is colliding with a placed block
    for (int i = 0; i < 4; i++) {
      if (board[ currentPiece.xPos + currentPiece.xOff + currentPiece.ori[0][i] ][ currentPiece.yPos + currentPiece.yOff + currentPiece.ori[1][i] ] == 1) {
        return true;
      }
    }
    return false;
  }

  void printBoard() {
    Serial.println("------------------------------");
    for (int i = 0; i < 40; i = i + 2) {
      for (int j = 0; j < 20; j = j + 2) {
        Serial.print(" ");
        if (currentPiece.xPos + currentPiece.xOff + currentPiece.ori[0][0] == j && currentPiece.yPos + currentPiece.yOff + currentPiece.ori[1][0] == i) {
          Serial.print("1");
        } else if (currentPiece.xPos + currentPiece.xOff + currentPiece.ori[0][1] == j && currentPiece.yPos + currentPiece.yOff + currentPiece.ori[1][1] == i) {
          Serial.print("1");
        } else if (currentPiece.xPos + currentPiece.xOff + currentPiece.ori[0][2] == j && currentPiece.yPos + currentPiece.yOff + currentPiece.ori[1][2] == i) {
          Serial.print("1");
        } else if (currentPiece.xPos + currentPiece.xOff + currentPiece.ori[0][3] == j && currentPiece.yPos + currentPiece.yOff + currentPiece.ori[1][3] == i) {
          Serial.print("1");
        } else {
          Serial.print(board[i][j]);
        }
        Serial.print(" ");
      }
      Serial.println("");
    }
    Serial.println("------------------------------");
  }

  boolean boundsCheck(int dx, int dy/*, int[][] dRot*/) { //returns true if proposed transformation puts piece out of bounds
    int xNew;
    int yNew;
    //int[][] oriNew = matrixMult(dRot, currentPiece.ori);
    for (int i = 0; i < 4; i++) {
      xNew = currentPiece.xPos + dx + currentPiece.xOff + currentPiece.ori[0][i]; //oriNew[0][i];
      yNew = currentPiece.yPos + dy + currentPiece.yOff + currentPiece.ori[1][i]; //oriNew[1][i];
      if (xNew < 0 || xNew > 40) {
        return true;
      }
      if (yNew < 0 || xNew > 80) {
        return true;
      }
    }
    return false;
  }
/*
  int[][4] matrixMult(int[][2] A, int[][4] B) { //2x2 matrix times 2x4 matrix
    int[2][4] M;
    for (int i = 0; i < 8; i++) {
      M[i/4][i%4] = A[i/4][0]*B[0][i%4] + A[i/4][1]B[1][i%4];
    }
    return M;
  }
  */

//-------------------------------------------------------------------------------

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
      if (t % 5000 == 0 && tLast != t) {
        Serial.println(t);
        Serial.println("Game currently inactive");
      }
      tLast = t;
      return;
    }

    //
    //GAME LOOP START------------------------------
    //
    if (t % refresh == 0 && tLast != t) { //Game loop
      setPiece(); //Places piece on board
      
      if (gameState == false) { //checks for game over
        Serial.println("Game Over");
        tLast = t;
        return;
      }
      
      movePiece(t, boundsCheck(0, 2)); //moves piece

      printBoard();
    }
    //
    //GAME LOOP END------------------------------------
    //

    tLast = t;
  }
