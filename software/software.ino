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
void K1()  //K1到K25位按键操作，可自行修改
{
  
}
void K2()
{}
void K3()
{}
void K4()
{}
void K5()
{}
void K6()
{}
void K7()
{}
void K8()
{}
void K9()
{}
void K10()
{}
void K11()
{}
void K12()
{}
void K13()
{}
void K14()
{}
void K15()
{}
void K16()
{}
void K17()
{}
void K18()
{}
void K19()
{}
void K20()
{}
void K21()
{}
void K22()
{}
void K23()
{}
void K24()
{}
void K25()
{}
void R1()       //第一行键盘操作
{
  if(row[0]==1 && first[0]==0) {K1();first[0]=1;}
  if(row[0]==0) first[0]=0;
  if(row[1]==1 && first[2]==0) K2();
  if(row[3]==1 && first[3]==0) K4();
  if(row[4]==1 && first[4]==0) K5();
}
void R2()       //第二行键盘操作
{
  if(row[0]==1 && first[5]==0) K6();
  if(row[1]==1 && first[6]==0) K7();
  if(row[2]==1 && first[7]==0) K8();
  if(row[3]==1 && first[8]==0) K9();
  if(row[4]==1 && first[9]==0) K10();
}
void R3()       //第三行键盘操作
{
  if(row[0]==1 && first[10]==0) K11();
  if(row[1]==1 && first[11]==0) K12();
  if(row[2]==1 && first[12]==0) K13();
  if(row[3]==1 && first[13]==0) K14();
  if(row[4]==1 && first[14]==0) K15();
}
void R4()       //第四行键盘操作
{
  if(row[0]==1 && first[15]==0) K16();
  if(row[1]==1 && first[16]==0) K17();
  if(row[2]==1 && first[17]==0) K18();
  if(row[3]==1 && first[18]==0) K19();
  if(row[4]==1 && first[19]==0) K20();
}
void R5()       //第五行键盘操作
{
  if(row[0]==1 && first[20]==0) K21();
  if(row[1]==1 && first[21]==0) K22();
  if(row[2]==1 && first[22]==0) K23();
  if(row[3]==1 && first[23]==0) K24();
  if(row[4]==1 && first[24]==0) K25();
}
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
  if (ro==0)
  {
     if (mode==0)
     {
      
     }
     if (mode==1)
     {
      
     }
     if (mode==2)
     {
      
     }
     if (mode==3)
     {
      
     }
  }
  else
  {
     if (mode==0)
     {
      
     }
     if (mode==1)
     {
      
     }
     if (mode==2)
     {
      
     }
     if (mode==3)
     {
      
     }
  }
}
void PRESS()   //旋转编码器按键中断函数
{
  sei();
  delay(5);
  sw=digitalRead(1);
  if (sw==0)
  {
     if (mode==0)
     {
      
     }
     if (mode==1)
     {
      
     }
     if (mode==2)
     {
      
     }
     if (mode==3)
     {
      
     }
  }
  else
  {
     if (mode==0)
     {
      
     }
     if (mode==1)
     {
      
     }
     if (mode==2)
     {
      
     }
     if (mode==3)
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
