
// LED cube operates in DEV (for debug and testing), SEQUENCE (effects in order), RANDOM (randomize effects)
enum mode         
{
  DEV,
  SEQUENCE,
  RANDOM
};
mode setting = SEQUENCE;

long effect_index = 0;    //indicate which effect is played

const int LED_cube_layer[3]  = {A0,A1,A2};                //Analog pins with 2N3904 NPN transistors with 2.2Kohm resistors
const int LED_cube_column[9] = {2,3,4,5,6,7,8,9,10};       //Digital pins with 220ohm resistors

/***********  3x3x3 LED Cube ********************************************************************************************************************************

  LED #  - Layer, Column - pins                    LED #  - Layer, Column - pins                     LED #  - Layer, Column - pins
  1          1      1      A0,D2  [0][0]           10         2      1      A1,D2   [1][0]           19         3      1      A2,D2   [2][0]
  2          1      2      A0,D3  [0][1]           11         2      2      A1,D3   [1][1]           20         3      2      A2,D3   [2][1] 
  3          1      3      A0,D4  [0][2]           12         2      3      A1,D4   [1][2]           21         3      3      A2,D4   [2][2]
  4          1      4      A0,D5  [0][3]           13         2      4      A1,D5   [1][3]           22         3      4      A2,D5   [2][3]
  5          1      5      A0,D6  [0][4]           14         2      5      A1,D6   [1][4]           23         3      5      A2,D6   [2][4]
  6          1      6      A0,D7  [0][5]           15         2      6      A1,D7   [1][5]           24         3      6      A2,D7   [2][5]
  7          1      7      A0,D8  [0][6]           16         2      7      A1,D8   [1][6]           25         3      7      A2,D8   [2][6]
  8          1      8      A0,D9  [0][7]           17         2      8      A1,D9   [1][7]           26         3      8      A2,D9   [2][7]
  9          1      9      A0,D10 [0][8]           18         2      9      A1,D10  [1][8]           27         3      9      A2,D10  [2][8]


            (1-10-19)         (4-13-22)         (7-16-25)
            (2-11-20)         (5-14-23)         (8-17-26)
            (3-12-21)         (6-15-24)         (9-18-27)
  
************************************************************************************************************************************************************/

void setup() 
{
  Serial.begin(9600);
  Serial.println(F("* * * * LED Cube: 3x3x3 * * * *"));
  randomSeed(analogRead(4));

  for(int i=0; i<3; i++)
  {
    pinMode(LED_cube_layer[i],OUTPUT);
  }
  for(int i=0; i<9; i++)
  {
    pinMode(LED_cube_column[i],OUTPUT);
  }
  for(int i=0; i<3; i++)
  {
    digitalWrite(LED_cube_layer[i],LOW);
  }
}

void loop() 
{

  switch (setting) {
    case DEV:
      Serial.println(F("## ~~ DEV mode ~~ ##"));
      effect_index = 0;
      break;
    case SEQUENCE:
      Serial.println(F("## ~~ SEQUENCE mode ~~ ##"));
      effect_index = effect_index +1;  
      if(effect_index > 15)        
        effect_index = 0;
      break;
    case RANDOM:
      Serial.println(F("## ~~ RANDOM mode ~~ ##"));
      effect_index = random(16);
      break;
  }

  //play effect
  LEDCube();    

}


/* ----------------- Main functions --------------- */

void LEDCube()
{
  Serial.print(F("Effect: "));
  Serial.println(effect_index);

  switch(effect_index)
  {
    case 0:
      Effect0();    
      break;
    case 1:
      Effect1();    
      break;  
    case 2:
      Effect2();    
      break;  
    case 3:
      Effect3();    
      break;  
    case 4:
      Effect4();    
      break;  
    case 5:
      Effect5();    
      break;  
    case 6:
      Effect6();    
      break;  
    case 7:
      Effect7();    
      break;  
    case 8:
      Effect8();    
      break; 
    case 9:
      Effect9();    
      break;   
    case 10:
      Effect10();    
    case 11:
      Effect11();    
      break;  
    case 12:
      Effect12();    
      break;  
    case 13:
      Effect13();    
      break;  
    case 14:
      Effect14();    
      break;  
    case 15:
      Effect15();    
      break;  
    default:
      Effect0();
      break;
  }

  LED_ALL_OFF();
  delay(500);
}

