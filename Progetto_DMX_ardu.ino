

#include "MIDIUSB.h"
#include <Conceptinetics.h>

#define BITMASK_CHANNEL B00001111

DMX_Master _dmx(4, 2);

void setup() {
  Serial.begin(115200);
  _dmx.enable();
  _dmx.setChannelRange(1, 4, 0);
}

/*
void loop() {
  midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      Serial.print("Received: ");
      Serial.print(rx.header, HEX);
      Serial.print("-");
      Serial.print(rx.byte1, HEX);
      Serial.print("-");
      Serial.print(rx.byte2, HEX);
      Serial.print("-");
      Serial.println(rx.byte3, HEX);
    }
  } while (rx.header != 0);
}
*/

/*void loop() {
  midiEventPacket_t rx;
  rx = MidiUSB.read();
  if (rx.header != 0) {
    Serial.println(rx.header, DEC); //header sono i primi 4 bit quindi ci dice se è noteon, noteoff, cc
    Serial.println(rx.byte1, DEC);
    Serial.println(rx.byte2, DEC);
    Serial.println(rx.byte3, DEC);
    byte Status_byte = rx.byte1;
    byte channel = Status_byte & BITMASK_CHANNEL;
    Serial.println(channel);
  }
}*/

/*
L'header ci indica che il messaggio è di tipo control change
Il Byte 1 lo considero poco significativo poichè indica il tipo di messaggio (che ci viene già segnalato dell'header)
e il canale che andremo ad estrapolare con una bit mask, considerando il contesto comunque probabilmente ci manterremo
sempre all'interno dello stesso quindi è quasi superfluo (se andremo ad usare molti canali allora divernterà significativo)
Il byte 2 ci dà il numero del controller e servirà per definire i canali DMX (sommando due controller avremo un canale DMX)
Il Byte 3 ci darà l'effettivo valore all'interno del canale
*/

void loop() {
  midiEventPacket_t rx;
  rx = MidiUSB.read();
  if (rx.header != 0) {
    Serial.print("Header: "); // per rendere più chiaro il monitor seriale
    Serial.println(rx.header, DEC); //header sono i primi 4 bit del primo Byte (status byte)
    Serial.print("Controller: ");
    Serial.println(rx.byte2, DEC);
    if (rx.byte2%2 != 0 ) {
      int Valore = 128 + rx.byte3;
      Serial.print("Valore: ");
      Serial.println(Valore);
    }
    else {
      Serial.print("Valore: ");
      Serial.println(rx.byte3, DEC);
    }
    byte Status_byte = rx.byte1;
    byte channel = Status_byte & BITMASK_CHANNEL; // si può usare 0x0F al posto di definire bitmask
    Serial.print("Canale: ");
    Serial.println(channel);
  }
}