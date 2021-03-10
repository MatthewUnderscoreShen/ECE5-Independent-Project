#define joyX A4
#define joyY A5
#define LCD_DC 9
#define LCD_CS 10
#define buttonJoy 11
#define buttonB 12
#define buttonA 13

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Fonts/FreeSans9pt7b.h"

Adafruit_ILI9341 lcd = Adafruit_ILI9341(LCD_CS, LCD_DC);

int x, y; //joystick inputs
int a, b, aLast, bLast; //button inputs
int aDelay, bDelay; //frame delay after pressing a button
int buttonDelay = 3;
bool aPress, bPress; //is a or b pressed?
int DASFrame; //start frame for das
bool DAS; //has das delay happened yet?
bool lock; //should the piece be locked?
int ARE; //entry delay
int clearDelay = 0;
bool clearline = false; //clear line?
int linesToClear; //which lines to clear (it's like a string)
int refresh = 16; //game refresh rate in milliseconds
int fallSpeed = 48; //How many frames it takes to fall one block
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
  int color; //color
  int startFrame; //frame where piece was entered
  int ori[2][4]; //piece matrix
};
typedef struct piece Piece;

//Initializing pieces.
// 0:I  1:O  2:T  3:J  4:L  5:S  6:Z
Piece pieces[] = {
      (Piece){-1, 1, 10, 38, ILI9341_CYAN, 0, {
                {-3, -1, 1, 3}, //x
                { 1,  1, 1, 1}  //y
             }}, //I piece
      (Piece){1, 1 , 8, 36, ILI9341_YELLOW, 0, { 
                {-1, -1,  1, 1},
                {-1,  1, -1, 1} 
             }}, //O piece
      (Piece){0, 0, 8, 36, ILI9341_MAGENTA, 0, {
                {0, -2, 0, 2},
                {0,  0, 2, 0}
             }}, //T piece
      (Piece){0, 0, 8, 36, ILI9341_BLUE, 0, {
                {0, -2, -2, 2},
                {0,  2,  0, 0}
             }}, //J piece
      (Piece){0, 0, 8, 36, ILI9341_ORANGE, 0, {
                {0, -2, 2, 2},
                {0,  0, 0, 2}
             }}, //L piece
      (Piece){0, -1, 8, 36, ILI9341_GREENYELLOW, 0, {
                {-2,    0,   0,   2},
                {-0.5, -0.5, 0.5, 0.5}
             }}, //S piece
      (Piece){0, -1, 8, 36, ILI9341_RED, 0, {
                {-2,   0,    0,    2},
                { 0.5, 0.5, -0.5, -0.5}
             }}  //Z piece
  };

Piece currentPiece;

