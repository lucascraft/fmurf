SinOsc fid0;
SqrOsc fid1;
TriOsc fid2;
SawOsc fid3;
PulseOsc fid4;
Phasor fid5;
Echo fid6;
JCRev fid7;
2 => fid0.sync;
50 => fid0.gain;
2 => fid1.sync;
50 => fid1.gain;
2 => fid2.sync;
50 => fid2.gain;
2 => fid3.sync;
50 => fid3.gain;
2 => fid4.sync;
50 => fid4.gain;
2 => fid5.sync;
50 => fid5.gain;

//JCRev rev;
//2 => rev.op;
//rev => dac;


fun void handleDACConnection(int _fid, int status) {
    if (_fid == 0) {
        if (status == 0) { // DISCONNECTION
            fid0 =< dac;
        } else {
            fid0 => dac;
        }
    } else if(_fid == 1) {
        if (status == 0) { // DISCONNECTION
            fid1 =< dac;
        } else {
            fid1 => dac;
        }
    } else if (_fid == 2) {
        if (status == 0) { // DISCONNECTION
            fid2 =< dac;
        } else {
            fid2 => dac;
        }
    } else if (_fid == 3) {
        if (status == 0) { // DISCONNECTION
            fid3 =< dac;
        } else {
            fid3 => dac;
        }
    } else if (_fid == 4) {
        if (status == 0) { // DISCONNECTION
            fid4 =< dac;
        } else {
            fid4 => dac;
        }
    } else if (_fid == 5) {
        if (status == 0) { // DISCONNECTION
            fid5 =< dac;
        } else {
            fid5 => dac;
        }
    } else if (_fid == 6) {
        if (status == 0) { // DISCONNECTION
            fid6 =< dac;
        } else {
            fid6 => dac;
        }
    } else if (_fid == 7) {
        if (status == 0) { // DISCONNECTION
            fid7 =< dac;
        } else {
            fid7 => dac;
        }
    }

}

fun void handleFidConnection(int _from, int _to) {
    /*  */ if (_from == 0 && _to == 1) {
        fid0 => fid1;
    } else if (_from == 0 && _to == 2) {
        fid0 => fid2;
    } else if (_from == 0 && _to == 3) {
        fid0 => fid3;
    } else if (_from == 0 && _to == 4) {
        fid0 => fid4;
    } else if (_from == 0 && _to == 5) {
        fid0 => fid5;
    } else if (_from == 0 && _to == 6) {
        fid0 => fid6;
    } else if (_from == 0 && _to == 7) {
        fid0 => fid7;
    } else if (_from == 1 && _to == 0) {
        fid1 => fid0;
    } else if (_from == 1 && _to == 2) {
        fid1 => fid2;
    } else if (_from == 1 && _to == 3) {
        fid1 => fid3;
    } else if (_from == 1 && _to == 4) {
        fid1 => fid4;
    } else if (_from == 1 && _to == 5) {
        fid1 => fid5;
    } else if (_from == 1 && _to == 6) {
        fid1 => fid6;
    } else if (_from == 1 && _to == 7) {
        fid1 => fid7;
    } else if (_from == 2 && _to == 0) {
        fid2 => fid0;
    } else if (_from == 2 && _to == 1) {
        fid2 => fid1;
    } else if (_from == 2 && _to == 3) {
        fid2 => fid3;
    } else if (_from == 2 && _to == 4) {
        fid2 => fid4;
    } else if (_from == 2 && _to == 5) {
        fid2 => fid5;
    } else if (_from == 2 && _to == 6) {
        fid2 => fid6;
    } else if (_from == 2 && _to == 7) {
        fid2 => fid7;
    } else if (_from == 3 && _to == 0) {
        fid3 => fid0;
    } else if (_from == 3 && _to == 1) {
        fid3 => fid1;
    } else if (_from == 3 && _to == 2) {
        fid3 => fid2;
    } else if (_from == 3 && _to == 4) {
        fid3 => fid4;
    } else if (_from == 3 && _to == 5) {
        fid3 => fid5;
    } else if (_from == 3 && _to == 6) {
        fid3 => fid6;
    } else if (_from == 3 && _to == 7) {
        fid3 => fid7;
    } else if (_from == 4 && _to == 0) {
        fid4 => fid0;
    } else if (_from == 4 && _to == 1) {
        fid4 => fid1;
    } else if (_from == 4 && _to == 2) {
        fid4 => fid2;
    } else if (_from == 4 && _to == 3) {
        fid4 => fid3;
    } else if (_from == 4 && _to == 5) {
        fid4 => fid5;
    } else if (_from == 4 && _to == 6) {
        fid4 => fid6;
    } else if (_from == 4 && _to == 7) {
        fid4 => fid7;
    } else if (_from == 5 && _to == 0) {
        fid5 => fid0;
    } else if (_from == 5 && _to == 1) {
        fid5 => fid1;
    } else if (_from == 5 && _to == 2) {
        fid5 => fid2;
    } else if (_from == 5 && _to == 3) {
        fid5 => fid3;
    } else if (_from == 5 && _to == 4) {
        fid5 => fid4;
    } else if (_from == 5 && _to == 6) {
        fid5 => fid6;
    } else if (_from == 5 && _to == 7) {
        fid5 => fid7;
    } else if (_from == 6 && _to == 0) {
        fid6 => fid0;
    } else if (_from == 6 && _to == 1) {
        fid6 => fid1;
    } else if (_from == 6 && _to == 2) {
        fid6 => fid2;
    } else if (_from == 6 && _to == 3) {
        fid6 => fid3;
    } else if (_from == 6 && _to == 4) {
        fid6 => fid4;
    } else if (_from == 6 && _to == 5) {
        fid6 => fid5;
    } else if (_from == 6 && _to == 7) {
        fid6 => fid7;
    } else if (_from == 7 && _to == 0) {
        fid7 => fid0;
    } else if (_from == 7 && _to == 1) {
        fid7 => fid1;
    } else if (_from == 7 && _to == 2) {
        fid7 => fid2;
    } else if (_from == 7 && _to == 3) {
        fid7 => fid3;
    } else if (_from == 7 && _to == 4) {
        fid7 => fid4;
    } else if (_from == 7 && _to == 5) {
        fid7 => fid5;
    } else if (_from == 7 && _to == 6) {
        fid7 => fid6;
    }
}

