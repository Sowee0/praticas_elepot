//Código simples para fazer o controle de uma chave em PWM de acordo com o valor de um potênciometro

const int portaSaida = 9;
const int portaPotenciometro = A0;
const int pinoBotao = 2;
const int pinoLED = 13;
int razaoCiclicaAtual;

//Configurações do modo de operação oscilado
const int tempoOscilacao = 1000; // em milisegundos
const int razaoCiclicaUm = 0.55 * 255; // em porcentagem
const int razaoCiclicaDois = 0.65 * 255; //em porcentagem

int modoOperacao = 0;
int tempoAtual, tempoAnterior;

void setPwmFrequencyMEGA2560(int pin, int divisor);

void setup() {
  
  setPwmFrequencyMEGA2560(portaSaida, 2);
  pinMode(portaSaida, OUTPUT);
  pinMode(pinoLED, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  if(!modoOperacao)
  {
  razaoCiclicaAtual = analogRead(portaPotenciometro);
  razaoCiclicaAtual = razaoCiclicaAtual / 4;
  }

  else
  {
    tempoAtual = millis();

    if(tempoAtual - tempoAnterior > tempoOscilacao){

      if(razaoCiclicaAtual == razaoCiclicaUm)
        razaoCiclicaAtual = razaoCiclicaDois;
      else
        razaoCiclicaAtual = razaoCiclicaUm;

      tempoAnterior = tempoAtual;
    }

  }

  if(digitalRead(pinoBotao)){
    modoOperacao = !modoOperacao;
    Serial.print("Modo de operação atual: ");

    if(!modoOperacao){
      Serial.println("Potenciometro");
      digitalWrite(pinoLED, LOW);
    }

    else{
      Serial.println("Oscilante");
      digitalWrite(pinoLED, HIGH);
    }
    
  }

  analogWrite(portaSaida, razaoCiclicaAtual);
  delay(200);

  Serial.print("D = ");
  Serial.println(razaoCiclicaAtual);
}

void setPwmFrequencyMEGA2560(int pin, int divisor) {
  byte mode;
      switch(divisor) {
      case 1: mode = 0x01; break;
      case 2: mode = 0x02; break;
      case 3: mode = 0x03; break;
      case 4: mode = 0x04; break;
      case 5: mode = 0x05; break;
      case 6: mode = 0x06; break;
      case 7: mode = 0x07; break;
      default: return;
      }
      
        switch(pin) {    
      case 2:  TCCR3B = TCCR3B  & 0b11111000 | mode; break;
      case 3:  TCCR3B = TCCR3B  & 0b11111000 | mode; break;
      case 4:  TCCR0B = TCCR0B  & 0b11111000 | mode; break;
      case 5:  TCCR3B = TCCR3B  & 0b11111000 | mode; break;
      case 6:  TCCR4B = TCCR4B  & 0b11111000 | mode; break;
      case 7:  TCCR4B = TCCR4B  & 0b11111000 | mode; break;
      case 8:  TCCR4B = TCCR4B  & 0b11111000 | mode; break;
      case 9:  TCCR2B = TCCR0B  & 0b11111000 | mode; break;
      case 10: TCCR2B = TCCR2B  & 0b11111000 | mode; break;
      case 11: TCCR1B = TCCR1B  & 0b11111000 | mode; break;  
      case 12: TCCR1B = TCCR1B  & 0b11111000 | mode; break;  
      case 13: TCCR0B = TCCR0B  & 0b11111000 | mode; break;
      default: return;
    }

}
