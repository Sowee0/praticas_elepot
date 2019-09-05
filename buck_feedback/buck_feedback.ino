//Código simples para fazer o controle de uma chave em PWM de acordo com o valor de um potênciometro


//Definições referentes ao circuito
const float tensaoFonte = 15;
const float valorDesejadoTensao = 12;
const float relacaoDivisorTensao = 0.333;

//Variáveis de porta
const int portaSaida = 9;
const int portaDivisorTensao = A0;

//variáveis de controle
int valorDivisorTensao;
int valorDesejadoDividido;
int valorPWM;

float maximaTensaoDivisor;


void setPwmFrequencyMEGA2560(int pin, int divisor);

void setup() {
  
  //Inicializando os pinos e a comunicação serial
  pinMode(portaSaida, OUTPUT);
  Serial.begin(9600);

  //Mudando a frequência do timer interno do arduino que governa o PWM (padrão: 500hz)
  setPwmFrequencyMEGA2560(9, 2);

  //Calculando o valor desejado de acordo com a tensao desejada de saida e a relação de R1/R2

  valorDesejadoDividido = tensaoFonte * relacaoDivisorTensao;
  valorDesejadoDividido = (valorDesejadoDividido / 5) * 255;
  

}

void loop() {

  //Lendo o valor do divisor de tensão
  valorDivisorTensao = analogRead(portaDivisorTensao);

  //Fazendo um controle usando o feedback do divisor de tensão para alcançar o valor desejado no divisor de tensão
  if(valorDivisorTensao < valorDesejadoDividido){

    if(valorPWM < 255) //impedindo que o PWM dê overflow dado que seu valor é de 8 bits.
      valorPWM++;

  }
  
  else{

    if(valorPWM > 0) //impedindo que o PWM alcance valores negativos, o que não é permitido.
      valorPWM--;

  }

  //Escrevendo o valor decidido pelo controle simples e depois imprimindo-o via serial
  analogWrite(portaSaida, valorPWM);
  Serial.println(valorPWM);

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
