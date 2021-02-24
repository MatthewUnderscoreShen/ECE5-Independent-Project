int Background[40][20];

void RowClear_check() { //this function will check if a row is full, so that it clears the row and moves the above rows down
  
  int FullRow[1][20] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
  int EmptyRow[1][20];
  
  int i;
  int j;

  for (i = 0; i < 40; i++) {
    for (j = 0; j < 20; j++) {
      if (Background[CurrentRow][j] == FullRow[0][j]) {
        for (i = 0; i < CurrentRow; i++) {
          for (j = 0; j <20; j++) {
            Background[i + 1][j + 1] = Background[i][j];
            Background[0][j] = EmptyRow[0][j];
          }
        }
      }
    }
  }
}











void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
