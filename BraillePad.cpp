// Braille.cpp
/*
  Braille library for Arduino 
  Written by Lorenzo Cavalieri, PhD Student at UNIVPM (Italy)
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "DB.h"
#include "BraillePad.h"

BraillePad::BraillePad(const BraillePad &BP){
 BraillePad(BP.pinArray[0],BP.pinArray[1],BP.pinArray[2],BP.pinArray[3],BP.pinArray[4],BP.pinArray[5]);
}

BraillePad::BraillePad(int pin11, int pin12, int pin21, int pin22, int pin31, int pin32) {

//Configurazione dei pin
pinMode(pin11,OUTPUT);
pinMode(pin12,OUTPUT);
pinMode(pin21,OUTPUT);
pinMode(pin22,OUTPUT);
pinMode(pin31,OUTPUT);
pinMode(pin32,OUTPUT);

//Inizializzazione dell'array dei pin
pinArray[0]= pin11;
pinArray[1]= pin12;
pinArray[2]= pin21;
pinArray[3]= pin22;
pinArray[4]= pin31;
pinArray[5]= pin32;



db_Braille.create(1,sizeof(cBraille));
db_Braille.open(1);
//createRecord(db_Braille,'a',11,12,21,22,31,32);
createRecord(db_Braille,'A',1,0,0,0,0,0);
createRecord(db_Braille,'B',1,0,1,0,0,0);
createRecord(db_Braille,'C',1,1,0,0,0,0);
createRecord(db_Braille,'D',1,1,0,1,0,0);
createRecord(db_Braille,'E',1,0,0,1,0,0);
createRecord(db_Braille,'F',1,1,1,0,0,0);
createRecord(db_Braille,'H',1,0,1,1,0,0);
createRecord(db_Braille,'I',0,1,1,0,0,0);
createRecord(db_Braille,'J',0,1,1,1,0,0);
createRecord(db_Braille,'K',1,0,0,0,1,0);
createRecord(db_Braille,'L',1,0,1,0,1,0);
createRecord(db_Braille,'M',1,1,0,0,1,0);
createRecord(db_Braille,'N',1,1,0,1,1,0);
createRecord(db_Braille,'O',1,0,0,1,1,0);
createRecord(db_Braille,'P',1,1,1,0,1,0);
createRecord(db_Braille,'Q',1,1,1,1,1,0);
createRecord(db_Braille,'R',1,0,1,1,1,0);
createRecord(db_Braille,'S',0,1,1,0,1,0);
createRecord(db_Braille,'T',0,1,1,1,1,0);
createRecord(db_Braille,'U',1,0,0,0,1,1);
createRecord(db_Braille,'V',1,0,1,0,1,1);
createRecord(db_Braille,'W',0,1,1,1,0,1);
createRecord(db_Braille,'X',1,1,0,0,1,1);
createRecord(db_Braille,'Y',1,1,0,1,1,1);
createRecord(db_Braille,'Z',1,0,0,1,1,1);

}

BraillePad::~BraillePad() {
//delete db_Braille;
}

// Writing Character Function on Braille Pad
void BraillePad::writeBraille(char c){
int ActivationTime= 2000;
//Mapping Char-Int Alphabet
int charID;


for (int n=1; n<db_Braille.nRecs(); n++) {
db_Braille.read(n, DB_REC cBraille);
if (cBraille.character==c) {
	charID=n;
	n=db_Braille.nRecs(); //To exit from the cycle
	}
}
///_________________________________________
// charID = int(c) - 40; //da testare se viene...è molto più veloce
// 
// //--- DEBUG -----------
// serial.println(charID);
// //---------------------
// //___________________________________________
db_Braille.read(charID,DB_REC cBraille);
int pins[]= {cBraille.pin11, cBraille.pin12, cBraille.pin21, cBraille.pin22, cBraille.pin31, cBraille.pin32}; //Pins Configuration
pinsOn(pins, ActivationTime);
}

void BraillePad::writeSequence(char *s, int length) {
	for(int i=0;i<length;i++) writeBraille(s[i]);
}

void BraillePad::createRecord (DB &db, char c,int pin11, int pin12, int pin21, int pin22, int pin31, int pin32) {
cBraille.character = c;
cBraille.pin11 = pin11;
cBraille.pin12 = pin12;
cBraille.pin21 = pin21;
cBraille.pin22 = pin22;
cBraille.pin31 = pin31;
cBraille.pin32 = pin32;

db.append(DB_REC cBraille);
}

void BraillePad::pinsOn (int pins[6], int Delay){
int length=6;
	for (int i=0; i<length-1;i++) {
		if (pins[i]==1) digitalWrite(pinArray[i], HIGH);
	}
	delay(Delay);  
	for (int i=0; i<length-1;i++) {
		if (pins[i]==1) digitalWrite(pinArray[i], LOW);
	}
}