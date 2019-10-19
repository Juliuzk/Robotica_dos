// # Conexion:
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


// ruedas de la izquierda
int E1I = 3;
int M1I = 2;
int E2I = 5;
int M2I = 4;

//ruedas de la derecha
int E1D = 6;
int M1D = 7;
int E2D = 8;
int M2D = 9;

void setup()
{
    pinMode(M1I, OUTPUT);
    pinMode(M2I, OUTPUT);
    pinMode(M1D, OUTPUT);
    pinMode(M2D, OUTPUT);
}

void loop()
{
  int value;
  // se mueva a una velocidad y vaya aumentando
  for(value = 0 ; value <= 250; value+=5)
  {
    digitalWrite(M1I,HIGH);
    digitalWrite(M2I,HIGH);
    digitalWrite(M1D,HIGH);
    digitalWrite(M2D,HIGH);
    analogWrite(E1I, value);   //PWM Speed Control
    analogWrite(E2I, value);   //PWM Speed Control
    analogWrite(E1D, value);   //PWM Speed Control
    analogWrite(E2D, value);   //PWM Speed Control
    
  }
}
