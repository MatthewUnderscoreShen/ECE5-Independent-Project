int T[4][2] = {{0,0},{1,0},{1,1},{1,0}};
int L[4][2] = {{0,0},{1,0},{1,0},{1,1}};
int J[4][2] = {{0,0},{1,1},{1,0},{1,0}};
int O[4][2] = {{0,0},{1,1},{1,1},{0,0}};
int I[4][2] = {{1,0},{1,0},{1,0},{1,0}};
int Z[4][2] = {{0,0},{0,1},{1,1},{1,0}};
int S[4][2] = {{0,0},{1,0},{1,1},{0,1}};

void setup() {
  Serial.begin(9600);

}


void matrixPrinter(int matrix[4][2]) {

  int i;
  int j;

  for (i = 0;i < 4;i++) {
      for (j = 0;j < 2;j++) {
        Serial.println(matrix[i][j]); 
      }
      Serial.println('\t');
  }
}


void SevenSided(int R_var) {

  if (R_var%8 == 1) {
    matrixPrinter(T);
  }
  else if (R_var%8 == 2) {
    matrixPrinter(L);
  }
  else if (R_var%8 == 3) {
    matrixPrinter(J);
  }
  else if (R_var%8 == 4) {
    matrixPrinter(O);
  }
  else if (R_var%8 == 5) {
    matrixPrinter(I);
  }
  else if (R_var%8 == 6) {
    matrixPrinter(Z);
  }
  else if (R_var%8 == 7) {
    matrixPrinter(S); 
  }
}



void loop() 
{ 
 
  int R_var = rand();
  SevenSided(R_var);

}
