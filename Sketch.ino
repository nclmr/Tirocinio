int n = 3;
int tacquisizione;
char command;
int tOn;

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars]; /*array temporaneo per il parsing*/

boolean newData = false;
void setup() {
  // put your setup code here, to run once:
  Serial.println("Inserisci i dati in questo modo <Modalità, tempoacquisizione, ton>"); 
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedlyz
  recvWithStartEndMarkers();
    if (newData == true) {
      strcpy (tempChars, receivedChars);
      parseData();
      showParsedData();
      
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
    newData = false;
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
    Serial.println("Inserire tempo acquisizione: ");
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

/* FUNZIONE PER PARSARE LA STRINGA DA TERMINALE */
void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    command = *tempChars;
    strtokIndx = strtok(tempChars,",");
    
    /*strtokIndx = strtok(tempChars,",");      // get the first part - the string
    command = atoi(strtokIndx); // copy it to messageFromPC*/
 
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    tacquisizione = atoi(strtokIndx);     // converte questa parte in un intero

    strtokIndx = strtok(NULL, ",");
    tOn = atoi(strtokIndx);     

}

void showParsedData() {
    Serial.print("Modalità: ");
    Serial.println(command);
    Serial.print("Tempo Acquisizione: ");
    Serial.println(tacquisizione);
    Serial.print("TOn: ");
    Serial.println(tOn);
}
