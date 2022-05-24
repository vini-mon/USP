
#define PINO_RX 13
#define PINO_TX 13
#define RTS 11
#define CTS 10
#define BAUD_RATE 30
#define HALF_BAUD 1000/(2*BAUD_RATE)

#include "Temporizador.h"

int actualBit = 0;
int val;
char actualChar;
bool temp = false;

bool bitParidadeRecebido = false;

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

  val = digitalRead(PINO_TX);
     
  if(actualBit >= 0 && actualBit < 8){
    bitWrite(actualChar, actualBit, val);
  }

  //bit de paridade
  else if(actualBit == 8) {
    bitParidadeRecebido = val == 0 ? true : false;
  }
  
  if(actualBit <= 9){
    actualBit++;
    //Serial.print(val);
  }
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
    actualBit = -1;   // resetando
    delay(HALF_BAUD);  // delay para controlar a sincronizacao de escrita/leitura
                // deixar delay na metade do período do clock
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
    if(bitParidade(actualChar) == bitParidadeRecebido ) {
      Serial.print(actualChar);
    }
  }
}