int rots[][2][2] = 
  { //Rotation matricies
    { {0, -1}, { 1, 0} }, //90deg ccw
    { {1,  0}, { 0, 1} }, //0deg
    { {0,  1}, {-1, 0} }  //90deg cw
  };

  void printBoard() {
    lcd.drawRect(6, 32, 122, 282, ILI9341_LIGHTGREY);
    for (int i = 38; i >= 0; i = i - 2) {
      for (int j = 0; j < 20; j = j + 2) {
        lcd.fillRect(7 + 6*j, 7*(38-i) + 33, 12, 14, board[i][j]); 
        lcd.drawRect(7 + 6*j, 7*(38-i) + 33, 12, 14, ILI9341_LIGHTGREY);
      }
    }
  }

  void printPiece(int c) {
    for (int i = 0; i < 4; i++) {
      lcd.fillRect(7 + 6*(currentPiece.xPos + currentPiece.xOff + currentPiece.ori[0][i]), 
                   7*(38-(currentPiece.yPos + currentPiece.yOff + currentPiece.ori[1][i])) + 33,
                   12, 14, c);
      lcd.drawRect(7 + 6*(currentPiece.xPos + currentPiece.xOff + currentPiece.ori[0][i]), 
                   7*(38-(currentPiece.yPos + currentPiece.yOff + currentPiece.ori[1][i])) + 33,
                   12, 14, ILI9341_LIGHTGREY);
    }
  }

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
    currentPiece.color = pieces[pieceNum].color;
    for (int i = 0; i < 8; i++) {
      currentPiece.ori[i/4][i%4] = pieces[pieceNum].ori[i/4][i%4];
    }
    currentPiece.startFrame = t/refresh;

    if (checkCollision()) {
      Serial.println("Game Over");
      gameState = false;
      return;
    }

    activePiece = true;
    lastPiece = pieceNum;
  }

  void movePiece(int dx, int dy, int dRot) {
    if (dx == 0 && ((t/refresh-currentPiece.startFrame)%(fallSpeed/dy) != 0) && dRot == 1) {
      return;
    }
    
    if (boundsCheck(dx, dy, rots[dRot])) { //both directions pass
      printPiece(ILI9341_BLACK);
      currentPiece.xPos = currentPiece.xPos + dx;
      currentPiece.yPos = currentPiece.yPos + ((t/refresh-currentPiece.startFrame)%(fallSpeed/dy) == 0 ? -2 : 0);
      matrixMult(rots[dRot], currentPiece.ori, currentPiece.ori);
      printPiece(currentPiece.color);
    } else if (boundsCheck(dx, 0, rots[dRot])){ //vertical fail
      printPiece(ILI9341_BLACK);
      currentPiece.xPos = currentPiece.xPos + dx;
      matrixMult(rots[dRot], currentPiece.ori, currentPiece.ori);
      lock = true;
      printPiece(currentPiece.color);
    } else if (boundsCheck(0, dy, rots[dRot])) { //horizontal fail
      printPiece(ILI9341_BLACK);
      currentPiece.yPos = currentPiece.yPos + (t/refresh%(fallSpeed/dy) == 0 ? -2 : 0);
      matrixMult(rots[dRot], currentPiece.ori, currentPiece.ori);
      //DAS
      printPiece(currentPiece.color);
    } else { //both directions fail
      return;
    }
  }

  void checkLock() {
    if (lock) {
      for (int i = 0; i < 4; i++) {
        board[currentPiece.xPos + currentPiece.xOff + currentPiece.ori[0][i]][currentPiece.yPos + currentPiece.yOff + currentPiece.ori[1][i]] = currentPiece.color;
      }
      activePiece = false;
      //ARE = 10 + ((currentPiece.yPos + 2)/4)*2
    }
  }

  void checkLineClear() {
    if (lock) {
      for (int i = 0; i < 40; i = i + 2) {
        for (int j = 0; j < 20; j = j + 2) {
          
        }
      }
    }
  }

  bool checkCollision() { //Checks to see if the current block is colliding with a placed block
    for (int i = 0; i < 4; i++) {
      if (board[ currentPiece.xPos + currentPiece.xOff + currentPiece.ori[0][i] ][ currentPiece.yPos + currentPiece.yOff + currentPiece.ori[1][i] ] > 0) {
        return true;
      }
    }
    return false;
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
      if (board[xNew][yNew] != 0) { return false; }
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

  int getdRots(int aIn, int alIn, int bIn, int blIn) {
    int rot = 1;
    if (aIn > 0 && alIn == 0) {
      if (aDelay == 0) {
        aDelay = buttonDelay;
        rot = rot + 1;
        Serial.println("cw");
      }
    }
    if (bIn > 0 && blIn == 0) {
      if (bDelay == 0) {
        bDelay = buttonDelay;
        rot = rot - 1;
        Serial.println("ccw");
      }
    }
    aDelay = (aDelay == 0) ? 0 : aDelay - 1;
    bDelay = (bDelay == 0) ? 0 : bDelay - 1;
    return rot;
  }

//-------------------------------------------------------------------------------

  void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    lcd.begin();
    uint8_t lcdRead = lcd.readcommand8(ILI9341_RDMODE);
    lcd.setRotation(2);
    pinMode(buttonA, INPUT);
    pinMode(buttonB, INPUT);
    for (int i = 0; i < 800; i++) { //initalizes the board
      board[i / 20][i % 20] = 0x0000;
    }

    lcd.fillScreen(ILI9341_BLACK);
    printBoard();

    ARE = 10;
    aDelay = 0;
    bDelay = 0;

    aLast = 0;
    bLast = 0;
    tLast = 0;
  }

  void loop() {
    // put your main code here, to run repeatedly:
    t = millis();
    
    //
    //GAME LOOP START--------------------------------------------------------
    //
    if (t % refresh == 0 && tLast != t) { //Game loop

      x = analogRead(joyX);
      y = analogRead(joyY);
      a = a + digitalRead(buttonA);
      b = b + digitalRead(buttonB);

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

      //printPiece(ILI9341_BLACK);
      
      movePiece(getdx(x), getdy(y), getdRots(a, aLast, b, bLast)); //moves piece

      checkLock();

      //checkLine();

      //printPiece(currentPiece.color);

      aLast = a;
      bLast = b;
      a = 0;
      b = 0;
    }
    //
    //GAME LOOP END-------------------------------------------------------------
    //

/*
    Serial.print(x);
    Serial.print("\t");
    Serial.println(y);
*/
    tLast = t;
  }