fun void handleFidDisconnection(int _from, int _to) {
    /*  */ if (_from == 0 && _to == 1) {
        fid0 =< fid1;
    } else if (_from == 0 && _to == 2) {
        fid0 =< fid2;
    } else if (_from == 0 && _to == 3) {
        fid0 =< fid3;
    } else if (_from == 0 && _to == 4) {
        fid0 =< fid4;
    } else if (_from == 0 && _to == 5) {
        fid0 =< fid5;
    } else if (_from == 0 && _to == 6) {
        fid0 =< fid6;
    } else if (_from == 0 && _to == 7) {
        fid0 =< fid7;
    } else if (_from == 1 && _to == 0) {
        fid1 =< fid0;
    } else if (_from == 1 && _to == 2) {
        fid1 =< fid2;
    } else if (_from == 1 && _to == 3) {
        fid1 =< fid3;
    } else if (_from == 1 && _to == 4) {
        fid1 =< fid4;
    } else if (_from == 1 && _to == 5) {
        fid1 =< fid5;
    } else if (_from == 1 && _to == 6) {
        fid1 =< fid6;
    } else if (_from == 1 && _to == 7) {
        fid1 =< fid7;
    } else if (_from == 2 && _to == 0) {
        fid2 =< fid0;
    } else if (_from == 2 && _to == 1) {
        fid2 =< fid1;
    } else if (_from == 2 && _to == 3) {
        fid2 =< fid3;
    } else if (_from == 2 && _to == 4) {
        fid2 =< fid4;
    } else if (_from == 2 && _to == 5) {
        fid2 =< fid5;
    } else if (_from == 2 && _to == 6) {
        fid2 =< fid6;
    } else if (_from == 2 && _to == 7) {
        fid2 =< fid7;
    } else if (_from == 3 && _to == 0) {
        fid3 =< fid0;
    } else if (_from == 3 && _to == 1) {
        fid3 =< fid1;
    } else if (_from == 3 && _to == 2) {
        fid3 =< fid2;
    } else if (_from == 3 && _to == 4) {
        fid3 =< fid4;
    } else if (_from == 3 && _to == 5) {
        fid3 =< fid5;
    } else if (_from == 3 && _to == 6) {
        fid3 =< fid6;
    } else if (_from == 3 && _to == 7) {
        fid3 =< fid7;
    } else if (_from == 4 && _to == 0) {
        fid4 =< fid0;
    } else if (_from == 4 && _to == 1) {
        fid4 =< fid1;
    } else if (_from == 4 && _to == 2) {
        fid4 =< fid2;
    } else if (_from == 4 && _to == 3) {
        fid4 =< fid3;
    } else if (_from == 4 && _to == 5) {
        fid4 =< fid5;
    } else if (_from == 4 && _to == 6) {
        fid4 =< fid6;
    } else if (_from == 4 && _to == 7) {
        fid4 =< fid7;
    } else if (_from == 5 && _to == 0) {
        fid5 =< fid0;
    } else if (_from == 5 && _to == 1) {
        fid5 =< fid1;
    } else if (_from == 5 && _to == 2) {
        fid5 =< fid2;
    } else if (_from == 5 && _to == 3) {
        fid5 =< fid3;
    } else if (_from == 5 && _to == 4) {
        fid5 =< fid4;
    } else if (_from == 5 && _to == 6) {
        fid5 =< fid6;
    } else if (_from == 5 && _to == 7) {
        fid5 =< fid7;
    } else if (_from == 6 && _to == 0) {
        fid6 =< fid0;
    } else if (_from == 6 && _to == 1) {
        fid6 =< fid1;
    } else if (_from == 6 && _to == 2) {
        fid6 =< fid2;
    } else if (_from == 6 && _to == 3) {
        fid6 =< fid3;
    } else if (_from == 6 && _to == 4) {
        fid6 =< fid4;
    } else if (_from == 6 && _to == 5) {
        fid6 =< fid5;
    } else if (_from == 6 && _to == 7) {
        fid6 =< fid7;
    } else if (_from == 7 && _to == 0) {
        fid7 =< fid0;
    } else if (_from == 7 && _to == 1) {
        fid7 =< fid1;
    } else if (_from == 7 && _to == 2) {
        fid7 =< fid2;
    } else if (_from == 7 && _to == 3) {
        fid7 =< fid3;
    } else if (_from == 7 && _to == 4) {
        fid7 =< fid4;
    } else if (_from == 7 && _to == 5) {
        fid7 =< fid5;
    } else if (_from == 7 && _to == 6) {
        fid7 =< fid6;
    }
}

