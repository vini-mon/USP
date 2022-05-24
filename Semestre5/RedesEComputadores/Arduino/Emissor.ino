
#define PINO_RX 13
#define PINO_TX 13
#define RTS 11
#define CTS 10
#define BAUD_RATE 1
#define HALF_BAUD 1000/(2*BAUD_RATE)

#include "Temporizador.h"

char actualChar;
int actualBit = -1;
bool temp = false;

// Calcula bit de paridade - Par ou impar
bool bitParidade(char dado){
  int counter = 0;
  for(int i = 0; i < 8; i++)
    counter+=bitRead(dado, i);
  return (counter + 1) % 2 == 0;
}

ISR(TIMER1_COMPA_vect){
  //bit inicio
  if(actualBit == -1)
    digitalWrite(PINO_TX, HIGH);
    
  //bits de dados
  else if(actualBit >= 0 && actualBit < 8)
    digitalWrite(PINO_TX, bitRead(actualChar, actualBit) ? HIGH : LOW);
  
  //bit de paridade
  else if(actualBit == 8)
    digitalWrite(PINO_TX, bitParidade(actualChar) ? HIGH : LOW);
  
  //bit de encerramento
  else if(actualBit == 9)
    digitalWrite(PINO_TX, HIGH);
  
  else if(actualBit>9){
    digitalWrite(RTS, LOW);
    temp = false;
    paraTemporizador();
  }
  
  
  if(actualBit <= 9)
    actualBit++;


  //teste
  Serial.print(digitalRead(PINO_TX));
}

void setup(){
  //desabilita interrupcoes
  noInterrupts();
  
  // Configura porta serial (Serial Monitor - Ctrl + Shift + M)
  Serial.begin(9600);
  
  // Inicializa TX ou RX
  pinMode(PINO_TX, OUTPUT);
  pinMode(RTS, OUTPUT);
  pinMode(CTS, INPUT);
  digitalWrite(RTS, LOW);
  
  // Configura timer
  configuraTemporizador(BAUD_RATE);
  
  // habilita interrupcoes
  interrupts();
}

void loop ( ) {
  //há dados mas não há transmissão sendo feita
  if(Serial.available() > 0 && digitalRead(RTS) == LOW && digitalRead(CTS) == LOW && !temp) {
    actualChar = Serial.read();
    //teste
    Serial.println("Caractere atual");
    //teste
    Serial.println((int) actualChar);
    actualBit = -1;
    digitalWrite(RTS, HIGH);
  }
  /*
  //teste
  else if(digitalRead(RTS) == HIGH &&  !temp) {
    temp = true;
    iniciaTemporizador();
  }
  //teste
  else if(digitalRead(RTS) == HIGH && actualBit > 9 && temp) {
    temp = false;
    digitalWrite(RTS, false);
    paraTemporizador();
  }*/
  //receptor seta CTS como HIGH
  else if(digitalRead(RTS) == HIGH && digitalRead(CTS) == HIGH && !temp) {
    temp = true;
    iniciaTemporizador();
  }

}
