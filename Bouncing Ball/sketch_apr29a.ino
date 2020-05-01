#include <Wire.h>
#include <Adafruit_GFX.h> // Adafruit GFX Library
#include "Adafruit_LEDBackpack.h" //Adafruit LED Backpack Library

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();

//void setup() {
////  Serial.begin(9600);
////  Serial.println("16x8 LED Matrix Test");
//  
//  matrix.begin(0x00);  // pass in the address
//  
//}

void setup() {       
 Serial.begin(9600);       
 // Good idea to send data to both        
 // device and serial as it helps with       
 // troubleshooting.        
 Serial.println("8x16 LED Matrix Test");       
 // set the address       
 matrix.begin(0x70);        
} 

static const uint8_t PROGMEM // the key to the LED Matrix
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 };

void loop() {
  int x = 0;
  int y = 0;
  int a = 0;
  int tell = 1; 
  int till = 1; 
  while (a == 0){ // always true
    //保持闪烁状态
    matrix.drawPixel(x, y, LED_ON);  
    matrix.writeDisplay();  
    delay(40); 
    matrix.drawPixel(x, y, LED_OFF);  
    matrix.writeDisplay();  
    delay(40); 

    //从两个坐标轴出发，考虑球体变化
    //首先，因为上下排列关系8*16，横坐标为8，纵坐标为16，中间没有直接相连。所以在通过中间位置时，需要重新计算长度，而且不算碰撞
    //先横坐标开始考虑
    
//    //撞到左上角
//    if(x==7&&y==0){
//      tell=0;//x--
//      till=1;//y++
//    }
//    //撞到左下角
//    if(x==7&&y==7){
//      tell=0;
//      till=0;
//    }
//    //撞到左边边框（非上下）
//    if(x==7){
//      tell=0
//    }
    //左边框逻辑综合
    if(x==7&&y<=7){
      tell=0;
      if(y==0){
        till=1;
      }else if(y==7){
        till=0;
      }
    }
    
//    //第一个8*8矩阵的右上角
//    if(x==0&&y==0){
//      //判断x与y的原变化方向
//      //即小球的原运动方向
//      //小球是向上运动，但是不能确定他是否向左右运动
//      if(tell==0){
//        //向右运动
//        //坐标系变换
//        x=8;
//        y=8;
//      }
//      //往左边运动时不变
//      //tell不变，x的变化方向不变
//      till=1;
//    }
//    //第一个8*8矩阵的右下角
//    if(x==0&&y==7){
//      //向右运动
//      if(tell=0){
//        x=8;
//        y=15;
//      }
//
//      till=0
//    }
    //第一个8*8矩阵右边框逻辑综合
    if(x==0&&y<=7){
      //右上角
      if(y==0){
        if(tell==0){
        //向右运动
        //坐标系变换
        x=8;
        y=8;
        }
        till=1;
      }else if(y==7){
        //向右运动
        if(tell==0){
          x=8;
          y=15;
        }
        till=0;
      }else {
        if(tell==0){
          //向右运动
          x=8;
          y+=8;//上下运动的方向不变
        }
        //向左运动，不处理
      }
    }

    //左边8*8的上边框
    if(y==0&&x>0&&x<7){
      till=1;
    }
    //左边8*8的下边框
    if(y==7&&x>0&&x<7){
      till=0;
    }


    //右边矩阵的右边框
    if(x==0&&y>7){
      if(y==8){
        till=1;
      }else if(y==15){
        till=0;
      };
      tell=1;
    }

    //右边矩阵的左边框
    if(x==7&&y>7){
      if(y==8){
        if(tell==1){
          x=(-1);//+1后变成左边矩阵的第一列，也就是x=0
          y=0;//-1后变为下一个位置
        }
        till=1;
      }else if(y==15){
        if(tell==1){
          x=(-1);
          y=7;
        }
        till=0;
      }else{
        //边框非边界点
        if(tell==1){
          //向左
          x=(-1);
          y=y-8;
        }
        //向右不用处理
      }
    }

    //右边矩阵的上边框
    if(y==8&&x>0&&x<7){
      till=1;
    }
    //右边矩阵的下边框
    if(y==15&&x>0&&x<7){
      till=0;
    }
    //右边矩阵的下边框
//    if (x == 7){ 
//      tell = 0;  
//    }
//  
//    
//    if (x == 0){
//      tell = 1;
//    }
//    
//    if (y == 15){
//      till = 0;
//    }
//  
//    
//    if (y == 0){
//      till = 1;
//    }
  
    
    if(tell == 1){
      x++;
    }else{
      x--;
    }
   if(till == 1){
    y++;
   }else{
    y--;
   }
//   a++;
 }
}      