fun void setOscFreq(int _id, float _freq) {
    if (_id == 0) {
        _freq => fid0.freq;
    } else if(_id == 1) {
        _freq => fid1.freq;
    } else if (_id == 2) {
        _freq => fid2.freq;
    } else if (_id == 3) {
        _freq => fid3.freq;
    } else if (_id == 4) {
        _freq => fid3.freq;
    } else if (_id == 5) {
        _freq => fid3.freq;
    }
}

fun void setOscGain(int _id, float _gain) {
    if (_id == 0) {
        _gain => fid0.gain;
    } else if(_id == 1) {
        _gain => fid1.gain;
    } else if (_id == 2) {
        _gain => fid2.gain;
    } else if (_id == 3) {
        _gain => fid3.gain;
    } else if (_id == 4) {
        _gain => fid3.gain;
    } else if (_id == 5) {
        _gain => fid3.gain;
    }
}


OscRecv recv;

4444 => recv.port;

recv.listen();

recv.event( "/smurf/connection/add, i, i, i" ) @=> OscEvent connAddListener;
recv.event( "/smurf/connection/update, i, i, i" ) @=> OscEvent connUpdateListener;
recv.event( "/smurf/connection/remove, i, i, i" ) @=> OscEvent connRemoveListener;

recv.event( "/smurf/fid/0/bang, f, f, f" ) @=> OscEvent fidBang0;
recv.event( "/smurf/fid/0/add, f, f, f" ) @=> OscEvent fidAdd0;
recv.event( "/smurf/fid/0/update, f, f, f" ) @=> OscEvent fidUpdate0;
recv.event( "/smurf/fid/0/remove, f, f, f" ) @=> OscEvent fidRemove0;

