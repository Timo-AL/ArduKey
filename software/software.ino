#include <Mouse.h>
#include <Keyboard.h>

bool row[5]={0,0,0,0,0};    //传输行读取数据数组
bool key[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};     //按键记录数组
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
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(16,INPUT);
  pinMode(14,INPUT);
  pinMode(15,INPUT);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);                 //初始化IO端口
  attachInterrupt(0,ROLL,FALLING);     //旋转编码器旋转中断
  attachInterrupt(2,PRESS,FALLING);    //旋转编码器按键中断
}

void ROWR()     //读取行扫描数据
{
  row[0]=digitalRead(9);
  row[1]=digitalRead(10);
  row[2]=digitalRead(14);
  row[3]=digitalRead(15);
  row[4]=digitalRead(16);
}

void R1()       //第一行键盘操作
{}

void R2()       //第二行键盘操作
{}

void R3()       //第三行键盘操作
{}

void R4()       //第四行键盘操作
{}

void R5()       //第五行键盘操作
{}

void MODE()     //读取键盘模式
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
  
  digitalWrite(4,HIGH);
  ROWR();
  R1();
  digitalWrite(4,LOW);
  
  digitalWrite(5,HIGH);
  ROWR();
  R2();
  digitalWrite(5,LOW);

  digitalWrite(6,HIGH);
  ROWR();
  R3();
  digitalWrite(6,LOW);
  
  digitalWrite(7,HIGH);
  ROWR();
  R4();
  digitalWrite(7,LOW);

  digitalWrite(8,HIGH);
  ROWR();
  R5();
  digitalWrite(8,LOW);
}
