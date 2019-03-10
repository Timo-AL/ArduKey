#include <Mouse.h>
#include <Keyboard.h>

bool first[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   //单触发记录数组
short repeat[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //多触发记录数组
short mode;  //模式切换
bool sw;     //按键中断用变量
bool ro;     //旋转中断用变量
short ms0;   //模式切换1（模拟）
short ms1;   //模式切换2（模拟）

void setup()
{
  pinMode(0,INPUT);
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
  pinMode(14,INPUT);
  pinMode(15,INPUT);                   //初始化IO端口
  attachInterrupt(0,ROLL,FALLING);     //旋转编码器旋转中断
  attachInterrupt(2,PRESS,FALLING);    //旋转编码器按键中断  
}

void MODE()
{
  ms0=analogRead(0);
  ms1=analogRead(1);
  if (ms0<256)
    {
      if (ms1<256) mode=0;
      else mode=1;
    }
  else
    {
      if (ms1<256) mode=3;
      else mode=4;
    }
}

void ROLL()    //旋转编码器旋转中断函数
{
  sei();
  delay(5);
  ro=digitalRead(1);
  if (ro=0)
  {
     if (mode=0)
     {
      
     }
     if (mode=1)
     {
      
     }
     if (mode=2)
     {
      
     }
     if (mode=3)
     {
      
     }
  }
  else
  {
     if (mode=0)
     {
      
     }
     if (mode=1)
     {
      
     }
     if (mode=2)
     {
      
     }
     if (mode=3)
     {
      
     }
  }
}

void PRESS()   //旋转编码器按键中断函数
{
  sei();
  delay(5);
  sw=digitalRead(1);
  if (sw=0)
  {
     if (mode=0)
     {
      
     }
     if (mode=1)
     {
      
     }
     if (mode=2)
     {
      
     }
     if (mode=3)
     {
      
     }
  }
  else
  {
     if (mode=0)
     {
      
     }
     if (mode=1)
     {
      
     }
     if (mode=2)
     {
      
     }
     if (mode=3)
     {
      
     }
  }
}

void loop()    //扫描键盘
{
  MODE();
}
