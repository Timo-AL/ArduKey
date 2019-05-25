#include <Mouse.h>
#include <Keyboard.h>
#include <HID.h>

#define CLK 0
#define DT 1
#define SW 2//旋转编码器定义

#define MK1 18
#define MK2 19//开关按键定义

#define PS  0
#define PR  1
#define DAV 2
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

bool key[5][5]={0};   //存储键盘当前状态用的数组
bool key_[5][5]={0};  //存储键盘上次状态用的数组

void wheel(bool direct)  //用于模拟鼠标滚轮的函数
{
  static uint8_t m[4]={0,0,0,0};
  short dir=1;   //修改这个值可以改变速度，然而1已经很快了
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
  pinMode(Y5,INPUT_PULLUP);
  high();                   //初始化矩阵键盘状态

  pinMode(MK1,INPUT_PULLUP);
  pinMode(MK2,INPUT_PULLUP);//初始化模式开关
  
  pinMode(SW,INPUT);
  digitalWrite(SW,HIGH);
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  attachInterrupt(2,ClockChanged,CHANGE);//旋转编码器初始化,中断函数ClockChanged
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
    high();
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
  if(!sw)
    wheel(!tra);
  else
  {
    if(tra)
      {
        Keyboard.press(KEY_LEFT_ARROW);
        delayMicroseconds(50);
        Keyboard.release(KEY_LEFT_ARROW);
      }
    else
    {
       Keyboard.press(KEY_RIGHT_ARROW);
       delayMicroseconds(50);
       Keyboard.release(KEY_RIGHT_ARROW);
    }
  }
}

void mode() //获取键盘模式
{
  int mk1,mk2;
  mk1=digitalRead(MK1);
  mk2=digitalRead(MK2);
  if(  (mk1) &&  (mk2) ) mod=PS;
  if( !(mk1) &&  (mk2) ) mod=SAI;
  if(  (mk1) && !(mk2) ) mod=DAV;
  if( !(mk1) && !(mk2) ) mod=PR;
}

