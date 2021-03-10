#define joyX A4
#define joyY A5
#define buttonJoy 11
#define buttonA 12
#define buttonB 13

int x, y; //joystick inputs
int a, b, aLast, bLast; //button inputs
long atLast, btLast;
bool aPress, bPress; //is a or b pressed?
bool DAS; //has das delay happened yet?
bool lock; //should the piece be locked?
int refresh = 1000; //game refresh rate in milliseconds
int fallSpeed = 4; //How many frames it takes to fall one block
int bRefresh = 8; //button press refresh rate
int pieceNum = 0; //piece number
int lastPiece = 7;
long t = 0;
long tLast = 0;
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
      (Piece){-1, 1, 10, 38, {
                {-3, -1, 1, 3}, //x
                { 1,  1, 1, 1}  //y
             }}, //I piece
      (Piece){1, 1 , 8, 36, { 
                {-1, -1,  1, 1},
                {-1,  1, -1, 1} 
             }}, //O piece
      (Piece){0, 0, 8, 36, {
                {0, -2, 0, 2},
                {0,  0, 2, 0}
             }}, //T piece
      (Piece){0, 0, 8, 36, {
                {0, -2, -2, 2},
                {0,  2,  0, 0}
             }}, //J piece
      (Piece){0, 0, 8, 36, {
                {0, -2, 2, 2},
                {0,  0, 0, 2}
             }}, //L piece
      (Piece){0, -1, 8, 36, {
                {-2,    0,   0,   2},
                {-0.5, -0.5, 0.5, 0.5}
             }}, //S piece
      (Piece){0, -1, 8, 36, {
                {-2,   0,    0,    2},
                { 0.5, 0.5, -0.5, -0.5}
             }}  //Z piece
  };

Piece currentPiece;

int rots[][2][2] = 
  { //Rotation matricies
    { {1,  0}, { 0, 1} }, //0 deg 
    { {0, -1}, { 1, 0} }, //90deg ccw around origin
    { {0,  1}, {-1, 0} }  //90deg cw around origin
  };

  int choosePiece() {
    int r = random(7);
    return ( (r == 7 || r == lastPiece) ? random(6) : r );
  }

  void setPiece() { //this function chooses and sets the piece
    if (activePiece) { return; }
    pieceNum = choosePiece();
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
    lastPiece = pieceNum;
  }

  void movePiece(int dx, int dy, int dRot[][2]) {
    if (boundsCheck(dx, dy, dRot)) { //both directions pass
      currentPiece.xPos = currentPiece.xPos + dx;
      currentPiece.yPos = currentPiece.yPos + (t/refresh%(fallSpeed/dy) == 0 ? -2 : 0);
      matrixMult(dRot, currentPiece.ori, currentPiece.ori);
    } else if (boundsCheck(dx, 0, dRot){ //vertical fail
      currentPiece.xPos = currentPiece.xPos + dx;
      matrixMult(dRot, currentPiece.ori, currentPiece.ori);
      lock = true;
    } else if (boundsCheck(0, dy, dRot) { //horizontal fail
      currentPiece.yPos = currentPiece.yPos + (t/refresh%(fallSpeed/dy) == 0 ? -2 : 0);
      matrixMult(dRot, currentPiece.ori, currentPiece.ori);
    } else { //both directions fail
      return;
    }
  }

  void checkLock() {
    if (lock) {
      
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
    for (int i = 38; i >=  0; i = i - 2) {
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

  //Matrix A, Matrix B, the matrix to copy to
  void matrixMult(int A[][2], int B[][4], int C[][4]) { //2x2 matrix times 2x4 matrix
    int M[2][4];
    for (int i = 0; i < 8; i++) {
      M[i/4][i%4] = A[i/4][0]*B[0][i%4] + A[i/4][1]*B[1][i%4];
    }
    for (int i = 0; i < 8; i++) {
      C[i/4][i%4] = M[i/4][i%4];
    }
  }

  int boundsCheck(int dx, int dy, int dRot[][2]) {
    int xNew;
    int yNew;
    int oriNew[2][4];
    matrixMult(dRot, currentPiece.ori, oriNew);
    for (int i = 0; i < 4; i++) {
      xNew = currentPiece.xPos + dx + currentPiece.xOff + oriNew[0][i];
      yNew = currentPiece.yPos + (t/refresh%(fallSpeed/dy) == 0 ? -2 : 0) + currentPiece.yOff + oriNew[1][i];
      if (xNew < 0 || xNew > 18) { return false; }
      if (yNew < 0 || yNew > 40) { return false; }
      if (currentPiece.ori[xNew][yNew] == 1) { return false; }
    }
    return true;
  }

  int getdx(double x) {
    if (x < 450) {
      return 2;
    } else if (x > 1000) {
      return -2;
    } else {
      return 0;
    }
  }

  int getdy(double y) {
    return y > 1000 ? 2 : 1;   
  }
/*
  int getdRots(int aIn, int, alIn, int bIn, int blIn) {
    if (aIn == 1 && alIn == 0) {
      return 2;
    } else if (
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

    aLast = 0;
    bLast = 0;
    tLast = 0;    
  }

  void loop() {
    // put your main code here, to run repeatedly:
    t = millis();

    x = analogRead(joyX);
    y = analogRead(joyY);
    a = digitalRead(buttonA);
    b = digitalRead(buttonB);

    if (a == 1 && !aPress && (atLast + 10) == t) {
      aPress = true;
    } else if (a == 1 && !aPress && atLast != t) {
      atLast = t;
    }

    if (b == 1 && !bPress && (btLast + 10) == t) {
      aPress = true;
    } else if (b == 1 && !bPress && btLast != t) {
      atLast = t;
    }
    
    //
    //GAME LOOP START--------------------------------------------------------
    //
    if (t % refresh == 0 && tLast != t) { //Game loop

      //Check if game is active
      if (gameState == false) {
        if (t % 5000 == 0 && tLast != t) {
          Serial.println(t);
          Serial.println("Game currently inactive");
        }
        tLast = t;
        return;
      }

      setPiece(); //Places piece on board

      if (!activePiece) { return; }
      
      movePiece(getdx(x), getdy(y), rots[0]/*rots[getdRot(a, aLast, b, bLast)]*/); //moves piece

      checkLock():

      printBoard();

      aLast = a;
      bLast = b;
    }
    //
    //GAME LOOP END-------------------------------------------------------------
    //

/*
    Serial.print(x);
    Serial.print("\t");
    Serial.println(y);
*/
    aLast = a;
    bLast = b;
    tLast = t;
  }
