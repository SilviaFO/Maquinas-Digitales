#define PIN_BUTTON 34

int numBotPres = 0; //Numero de veces que el boton se presiona
uint32_t lastMillis = 0;//Variable que mide tiempo

void IRAM_ATTR isrButton() {//Se guarda en la memoria interna
  if(millis()- lastMillis > 10) {//cuanto tiempo ha pasado desde que se encendio la esp32
  numBotPres += 1;
  lastMillis = millis(); //Evitas 10 ms de fluctuaciones
  }
  
  // Incremet=nta la variable en uno
  }

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BUTTON, INPUT);

  attachInterrupt(PIN_BUTTON, isrButton, RISING); 
  //Interrupcion adjunta al boton, hace la funcion isrButton 
  //y se detecta con RISING o en cada subida

}

void loop() {
  Serial.printf("El boton se ha presionado %u veces\n", numBotPres);
  delay(100);

}