void runnaX1()  //key1～key5功能设置
{
  if(key[0][0] && key[0][0]!=key_[0][0])     //key1
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.print("s");
       break;
     case DAV:
       Keyboard.print("n");
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[0][1] && key[0][1]!=key_[0][1])     //key2
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.print("f");
       break;
     case DAV:
       Keyboard.print("f");
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[0][2] && key[0][2]!=key_[0][2])     //key3
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.print("v");
       break;
     case DAV:
       Keyboard.print("a");
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[0][3] && key[0][3]!=key_[0][3])     //key4
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.print("c");
       break;
     case DAV:
       Keyboard.print("b");
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[0][4] && key[0][4]!=key_[0][4])     //key5
  {
      Keyboard.press(KEY_RIGHT_CTRL);
      delayMicroseconds(25);
      Keyboard.print('c');
      delayMicroseconds(25);
      Keyboard.release(KEY_RIGHT_CTRL);
  }
}
void runnaX2()  //key6～key10功能设置
{
  if(key[1][0] && key[1][0]!=key_[1][0])     //key6
  {
      Keyboard.press(KEY_RIGHT_CTRL);
      delayMicroseconds(25);
      Keyboard.print('v');
      delayMicroseconds(25);
      Keyboard.release(KEY_RIGHT_CTRL);
  }
  if(key[1][1] && key[1][1]!=key_[1][1])     //key7
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.print("\\");
       break;
     case DAV:
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.print("z");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_SHIFT);
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[1][2] && key[1][2]!=key_[1][2])     //key8
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.print("i");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_SHIFT);
       break;
     case DAV:
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.print("i");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_SHIFT);
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[1][3] && key[1][3]!=key_[1][3])     //key9
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.print("i");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_SHIFT);
       Keyboard.release(KEY_LEFT_CTRL);
       break;
     case DAV:
       Keyboard.press(KEY_LEFT_ALT);
       Keyboard.print("i");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_ALT);
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[1][4] && key[1][4]!=key_[1][4])     //key10
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.print("i");
       break;
     case DAV:
       Keyboard.print("i");
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
}
void runnaX3()  //key11～key15功能设置
{
  if(key[2][0] && key[2][0]!=key_[2][0])     //key11剪切
  {
      Keyboard.press(KEY_RIGHT_CTRL);
      delayMicroseconds(25);
      Keyboard.print('x');
      delayMicroseconds(25);
      Keyboard.release(KEY_RIGHT_CTRL);
  }
  if(key[2][1] && key[2][1]!=key_[2][1])     //key12
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.print("x");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_SHIFT);
       Keyboard.release(KEY_LEFT_CTRL);
       break;
     case DAV:
       Keyboard.press(KEY_LEFT_ALT);
       Keyboard.print("x");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_ALT);
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[2][2] && key[2][2]!=key_[2][2])     //key13
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.print("o");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_SHIFT);
       break;
     case DAV:
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.print("o");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_SHIFT);
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[2][3] && key[2][3]!=key_[2][3])     //key14
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.print("o");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_SHIFT);
       Keyboard.release(KEY_LEFT_CTRL);
       break;
     case DAV:
       Keyboard.press(KEY_LEFT_ALT);
       Keyboard.print("o");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_ALT);
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[2][4] && key[2][4]!=key_[2][4])     //key15
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.print("o");
       break;
     case DAV:
       Keyboard.print("o");
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
}
void runnaX4()  //key16～key20功能设置
{
  if(key[3][0] && key[3][0]!=key_[3][0])    //Key16保存
  {
      Keyboard.press(KEY_RIGHT_CTRL);
      delayMicroseconds(25);
      Keyboard.print('s');
      delayMicroseconds(25);
      Keyboard.release(KEY_RIGHT_CTRL);
  }
  if(key[3][1] && key[3][1]!=key_[3][1])    //Key17另存为
  {
    Keyboard.press(KEY_RIGHT_CTRL);
    Keyboard.press(KEY_RIGHT_ALT);
    delayMicroseconds(25);
    Keyboard.print('s');
    delayMicroseconds(25);
    Keyboard.release(KEY_RIGHT_CTRL);
    Keyboard.release(KEY_RIGHT_ALT);
  }
  if(key[3][2] && key[3][2]!=key_[3][2])    //key18
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.print("=");
       break;
     case DAV:
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.print("=");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_CTRL);
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[3][3] && key[3][3]!=key_[3][3])    //key19
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.print("-");
       break;
     case DAV:
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.print("-");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_CTRL);
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[3][4] && key[3][4]!=key_[3][4])    //key20
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.print("j");
       break;
     case DAV:
       Keyboard.print("j");
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
}
void runnaX5()  //key21～key25功能设置
{
  if(key[4][0] && key[4][0]!=key_[4][0])    //key21
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.print(" ");
       break;
     case DAV:
       Keyboard.print(" ");
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[4][1] && key[4][1]!=key_[4][1])    //key22显示工作模式
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("Photoshop");
       break;
     case PR:
       Keyboard.print("Premiere");
       break;
     case DAV:
       Keyboard.print("DavinchResolve");
       break;
     case SAI:
       Keyboard.print("EasyPaintToolSAI");
       break;
   }
  }
  if(key[4][2] && key[4][2]!=key_[4][2])    //key23
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.print("r");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_CTRL);
       break;
     case DAV:
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.print("r");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_SHIFT);
       Keyboard.release(KEY_LEFT_CTRL);
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[4][3] && key[4][3]!=key_[4][3])    //key24
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.print("z");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_CTRL);
       break;
     case DAV:
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.print("z");
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_CTRL);
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
  if(key[4][4] && key[4][4]!=key_[4][4])    //key25
  {
    switch(mod)
    {
     case PS:
       Keyboard.print("a");
       break;
     case PR:
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.press(KEY_DELETE);
       delayMicroseconds(50);
       Keyboard.release(KEY_LEFT_SHIFT);
       Keyboard.release(KEY_DELETE);
       break;
     case DAV:
       Keyboard.press(KEY_DELETE);
       delayMicroseconds(50);
       Keyboard.release(KEY_DELETE);
       break;
     case SAI:
       Keyboard.print("d");
       break;
   }
  }
}

void loop()
{
  int check_row,shock_a,shock_b;
  mode();
  scan();
  runnaX1();
  runnaX2();
  runnaX3();
  runnaX4();
  runnaX5();
  for(check_row=0;check_row<25;check_row++)
      *(key_[0]+check_row)=*(key[0]+check_row);
  Keyboard.releaseAll();
}
 
