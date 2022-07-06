/*
Описание функций библиотеки TM1637

init() - инициализация 
set(n) - яркость сегментов от 0 до 7
clearDisplay() - очистить экран
point(True) - выключить/включить разделитель(две вертикальные точки)
displayInt(value) - вывести на экран четырёхзначное число
displayIntZero(value) - вывести на экран четырёхзначное число с нулями слева
display(posit, Byte) - вывести на экран символ Byte (0-9) в одну из четырёх позиций posit(0-3)
display(array) - вывести на экран массив array из четырёх символов
displayByte(posit, Byte) - вывести на экран символ Byte в одну из четырёх позиций posit(0-3)
displayByte(ARRAY_BYTE) - RRAY_BYTE - массив ( 0x7d, 0x7d, 0x7d, 0x7d )
displayByte(Byte1, Byte2, Byte3, Byte4) - вывести на экран четыре  знака
runningString(buf, sizeof(buf), delay) - бегущая строка из массива (массив, размер массива, задержка в мс)
scroll(BitAddr, DispData, delayms); - обновить значение пролистыванием (адрес, символ, задержка в мс)
scroll(DispData[], delayms); - обновить значение пролистыванием (массив символов, задержка в мс)
scrollByte(BitAddr, DispData, delayms); - обновить значение пролистыванием (адрес, БАЙТ, задержка в мс)
scrollByte(DispData[], delayms); - обновить значение пролистыванием (массив, задержка в мс)  
twist(BitAddr, DispData, delayms) - обновить значение вращением (адрес, символ, задержка в мс)
twist(DispData[], delayms) - обновить значение вращением (массив символов, задержка в мс)
twistByte(BitAddr, DispData, delayms) - обновить значение вращением (адрес, БАЙТ, задержка в мс)
twistByte(DispData[], delayms) - обновить значение вращением (массив, задержка в мс)
displayClock(hrs, mins) - выводит часы, минуты
displayClockScroll(hrs, mins, delayms) - выводит часы, минуты с эффектом пролистывания экрана вниз
displayClockTwist(hrs, mins, delayms) - выводит часы, минуты с эффектом вращения знакоместа
*/
#define CLK 3
#define DIO 2
#define outputRelayBrow 10
#define outputRealyBlue 11

#include "TM1637.h"
#include "max6675.h"

TM1637 disp(CLK, DIO);
int count = 0;

#define outputA 4
#define outputB 5

 int counter = 0; 
 int aState;
 int aLastState;

 int thermoDO = 7;  //он же SO
int thermoCS = 8;
int thermoCLK = 9;  //он же SCK

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() 
{
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);

   pinMode (outputRelayBrow, OUTPUT);
   pinMode (outputRealyBlue, OUTPUT);
   
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA); 
  
  disp.clear();
  disp.brightness(7);  // яркость минимум =0, стандарт=2,  максимум=7)
  disp.displayInt(0);
}

void loop() 
{ 
  /*encoder source
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       count++;
     } else {
       count--;
     }
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
   disp.displayInt(count);
   */
   if(thermocouple.readCelsius() >= 157) {
    //off relay
    disp.point(true);
    digitalWrite(outputRelayBrow,LOW);
    digitalWrite(outputRealyBlue,LOW);
   }
   else if(thermocouple.readCelsius() < 157){
    //on relay
    disp.point(false);
    digitalWrite(outputRelayBrow,HIGH);
    digitalWrite(outputRealyBlue,HIGH);
   }
   disp.displayInt(thermocouple.readCelsius());
   delay(300);
  }

 
