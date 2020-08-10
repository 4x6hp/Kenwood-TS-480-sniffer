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

#ifndef KenwoodBandData_h
#define KenwoodBandData_h

//General fuctions
#include "Arduino.h"
#include <SoftwareSerial.h>

class KenwoodBandData
{
public:
	KenwoodBandData(SoftwareSerial* serial, int trxMode);
	long GetFrequency();
	long GetBand();
	void GetTXRXState();
	void GetTRXMode();
	String PollTRXData();

private:
	SoftwareSerial* _serial;
	String _strIF;		//Current IF string got from TRX
	int _inByte = -1;	// incoming byte from serial RX
	char _buffer[37];	// string for incoming serial data
	int  _bufferPos = 0;  //buffer position
	int _trxMode = 0;	//TRX mode, 0 - SM (sniffer mode), 1 - SAM (stand alone mode)
	String _str_if;		//Current IF string got from TRX to parse
	long _chastota;	//Frequency variable
	long _diapazon;	//Band variable
};
#endif