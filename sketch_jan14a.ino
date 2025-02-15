// Подключение библиотеки для работы с ультразвуковым датчиком
#include <NewPing.h>

// Определение пинов для ультразвукового датчика
#define TRIGGER_PIN  9
#define ECHO_PIN     10
#define MAX_DISTANCE 200  // Максимальное расстояние для измерения (в см)

// Определение пинов для управления моторами
#define MOTOR_A_FORWARD  4
#define MOTOR_A_BACKWARD 5
#define MOTOR_B_FORWARD  6
#define MOTOR_B_BACKWARD 7

// Создание объекта для работы с ультразвуковым датчиком
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  // Настройка пинов для управления моторами как выходы
  pinMode(MOTOR_A_FORWARD, OUTPUT);
  pinMode(MOTOR_A_BACKWARD, OUTPUT);
  pinMode(MOTOR_B_FORWARD, OUTPUT);
  pinMode(MOTOR_B_BACKWARD, OUTPUT);

  // Инициализация Serial для отладки
  Serial.begin(9600);
}

void loop() {
  // Измерение расстояния до препятствия
  int distance = sonar.ping_cm();

  // Вывод расстояния в Serial Monitor для отладки
  Serial.print("Distance: ");
  Serial.println(distance);

  // Проверка расстояния до препятствия
  if (distance > 0 && distance < 20) {  // Если препятствие ближе 20 см
    // Препятствие обнаружено, поворот влево
    turnLeft();
    delay(500);  // Поворот на 500 мс
  } else {
    // Препятствий нет, движение вперед
    moveForward();
  }

  delay(100);  // Небольшая задержка для стабильности
}

// Функция для движения вперед
void moveForward() {
  digitalWrite(MOTOR_A_FORWARD, LOW);
  digitalWrite(MOTOR_A_BACKWARD, HIGH);
  digitalWrite(MOTOR_B_FORWARD, HIGH);
  digitalWrite(MOTOR_B_BACKWARD, HIGH);
}

// Функция для поворота влево
void turnLeft() {
  digitalWrite(MOTOR_A_FORWARD, LOW);
  digitalWrite(MOTOR_A_BACKWARD, HIGH);  // Левый мотор назад
  digitalWrite(MOTOR_B_FORWARD, LOW);   // Правый мотор вперед
  digitalWrite(MOTOR_B_BACKWARD, LOW);
}

// Функция для остановки
void stopMotors() {
  digitalWrite(MOTOR_A_FORWARD, LOW);
  digitalWrite(MOTOR_A_BACKWARD, LOW);
  digitalWrite(MOTOR_B_FORWARD, LOW);
  digitalWrite(MOTOR_B_BACKWARD, LOW);
}