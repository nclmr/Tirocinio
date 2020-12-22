int n = 3;
int tacquisizione = 5000;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedlyz
  
  if(Serial.available()) 
  {
    int command = Serial.read();
    switch (command){
      case 'a' : 
      startREC(); break;
      case 'b' :
      stopREC(); break;
      case 'c' : 
      startstopREC(); break;
      case 'd' :
      nacquisitionREC(); break;
    }
  }
}

void startREC() {
  digitalWrite (LED_BUILTIN, HIGH);
  Serial.println("Acceso");
}

void stopREC() {
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Spento");
}

void startstopREC() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(tacquisizione);
    digitalWrite(LED_BUILTIN, LOW);
    delay(tacquisizione);
}

void nacquisitionREC() {
  for (int i=0; i<n; i++) {
    digitalWrite(i, HIGH);
    }
  delay(tacquisizione);
  for (int i=0; i<n; i++) { 
    digitalWrite(i, LOW);
    }
  }
 
