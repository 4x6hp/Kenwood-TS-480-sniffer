/*
Simple arduino library for parsing Kenwood RS232 data for bands
Kenwood Bandecoder for PA
	by Yuli Kaplan 4x6hp, yuli.kaplan@gmail.com

	IF string example: IF00007021730      006000000030000080

	Reference: PC CONTROL COMMAND REFERENCE FOR THE TS - 480HX / SAT TRANSCEIVER

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//General fuctions

#include "Arduino.h"
#include "KenwoodBandData.h"
#include <SoftwareSerial.h>

#define DEBUG

KenwoodBandData::KenwoodBandData(SoftwareSerial* serial, int trxMode)
{
	_serial = serial;
	_trxMode = trxMode;
}

long KenwoodBandData::GetFrequency()
{
	_str_if = PollTRXData();//Get IF string
	_chastota=_str_if.substring(2, 13).toInt();//get freq from string and convert to long

	#ifdef DEBUG	
	Serial.print("Get str_if freq fun lib: ");
	Serial.println(_chastota);
	#endif // DEBUG

	return _chastota;
}

long KenwoodBandData::GetBand()
{
	_str_if = PollTRXData();//Get IF string
	_chastota=_str_if.substring(2, 13).toInt();//get freq from string and convert to long

	//Map frequency to band
	if (_chastota >=   1800000 && _chastota <=   2000000) {
		_diapazon=160;
	}
	else if (_chastota >=   3500000 && _chastota <=   3800000) {
		_diapazon=80;
	}
	else if (_chastota >=   7000000 && _chastota <=   7200000) {
		_diapazon=40;
	}
	else if (_chastota >=  10100000 && _chastota <=  10150000) {
		_diapazon=30;
	}
	else if (_chastota >=  14000000 && _chastota <=  14350000) {
		_diapazon=20;
	}
	else if (_chastota >=  18068000 && _chastota <=  18168000) {
		_diapazon=17;
	}
	else if (_chastota >=  21000000 && _chastota <=  21450000) {
		_diapazon=15;
	}
	else if (_chastota >=  24890000 && _chastota <=  24990000) {
		_diapazon=12;
	}
	else if (_chastota >=  28000000 && _chastota <=  29700000) {
		_diapazon=10;
	}
	else if (_chastota >=  50000000 && _chastota <=  52000000) {
		_diapazon=6;
	}
	else {
		_diapazon=0;
	}

	return _diapazon;
}

void KenwoodBandData::GetTXRXState()
{

}

void KenwoodBandData::GetTRXMode()
{

}

//Function to read IF string from TRX
String KenwoodBandData::PollTRXData()
{
	//Flush TRX serial
	_serial->flush();

	//If SAM then send IF; to TRX
	if (_trxMode==1)
	{
		Serial.println("Send IF");
		_serial->print("IF;");
		_serial->flush();
	}

	//Read and fill 38 chars from TRX IF string, accourding Kenwood PC commands IF (Retrieves the transceiver status) page 11 in PC CONTROL COMMAND REFERENCE FOR THE TS - 480HX / SAT TRANSCEIVER
	while (_serial->available())
	{
		_inByte = _serial->read();//Read first byte

		if (_inByte == 'I') {
			while (_bufferPos != 37) {
				if (_serial->available() > 0) {
					_buffer[_bufferPos] = _inByte;
					_bufferPos++;
					_inByte = _serial->read();
					if (_inByte == ';') break;
				}
			}

			_str_if = _buffer;

			//memset(_buffer, 0, sizeof(_buffer));
			_bufferPos = 0;
		}
	}

	#ifdef DEBUG
	Serial.print("Buff: ");
	Serial.println((char*)_buffer);
	Serial.flush();
	#endif // DEBUG

	//memset(_buffer, 0, sizeof(_buffer));

	#ifdef DEBUG
	//Serial.print("Buff cleared: ");
	//Serial.println((char*)_buffer);
	#endif // DEBUG

	return _str_if;
}