/* ----------------- LED Cube 3x3x3 Methods --------------- */

void LED_ON(int layer, int column)
{
  digitalWrite(LED_cube_layer[layer-1],HIGH);
  digitalWrite(LED_cube_column[column-1],HIGH);
}

void LED_OFF(int layer, int column)
{
  digitalWrite(LED_cube_layer[layer-1],LOW);
  digitalWrite(LED_cube_column[column-1],LOW);
}

void LED_ALL_ON()
{
  for(int i = 1; i<=4; i++)
  {
    for(int j =1; j <= 10 ; j++)
      LED_ON(i,j);
  }
}

void LED_ALL_OFF()
{
  for(int i= 1; i<=4; i++)
  {
    for(int j =1; j <= 10; j++)
      LED_OFF(i,j);
  }
}

void LED_ALL_OFF(int wait)
{
  delay(wait);
  LED_ALL_OFF();
  delay(wait);
}

void LED_RANDOM_ON()
{
  int rand_layer = random(4);
  int rand_col = random(10);
  LED_ON(rand_layer, rand_col);
}

void LED_RANDOM_OFF()
{
  int rand_layer = random(4);
  int rand_col = random(10);
  LED_OFF(rand_layer, rand_col);
}

/* ----------------- LED Cube Layer Methods --------------- */

void LAYER_ON(int layer)
{
  digitalWrite(LED_cube_layer[layer-1],HIGH);
}

void LAYER_OFF(int layer)
{
  digitalWrite(LED_cube_layer[layer-1],LOW);
}

void LAYER_ALL(int layer)
{
  LAYER_ON(layer);
  for(int i =1; i <= 9; i++)
  {
    COLUMN_ON(i);
  }
}

void LAYER_RANDOM(int layer)
{
  int rand_col = random(1,10);
  LED_ON(layer, rand_col);
}

void LAYER_SQUARE(int layer)
{
  LAYER_ON(layer);
  COLUMN_ON(1);
  COLUMN_ON(2);
  COLUMN_ON(3);
  COLUMN_ON(4);
  COLUMN_ON(6);
  COLUMN_ON(7);
  COLUMN_ON(8);
  COLUMN_ON(9);
}

void LAYER_CORNER(int layer)
{
  LAYER_ON(layer);
  COLUMN_ON(1);
  COLUMN_ON(3);
  COLUMN_ON(7);
  COLUMN_ON(9);
}

void LAYER_DIAMOND(int layer)
{
  LAYER_ON(layer);
  COLUMN_ON(2);
  COLUMN_ON(4);
  COLUMN_ON(6);
  COLUMN_ON(8);
}

void LAYER_X(int layer)
{
  LAYER_ON(layer);
  COLUMN_ON(1);
  COLUMN_ON(3);
  COLUMN_ON(5);
  COLUMN_ON(7);
  COLUMN_ON(9);
}

void LAYER_CROSS(int layer)
{
  LAYER_ON(layer);
  COLUMN_ON(2);
  COLUMN_ON(4);
  COLUMN_ON(5);
  COLUMN_ON(6);
  COLUMN_ON(8);
}

void LAYER_CENTRE(int layer)
{
  LAYER_ON(layer);
  COLUMN_ON(5);
}

void LAYER_SPIRAL_IN_CW(int layer, int wait)
{
  LAYER_ON(layer);
  COLUMN_ON(1);
  delay(wait);
  COLUMN_ON(4);
  delay(wait);
  COLUMN_ON(7);
  delay(wait);
  COLUMN_ON(8);
  delay(wait);
  COLUMN_ON(9);
  delay(wait);
  COLUMN_ON(6);
  delay(wait);
  COLUMN_ON(3);
  delay(wait);
  COLUMN_ON(2);
  delay(wait);
  COLUMN_ON(5);
  delay(wait);
  //1,4,7,8,9,6,3,2,5
}

