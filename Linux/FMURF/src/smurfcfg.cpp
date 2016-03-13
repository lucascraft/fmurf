/*
 *  smurfcfg.cpp
 *
 *  openFrameworks
 *
 *  Created by lucas bigeardel on 16/02/10.
 *  Copyright Lucas Bigeardel 2010. All rights reserved.
 *  This file is part of Fmurf.
 *
 *  Fmurf is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Fmurf is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Fmurf.  If not, see <http://www.gnu.org/licenses/>
 *
 */

#include "smurfcfg.h"
#include "smurf.h"
#include "ofxMSAUtils.h"
#include "ofxXmlSettings.h"
#include <fstream>
using namespace std;

SmurfCfg::SmurfCfg() {
	initColors();
	initSettings();
}

void SmurfCfg::initColors() {
	colors = map<string, msaColor>();

	colors["Aquamarine"]=msaColor( 0x70, 0xDB, 0x93);
	colors["Baker's Chocolate"]=msaColor( 0x5C, 0x33, 0x17);
	colors["Black"]=msaColor( 0x00, 0x00, 0x00);
	colors["Blue"]=msaColor( 0x00, 0x00, 0xFF);
	colors["Brass"]=msaColor( 0xB5, 0xA6, 0x42);
	colors["Bright Gold"]=msaColor( 0xD9, 0xD9, 0x19);
	colors["Brown"]=msaColor( 0xA6, 0x2A, 0x2A);
	colors["Bronze"]=msaColor( 0x8C, 0x78, 0x53);
	colors["Gold"]=msaColor( 0xCD, 0x7F, 0x32);
	colors["Grey"]=msaColor( 0xC0, 0xC0, 0xC0);
	colors["Green"]=msaColor( 0x00, 0xFF, 0x00);
	colors["Copper"]=msaColor( 0xB8, 0x73, 0x33);
	colors["Coral"]=msaColor( 0xFF, 0x7F, 0x00);
	colors["Cyan"]=msaColor( 0x00, 0xFF, 0xFF);
	colors["Dark Green"]=msaColor( 0x2F, 0x4F, 0x2F);
	colors["Green Yellow"]=msaColor( 0x93, 0xDB, 0x70);
	colors["Magenta"]=msaColor(0xFF, 0x00, 0xFF);
	colors["Maroon"]=msaColor( 0x8E, 0x23, 0x6B);
	colors["Medium Blue"]=msaColor( 0x32, 0x32, 0xCD);
	colors["Sienna"]=msaColor( 0x8E, 0x6B, 0x23);
	colors["Silver"]=msaColor( 0xE6, 0xE8, 0xFA);
	colors["Salmon"]=msaColor( 0x6F, 0x42, 0x42);
	colors["Orange"]=msaColor( 0xFF, 0x7F, 0x00);
	colors["Pink"]=msaColor( 0xBC, 0x8F, 0x8F);
	colors["Red"]=msaColor( 0xFF, 0x00, 0x00);
	colors["Summer Sky"]=msaColor( 0x5C, 0x33, 0x17);
	colors["Tan"]=msaColor( 0xDB, 0x93, 0x70);
	colors["Thistle"]=msaColor( 0xD8, 0xBF, 0xD8);
	colors["Turquoise"]=msaColor( 0xAD, 0xEA, 0xEA);
	colors["Very Dark Brown"]=msaColor( 0x5C, 0x40, 0x33);
	colors["Very Light Grey"]=msaColor( 0xCD, 0xCD, 0xCD);
	colors["Violet"]=msaColor( 0x4F, 0x2F, 0x4F);
	colors["Violet Red"]=msaColor( 0xCC, 0x32, 0x99);
	colors["Wheat"]=msaColor( 0xD8, 0xD8, 0xBF);
	colors["White"]=msaColor( 0xFF, 0xFF, 0xFF);
	colors["Yellow"]=msaColor( 0xFF, 0xFF, 0x00);
	colors["Yellow Green"]=msaColor( 0x99, 0xCC, 0x32);
	colors["Dark Yellow"]=msaColor( 0x99, 0xCC, 0x32);
	colors["Bronze II"]=msaColor( 0xA6, 0x7D, 0x3D);
	colors["Cadet Blue"]=msaColor( 0x5F, 0x9F, 0x9F);
    colors["Cool Copper"]=msaColor( 0xD9, 0x87, 0x19);
	colors["Corn Flower Blue"]=msaColor( 0x42, 0x42, 0x6F);
	colors["Dark Brown"]=msaColor( 0x5C, 0x40, 0x33);
	colors["Dark Green Copper"]=msaColor( 0x4A, 0x76, 0x6E);
	colors["Dark Olive Green"]=msaColor( 0x4F, 0x4F, 0x2F);
	colors["Dark Orchid"]=msaColor( 0x99, 0x32, 0xCD);
	colors["Dark Purple"]=msaColor( 0x87, 0x1F, 0x78);
	colors["Dark Slate Blue"]=msaColor(0x6B, 0x23, 0x8E);
	colors["Dark Slate Grey"]=msaColor( 0x2F, 0x4F, 0x4F);
	colors["Dark Tan"]=msaColor(0x97, 0x69, 0x4F);
	colors["Dark Turquoise"]=msaColor( 0x70, 0x93, 0xDB);
	colors["Dark Wood"]=msaColor(0x85, 0x5E, 0x42);
	colors["Dim Grey"]=msaColor( 0x54, 0x54, 0x54);
	colors["Dusty Rose"]=msaColor( 0x85, 0x63, 0x63);
	colors["Feldspar"]=msaColor( 0xD1, 0x92, 0x75);
	colors["Firebrick"]=msaColor( 0x8E, 0x23, 0x23);
	colors["Forest Green"]=msaColor(  0x23, 0x8E, 0x23);
	colors["Goldenrod"]=msaColor( 0xDB, 0xDB, 0x70);
	colors["Green Copper"]=msaColor( 0x52, 0x7F, 0x76);
	colors["Hunter Green"]=msaColor( 0x21, 0x5E, 0x21);
	colors["Indian Red"]=msaColor( 0x4E, 0x2F, 0x2F);
	colors["Khaki"]=msaColor( 0x9F, 0x9F, 0x5F);
	colors["Light Blue"]=msaColor( 0xC0, 0xD9, 0xD9);
	colors["Light Grey"]=msaColor( 0xA8, 0xA8, 0xA8);
	colors["Light Steel Blue"]=msaColor( 0x8F, 0x8F, 0xBD);
	colors["Light Wood"]=msaColor( 0xE9, 0xC2, 0xA6);
	colors["Lime Green"]=msaColor( 0x5C, 0x33, 0x17);
	colors["Mandarian Orange"]=msaColor( 0xE4, 0x78, 0x33);
	colors["Medium Aquamarine"]=msaColor( 0x5C, 0x33, 0x17);
	colors["Medium Forest Green"]=msaColor( 0x6B, 0x8E, 0x23);
	colors["Medium Goldenrod"]=msaColor( 0xEA, 0xEA, 0xAE);
	colors["Medium Orchid"]=msaColor( 0x93, 0x70, 0xDB);
	colors["Medium Sea Green"]=msaColor( 0x42, 0x6F, 0x42);
	colors["Medium Slate Blue"]=msaColor(0x7F, 0x00, 0xFF);
	colors["Medium Spring Green"]=msaColor(0x7F, 0xFF, 0x00);
	colors["Medium Turquoise"]=msaColor( 0x70, 0xDB, 0xDB);
	colors["Medium Violet Red"]=msaColor( 0xDB, 0x70, 0x93);
	colors["Medium Wood"]=msaColor( 0xA6, 0x80, 0x64);
	colors["Midnight Blue"]=msaColor( 0x2F, 0x2F, 0x4F);
	colors["Navy Blue"]=msaColor( 0x23, 0x23, 0x8E);
	colors["Neon Blue"]=msaColor( 0x4D, 0x4D, 0xFF);
	colors["Neon Pink"]=msaColor( 0xFF, 0x6E, 0xC7);
	colors["New Midnight Blue"]=msaColor( 0x00, 0x00, 0x9C);
	colors["New Tan"]=msaColor( 0xEB, 0xC7, 0x9E);
	colors["Old Gold"]=msaColor( 0xCF, 0xB5, 0x3B);
	colors["Orange Red"]=msaColor( 0xFF, 0x24, 0x00);
	colors["Orchid"]=msaColor( 0xDB, 0x70, 0xDB);
	colors["Pale Green"]=msaColor( 0x8F, 0xBC, 0x8F);
	colors["Plum"]=msaColor( 0xEA, 0xAD, 0xEA);
	colors["Quartz"]=msaColor( 0xD9, 0xD9, 0xF3);
	colors["Rich Blue"]=msaColor( 0x59, 0x59, 0xAB);
	colors["Scarlet"]=msaColor( 0x8C, 0x17, 0x17);
	colors["Sea Green"]=msaColor( 0x5C, 0x33, 0x17);
	colors["Semi-Sweet Chocolate"]=msaColor( 0x5C, 0x33, 0x17);
	colors["Sky Blue"]=msaColor(0x32, 0x99, 0xCC);
	colors["Slate Blue"]=msaColor( 0x00, 0x7F, 0xFF);
	colors["Spicy Pink"]=msaColor( 0xFF, 0x1C, 0xAE);
	colors["Spring Green"]=msaColor( 0x00, 0xFF, 0x7F);
	colors["Steel Blue"]=msaColor( 0x23, 0x6B, 0x8E);
}

