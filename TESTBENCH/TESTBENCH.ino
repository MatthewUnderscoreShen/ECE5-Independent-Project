#define joyX A4
#define joyY A5
#define buttonJoy 11
#define buttonA 12
#define buttonB 13





double x, y;
int a, b;
bool gameState = false;

int board[20][10];

int rots[][2][2] = 
  { 
    { {0, 1},  {-1, 0} }, //90deg cw around origin
    { {0, -1}, {1, 0}  }  //90deg ccw around origin
  };
  
struct piece {
  int xOff; //offsets define what to add to the matrix
  int yOff; //to shift it to the board
  int xStart; //starting point of piece center
  int yStart;
  int ori[2][4];
};
typedef struct piece Piece;

Piece IPiece = (Piece){-0.5, 0.5, 4, 20, {
                          {-1.5, -0.5, 0.5, 1.5},
                          { 0.5,  0.5, 0.5, 0.5}
                      }};
Piece OPiece = (Piece){0.5, 0.5 , 4, 19, { 
                          {0, 1, 0, 1},
                          {0, 0, 1, 1} 
                      }};
Piece TPiece = (Piece){0, 0, 4, 19, {
                          {0, -1, 0, 1},
                          {0,  0, 1, 0}
                      }};
Piece JPiece = (Piece){0, 0, 4, 19, {
                          {0, -1, -1, 1},
                          {0,  1,  0, 0}
                      }};
Piece LPiece = (Piece){0, 0, 4, 19, {
                          {0, -1, 1, 1},
                          {0,  0, 0, 1}
                      }};
Piece SPiece = (Piece){0, 0, 4, 19, {
                          {0, -1, 0, 1},
                          {0,  0, 1, 1}
                      }};
Piece SPiece = (Piece){0, 0, 4, 19, {
                          {0, -1, 0, 1},
                          {0,  1, 1, 0}
                      }};

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