void LAYER_SPIRAL_IN_CCW(int layer, int wait)
{
  LAYER_ON(layer);
  COLUMN_ON(7);
  delay(wait);
  COLUMN_ON(4);
  delay(wait);
  COLUMN_ON(1);
  delay(wait);
  COLUMN_ON(2);
  delay(wait);
  COLUMN_ON(3);
  delay(wait);
  COLUMN_ON(6);
  delay(wait);
  COLUMN_ON(9);
  delay(wait);
  COLUMN_ON(8);
  delay(wait);
  COLUMN_ON(5);
  delay(wait);
 //7,4,1,2,3,6,9,8,5
}

void LAYER_SPIRAL_OUT_CW(int layer, int wait)
{
  LAYER_ON(layer);
  COLUMN_ON(5);
  delay(wait);
  COLUMN_ON(8);
  delay(wait);
  COLUMN_ON(9);
  delay(wait);
  COLUMN_ON(6);
  delay(wait);
  COLUMN_ON(3);
  delay(wait);
  COLUMN_ON(2);
  delay(wait);
  COLUMN_ON(1);
  delay(wait);
  COLUMN_ON(4);
  delay(wait);
  COLUMN_ON(7);
  delay(wait);
  //5,8,9,6,3,2,1,4,7
}

void LAYER_SPIRAL_OUT_CCW(int layer, int wait)
{
  LAYER_ON(layer);
  COLUMN_ON(5);
  delay(wait);
  COLUMN_ON(2);
  delay(wait);
  COLUMN_ON(3);
  delay(wait);
  COLUMN_ON(6);
  delay(wait);
  COLUMN_ON(9);
  delay(wait);
  COLUMN_ON(8);
  delay(wait);
  COLUMN_ON(7);
  delay(wait);
  COLUMN_ON(4);
  delay(wait);
  COLUMN_ON(1);
  delay(wait);
  //5,2,3,6,9,8,7,4,1
}

/* ----------------- LED Cube Column Methods --------------- */

void COLUMN_ON(int column)
{
  digitalWrite(LED_cube_column[column-1],HIGH);
}

void COLUMN_OFF(int column)
{
  digitalWrite(LED_cube_column[column-1],LOW);
}

void COLUMN_ALL(int column)
{
  LAYER_ON(1);
  LAYER_ON(2);
  LAYER_ON(3);
  COLUMN_ON(column);
}

void COLUMN_RANDOM(int column)
{
  int rand_row = random(1,4);
  LAYER_ON(rand_row);
  COLUMN_ON(column);
}

void COLUMN_UP(int column, int wait)
{
  COLUMN_ON(column);
  LAYER_ON(1);
  delay(wait);
  LAYER_ON(2);
  delay(wait);
  LAYER_ON(3);
  delay(wait);
}

void COLUMN_DOWN(int column, int wait)
{
  COLUMN_ON(column);
  LAYER_ON(3);
  delay(wait);
  LAYER_ON(2);
  delay(wait);
  LAYER_ON(1);
  delay(wait);
}

void COLUMN_UP_SOLO(int column, int wait)
{
  COLUMN_ON(column);
  LAYER_ON(1);
  LAYER_OFF(2);
  LAYER_OFF(3);
  delay(wait);
  LAYER_ON(2);
  LAYER_OFF(1);
  LAYER_OFF(3);
  delay(wait);
  LAYER_ON(3);
  LAYER_OFF(1);
  LAYER_OFF(2);
  delay(wait);
}

void COLUMN_DOWN_SOLO(int column, int wait)
{
  COLUMN_ON(column);
  LAYER_ON(3);
  LAYER_OFF(2);
  LAYER_OFF(1);
  delay(wait);
  LAYER_ON(2);
  LAYER_OFF(3);
  LAYER_OFF(1);
  delay(wait);
  LAYER_ON(1);
  LAYER_OFF(2);
  LAYER_OFF(3);
  delay(wait);
}

/* ----------------- LED Cube Face Methods --------------- */

void FACE_123()
{
  LAYER_ON(1);
  LAYER_ON(2);
  LAYER_ON(3);
  COLUMN_ON(1);
  COLUMN_ON(2);
  COLUMN_ON(3);
}

void FACE_456()
{
  LAYER_ON(1);
  LAYER_ON(2);
  LAYER_ON(3);
  COLUMN_ON(4);
  COLUMN_ON(5);
  COLUMN_ON(6);
}

