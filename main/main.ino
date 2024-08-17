#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <Servo.h>
Servo myservo;

#define sensor 9
#define RELAY  10
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#define LED 3
#define button 2

int   mang_mau[2]; 
int   other = 0;
int   orange = 0;
int   yellow=0;
int   tt = 0;
int   all;
int   reset;
int   tt_servo = 0;

void check();
void on_bangtai();
void off_bangtai();
void on_led();
void off_led();
void Display_yellow();
void Display_orange();
void Display_other();
void Display_all();
void resetBoard();
void quay0 ();
void quay180 ();

void setup() 
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight(); 
  
  pinMode(sensor, INPUT);

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);

  pinMode(LED, OUTPUT);

  pinMode(button, INPUT_PULLUP);

  myservo.attach(1);
}

void loop() 
{
  quay0();
  on_bangtai();
  if(digitalRead(sensor)==0)
  {
    while(tt==0)
    {
      off_bangtai();
      on_led();
      check();
      if(mang_mau[0]> 15 && mang_mau[0]< 20 && (mang_mau[0]>= mang_mau[1]) && (mang_mau[0]> mang_mau[2]))
      {
        orange++;
        tt = 1;
        break;
      }
      else if(mang_mau[0]> 235 && mang_mau[0]< 200 && (mang_mau[0]>= mang_mau[1]) && (mang_mau[0]> mang_mau[2]))
      {
        yellow++;
        tt = 1;
        break;
      }
      else
      {
        other++;
        tt_servo=1;
        tt = 1;
        break;
      }
      off_led();
    }
  }  
  if(tt==1)
  {
    tt=0;
    off_led();
    on_bangtai();
    if(tt_servo == 1)
    {
      void quay180();
      delay(100);
      void quay0();
      tt_servo=0;
    }
  }
  all = orange + other + yellow; 
  Display_all();
  Display_other();
  Display_orange();
  Display_yellow();
  delay(1000);
  if(reset == 0)
  {
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("RESET.......");
    delay(1000);
    resetBoard();
  }
}

void check()
{
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  mang_mau[0] = pulseIn(sensorOut, LOW);
  Serial.print("R= ");
  Serial.print(mang_mau[0]);
  Serial.print("  ");
  delay(100);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  mang_mau[1] = pulseIn(sensorOut, LOW);
  Serial.print("G= ");
  Serial.print(mang_mau[1]); 
  Serial.print("  ");
  delay(100);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  mang_mau[2] = pulseIn(sensorOut, LOW);
  Serial.print("B= ");
  Serial.print(mang_mau[2]);
  Serial.println("  ");
  delay(100);
}

void on_bangtai()
{
  digitalWrite(RELAY, LOW);
}
void off_bangtai()
{
  digitalWrite(RELAY, HIGH);
}
void on_led()
{
  digitalWrite(LED, HIGH);
}
void off_led()
{
  digitalWrite(LED, LOW);
}

void Display_yellow()
{
  lcd.setCursor(0,1);
  lcd.print("Y:");
  lcd.print(yellow);
}
void Display_orange()
{
  lcd.setCursor(6,0);
  lcd.print("OG:");
  lcd.print(orange);
}


void Display_other()
{
  lcd.setCursor(11,0);
  lcd.print("OH:");
  lcd.print(other);
}
void Display_all()
{
  lcd.setCursor(11,1);
  lcd.print("SUM:");
  lcd.print(all);
}
void resetBoard()
{
  asm volatile ("jmp 0");
}
void quay0 ()
{
  myservo.write(0);
  delay(1000);
}
void quay180 ()
{
  myservo.write(180);
  delay(1000);
}
