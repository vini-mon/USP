
#define PINO_RX 13
#define PINO_TX 13
#define RTS 11
#define CTS 10
#define BAUD_RATE 1
#define HALF_BAUD 1000/(2*BAUD_RATE)

#include "Temporizador.h"

int actualBit = 0;
int val;
char actualChar;
bool temp = false;

// Calcula bit de paridade - Par ou impar
bool bitParidade(char dado){
  int counter = 0;
  
  for(int i = 0; i < 8; i++)
    counter += bitRead(dado, i);
    
  return (counter) % 2 == 0;
}

// Rotina de interrupcao do timer1
// O que fazer toda vez que 1s passou?
ISR(TIMER1_COMPA_vect){

  // começo a ler a partir dos dados
  //bits de dados
  if(actualBit >= 0 && actualBit < 8){
    val = digitalRead(PINO_TX);
    bitWrite(actualChar, actualBit, val);
  }

  //bit de paridade
  else if(actualBit == 8) {
    val = digitalRead(PINO_TX);
  }   
  
  else if(actualBit > 9){
    
    digitalWrite(CTS, LOW);
    paraTemporizador();
  }
  
  if(actualBit <= 9)
    actualBit++;
}


// Executada uma vez quando o Arduino reseta
void setup(){
  //desabilita interrupcoes
  noInterrupts();
  
  // Configura porta serial (Serial Monitor - Ctrl + Shift + M)
  Serial.begin(9600);
  
  // Inicializa TX ou RX
  pinMode(PINO_RX, INPUT);  // Inicializando o pino receptor
  pinMode(RTS, INPUT);      // Handshake do emissor para receptor
  pinMode(CTS, OUTPUT);     // Handshake do receptor para o emissor
  digitalWrite(CTS, LOW);   // Inicialmente desligado
  
  // Configura timer
  configuraTemporizador(BAUD_RATE);
  
  // habilita interrupcoes
  interrupts();
}

// O loop() eh executado continuamente (como um while(true))
void loop ( ) {
  // VERIFICAR SE O RTS É HIGH E O CTS TÁ LOW, SE SIM, SETO O CTS PRA HIGH
  if(digitalRead(RTS) == HIGH && digitalRead(CTS) == LOW) {
    digitalWrite(CTS, HIGH);
    actualBit = 0;   // resetando
  }
   

  if(digitalRead(RTS) == HIGH && digitalRead(CTS) == HIGH && !temp && digitalRead(PINO_TX) == HIGH) { // o start bit foi utilizado para iniciar o temporizador
    temp = true;
    iniciaTemporizador();
  }

  // VERIFICA SE RTS É LOW E ESTAMOS NO MEIO DE UMA TRANSMISSAO
  // SE SIM, EU SETO MEU CTS PRA LOW, PARO O TEMPORIZADOR
  if(digitalRead(RTS) == LOW && digitalRead(CTS) == HIGH && temp) {
    digitalWrite(CTS, LOW);
    temp = false;
    paraTemporizador();

    // se o bit de paridade for par, printo o ultimo char
    if(bitParidade(actualChar)) {
      Serial.print(actualChar);
    }
  }
}