void FACE_789()
{
  LAYER_ON(1);
  LAYER_ON(2);
  LAYER_ON(3);
  COLUMN_ON(7);
  COLUMN_ON(8);
  COLUMN_ON(9);
}

void FACE_147()
{
  LAYER_ON(1);
  LAYER_ON(2);
  LAYER_ON(3);
  COLUMN_ON(1);
  COLUMN_ON(4);
  COLUMN_ON(7);
}  

void FACE_258()
{
  LAYER_ON(1);
  LAYER_ON(2);
  LAYER_ON(3);
  COLUMN_ON(2);
  COLUMN_ON(5);
  COLUMN_ON(8);
}

void FACE_369()
{
  LAYER_ON(1);
  LAYER_ON(2);
  LAYER_ON(3);
  COLUMN_ON(3);
  COLUMN_ON(6);
  COLUMN_ON(9);
}

void FACE_159()
{
  LAYER_ON(1);
  LAYER_ON(2);
  LAYER_ON(3);
  COLUMN_ON(1);
  COLUMN_ON(5);
  COLUMN_ON(9);
}

void FACE_357()
{
  LAYER_ON(1);
  LAYER_ON(2);
  LAYER_ON(3);
  COLUMN_ON(3);
  COLUMN_ON(5);
  COLUMN_ON(7);
}

void FACE_TOP()
{
  LAYER_ALL(3);
}

void FACE_BOTTOM()
{
  LAYER_ALL(1);
}

void FACE_MIDDLE()
{
  LAYER_ALL(2);
}

void CORNERS()
{
  LAYER_CORNER(1);
  LAYER_CORNER(3);
}

void CENTRE()
{
  LAYER_CENTRE(2);
}

/* ----------------- LED Cube 3x3x3 Effects --------------- */

//Flash ALL - ON and OFF
void Effect0()
{
  int wait = 400;

  while(wait > 0){
    LED_ALL_ON();
    LED_ALL_OFF(wait);
    wait -= 20;
  }

}

//Randon ON flash
void Effect1()
{
  int wait = 120;
  for(int i = 0; i<25; i++)
  {
    LED_RANDOM_ON();
    LED_ALL_OFF(wait);
  }
}

//Corners and Centre
void Effect2()
{
  int wait = 700;

  while(wait > 0){
    CORNERS();
    delay(wait);
    LED_ALL_OFF();
    // delay(wait/2);
    CENTRE();
    delay(wait);
    LED_ALL_OFF();
    wait -= 50;
  }
}

//Full column spirals
void Effect3()
{
  //5,2,1,4,7,8,9,6,3

  for(int wait = 300; wait >0; wait-=100)
  {
    COLUMN_ALL(5);
    delay(wait);
    LED_ALL_OFF();
    COLUMN_ALL(2);
    delay(wait);
    LED_ALL_OFF();
    COLUMN_ALL(1);
    delay(wait);
    LED_ALL_OFF();
    COLUMN_ALL(4);
    delay(wait);
    LED_ALL_OFF();
    COLUMN_ALL(7);
    delay(wait);
    LED_ALL_OFF();
    COLUMN_ALL(8);
    delay(wait);
    LED_ALL_OFF();
    COLUMN_ALL(9);
    delay(wait);
    LED_ALL_OFF();
    COLUMN_ALL(6);
    delay(wait);
    LED_ALL_OFF();
    COLUMN_ALL(3);
    delay(wait);
    LED_ALL_OFF();
    COLUMN_ALL(2);
    delay(wait);
    LED_ALL_OFF();

    COLUMN_ALL(5);
    delay(wait);
    COLUMN_ALL(2);
    delay(wait);
    COLUMN_ALL(1);
    delay(wait);
    COLUMN_ALL(4);
    delay(wait);
    COLUMN_ALL(7);
    delay(wait);
    COLUMN_ALL(8);
    delay(wait);
    COLUMN_ALL(9);
    delay(wait);
    COLUMN_ALL(6);
    delay(wait);
    COLUMN_ALL(3);
    delay(wait);
    COLUMN_ALL(2);
    delay(wait);
    LED_ALL_OFF();
  }
}

