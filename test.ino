
/*
  Datalogger cartão SD

 Este exemplo mostra como registrar dados de três sensores analógicos
 para um cartão SD usando a biblioteca SD.

 O circuito:
 * sensores analógicos nos ins analógicos 0, 1 e 2
 * Cartão SD conectado ao barramento SPI da seguinte maneira:
 ** MOSI - pino 11
 ** MISO - pino 12
 ** CLK - pino 13
 ** CS - pino 4 (para MKRZero SD: SDCARD_SS_PIN)


 */

#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

void setup() {
// Abra a comunicação serial e espere a porta abrir:
Serial.begin(9600);
  while (!Serial) {
    ; // espera que a porta serial se conecte. Necessário apenas para porta USB
  }


  Serial.print("Initializing SD card...");

  // veja se o cartão está presente e pode ser inicializado:

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");

// não faça mais nada:
while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
// cria uma string para montar os dados para registrar:
  String dataString = "";

// leia três sensores e acrescente à string:
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ",";
    }
  }

//  abre o arquivo. note que apenas um arquivo pode ser aberto por vez
  // então você tem que fechar este antes de abrir outro.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // se o arquivo estiver disponível, escreva para ele:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
// imprime para a porta serial também:
    Serial.println(dataString);
  }
// se o arquivo não estiver aberto, aparece um erro:
  else {
    Serial.println("error opening datalog.txt");
  }
}








