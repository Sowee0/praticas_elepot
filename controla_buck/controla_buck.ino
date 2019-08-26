const int portaSaida = 9;
const int portaPotenciometro = A0;
int valorPotenciometro;

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  valorPotenciometro = analogRead(portaPotenciometro);
  analogWrite(portaSaida, valorPotenciometro/4);
  Serial.println(valorPotenciometro/4);

}