//Random column up and down
void Effect4()
{
  int wait = 300;
  for(int i=0; i<3; i++)
  {
    int column = random(10);
    COLUMN_UP(column, wait);
    LED_ALL_OFF();
    column = random(10);
    COLUMN_DOWN(column, wait);
    LED_ALL_OFF();
    column = random(10);
    COLUMN_UP_SOLO(column, wait);
    LED_ALL_OFF();
    column = random(10);
    COLUMN_DOWN_SOLO(column, wait);
    LED_ALL_OFF();
  }
}

//Spirals 
void Effect5()
{
  for(int wait = 150; wait > 25; wait = wait-50)
  {
    for(int i = 1 ; i < 4; i++)
    {
      LAYER_SPIRAL_IN_CW(i, wait);
      LED_ALL_OFF();
    }
    for(int i = 3 ; i > 0; i--)
    {
      LAYER_SPIRAL_OUT_CCW(i, wait);
      LED_ALL_OFF();
    }
    for(int i = 1 ; i < 4; i++)
    {
      LAYER_SPIRAL_IN_CCW(i, wait);
      LED_ALL_OFF();
    }
    for(int i = 3 ; i > 0; i--)
    {
      LAYER_SPIRAL_OUT_CW(i, wait);
      LED_ALL_OFF();
    }
  }
}

//X,Y,Z traveling faces
void Effect6()
{
  for(int wait = 250; wait > 0; wait = wait-50)
  {
    for(int i = 1 ; i<4; i++)
    {
    LAYER_ALL(i);
    LED_ALL_OFF(wait);
    }
    for(int i = 2 ; i>0; i--)
    {
    LAYER_ALL(i);
    LED_ALL_OFF(wait);
    }

    FACE_123();
    LED_ALL_OFF(wait);
    FACE_456();
    LED_ALL_OFF(wait);
    FACE_789();
    LED_ALL_OFF(wait);
    FACE_456();
    LED_ALL_OFF(wait);
    FACE_123();
    LED_ALL_OFF(wait);

    FACE_147();
    LED_ALL_OFF(wait);
    FACE_258();
    LED_ALL_OFF(wait);
    FACE_369();
    LED_ALL_OFF(wait);
    FACE_258();
    LED_ALL_OFF(wait);
    FACE_147();
    LED_ALL_OFF(wait);
  }
}

//Xs and Crosses 
void Effect7()
{
  for(int wait = 200; wait >0; wait = wait-50)
  {
    LAYER_X(1);
    LED_ALL_OFF(wait);
    LAYER_CROSS(2);
    LED_ALL_OFF(wait);
    LAYER_X(3);
    LED_ALL_OFF(wait);
    LAYER_CROSS(2);
    LED_ALL_OFF(wait);
    LAYER_X(1);
    LED_ALL_OFF(wait);
  }
}

//Corners and Diamonds
void Effect8()
{
  for(int wait = 200; wait >0; wait = wait-50)
  {
    LAYER_CORNER(1);
    LED_ALL_OFF(wait);
    LAYER_DIAMOND(2);
    LED_ALL_OFF(wait);
    LAYER_CORNER(3);
    LED_ALL_OFF(wait);
    LAYER_DIAMOND(2);
    LED_ALL_OFF(wait);
    LAYER_CORNER(1);
    LED_ALL_OFF(wait);
  }
}

//Spinning Faces Star
void Effect9()
{
  for(int wait = 175; wait > 0; wait = wait - 25)
  {
    for(int i = 0 ; i<2; i++)
    {
      FACE_456();
      LED_ALL_OFF(wait);
      FACE_159();
      LED_ALL_OFF(wait);
      FACE_258();
      LED_ALL_OFF(wait);
      FACE_357();
      LED_ALL_OFF(wait);
    }
    for(int i = 0 ; i<2; i++)
    {
      FACE_456();
      LED_ALL_OFF(wait);
      FACE_357();
      LED_ALL_OFF(wait);
      FACE_258();
      LED_ALL_OFF(wait);
      FACE_159();
      LED_ALL_OFF(wait);
    }
  }
}

