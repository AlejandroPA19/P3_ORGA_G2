 long t1s1, t2s2;
long d1s1, d2s2;
long t3s3, t4s4;
long d3s3, d4s4;


const int TriggerRestaC1 = 13;   
const int EchoRestaC1 = 12;   
const int TriggerSumaC1 = 11;   
const int EchoSumaC1 = 10;       

const int TriggerRestaC2 = 9;   
const int EchoRestaC2 = 8;      
const int TriggerSumaC2 = 7;     
const int EchoSumaC2 = 6; 

const int flipFlopClockC1 = 3;   
const int multiplexorABC1 = 2;  


const int flipFlopClockC2 = 5;   
const int multiplexorABC2 = 4;  

bool estadoSumaPrevioC1 = false;  
bool estadoRestaPrevioC1 = false;  

bool estadoSumaPrevioC2 = false;
bool estadoRestaPrevioC2 = false;

void setup() {
  Serial.begin(9600);
  pinMode(TriggerSumaC1, OUTPUT);
  pinMode(EchoSumaC1, INPUT);
  pinMode(TriggerRestaC1, OUTPUT);
  pinMode(EchoRestaC1, INPUT);
  pinMode(flipFlopClockC1, OUTPUT);  
  pinMode(multiplexorABC1, OUTPUT);  
  digitalWrite(TriggerSumaC1, LOW);
  digitalWrite(TriggerRestaC1, LOW);

  pinMode(TriggerSumaC2, OUTPUT);
  pinMode(EchoSumaC2, INPUT);
  pinMode(TriggerRestaC2, OUTPUT);
  pinMode(EchoRestaC2, INPUT);
  pinMode(flipFlopClockC2, OUTPUT);  
  pinMode(multiplexorABC2, OUTPUT);  
  digitalWrite(TriggerSumaC2, LOW);
  digitalWrite(TriggerRestaC2, LOW);
  
}

void loop() {
  // Leer el primer sensor (suma)
  digitalWrite(TriggerSumaC1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerSumaC1, LOW);
  t1s1 = pulseIn(EchoSumaC1, HIGH);
  d1s1 = t1s1 / 59;

digitalWrite(TriggerSumaC2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerSumaC2, LOW);
  t3s3 = pulseIn(EchoSumaC2, HIGH);
  d3s3 = t3s3 / 59;
 
  digitalWrite(TriggerRestaC1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerRestaC1, LOW);
  t2s2 = pulseIn(EchoRestaC1, HIGH);
  d2s2 = t2s2 / 59;

  digitalWrite(TriggerRestaC2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerRestaC2, LOW);
  t4s4 = pulseIn(EchoRestaC2, HIGH);
  d4s4 = t4s4 / 59;

  
  bool estadoSumaActual = (d1s1 <= 10);  
  bool estadoSumaActualC2 = (d3s3 <= 10);
  
  if (estadoSumaActual && !estadoSumaPrevioC1) {
 
    digitalWrite(multiplexorABC1, LOW);  
    activarClock();   
  } 
  estadoSumaPrevioC1 = estadoSumaActual;


if (estadoSumaActualC2 && !estadoSumaPrevioC2) {
    
    digitalWrite(multiplexorABC2, LOW);  
    activarClockC2(); 
  } 
  estadoSumaPrevioC2 = estadoSumaActualC2;

 
  bool estadoRestaActual = (d2s2 <= 10);  
  bool estadoRestaActualC2 = (d4s4 <= 10);
  
  if (estadoRestaActual && !estadoRestaPrevioC1) { 
    digitalWrite(multiplexorABC1, HIGH);   
    activarClock();  
  }
 
  estadoRestaPrevioC1 = estadoRestaActual;

if (estadoRestaActualC2 && !estadoRestaPrevioC2) { 
    digitalWrite(multiplexorABC2, HIGH);  
    activarClockC2(); 
  }
  estadoRestaPrevioC2 = estadoRestaActualC2;

  delay(100);  
}
 
void activarClock() {
  digitalWrite(flipFlopClockC1, HIGH);
  delay(10);   
  digitalWrite(flipFlopClockC1, LOW);
}

void activarClockC2() {
  digitalWrite(flipFlopClockC2, HIGH);
  delay(10);
  digitalWrite(flipFlopClockC2, LOW);
}