SmurfAspect SmurfCfg::getStyle(string _style) {
	if (_style == "SQUARE") {
		return SMURF_ASPECT_SQUARE;
	} else if (_style == "STAR") {
		return SMURF_ASPECT_STAR;
	} else { 
		return SMURF_ASPECT_DISC;
	}
}

SmurfFunction SmurfCfg::getFunction(string _function) {
	if (_function == "KNOB") {
		return SMURF_FUNC_KNOB;
	}  else { 
		return SMURF_FUNC_NONE;
	}
}


//
// Return the color corresponding to a given index
//
msaColor SmurfCfg::getColor(int _idx) {
	int index = _idx%colors.size(), i = 0;
	map<string, msaColor>::iterator it;
	for ( it=colors.begin() ; it != colors.end(); it++ ) {
		if (i == index) {
			return it->second;
		}
		i++;
	}
	return getColor("Red");
}

void SmurfCfg::initSettings() {	
	details = map<float, SmurfDetails*>();
	int path_size = 1024;
	char* path = new char[path_size];   
	path = getcwd(path, path_size);
	
#ifdef TARGET_OS_MAC
	const char* settingsFilePath = strcat(path, "/../../../data/settings.xml");
#elif TARGET_OS_UNIX
	const char* settingsFilePath = strcat(path, "/data/settings.xml");
//#else // UNIX
//	const char* settingsFilePath = strcat(path, "/data/settings.xml");
#endif
	cout << "Settings File Path : " << settingsFilePath << endl;
	
	ofDisableDataPath();
	
	if( XML.loadFile(settingsFilePath)){
        					
		// OSC Send Address
		string addr = XML.getValue("smurf:settings:OscSendAddress", "localhost");
		setOscSendAddress(addr);
				
		// OSC Send Port
		int oscSendPort = XML.getValue("smurf:settings:OscSendPort",  12345);
		setOscSendPort(oscSendPort);
		
		// OSC Receive Port
		int oscReceivePort = XML.getValue("smurf:settings:OscReceivePort",  3334);
		setOscReceivePort(oscReceivePort);
		
		// TUIO Port
		int tuioPort = XML.getValue("smurf:settings:TuioPort",  3333);
		setTuioPort(tuioPort);
				
		cout 
		<< "OSC Send on " << addr 
		<< " @ " << oscSendPort 
		<< " listening : TUIO on " << tuioPort 
		<< ", OSC on " << oscReceivePort 
		<< endl;
						
		XML.pushTag("smurf", 0);

		int numTags = XML.getNumTags("fid");	

		for (int i=0;i<numTags;i++) {
			XML.pushTag("fid", i);
			// <fid> id=0 style=ROUND FG="Green" radius=30.0 </fid>
			float uid = XML.getValue("id", 0.0);
			string style = XML.getValue("style", "");
			string kind = XML.getValue("kind", "");
			string bg = XML.getValue("BG", "");
			string fg = XML.getValue("FG", "");
			float radius = XML.getValue("radius", 0.0);
			float proxima = XML.getValue("proxima", 15.0);
			float range = XML.getValue("range", 15.0);
			string function = XML.getValue("function", "");
			bool proximaVisible = XML.getValue("proximaVisible", false);
			
			details[uid] = new SmurfDetails(uid, 0.0, getColor(fg), getColor(bg), getStyle(style), radius, proxima, range, getFunction(function), kind, proximaVisible);
			
			XML.popTag();
		}
		
		XML.popTag();
		XML.popTag();
		
		ofLog(OF_LOG_NOTICE, "Settings read successfully");
	}
}

