
void setup() {
  Serial.begin(9600);
  
  struct TetrisPieces {
    int matrix[4][2];
  };
  TetrisPieces T, L, J, O, I, Z, S;

  T.matrix[0][0] = T.matrix[0][1] = T.matrix[1][1] = T.matrix[3][1] = 0;
  T.matrix[1][0] = T.matrix[2][0] = T.matrix[2][1] = T.matrix[3][0] = 1;

  L.matrix[0][0] = L.matrix[0][1] = L.matrix[1][1] = L.matrix[2][1] = 0;
  L.matrix[1][0] = L.matrix[2][0] = L.matrix[3][0] = L.matrix[3][1] = 1;

  J.matrix[0][0] = J.matrix[0][1] = J.matrix[1][0] = J.matrix[2][0] = 0;
  J.matrix[1][1] = J.matrix[2][1] = J.matrix[3][0] = J.matrix[3][1] = 1;

  O.matrix[0][0] = O.matrix[0][1] = O.matrix[3][0] = O.matrix[3][1] = 0;
  O.matrix[1][0] = O.matrix[1][1] = O.matrix[2][0] = O.matrix[2][1] = 1;

  I.matrix[0][0] = I.matrix[1][0] = I.matrix[2][0] = I.matrix[3][0] = 0;
  I.matrix[0][1] = I.matrix[1][1] = I.matrix[2][1] = I.matrix[3][1] = 1;

  Z.matrix[0][0] = Z.matrix[0][1] = Z.matrix[1][0] = Z.matrix[3][1] = 0;
  Z.matrix[1][1] = Z.matrix[2][0] = Z.matrix[2][1] = Z.matrix[3][0] = 1;

  S.matrix[0][0] = S.matrix[0][1] = S.matrix[1][1] = S.matrix[3][0] = 0;
  S.matrix[1][0] = S.matrix[2][0] = S.matrix[2][1] = S.matrix[3][1] = 1;

  int i;
  int j;
    
  rand();
  
  if (rand()%8 == 1) {
    for (i = 0;i < 4;i++) {
      for (j = 0;j < 2;j++) {
        Serial.println(T.matrix[i][j]); //T shape will be assigned 1
      }
      Serial.println('\t'); 
    } 
  }
  else if (rand()%8 == 2) {
    for (i = 0;i < 4;i++) {
      for (j = 0;j < 2;j++) {
        Serial.println(L.matrix[i][j]); //L shape will be assigned 2
      }
    Serial.println('\t');
    } 
  }
  else if (rand()%8 == 3) {
    for (i = 0;i < 4;i++) {
      for (j = 0;j < 2;j++) {
        Serial.println(J.matrix[i][j]); //J shape will be assigned 3
      }
    Serial.println('\t');
    } 
  }
  else if (rand()%8 == 4) {
    for (i = 0;i < 4;i++) {
      for (j = 0;j < 2;j++) {
        Serial.println(O.matrix[i][j]); //O shape will be assigned 4
      }
    Serial.println('\t');
    } 
  }
  else if (rand()%8 == 5) {
    for (i = 0;i < 4;i++) {
      for (j = 0;j < 2;j++) {
        Serial.println(I.matrix[i][j]); //I shape will be assigned 5
      }
    Serial.println('\t');
    } 
  }
  else if (rand()%8 == 6) {
    for (i = 0;i < 4;i++) {
      for (j = 0;j < 2;j++) {
        Serial.println(Z.matrix[i][j]); //Z shape will be assigned 6
      }
    Serial.println('\t');
    } 
  }
  else if (rand()%8 == 7) {
    for (i = 0;i < 4;i++) {
      for (j = 0;j < 2;j++) {
        Serial.println(S.matrix[i][j]); //S shape will be assigned 7
      }
    Serial.println('\t');
    } 
  }

}

void loop() 
{ 

}
