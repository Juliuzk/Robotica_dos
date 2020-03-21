 // Librerias externas
#include <Servo.h>

// # Conexion Pines:
// # Ruedas de la Izquierda
// #        M1I pin  -> Digital pin 2
// #        E1I pin  -> Digital pin 3
// #        M2I pin  -> Digital pin 4
// #        E2I pin  -> Digital pin 5
// # Ruedas de la Derecha
// #        M1D pin  -> Digital pin 6
// #        E1D pin  -> Digital pin 7
// #        M2D pin  -> Digital pin 8
// #        E2D pin  -> Digital pin 9


// #Declaracion de Variables necesarias para funcionamiento
// Senson Ultrasonico

const int trigPin = 10;
const int echoPin = 11;

//configuramos sensor ultrasonico

long duration;
long distance;

//ruedas de la izquierda
int E1I = 2;
int M1I = 3;
int E2I = 4;
int M2I = 5;

//ruedas de la derecha
int E1D = 6;
int M1D = 7;
int E2D = 8;
int M2D = 9;

// sensor de luz
const int pinLight = A0;

// Definimos una variable de tipo servo(motor)

Servo myservo;  // crea el objeto servo
int pos;    // posicion del servo

// Definimos estado inicial
int estado; 


void setup() {
//Configuraremos todos los sensores, motores que searn usados

    
    //configurando motores
    pinMode(M1I, OUTPUT);
    pinMode(M2I, OUTPUT);
    pinMode(M1D, OUTPUT);
    pinMode(M2D, OUTPUT);


    //configurando sensor ultrasonico
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(trigPin, LOW);//Inicializamos el pin con 0
    // servo motor
    myservo.attach(12);  // vincula el servo al pin digital 9
  
    // si el pin de entrada analógica 0 está desconectado, el ruido analógico
    // hará la llamada a randomSeed () para generar diferentes
    // números de semilla cada vez que se ejecuta el programa. 
    // RandomSeed () A continuación, mezclará la función aleatoria.
      randomSeed(analogRead(0));
  
    //serial
    Serial.begin(9600);


}

void loop() {
  Serial.println("Iniciando");
  //inicializamos variables del robot
  //definimos estado inicial del robot, el cual es partir desde la plataforma negra
  estado = 0;
  //posicionamos la garra abierta
  abrir_garra();

  // definimos variables
  long check_distancia;
  int check_luz;
  
  do{
  
    Serial.println("entre do");
    // Paso 1: ROBOT COMIENZA EN PLATAFORMA NEGRA
    if(estado == 0){
      Serial.println("Paso 1");
      //si estado = inicial = 0, movemos el vehiculo hacia adelante durante un tiempo de 4 segundos
      seguir_derecho(2);
     
      frenar();
      estado = 1;
     
    }

    //Paso 2_
    if(estado == 1){
      Serial.println("Paso 2");
      // si estado es igual a 1, revisaremos si tenemos una pelota enfrente
      frenar();
      check_distancia = revisar_distancia_pelota();
      if(check_distancia < 8){
        cerrar_garra();

        //estado 2 = garra cerrada, debe buscar area negra y abrir garra
        estado = 2;
      }else{
      giro_random(random_num());
      seguir_derecho(2);
      }
    }

      if(estado == 2){
        Serial.println("Paso 3");
      
      frenar();
      // si estado es igual a 1, revisaremos si tenemos una pelota enfrente
      check_luz = sensor_luz();
      if(check_luz < 20){
        frenar();  
        abrir_garra();
        //si el vehiculo se encuentra en estado 3, significa que abrio la garra y solo la pelota en el area negra, por lo cual debe volver a comenzar
        estado = 3;
      }else{
        giro_random(random_num());
        seguir_derecho(2);
      }
    }

  }while(estado != 3);
  
}



int sensor_luz(){
  Serial.println("Entre al sensor de luz.");
  int sensorValue = analogRead(pinLight);
  return sensorValue;
}



void seguir_derecho(int segundos){
  
    digitalWrite(M1I,HIGH);
    digitalWrite(M2I,HIGH);
    digitalWrite(M1D,HIGH);
    digitalWrite(M2D,HIGH);
    
    analogWrite(E1I, 250);   //PWM Speed Control
    analogWrite(E2I, 250);   //PWM Speed Control
    analogWrite(E1D, 250);   //PWM Speed ControlitalWrit
    analogWrite(E2D, 250);   //PWM Speed Control

    delay(segundos*1000);
}

void giro_random(int segundos){
  
    digitalWrite(M1I,HIGH);
    digitalWrite(M2I,HIGH);
    digitalWrite(M1D,LOW);
    digitalWrite(M2D,LOW);
    
    analogWrite(E1I, 150);   //PWM Speed Control
    analogWrite(E2I, 150);   //PWM Speed Control
    analogWrite(E1D, 150);   //PWM Speed ControlitalWrit
    analogWrite(E2D, 150);   //PWM Speed Control

    delay(segundos*1000);
}

void frenar(){
  

    digitalWrite(M1I,HIGH);
    digitalWrite(M2I,HIGH);
    digitalWrite(M1D,HIGH);
    digitalWrite(M2D,HIGH);
    
    analogWrite(E1I, 0);   //PWM Speed Control
    analogWrite(E2I, 0);   //PWM Speed Control
    analogWrite(E1D, 0);   //PWM Speed ControlitalWrit
    analogWrite(E2D, 0);   //PWM Speed Control

    delay(2000);
}


void cerrar_garra(){
        //varia la posicion de 0 a 180, con esperas de 15ms
      for (pos = 0; pos <= 180; pos += 1) 
      {
      myservo.write(pos);              
      delay(50);                       
      }
}

void abrir_garra(){
        //varia la posicion de 0 a 180, con esperas de 15ms
      for (pos = 180; pos >= 0; pos -= 1) 
      {
        myservo.write(pos);              
        delay(50);                       
      }
}

long revisar_distancia_pelota(){
  
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);          //Enviamos un pulso de 10us
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin,HIGH);
    distance = duration/59;

    return distance;
}


int random_num(){

  return random(3, 10);
}
  