recv.event( "/smurf/fid/1/bang, f, f, f" ) @=> OscEvent fidBang1;
recv.event( "/smurf/fid/1/add, f, f, f" ) @=> OscEvent fidAdd1;
recv.event( "/smurf/fid/1/update, f, f, f" ) @=> OscEvent fidUpdate1;
recv.event( "/smurf/fid/1/remove, f, f, f" ) @=> OscEvent fidRemove1;

recv.event( "/smurf/fid/2/bang, f, f, f" ) @=> OscEvent fidBang2;
recv.event( "/smurf/fid/2/add, f, f, f" ) @=> OscEvent fidAdd2;
recv.event( "/smurf/fid/2/update, f, f, f" ) @=> OscEvent fidUpdate2;
recv.event( "/smurf/fid/2/remove, f, f, f" ) @=> OscEvent fidRemove2;

recv.event( "/smurf/fid/3/bang, f, f, f" ) @=> OscEvent fidBang3;
recv.event( "/smurf/fid/3/add, f, f, f" ) @=> OscEvent fidAdd3;
recv.event( "/smurf/fid/3/update, f, f, f" ) @=> OscEvent fidUpdate3;
recv.event( "/smurf/fid/3/remove, f, f, f" ) @=> OscEvent fidRemove3;

recv.event( "/smurf/fid/4/bang, f, f, f" ) @=> OscEvent fidBang4;
recv.event( "/smurf/fid/4/add, f, f, f" ) @=> OscEvent fidAdd4;
recv.event( "/smurf/fid/4/update, f, f, f" ) @=> OscEvent fidUpdate4;
recv.event( "/smurf/fid/4/remove, f, f, f" ) @=> OscEvent fidRemove4;

recv.event( "/smurf/fid/5/bang, f, f, f" ) @=> OscEvent fidBang5;
recv.event( "/smurf/fid/5/add, f, f, f" ) @=> OscEvent fidAdd5;
recv.event( "/smurf/fid/5/update, f, f, f" ) @=> OscEvent fidUpdate5;
recv.event( "/smurf/fid/5/remove, f, f, f" ) @=> OscEvent fidRemove5;

recv.event( "/smurf/fid/6/bang, f, f, f" ) @=> OscEvent fidBang6;
recv.event( "/smurf/fid/6/add, f, f, f" ) @=> OscEvent fidAdd6;
recv.event( "/smurf/fid/6/update, f, f, f" ) @=> OscEvent fidUpdate6;
recv.event( "/smurf/fid/6/remove, f, f, f" ) @=> OscEvent fidRemove6;

recv.event( "/smurf/fid/7/bang, f, f, f" ) @=> OscEvent fidBang7;
recv.event( "/smurf/fid/7/add, f, f, f" ) @=> OscEvent fidAdd7;
recv.event( "/smurf/fid/7/update, f, f, f" ) @=> OscEvent fidUpdate7;
recv.event( "/smurf/fid/7/remove, f, f, f" ) @=> OscEvent fidRemove7;

//
// 
//
fun void connAdd(OscEvent _connAdd) {
    while ( true )
    {
        _connAdd => now;
        while(_connAdd.nextMsg() != 0) 
        {
            _connAdd.getInt() => int from;
            _connAdd.getInt() => int to;
            _connAdd.getInt() => int status;
 
             <<< "got ADD connection [" + from + " -> " + to + "] from (via OSC):" >>>;

                if (to == -440) {
                    handleDACConnection(from, 1);
                } else {
                    handleFidConnection(from, to);
               }
        }            
    }
}


fun void connUpdate(OscEvent _connUpdate) {
    while ( true )
    {
        _connUpdate => now;
        while(_connUpdate.nextMsg() != 0) 
        {
            _connUpdate.getInt() => int from;
            _connUpdate.getInt() => int to;
            _connUpdate.getInt() => int status;
            
            <<< "got UPDATE connection [" + from + " -> " + to + "] from (via OSC):" >>>;
        }            
    }
}

//
// 
//
fun void connRemove(OscEvent _connRemove) {
    while ( true )
    {
        _connRemove => now;
        while(_connRemove.nextMsg() != 0) 
        {
            _connRemove.getInt() => int from;
            _connRemove.getInt() => int to;
            _connRemove.getInt() => int status;
      
            <<< "got REMOVE connection [" + from + " -> " + to + "] from (via OSC):" >>>;
            if (to == -440) {
                handleDACConnection(from, 0);
            } else {
                handleFidDisconnection(from, to);
           }
        }            
    }
}

