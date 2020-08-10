/*
Simple code to use Kenwood RS232 data library to get frequency, band, mode and TRX status
Used for Kenwood Bandecoder for LDOMS PA with Nextion display

Written	by Yuli Kaplan 4X6HP, yuli.kaplan@gmail.com

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

#include <KenwoodBandData.h>

#define trxMode 0 //TRX mode, 0 - SM (sniffer mode), 1 - SAM (stand alone mode)

SoftwareSerial trxSerial(10, 11);// RX, TX
KenwoodBandData trx(&trxSerial, trxMode);

void setup(void) {
	Serial.begin(115200);
	trxSerial.begin(38400);
}

void loop(void) {
	long qrg = trx.GetFrequency();
	long band = trx.GetBand();
	Serial.print("Get freq: ");
	Serial.print(qrg);
	Serial.print(" Get band: ");
	Serial.println(band);
	Serial.flush();
	delay(1000);
}