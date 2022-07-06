// подключение библиотеки Servo
#include <Servo.h> 
 
// пины подключения сервоприводов
#define PIN_SERVO_X 9
#define PIN_SERVO_Y 10
// пин подключения контакта VRX
#define PIN_VRX A0
// пин подключения контакта VRY
#define PIN_VRY A1
// пин подключения кнопки
#define PIN_BUTTON 3

// создание объектов Servo
Servo servoX;  
Servo servoY;  
// служебные переменные
int joyXpr=0; 
int joyYpr=0; 
int joyX, joyY; 
int angleX, angleY; 
 
void setup() { 
   // запуск последовательного порта
   Serial.begin (9600);             
   // подключить управление сервоприводом к пинам
   // PIN_SERVO_X и PIN_SERVO_Y
   servoX.attach(PIN_SERVO_X);  
   servoY.attach(PIN_SERVO_Y); 
} 

void loop () {
   // получение данных с джойстика
   joyX=analogRead(PIN_VRX);
   joyY=analogRead(PIN_VRY);
   // Выводим значение по оси X
   Serial.print("X = ");            
   Serial.print(joyX);      
   // Выводим значение по оси Y
   Serial.print("  Y = ");            
   Serial.println(joyY);      
   // сравнение с предыдущими
   if(abs(joyX-joyXpr)>10) { // повернуть по оси X
       angleX=map(joyX,0,1023,0,180);
       servoX.write(angleX);              
       // время на перемещение сервопривода
       delay(15); 
   }
   if(abs(joyY-joyYpr)>10) { // повернуть по оси Y
       angleY=map(joyY,0,1023,0,180);
       servoY.write(angleY);              
       // время на перемещение сервопривода
       delay(15); 
   }
   joyXpr=joyX;
   joyYpr=joyY;
}

