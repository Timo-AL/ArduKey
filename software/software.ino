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

#define X1 8
#define X2 7
#define X3 6
#define X4 5
#define X5 4//横行定义，读取时低电平

#define Y1 9
#define Y2 10
#define Y3 16
#define Y4 14
#define Y5 15//纵行定义，全部上拉读取 

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

void high()
{
  digitalWrite(X1,HIGH);
  digitalWrite(X2,HIGH);
  digitalWrite(X3,HIGH);
  digitalWrite(X4,HIGH);
  digitalWrite(X5,HIGH);
}

void setup()
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
  
  Serial.begin(9600);
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

  delay(5);
  if (lastCLK != clkv)
  {
    lastCLK = clkv;
    if(clkv!=dtv)
      tra=true;
    else
      tra=false;
  }
  sw=digitalRead(SW);
  switch(mod)
  {
    case PS:
      if(tra);
    case PR:
      if(tra);
    case OFF:
      if(tra);
    case SAI:
      if(tra);
  }
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

void loop()
{
  bool swm;
  mode();
  /*if (!digitalRead(SW)) //扫描旋转编码器按键
  {
    delay(10);
    swm=digitalRead(SW);
    if (swm==0)
      {Serial.print("press");}
  }*/
}
 
