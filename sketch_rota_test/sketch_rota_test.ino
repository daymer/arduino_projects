#define pinDir 7
#define pinStep 8  // вывод, с которого идёт сигнал на драйвер
#define pirPin 9
#define LEDPin 12

#define pulse_rev 200 // настройка шагов на оборот на драйвере
double time_rev  = 8.0;  // время одного вращения в секундах .

unsigned long total; // всего микросекунд на 1 шаг
unsigned long tpulse; //длительность сигнала
unsigned long tpause; //пауза после сигнала
int pirValue;                        // Переменная для сохранения значения из PIR

void setup() {
  
// режим для STEP и DIR как OUTPUT
pinMode(pinStep, OUTPUT);
digitalWrite(pinStep, LOW);
pinMode(pinDir, OUTPUT);
digitalWrite(pinDir, LOW); // HIGH

pinMode(pirPin, INPUT); 

  total = (time_rev / pulse_rev) * 1000;
  tpulse = total * 0.1;     // должно быть не менее 5 !!! (микросекунд)
  tpause = total * 0.9;

}

void loop() {
    revolution();
}


void revolution(){
 unsigned int i;

  for ( i = 0; i < pulse_rev; i++ ){ 
    digitalWrite(pinStep, HIGH);
    delay(tpulse);
    digitalWrite(pinStep, LOW);
    delay(tpause);
  }
}