//
// 
//
fun void add(OscEvent _fidAdd, int _fid) {
    while ( true )
    {
        _fidAdd => now;
        while(_fidAdd.nextMsg() != 0) 
        {
//            _fidAdd.getFloat() => float fX;
//            _fidAdd.getFloat() => float fY;
              _fidAdd.getFloat() => float fAngle;
              <<< "got ADD fid #" + _fid + " (via OSC):" >>>;
//            <<< "got add fid #0 X (via OSC):", fX >>>;
//            <<< "got add fid #0 Y (via OSC):", fY >>>;
//            <<< "got add fid #0 Angle (via OSC):", fAngle >>>;
//            _fid.osc => dac;
              //0.0 => fiducials["fid"+_fid.id].osc.gain;
              
              if (_fid < 4) {
                  setOscFreq(_fid, fAngle);
              }
              //fAngle => fiducials["fid"+_fid.id].osc.freq;
        }            
    }
}

//
// 
//
fun void update(OscEvent _fidUpdate, int _fid) {
    while ( true )
    {
        _fidUpdate => now;
        while(_fidUpdate.nextMsg() != 0) 
        {
            _fidUpdate.getFloat() => float fX;
            _fidUpdate.getFloat() => float fY;
            _fidUpdate.getFloat() => float fAngle;
            <<< "got UPDATE fid #" + _fid + " (via OSC):" >>>;
//            <<< "got update fid #0 X (via OSC):", fX >>>;
//            <<< "got update fid #0 Y (via OSC):", fY >>>;
//            <<< "got update fid #0 Angle (via OSC):", fAngle >>>;
            setOscFreq(_fid, 500 * fAngle);
         }            
    }
}

//
// 
//
fun void remove(OscEvent _fidRemove, int _fid) {
    while ( true )
    {
        _fidRemove => now;
        while(_fidRemove.nextMsg() != 0) 
        {
//            _fidRemove.getFloat() => float fX;
//            _fidRemove.getFloat() => float fY;
//            _fidRemove.getFloat() => float fAngle;
            <<< "got REMOVE fid #" + _fid + " (via OSC):" >>>;
//            <<< "got remove fid #0 X (via OSC):", fX >>>;
//            <<< "got remove fid #0 Y (via OSC):", fY >>>;
//            <<< "got remove fid #0 Angle (via OSC):", fAngle >>>;
            //0.0 => fiducials["fid"+_fid.id].osc.gain;
        }            
    }
}

//
// 
//
fun void bang(OscEvent _fidAdd, int _fid) {

}

// Listeners
spork ~ connAdd(connAddListener);
spork ~ connUpdate(connUpdateListener);
spork ~ connRemove(connRemoveListener);

spork ~ add(fidAdd0, 0);
spork ~ update(fidUpdate0, 0);
spork ~ remove(fidRemove0, 0);
spork ~ bang(fidRemove0, 0);

spork ~ add(fidAdd1, 1);
spork ~ update(fidUpdate1, 1);
spork ~ remove(fidRemove1, 1);
spork ~ bang(fidRemove1, 1);

spork ~ add(fidAdd2, 2);
spork ~ update(fidUpdate2, 2);
spork ~ remove(fidRemove2, 2);
spork ~ bang(fidRemove2, 2);

spork ~ add(fidAdd3, 3);
spork ~ update(fidUpdate3, 3);
spork ~ remove(fidRemove3, 3);
spork ~ bang(fidRemove3, 3);

spork ~ add(fidAdd4, 4);
spork ~ update(fidUpdate4, 4);
spork ~ remove(fidRemove4, 4);
spork ~ bang(fidRemove4, 4);

spork ~ add(fidAdd5, 5);
spork ~ update(fidUpdate5, 5);
spork ~ remove(fidRemove5, 5);
spork ~ bang(fidRemove5, 5);

spork ~ add(fidAdd6, 6);
spork ~ update(fidUpdate6, 6);
spork ~ remove(fidRemove6, 6);
spork ~ bang(fidRemove6, 6);

spork ~ add(fidAdd7, 7);
spork ~ update(fidUpdate7, 7);
spork ~ remove(fidRemove7, 7);
spork ~ bang(fidRemove7, 7);

while(true) {
    5::ms => now;
}

