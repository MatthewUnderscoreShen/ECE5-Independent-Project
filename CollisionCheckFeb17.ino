int Background[40][20];
int TetrisPiece[2][4]; //placeholder tetris piece, put real pieces later

void Piece_to_background(int piece[2][4],int row_Num,int col_Num) {
  int i;
  int j;
  
  //Places contents of Piece matrix into the background matrix,
  //starting at the desired row and column of the background matrix
  
  for (i = 0 ;i < sizeof(piece[0]) ;i++) {
    for (j = 0 ;j < sizeof(piece[1]) ;j++) {
      Background[row_Num + i][col_Num + j] = piece[i][j];
    }
  }
}

void CollisionCheck(int CurrentRow, int CurrentCol){

  int EmptySpace[2][4] = {{0,0,0,0},{0,0,0,0}};

  int RandomVar = random(1,8);
  
  int i;
  int j;

  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      if (Background[CurrentRow + i][CurrentCol + j] == EmptySpace[i][j]) {
        CurrentRow = CurrentRow + 1; //put some stuff in here to move the TetrisPiece down one i somehow, implement millis function
      }
      else if (Background[CurrentRow + i][CurrentCol + j] != EmptySpace[i][j]) {
        Piece_to_background(TetrisPiece, CurrentRow - 1, CurrentCol); //places the tetris piece in the background matrix one row above where there is no more space in the background
        PieceRandomizer(RandomVar);    //fucntion I wrote in another file        
        //for (i= 0; i < 2; i++) {    (this might not be needed)
          //for (j = 0; j < 4; j++) {
            //TetrisPiece[i][j] = NewPiece[i][j]; //implement NewPiece as the result from SevenSided function instead of matrixPrinter
          }
        }
      }
    }
  }
}









void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
