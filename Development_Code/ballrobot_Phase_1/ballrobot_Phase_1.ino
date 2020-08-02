#include<SoftwareSerial.h>
#include<Servo.h>
#define forward 4
#define backward 6
#define turn 5
#define led 7
uint8_t degree = 90;
uint8_t lastdegree = 90;
#define leftofset 45
#define rightofset 45
SoftwareSerial BTR (10,3); //(declare rx, declare tx)
Servo servo;
bool calmode  = false;
int i;
void setup ()
{
    servo.attach(turn);
    pinMode(forward , OUTPUT);
    pinMode(backward , OUTPUT);
    pinMode(led , OUTPUT);
    BTR.begin(9600);
    servo.write(degree);
    digitalWrite(led , HIGH);
}
void loop ()
{
if (BTR.available())
  {
  char data = BTR.read();

if (data == 'c'  || calmode == true)
{
  calmode = true;
  if (data == 'e')
  {
    calmode = false;
  }
  else if (data != 'c')
  {
    degree = (uint8_t)data + degree - 48;
  }
}

  else if (data == '1')     {//servo.write(degree - 32);//////left
                             for (i=lastdegree ;i > (degree - leftofset) ;i--)
                             {
                                  delay (25);
                                  servo.write(i);
                             }
                             lastdegree = i;
                             }
  
  else if (data == '2')     {//servo.write(degree + 40);/////right 
                              for (i=lastdegree ; i < (degree + rightofset) ;i++)
                             {
                                  delay (25);
                                  servo.write( i);
                             }
                             lastdegree =  i;
                             }

  else if (data == '3')     {//servo.write(degree);
    if (lastdegree == (degree + rightofset))
    {
                             for (i=lastdegree ;i > degree ;i--)
                             {
                                  delay (25);
                                  servo.write( i);
                             }
                             lastdegree =  i;
    }
    else if(lastdegree == (degree - leftofset))
    {
                             for (i=lastdegree ;i < degree ;i++)
                             {
                                  delay (25);
                                  servo.write( i);
                             }
                             lastdegree =  i;
                             
    }
    }
 
  else if (data == '4')     {digitalWrite(forward ,LOW);digitalWrite(backward ,LOW);/*Serial.println("center");*/}

  else if (data == '5')     {movslowly(backward,forward);digitalWrite(forward ,HIGH);/*Serial.println("start");*/}
 
  else if (data == '6')     {movslowly(forward,backward); digitalWrite(backward ,HIGH);/*Serial.println("stop");*/}  
}
}

void movslowly(int a, int b)////pin a follows for gnd and b for 
{
  int j;
digitalWrite(a,LOW);
digitalWrite(b,LOW);
for(j=0;j<255;j++)
{
  analogWrite(b,j);
  delay (10);
}
}
