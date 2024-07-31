#include <Servo.h>

// Definición de pines
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 3;

// Configuración del servo
Servo myServo;
const int openAngle = 0;  // Ángulo de apertura
const int closeAngle = 90;  // Ángulo de cierre

// Variables
long duration;
int distance;
const int threshold = 30; // Distancia de detección en cm

void setup() {
  Serial.begin(9600);
  
  // Configuración de pines
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Inicialización del servo
  myServo.attach(servoPin);
  myServo.write(closeAngle);  // Iniciar en posición cerrada
}

void loop() {
  // Medir distancia
  distance = measureDistance();
  
  // Imprimir distancia para depuración
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Si se detecta un objeto cerca
  if (distance < threshold) {
    openDoor();
    delay(4000);  // Esperar 4 segundos
    closeDoor();
    
    // Esperar un poco antes de volver a medir
    delay(1000);
  }
  
  delay(100);  // Pequeña pausa para estabilidad
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void openDoor() {
  myServo.write(openAngle);
  Serial.println("Puerta abierta");
}

void closeDoor() {
  myServo.write(closeAngle);
  Serial.println("Puerta cerrada");
}