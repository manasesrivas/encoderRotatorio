#include <Arduino.h>

#define Pws A2
#define DT_A 2
#define CLK_B 4

int anterior = 50;

volatile int posicion = 50; // volatile es para hacer global una variable

void encoder(void);

void setup(){
  pinMode(Pws, INPUT_PULLUP);
  Serial.begin(9600);

  pinMode(DT_A, INPUT);
  pinMode(CLK_B, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(DT_A), encoder, LOW);
}

void loop(){
  if(posicion != anterior){
    Serial.println("boton de encoder "+String(digitalRead(Pws)));
    Serial.println("posicion: "+String(posicion));
    anterior=posicion;
  }

}

void encoder(){
  static unsigned long ultimaInterrupcion = 0;
  unsigned long tiempoInterrupcion = millis();

  if(tiempoInterrupcion - ultimaInterrupcion > 5){
    if(digitalRead(CLK_B) == HIGH){
      posicion++;
    Serial.println("posicion: "+String(posicion));

    }else{
      posicion--;
    Serial.println("posicion: "+String(posicion));

    }
    posicion = min(100, max(0, posicion));
    ultimaInterrupcion = tiempoInterrupcion;
  }
}