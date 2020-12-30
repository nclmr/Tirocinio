/*PARAMETRI PER ARDUINO*/
int tacquisizione;
int tOn;
int nimpulsi;
/*VARIABILI PER IL PARSING DELLA STRINGA*/
const byte numChars = 32;
char receivedChars[numChars];
char command[numChars] = {0};
char tempChars[numChars]; /*array temporaneo per il parsing*/
boolean newData = false;

void setup() {
  // put your setup code here, to run once:
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
    if (strcmp(command, "START") == 0) {
      startREC();
    } else if (strcmp(command, "STOP") == 0) {
      stopREC();
    } else if (strcmp(command, "START N") == 0) {
      startNImpulsi();
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

void startNImpulsi() {
  int tempo = 0;
  int i = 0;
  while (tempo <= nimpulsi * tacquisizione) {
    digitalWrite(LED_BUILTIN , HIGH);
    delay(tOn);
    digitalWrite(LED_BUILTIN, LOW);
    delay(tacquisizione - tOn);
    i++;
    tempo = tacquisizione * i;
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
  strtokIndx = strtok(tempChars, ",");
  strcpy (command, strtokIndx);

  /*strtokIndx = strtok(tempChars,",");      // get the first part - the string
    command = atoi(strtokIndx); // copy it to messageFromPC*/

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  tacquisizione = atoi(strtokIndx);     // converte questa parte in un intero

  strtokIndx = strtok(NULL, ",");
  tOn = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  nimpulsi = atoi(strtokIndx);

}

void showParsedData() {
  Serial.print("Modalità: ");
  Serial.println(command);
  Serial.print("Tempo Acquisizione: ");
  Serial.println(tacquisizione);
  Serial.print("TOn: ");
  Serial.println(tOn);
  Serial.print("Numero impulsi: ");
  Serial.println(nimpulsi);
}
