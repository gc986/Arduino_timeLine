#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <iarduino_RTC.h>

// Работа с дисплеем
int pinCS = 9;
int numberOfHorizontalDisplays = 4; // теперь у нас по-горизонтали 6 матриц
int numberOfVerticalDisplays = 1; // а по-вертикали, по-прежнему, одна

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "RobotClass.ru"; // текст, который будет плыть
int wait = 40; // время между крайними перемещениями букв

int spacer = 1; // расстояние между буквами
int width = 5 + spacer; // размер шрифта

// Работа со временем
iarduino_RTC time(RTC_DS1302, 8, 6, 7); // Задаем правильно название нашего модуля, а также указываем к каким цифровым пинам его подключаем(в нашем случае – 8,6,7)

void setup() {
  matrix.setIntensity(1); // яркость
  matrix.setPosition(0, 0, 0); // The first display is at <0, 0>
  matrix.setPosition(1, 1, 0); // The second display is at <1, 0>
  matrix.setPosition(2, 2, 0); // The third display is at <2, 0>
  matrix.setPosition(3, 3, 0); // And the last display is at <3, 0>

  matrix.setRotation(0, 1);    // The first display is position upside down
  matrix.setRotation(1, 1);    // The first display is position upside down
  matrix.setRotation(2, 1);    // The first display is position upside down
  matrix.setRotation(3, 1);    // The same hold for the last display

  time.begin();   // функция служит для инициализации работы модуля времени
}

void loop() {
  tape = time.gettime("H:i:s"); //d-m-Y, H:i:s, D
  
  for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {
    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }
      letter--;
      x -= width;
    }

    matrix.write();
    delay(wait);
  }
}