//Roating Faces Perimeter
void Effect10()
{
  for(int wait = 250; wait > 0; wait = wait-50)
  {
    FACE_123();
    LED_ALL_OFF(wait);
    FACE_369();
    LED_ALL_OFF(wait);
    FACE_789();
    LED_ALL_OFF(wait);
    FACE_147();
    LED_ALL_OFF(wait);

    FACE_123();
    delay(wait);
    FACE_369();
    delay(wait);
    FACE_789();
    delay(wait);
    FACE_147();
    delay(wait);
  }
}

//Perimeter columns
void Effect11()
{
  for(int wait = 200; wait > 0; wait -=50)
  {
    COLUMN_ALL(1);
    LED_ALL_OFF(wait);
    COLUMN_ALL(2);
    LED_ALL_OFF(wait);
    COLUMN_ALL(3);
    LED_ALL_OFF(wait);
    COLUMN_ALL(6);
    LED_ALL_OFF(wait);
    COLUMN_ALL(9);
    LED_ALL_OFF(wait);
    COLUMN_ALL(8);
    LED_ALL_OFF(wait);
    COLUMN_ALL(7);
    LED_ALL_OFF(wait);
    COLUMN_ALL(4);
    LED_ALL_OFF(wait);

    COLUMN_ALL(1);
    delay(wait);
    COLUMN_ALL(2);
    delay(wait);
    COLUMN_ALL(3);
    delay(wait);
    COLUMN_ALL(6);
    delay(wait);
    COLUMN_ALL(9);
    delay(wait);
    COLUMN_ALL(8);
    delay(wait);
    COLUMN_ALL(7);
    delay(wait);
    COLUMN_ALL(4);
    delay(wait);
  }
}

