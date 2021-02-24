
int T[2][4] = {{0,0,1,0},{0,1,1,1}};
int L[2][4] = {{0,0,0,1},{0,1,1,1}};
int J[2][4] = {{0,1,1,1},{0,0,0,1}};
int O[2][4] = {{0,1,1,0},{0,1,1,0}};
int I[2][4] = {{0,0,0,0},{1,1,1,1}};
int Z[2][4] = {{0,1,1,0},{0,0,1,1}};
int S[2][4] = {{0,0,1,1},{0,1,1,0}};

void setup() {
  Serial.begin(9600);

}


void matrixPrinter(int matrix[2][4]) {

  int i;
  int j;

  for (i = 0;i < 2;i++) {
      for (j = 0;j < 4;j++) {
        Serial.print(matrix[i][j]); 
      }
      Serial.print('\n');
  }
}


void SevenSided(int R_var) {

  if (R_var == 1) {
    matrixPrinter(T);
  }
  else if (R_var == 2) {
    matrixPrinter(L);
  }
  else if (R_var == 3) {
    matrixPrinter(J);
  }
  else if (R_var == 4) {
    matrixPrinter(O);
  }
  else if (R_var == 5) {
    matrixPrinter(I);
  }
  else if (R_var == 6) {
    matrixPrinter(Z);
  }
  else if (R_var == 7) {
    matrixPrinter(S); 
  }
}

int RandomVar = random(1,8);

void PieceRandomizer(int R_var) {

  int Old_RandomVar = RandomVar;
  
  SevenSided(RandomVar);
  RandomVar = random(1,8);
  
  int New_RandomVar = RandomVar;
  if (New_RandomVar==Old_RandomVar) {
    RandomVar = random(1,8);
  }
  
}

void loop() 
{ 
  PieceRandomizer(RandomVar);
  
  delay(2000);
  Serial.print('\n');
}
