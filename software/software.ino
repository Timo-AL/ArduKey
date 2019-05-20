#include <Mouse.h>
#include <Keyboard.h>
#include <HID.h>

#define CLK 0
#define DT 1
#define SW 2//旋转编码器定义

#define MK1 0
#define MK2 1//开关按键定义

#define PS  0
#define PR  1
#define OFF 2
#define SAI 3//键盘模式定义

#define Y1 8
#define Y2 7
#define Y3 6
#define Y4 5
#define Y5 4//纵行定义，全部上拉读取 

#define X1 9
#define X2 10
#define X3 16
#define X4 14
#define X5 15//横行定义，读取时低电平
int mod;//键盘模式变量

bool key[5][5]={0}; //存储键盘当前状态用的数组
bool key_[5][5]={0};//存储键盘上次状态用的数组

void wheel(bool direct)  //用于模拟鼠标滚轮的函数
{
  static uint8_t m[4]={0,0,0,0};
  short dir=1;   //修改这个值可以改变速度，然而1以及很快了
  if(direct) dir*=-1;
  m[3] = dir;
  HID().SendReport(1,m,4);
}

void high()    //拉高所有按键
{
  digitalWrite(X1,HIGH);
  digitalWrite(X2,HIGH);
  digitalWrite(X3,HIGH);
  digitalWrite(X4,HIGH);
  digitalWrite(X5,HIGH);
}

void setup()   //不就是初始化吗
{
  pinMode(X1,OUTPUT);
  pinMode(X2,OUTPUT);
  pinMode(X3,OUTPUT);
  pinMode(X4,OUTPUT);
  pinMode(X5,OUTPUT);
  pinMode(Y1,INPUT_PULLUP);
  pinMode(Y2,INPUT_PULLUP);
  pinMode(Y3,INPUT_PULLUP);
  pinMode(Y4,INPUT_PULLUP);
  pinMode(Y5,INPUT_PULLUP);//初始化矩阵键盘状态
  
  pinMode(SW,INPUT);
  digitalWrite(SW,HIGH);
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  attachInterrupt(2,ClockChanged,CHANGE);//旋转编码器初始化,中断函数ClockChanged
  high();
  Serial.begin(9600);
}

void scan()   //我来扫描键盘
{
    digitalWrite(X1,LOW);
    key[0][0]=digitalRead(Y1);
    key[0][1]=digitalRead(Y2);
    key[0][2]=digitalRead(Y3);
    key[0][3]=digitalRead(Y4);
    key[0][4]=digitalRead(Y5);
    high();
    digitalWrite(X2,LOW);
    key[1][0]=digitalRead(Y1);
    key[1][1]=digitalRead(Y2);
    key[1][2]=digitalRead(Y3);
    key[1][3]=digitalRead(Y4);
    key[1][4]=digitalRead(Y5);
    high();
    digitalWrite(X3,LOW);
    key[2][0]=digitalRead(Y1);
    key[2][1]=digitalRead(Y2);
    key[2][2]=digitalRead(Y3);
    key[2][3]=digitalRead(Y4);
    key[2][4]=digitalRead(Y5);
    high();
    digitalWrite(X4,LOW);
    key[3][0]=digitalRead(Y1);
    key[3][1]=digitalRead(Y2);
    key[3][2]=digitalRead(Y3);
    key[3][3]=digitalRead(Y4);
    key[3][4]=digitalRead(Y5);
    high();
    digitalWrite(X5,LOW);
    key[4][0]=digitalRead(Y1);
    key[4][1]=digitalRead(Y2);
    key[4][2]=digitalRead(Y3);
    key[4][3]=digitalRead(Y4);
    key[4][4]=digitalRead(Y5);
}

void ClockChanged()  //旋转编码器处理函数
{
  bool tra,sw;
  static int lastCLK;
  int clkv = digitalRead(CLK);//读取CLK引脚的电平
  int dtv = digitalRead(DT);//读取DT引脚的电平
  
  delay(5);//抖动消除
  int clkv_ = digitalRead(CLK);
  int dtv_ = digitalRead(DT);
  if(  clkv!=clkv_  ||  dtv!=dtv_  ) return 0;
  if (lastCLK != clkv)
  {
    lastCLK = clkv;
    if(clkv!=dtv)
      tra=true;
    else
      tra=false;
  }
  sw=digitalRead(SW);
  wheel(!tra);
}

void mode() //获取键盘模式
{
  int mk1,mk2;
  mk1=analogRead(MK1);
  mk2=analogRead(MK2);
  if(  (mk1) &&  (mk2) ) mod=PS;
  if( !(mk1) &&  (mk2) ) mod=PR;
  if(  (mk1) && !(mk2) ) mod=OFF;
  if( !(mk1) && !(mk2) ) mod=SAI;
}

void runnaX1()
{
  if(key[0][0] && key[0][0]!=key_[0][0])
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.print("b");
       break;
     case OFF:
       Keyboard.print("c");
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  ;
}
void runnaX2()
{
  ;
}
void runnaX3()
{
  ;
}
void runnaX4()
{
  ;
}
void runnaX5()
{
  ;
}

void loop()
{
  int check_row;
  mode();
  scan();
  for(check_row=0;check_row<25;check_row++)
  {
    *(key[0]+check_row)=!*(key[0]+check_row);
  }
  for(check_row=0;check_row<25;check_row++)
  {
//   Serial.print(*(key[0]+check_row));
//    Serial.print(*(key_[0]+check_row));
//    Serial.print(" ");
  }
//  delay(1000);
  Serial.println();
  runnaX1();
  runnaX2();
  runnaX3();
  runnaX4();
  runnaX5();
  for(check_row=0;check_row<25;check_row++)
      *(key_[0]+check_row)=*(key[0]+check_row);
}
 
