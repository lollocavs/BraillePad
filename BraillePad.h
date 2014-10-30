// Braille.h
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

#ifndef BRAILLEPAD_H
	
#define BRAILLEPAD_H

#include <EEPROM.h>
#include <String.h>
#include "DB.h"

//Creazione del database
struct charBraille {
  char character;
  int pin11;
  int pin12;
  int pin21;
  int pin22;
  int pin31;
  int pin32;
};

class BraillePad

{
public:

	//Costructors
	BraillePad(int pin11, int pin12, int pin21, int pin22, int pin31, int pin32);
	BraillePad(const BraillePad &BP);
	~BraillePad();
	//Configuration of Braille Pad with character input
	void writeBraille(char c);
	void writeSequence(char *s, int length);
private:
	
	//Pin Array for Braille Pad
	int pinArray[6]; 
	
	//DB to Alphabet-Braille Mapping
	charBraille cBraille;
	DB db_Braille; 
	
	//Function to pin activation
	void pinsOn (int pins[6], int Delay); 
	
	//automatic function recording
	void createRecord (DB &db, char c,int pin11, int pin12, int pin21, int pin22, int pin31, int pin32); 
};


#endif