msaColor SmurfCfg::getColor(string _name) {
	return colors[_name];
}

void SmurfCfg::setTuioPort(int _port) {
	tuioPort = _port;
}

int SmurfCfg::getTuioPort() {
	return tuioPort;
}

void SmurfCfg::setOscSendPort(int _port) {
	oscSendPort = _port;
}

int SmurfCfg::getOscSendPort() {
	return oscSendPort;
}

void SmurfCfg::setOscReceivePort(int _port) {
	oscReceivePort = _port;
}

int SmurfCfg::getOscReceivePort() {
	return oscReceivePort;
}

void SmurfCfg::setOscSendAddress(string _address) {
	oscSendAddress = _address;
}

string SmurfCfg::getOscSendAddress() {
	return oscSendAddress;
}

SmurfDetails* SmurfCfg::getSmurfDetails(float _uid) {
	return details[_uid];
}

SmurfDetails::SmurfDetails(float _uid, float _sessionId, msaColor _bg, msaColor _fg, SmurfAspect _aspect, float _radius, float _proxima, float _range, SmurfFunction _function, string _kind, bool _proximaVisible) {
	uid = _uid;
	sessionId = _sessionId;
	bg = _bg;
	fg = _fg;
	aspect = _aspect;
	radius = _radius;
	proxima = _proxima;
	range = _range;
	function = _function;
	kind = _kind;
}



