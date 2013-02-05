// Initalize our LED columns (positive)
int LEDPin[] = {
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
// Initalize the LED layers (ground)
int LayerPin[] = {
  16,17,18,19};
// Initialize the LED Array
boolean LED[4][4][4];

void setup(){
  // Seed the RNG
  randomSeed(analogRead(0));  

  //Serial.begin(9600);
  // Set up LED columns as output
  for(int pin = 0; pin < 16 ; pin++ ){
    pinMode(LEDPin[pin],OUTPUT);
    digitalWrite(LEDPin[pin],LOW);
  }
  // Set up LED Layers as output
  for(int layer = 0; layer < 4; layer++){
    pinMode(LayerPin[layer], OUTPUT);
    digitalWrite(LayerPin[layer], HIGH);
  }

  // Initalize the LED pins to all off
  resetCube();
}

void loop() {
  int disp = random(10);
  switch(disp) {
  case 0:
    fuzz(50);
    break;
  case 1:
    saturate();
    flash(500);
    break;
  case 2:
    doubleHelix();
    break;
  case 3:
    scan();
    break;
  case 4:
    rainyDay(100);
    break;
  case 5:
    edgeWalker(500);
    break;
  case 6:
    daBomb();
    break;
  case 7:
    upNDown(100);
    break;
  case 8:
    subSpace(50);
    break;
  case 9:
    spindle(15);
    break;
  default:
    break;
  }
}

void saturate() {
  boolean allOn = false;
  while (!allOn) {
    allOn = true;
    for (int x=0; x<4; x++) {
      for (int y=0; y<4; y++) {
        for (int z=0; z<4; z++) {  
          if (!LED[x][y][z]) {
            if (random(10) == 1) {
              LED[x][y][z] = true;
            } else {
              allOn = false;
            }
          }
        }
      }
    }
    flash(20);
  }
}

void spindle(int cycles) {
  int dly=15;
  for (int c=0; c<cycles; c++) {
    for (int y=0; y<4; y++) { // Edge
      LED[0][y][0] = true;
      LED[1][y][1] = true;
      LED[2][y][2] = true;
      LED[3][y][3] = true;
    }
    flash(dly);
    resetCube();
    for (int y=0; y<4; y++) {
      LED[0][y][1] = true;
      LED[3][y][2] = true;
  
      LED[1][y][1] = true;  
      LED[2][y][2] = true;      
    }
    flash(dly*.5);    
    resetCube();
    for (int y=0; y<4; y++) {
      LED[0][y][1] = true;
      LED[3][y][2] = true;
  
      LED[1][y][2] = true;  
      LED[2][y][2] = true;      
    }
    flash(dly*.5);    
    resetCube();
    for (int y=0; y<4; y++) {    
      LED[0][y][2] = true;
      LED[3][y][1] = true;
 
      LED[1][y][2] = true;  
      LED[2][y][2] = true;      
    }
    flash(dly*.5);
    resetCube();
    
    for (int y=0; y<4; y++) {    
      LED[0][y][2] = true;
      LED[3][y][1] = true;
 
      LED[1][y][2] = true;  
      LED[2][y][1] = true;
    }
    flash(dly);
    resetCube();    
    
    for (int y=0; y<4; y++) { // Edge
      LED[0][y][3] = true;
      LED[1][y][2] = true;
      LED[2][y][1] = true;
      LED[3][y][0] = true;
    }
    flash(dly);
    resetCube();
    for (int y=0; y<4; y++) {    
      LED[1][y][3] = true;
      LED[2][y][0] = true;
      LED[1][y][2] = true;
      LED[2][y][1] = true;      
    }
    flash(dly);
    resetCube();
    for (int y=0; y<4; y++) {    
      LED[2][y][3] = true;
      LED[1][y][0] = true;
      
      LED[2][y][2] = true;      
      LED[2][y][1] = true;  
    }
    flash(dly*.5);
    resetCube();
    for (int y=0; y<4; y++) {    
      LED[2][y][3] = true;
      LED[1][y][0] = true;
      
      LED[2][y][2] = true;      
      LED[1][y][1] = true;  
    }
    flash(dly*.5);
    resetCube();
  }  
}

// 2x2x2 cube wanders around the space
void subSpace(int cycles) {
  resetCube();
  for (int x=0; x<2; x++) {
    for (int y=0; y<2; y++) {
      for (int z=0; z<2; z++) {
        LED[x][y][z] = true;
      }
    }
  }
  boolean minX = true;
  boolean minY = true;
  boolean minZ = true;
  int dly = 20;
  int lastDir = -1;
  for (int c=0; c<cycles; c++) {
    flash(dly);
    int dir;
    do {
      dir = random(3);
    } while (dir == lastDir);
    lastDir = dir;
    int vel = 0;
    if (dir == 0) {
      if (minX) { vel = 1; } else { vel = -1; }
      translate(vel,0,0);
      flash(dly);
      translate(vel,0,0);
      minX = !minX;
    } else if (dir == 1) {
      if (minY) { vel = 1; } else { vel = -1; }
      translate(0,vel,0);
      flash(dly);
      translate(0,vel,0); 
      minY = !minY;     
    } else {
      if (minZ) { vel = 1; } else { vel = -1; }
      translate(0,0,vel);
      flash(dly);
      translate(0,0,vel);
      minZ = !minZ;
    }
  }
}

void upNDown(int cycles) {
  resetCube();
  setYLayer(3, true);
  flash(25);
  for (int c=0; c<cycles; c++) {
    // Select random x,z column
    int x = random(4);
    int z = random(4);
    
    if (LED[x][0][z]) {
      // Send LED up
      for (int y=0; y<3; y++) {
        LED[x][y][z] = false;
        LED[x][y+1][z] = true;
        flash(10);
      }
    } else {
      // Send LED Down
      for (int y=3; y>0; y--) {
        LED[x][y][z] = false;
        LED[x][y-1][z] = true;
        flash(10);
      }
    }
    flash(10);
  }
}

void translate(int xVel, int yVel, int zVel) {
  if (xVel < 0) {
    xVel += 4;
  }
  if (yVel < 0) {
    yVel += 4;
  }
  if (zVel < 0) {
    zVel += 4;
  }
  int tmp[4][4][4];
  for (int x=0; x<4; x++) {
    for (int y=0; y<4; y++) {
      for (int z=0; z<4; z++) {
        tmp[x][y][z] = false;
      }
    }
  }  
  for (int x=0; x<4; x++) {
    for (int y=0; y<4; y++) {
      for (int z=0; z<4; z++) {
        if (LED[x][y][z]) {
          tmp[(x+xVel)%4][(y+yVel)%4][(z+zVel)%4] = true;
        }
      }
    }
  }
  for (int x=0; x<4; x++) {
    for (int y=0; y<4; y++) {
      for (int z=0; z<4; z++) {
        LED[x][y][z] = tmp[x][y][z];
      }
    }
  }    
}

void daBomb() {
  resetCube();
  int x = random(4);
  int y = random(4);
  int z = random(4);
  
  for (int i=0; i<10; i++) {
    drawPower(x,y,z,max(10,50-10*i));
  }  
  
  for (int i=0; i<20; i++) {
    LED[x][y][z] = true;
    flash(5);
    LED[x][y][z] = false;
    flash(5);    
  }

  // Explode the bomb!
  for (int e=0; e<4; e++) {
    float minDist = 0;
    float maxDist = .5;
    while (minDist < 5.2) { // This is the max l2Norm Distance of a 4x4x4 cube
      for (int x2=0; x2<4; x2++) {
        for (int y2=0; y2<4; y2++) {
          for (int z2=0; z2<4; z2++) {
            float dist = l2Norm(x,y,z,x2,y2,z2);
            if (dist >= minDist && dist <= maxDist) {
              LED[x2][y2][z2] = true;
            } else {
              LED[x2][y2][z2] = false;
            }
          }
        }
      }
      flash(10);
      minDist += 0.5;
      maxDist += 0.5;
    }
  }
  
  // Half Explode 
  float minDist = 0;
  float maxDist = .5;
  while (minDist < 2.6) {
    for (int x2=0; x2<4; x2++) {
      for (int y2=0; y2<4; y2++) {
        for (int z2=0; z2<4; z2++) {
          float dist = l2Norm(x,y,z,x2,y2,z2);
          if (dist >= minDist && dist <= maxDist) {
            LED[x2][y2][z2] = true;
          } else {
            LED[x2][y2][z2] = false;
          }
        }
      }
    }
    flash(20);
    minDist += 0.5;
    maxDist += 0.5;
  }
}

float l2Norm(int x1, int y1, int z1, int x2, int y2, int z2) {
  return sqrt(pow(x1-x2,2) + pow(y1-y2,2) + pow(z1-z2,2));
}

void drawPower(int x, int y, int z, int drawSpeed) {
  LED[x][y][z] = true;
  for (int i=0; i<4; i++) {
    LED[i][y][z] = true;
  }  
  for (int i=0; i<4; i++) {
    LED[x][i][z] = true;
  }  
  for (int i=0; i<4; i++) {
    LED[x][y][i] = true;
  }    
  flash(drawSpeed);
  for (int dist = 3; dist >=1; dist--) {
    // Turn off all LEDs at distance dist
    for (int i=0; i<4; i++) {
      if (LED[i][y][z] and abs(i-x) >= dist) {
        LED[i][y][z] = false;
      }
    }
    for (int i=0; i<4; i++) {
      if (LED[x][i][z] and abs(i-y) >= dist) {
        LED[x][i][z] = false;
      }
    }
    for (int i=0; i<4; i++) {
      if (LED[x][y][i] and abs(i-z) >= dist) {
        LED[x][y][i] = false;
      }
    }    
    flash(drawSpeed); 
  }
}

void edgeWalker(int cycles) {
  resetCube();
  int len = 4;
  int snake_x[len];
  int snake_y[len];
  int snake_z[len];
  int head = 0;

  snake_x[head] = 0;
  snake_y[head] = 0;
  snake_z[head] = 0;
  LED[snake_x[head]][snake_y[head]][snake_z[head]] = true;
  for (int i=0; i<len-1; i++) {
    int newx, newy, newz;
    do {
      int newPt[3] = { 
        snake_x[(head+i)%len], snake_y[(head+i)%len], snake_z[(head+i)%len]       };
      findEdgeLED(newPt);
      newx = newPt[0];
      newy = newPt[1];
      newz = newPt[2];
    } 
    while (LED[newx][newy][newz]);
    LED[newx][newy][newz] = true;
    snake_x[(head+i+1)%len] = newx;
    snake_y[(head+i+1)%len] = newy;
    snake_z[(head+i+1)%len] = newz;
  }

  int dly = 50;
  int swap = 500;
  for (int c=0; c<cycles; c++) {
    int newx, newy, newz;
    do {
      int newPt[3] = { 
        snake_x[head], snake_y[head], snake_z[head]       };
      findEdgeLED(newPt);
      newx = newPt[0];
      newy = newPt[1];
      newz = newPt[2];
    } 
    while (LED[newx][newy][newz]);
    LED[newx][newy][newz] = true;
    head--;
    if (head < 0) { 
      head = len-1; 
    }
    LED[snake_x[head]][snake_y[head]][snake_z[head]] = false;
    snake_x[head] = newx;
    snake_y[head] = newy;
    snake_z[head] = newz;   
    flash(dly);
    swap -= dly;
    if (swap <= 0) {
      swap = 500;
      dly = max(5,dly * .75);
    }
  }
}

void findEdgeLED(int* loc) {
  for (int i=0; i<3; i++) {
    if (loc[i] == 1 || loc[i] == 2) {
      if (random(2) == 1) {
        loc[i] = loc[i] -1;
      } 
      else {
        loc[i] = loc[i] +1;
      }
      return;
    }
  }
  int dim = random(3);
  if (loc[dim] == 0) { 
    loc[dim] = 1; 
  }
  if (loc[dim] == 3) { 
    loc[dim] = 2; 
  }
}

//void snake(int cycles) {
//  resetCube();
//  int len = 5;
//  int snake_x[len];
//  int snake_y[len];
//  int snake_z[len];
//  int head = 0;
//  
//  // Spawn the snake
//  snake_x[head] = random(4);
//  snake_y[head] = random(4);
//  snake_z[head] = random(4);
//  LED[snake_x[head]][snake_y[head]][snake_z[head]] = true;
//  for (int i=0; i<len-1; i++) {
//    int newx, newy, newz;
//    do {
//      int newPt[3] = { snake_x[(head+i)%len], snake_y[(head+i)%len], snake_z[(head+i)%len] };
//      findContiguousLED(newPt);
//      newx = newPt[0];
//      newy = newPt[1];
//      newz = newPt[2];
//    } while (LED[newx][newy][newz]);
//    LED[newx][newy][newz] = true;
//    snake_x[(head+i+1)%len] = newx;
//    snake_y[(head+i+1)%len] = newy;
//    snake_z[(head+i+1)%len] = newz;
//  }
//
//  for (int c=0; c<cycles; c++) {
//    // Blink snake
//    for (int b=0; b < 1; b++) {
//      for (int i=0; i<1; i++) {
//        LED[snake_x[(head+i)%len]][snake_y[(head+i)%len]][snake_z[(head+i)%len]] = false;        
//        flash(20);
//        LED[snake_x[(head+i)%len]][snake_y[(head+i)%len]][snake_z[(head+i)%len]] = true;
//        flash(20);      
//      }
//    }
////    for (int i=0; i<len; i++) {
////       LED[snake_x[(head+i)%len]][snake_y[(head+i)%len]][snake_z[(head+i)%len]] = true;
////    }
//    // Move snake
//    int newx, newy, newz;
//    do {
//      int newPt[3] = { snake_x[head], snake_y[head], snake_z[head] };
//      findContiguousLED(newPt);
//      newx = newPt[0];
//      newy = newPt[1];
//      newz = newPt[2];
//    } while (LED[newx][newy][newz]);
//    LED[newx][newy][newz] = true;
//    head--;
//    if (head < 0) { head = len-1; }
//    LED[snake_x[head]][snake_y[head]][snake_z[head]] = false;
//    snake_x[head] = newx;
//    snake_y[head] = newy;
//    snake_z[head] = newz;   
//    
//    flash(20); 
//  }
//}

void findContiguousLED(int* loc) {
  int indx = random(3);
  if (loc[indx] == 0) {
    loc[indx] = 1;
    return;
  } 
  else if (loc[indx] == 3) {
    loc[indx] = 2;
    return;
  } 
  else {
    if (random(2) == 0) {
      loc[indx] = loc[indx] -1;
    } 
    else {
      loc[indx] = loc[indx] +1;
    }
    return;
  }
}

// Scans All 3 Dimensions
void scan() {
  resetCube();
  // Vertical Scan
  for (int y=3; y>=0; y--) {
    setYLayer(y, true);
    if (y < 3) { 
      setYLayer(y+1,false); 
    }
    flash(50);
  }
  for (int y=1; y<=3; y++) {
    setYLayer(y, true);
    setYLayer(y-1, false);
    flash(50);
  }
  resetCube();  

  // Hoizontal Scan
  for (int x=3; x>=0; x--) {
    setXLayer(x, true);
    if (x < 3) { 
      setXLayer(x+1, false); 
    }
    flash(50);
  }
  for (int x=1; x<=3; x++) {
    setXLayer(x, true);
    setXLayer(x-1, false);
    flash(50);
  }
  resetCube();

  // Z-Axis Scan
  for (int z=3; z>=0; z--) {
    setZLayer(z, true);
    if (z < 3) { 
      setZLayer(z+1, false); 
    }
    flash(50);
  }
  for (int z=1; z<=3; z++) {
    setZLayer(z, true);
    setZLayer(z-1, false);
    flash(50);
  }
}

void setXLayer(int layer, boolean val) {
  for (int y=0; y<4; y++) {
    for (int z=0; z<4; z++) {
      LED[layer][y][z] = val;
    }
  }
}
void setYLayer(int layer, boolean val) {
  for (int x=0; x<4; x++) {
    for (int z=0; z<4; z++) {
      LED[x][layer][z] = val;
    }
  }
}
void setZLayer(int layer, boolean val) {
  for (int x=0; x<4; x++) {
    for (int y=0; y<4; y++) {
      LED[x][y][layer] = val;
    }
  }
}

// Very cool double helix pattern
void doubleHelix() {
  int OuterEdge[] = {
    0,1,2,3,7,11,15,14,13,12,8,4  };
  int leadA=0;
  int f1=11;
  int f2=10;
  int f3=9;
  int leadB=6;
  int f1B=5;
  int f2B=4;
  int f3B=3;
  int timer = 0;
  int laps = 0;
  int count = 0; 
  while(count < 500){
    // Sets the time they all display or "blink together" to our eyes
    while(timer<10){
      digitalWrite(LayerPin[3],LOW);
      digitalWrite(LEDPin[OuterEdge[leadA]],HIGH);
      if(laps=1){
        digitalWrite(LEDPin[OuterEdge[leadB]],HIGH);
      }
      delay(3);
      digitalWrite(LEDPin[OuterEdge[leadA]],LOW);
      digitalWrite(LEDPin[OuterEdge[leadB]],LOW);
      digitalWrite(LayerPin[3],HIGH);
      digitalWrite(LayerPin[2],LOW);
      digitalWrite(LEDPin[OuterEdge[f1]],HIGH);
      if(laps=1){
        digitalWrite(LEDPin[OuterEdge[f1B]],HIGH);
      }
      delay(3);
      digitalWrite(LEDPin[OuterEdge[f1]],LOW);  
      digitalWrite(LEDPin[OuterEdge[f1B]],LOW);       
      digitalWrite(LayerPin[2],HIGH);
      digitalWrite(LayerPin[1],LOW);
      digitalWrite(LEDPin[OuterEdge[f2]],HIGH);
      if(laps=1){
        digitalWrite(LEDPin[OuterEdge[f2B]],HIGH);
      }
      delay(3);
      digitalWrite(LEDPin[OuterEdge[f2]],LOW);  
      digitalWrite(LEDPin[OuterEdge[f2B]],LOW);
      digitalWrite(LayerPin[1],HIGH);
      digitalWrite(LayerPin[0],LOW);
      digitalWrite(LEDPin[OuterEdge[f3]],HIGH);
      if(laps=1){
        digitalWrite(LEDPin[OuterEdge[f3B]],HIGH);
      }
      delay(3);
      digitalWrite(LEDPin[OuterEdge[f3]],LOW);    
      digitalWrite(LEDPin[OuterEdge[f3B]],LOW);      
      digitalWrite(LayerPin[0],HIGH);       
      timer++;
      count++;
    }
    timer=0;
    leadA++;
    f1++;
    f2++;
    f3++;
    leadB++;
    f1B++;
    f2B++;
    f3B++;
    if(leadA>11){
      leadA = 0;
      laps = 1;
    }
    if(f1>11){
      f1 = 0;
    }
    if(f2>11){
      f2 = 0;
    }
    if(f3>11){
      f3 = 0;
    }
    if(leadB>11){
      leadB = 0;
    }
    if(f1B>11){
      f1B = 0;
    }
    if(f2B>11){
      f2B = 0;
    }
    if(f3B>11){
      f3B = 0;
    }
  }  
}

void rainyDay(int cycles) {
  for (int c=0; c<cycles; c++) {
    // Introduce new leds
    for (int x=0; x<4; x++) {
      for (int z=0; z<4; z++) {
        if (random(100) == 0) {
          LED[x][3][z] = true;
        }
      }
    }

    // Drip the leds currently on
    for (int y=0; y<4; y++) {    
      for (int x=0; x<4; x++) {
        for (int z=0; z<4; z++) {
          if (LED[x][y][z]) {
            if (random(5) == 0) {
              LED[x][y][z] = false;
              if (y > 0) {
                LED[x][y-1][z] = true;
              }
            }
          }
        }
      }
    }
    flash(30);
  }
}

// Activates All LEDs
void allOn(int cycles) {
  for (int x=0; x<4; x++) {
    for (int y=0; y<4; y++) {
      for (int z=0; z<4; z++) {
        LED[x][y][z] = true;
      }
    }
  }  
  flash(cycles);
}

// Activates Random LEDs
void fuzz(int cycles) {
  for (int c=0; c<cycles; c++) {
    for (int x=0; x<4; x++) {
      for (int y=0; y<4; y++) {
        for (int z=0; z<4; z++) {
          if (random(10) == 0) {
            LED[x][y][z] = true;
          } 
          else {
            LED[x][y][z] = false;
          }
        }
      }
    }
    flash(25);
  }
}

// Turns off all LEDs in the cube
void resetCube() {
  for (int x=0; x<4; x++) {
    for (int y=0; y<4; y++) {
      for (int z=0; z<4; z++) {
        LED[x][y][z] = false;
      }
    }
  }
}

// Flashes the current configuration
void flash(int cycles) {
  for (int c=0; c<cycles; c++) {
    for (int y=0; y<4; y++) {
      if (y != 0) { 
        digitalWrite(LayerPin[y-1],HIGH); 
      }
      digitalWrite(LayerPin[y],LOW);
      for (int x=0; x<4; x++) {
        for (int z=0; z<4; z++) {
          if (LED[x][y][z]) {
            digitalWrite(LEDPin[4*z + x],HIGH);
          } 
          else {
            digitalWrite(LEDPin[4*z + x],LOW); 
          }
        }
      }
      delay(1);
    }
    digitalWrite(LayerPin[3],HIGH);
  }
}


