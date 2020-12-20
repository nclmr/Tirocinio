int n = 40;
int tacquisizione = 1;
int analogPin = A0;
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
      acquisitionREC(); break;
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

void acquisitionREC() {
  for (int i=0; i<n; i++) 
  {
  analogRead(analogPin);
  delay(tacquisizione);
  }
}
 
