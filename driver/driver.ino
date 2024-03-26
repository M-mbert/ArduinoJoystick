#include <GyverMotor.h>
GMotor engie1 (DRIVER2WIRE, 6, 5); //Классы
GMotor engie2 (DRIVER2WIRE, 3, 4);

int speedX = 0; // Вперед-назад
int speedZ = 0; // Скорость поворота

char Value; // Направление движения

void setup() {
  Serial.begin(9600);
  engie1.setDeadtime(2); // Чтобы драйвер не сжеч
  engie2.setDeadtime(2);

  engie1.setSmoothSpeed(20); // Чтобы скорость падала плавно
  engie2.setSmoothSpeed(20);

  engie1.setMode(AUTO); // Старт
  engie2.setMode(AUTO);
}

void loop() {
  if(Serial.available()){
    Serial.print(Value);
    if(speedX <= 255 and speedZ <= 225){// Защита против привышения скорости
      if(Value == "F"){ // Вперед
        speedX += 40;
        speedZ = 0;
        engie1.smoothTick(speedX);
        engie2.smoothTick(speedX);
      }
      else if(Value == "B"){// Назад
        speedX -= 40;
        speedZ = 0;
        engie1.smoothTick(speedX);
        engie2.smoothTick(speedX);
      }
      else if(Value == "R"){// Направо
        speedX = 0;
        speedZ +=10;
        engie1.smoothTick(speedX+speedZ);
        engie2.smoothTick(speedX-speedZ);
      }
      else if(Value == "L"){// Налево
        speedX = 0;
        speedZ +=10;
        engie1.smoothTick(speedX-speedZ);
        engie2.smoothTick(speedX+speedZ);
      }
    } else {
      speedX = 0;
      speedZ = 0;
    }
  }
}