//Perimeter Wave
void Effect12()
{
  for(int wait = 250; wait > 50; wait-=50)
  {
    COLUMN_UP(1, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_DOWN(2, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_UP(3, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_DOWN(6, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_UP(9, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_DOWN(8, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_UP(7, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_DOWN(4, wait/2);
    LED_ALL_OFF(wait);

    COLUMN_UP_SOLO(1, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_DOWN_SOLO(2, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_UP_SOLO(3, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_DOWN_SOLO(6, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_UP_SOLO(9, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_DOWN_SOLO(8, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_UP_SOLO(7, wait/2);
    LED_ALL_OFF(wait);
    COLUMN_DOWN_SOLO(4, wait/2);
    LED_ALL_OFF(wait);
  }
}

//Figure 8
void Effect13()
{
  //layers, full columns, wave
  // 1,2,3,6,5,4,7,8,9,6,5,4

  int wait = 115;

  LAYER_ON(1);
  COLUMN_ON(1);
  delay(wait);
  COLUMN_OFF(1);
  delay(wait);
  COLUMN_ON(2);
  delay(wait);
  COLUMN_OFF(2);
  delay(wait);
  COLUMN_ON(3);
  delay(wait);
  COLUMN_OFF(3);
  delay(wait);
  COLUMN_ON(6);
  delay(wait);
  COLUMN_OFF(6);
  delay(wait);
  COLUMN_ON(5);
  delay(wait);
  COLUMN_OFF(5);
  delay(wait);
  COLUMN_ON(4);
  delay(wait);
  COLUMN_OFF(4);
  delay(wait);
  COLUMN_ON(7);
  delay(wait);
  COLUMN_OFF(7);
  delay(wait);
  COLUMN_ON(8);
  delay(wait);
  COLUMN_OFF(8);
  delay(wait);
  COLUMN_ON(9);
  delay(wait);
  COLUMN_OFF(9);
  delay(wait);
  COLUMN_ON(6);
  delay(wait);
  COLUMN_OFF(6);
  delay(wait);
  COLUMN_ON(5);
  delay(wait);
  COLUMN_OFF(5);
  delay(wait);
  COLUMN_ON(4);
  delay(wait);
  COLUMN_OFF(4);
  delay(wait);

  LAYER_OFF(1);
  LAYER_ON(2);
  COLUMN_ON(1);
  delay(wait);
  COLUMN_OFF(1);
  delay(wait);
  COLUMN_ON(2);
  delay(wait);
  COLUMN_OFF(2);
  delay(wait);
  COLUMN_ON(3);
  delay(wait);
  COLUMN_OFF(3);
  delay(wait);
  COLUMN_ON(6);
  delay(wait);
  COLUMN_OFF(6);
  delay(wait);
  COLUMN_ON(5);
  delay(wait);
  COLUMN_OFF(5);
  delay(wait);
  COLUMN_ON(4);
  delay(wait);
  COLUMN_OFF(4);
  delay(wait);
  COLUMN_ON(7);
  delay(wait);
  COLUMN_OFF(7);
  delay(wait);
  COLUMN_ON(8);
  delay(wait);
  COLUMN_OFF(8);
  delay(wait);
  COLUMN_ON(9);
  delay(wait);
  COLUMN_OFF(9);
  delay(wait);
  COLUMN_ON(6);
  delay(wait);
  COLUMN_OFF(6);
  delay(wait);
  COLUMN_ON(5);
  delay(wait);
  COLUMN_OFF(5);
  delay(wait);
  COLUMN_ON(4);
  delay(wait);
  COLUMN_OFF(4);
  delay(wait);

  LAYER_OFF(1);
  LAYER_OFF(2);
  LAYER_ON(3);
  COLUMN_ON(1);
  delay(wait);
  COLUMN_OFF(1);
  delay(wait);
  COLUMN_ON(2);
  delay(wait);
  COLUMN_OFF(2);
  delay(wait);
  COLUMN_ON(3);
  delay(wait);
  COLUMN_OFF(3);
  delay(wait);
  COLUMN_ON(6);
  delay(wait);
  COLUMN_OFF(6);
  delay(wait);
  COLUMN_ON(5);
  delay(wait);
  COLUMN_OFF(5);
  delay(wait);
  COLUMN_ON(4);
  delay(wait);
  COLUMN_OFF(4);
  delay(wait);
  COLUMN_ON(7);
  delay(wait);
  COLUMN_OFF(7);
  delay(wait);
  COLUMN_ON(8);
  delay(wait);
  COLUMN_OFF(8);
  delay(wait);
  COLUMN_ON(9);
  delay(wait);
  COLUMN_OFF(9);
  delay(wait);
  COLUMN_ON(6);
  delay(wait);
  COLUMN_OFF(6);
  delay(wait);
  COLUMN_ON(5);
  delay(wait);
  COLUMN_OFF(5);
  delay(wait);
  COLUMN_ON(4);
  delay(wait);
  COLUMN_OFF(4);
  delay(wait);

  COLUMN_ALL(1);
  LED_ALL_OFF(wait);
  COLUMN_ALL(2);
  LED_ALL_OFF(wait);
  COLUMN_ALL(3);
  LED_ALL_OFF(wait);
  COLUMN_ALL(6);
  LED_ALL_OFF(wait);
  COLUMN_ALL(5);
  LED_ALL_OFF(wait);
  COLUMN_ALL(4);
  LED_ALL_OFF(wait);
  COLUMN_ALL(7);
  LED_ALL_OFF(wait);
  COLUMN_ALL(8);
  LED_ALL_OFF(wait);
  COLUMN_ALL(9);
  LED_ALL_OFF(wait);
  COLUMN_ALL(6);
  LED_ALL_OFF(wait);
  COLUMN_ALL(5);
  LED_ALL_OFF(wait);
  COLUMN_ALL(4);
  LED_ALL_OFF(wait);

  COLUMN_UP_SOLO(1,wait/2);
  LED_ALL_OFF(wait);
  COLUMN_DOWN_SOLO(2,wait/2);
  LED_ALL_OFF(wait);
  COLUMN_UP_SOLO(3,wait/2);
  LED_ALL_OFF(wait);
  COLUMN_DOWN_SOLO(6,wait/2);
  LED_ALL_OFF(wait);
  COLUMN_UP_SOLO(5,wait/2);
  LED_ALL_OFF(wait);
  COLUMN_DOWN_SOLO(4,wait/2);
  LED_ALL_OFF(wait);
  COLUMN_UP_SOLO(7,wait/2);
  LED_ALL_OFF(wait);
  COLUMN_DOWN_SOLO(8,wait/2);
  LED_ALL_OFF(wait);
  COLUMN_UP_SOLO(9,wait/2);
  LED_ALL_OFF(wait);
  COLUMN_DOWN_SOLO(6,wait/2);
  LED_ALL_OFF(wait);
  COLUMN_UP_SOLO(5,wait/2);
  LED_ALL_OFF(wait);
  COLUMN_DOWN_SOLO(4,wait/2);
  LED_ALL_OFF(wait);
}

//Zig-Zag
void Effect14()
{
  int wait = 175;

  LED_ON( 1,  1);
  LED_ALL_OFF(wait);
  LED_ON( 2,  2);
  LED_ALL_OFF(wait);
  LED_ON( 3,  3);
  LED_ALL_OFF(wait);
  LED_ON( 2,  6);
  LED_ALL_OFF(wait);
  LED_ON( 1,  9);
  LED_ALL_OFF(wait);
  LED_ON( 2,  8);
  LED_ALL_OFF(wait);
  LED_ON( 3,  7);
  LED_ALL_OFF(wait);
  LED_ON( 2,  4);
  LED_ALL_OFF(wait);
  LED_ON( 1,  1);
  LED_ALL_OFF(wait);

  LED_ON( 1,  1);
  LED_ALL_OFF(wait);
  LED_ON( 2,  4);
  LED_ALL_OFF(wait);
  LED_ON( 3,  7);
  LED_ALL_OFF(wait);
  LED_ON( 2,  8);
  LED_ALL_OFF(wait);
  LED_ON( 1,  9);
  LED_ALL_OFF(wait);
  LED_ON( 2,  6);
  LED_ALL_OFF(wait);
  LED_ON( 3,  3);
  LED_ALL_OFF(wait);
  LED_ON( 2,  2);
  LED_ALL_OFF(wait);
  LED_ON( 1,  1);
  LED_ALL_OFF(wait);

  LED_ON( 1,  3);
  LED_ALL_OFF(wait);
  LED_ON( 2,  6);
  LED_ALL_OFF(wait);
  LED_ON( 3,  9);
  LED_ALL_OFF(wait);
  LED_ON( 2,  8);
  LED_ALL_OFF(wait);
  LED_ON( 1,  7);
  LED_ALL_OFF(wait);
  LED_ON( 2,  4);
  LED_ALL_OFF(wait);
  LED_ON( 3,  1);
  LED_ALL_OFF(wait);
  LED_ON( 2,  2);
  LED_ALL_OFF(wait);
  LED_ON( 1,  3);
  LED_ALL_OFF(wait);

  LED_ON( 1,  3);
  LED_ALL_OFF(wait);
  LED_ON( 2,  2);
  LED_ALL_OFF(wait);
  LED_ON( 3,  1);
  LED_ALL_OFF(wait);
  LED_ON( 2,  4);
  LED_ALL_OFF(wait);
  LED_ON( 1,  7);
  LED_ALL_OFF(wait);
  LED_ON( 2,  8);
  LED_ALL_OFF(wait);
  LED_ON( 3,  9);
  LED_ALL_OFF(wait);
  LED_ON( 2,  6);
  LED_ALL_OFF(wait);
  LED_ON( 1,  3);
  LED_ALL_OFF(wait);
}

//X
void Effect15()
{
  int wait = 150;

  for(int i = 0; i <5; i++)
  {
    LED_ON( 1,  7);
    LED_ALL_OFF(wait);
    LED_ON( 2,  5);
    LED_ALL_OFF(wait);
    LED_ON( 3,  3);
    LED_ALL_OFF(wait);
    LED_ON( 1,  9);
    LED_ALL_OFF(wait);
    LED_ON( 2,  5);
    LED_ALL_OFF(wait);
    LED_ON( 3,  1);
    LED_ALL_OFF(wait);

    LED_ON( 3,  9);
    LED_ALL_OFF(wait);
    LED_ON( 2,  5);
    LED_ALL_OFF(wait);
    LED_ON( 1,  1);
    LED_ALL_OFF(wait);
    LED_ON( 3,  7);
    LED_ALL_OFF(wait);
    LED_ON( 2,  5);
    LED_ALL_OFF(wait);
    LED_ON( 1,  3);
    LED_ALL_OFF(wait);
  }
}

