SinOsc fid0 => FFT fft0 =^ Flux flux0 => blackhole;
SinOsc fid1 => FFT fft1 =^ Flux flux1 => blackhole;
SinOsc fid2 => FFT fft2 =^ Flux flux2 => blackhole;
SawOsc fid3 => FFT fft3 =^ Flux flux3 => blackhole;
SinOsc fid4 => FFT fft4 =^ Flux flux4 => blackhole;
SinOsc fid5 => FFT fft5 =^ Flux flux5 => blackhole;
Echo fid6 => FFT fft6 =^ Flux flux6 => blackhole;
JCRev fid7 => FFT fft7 =^ Flux flux7 => blackhole;
SndBuf fid8 => FFT fft8 =^ Flux flux8 => blackhole;
SndBuf fid9 => FFT fft9 =^ Flux flux9 => blackhole;
SndBuf fid10 => FFT fft10 =^ Flux flux10 => blackhole;

UAnaBlob blob0, blob1, blob2, blob3, blob4, blob5, blob6, blob7, blob8, blob9, blob10;

2 => fid0.sync;
1 => fid0.gain;
2 => fid1.sync;
1 => fid1.gain;
2 => fid2.sync;
1 => fid2.gain;
2 => fid3.sync;
1 => fid3.gain;
2 => fid4.sync;
1 => fid4.gain;
2 => fid5.sync;
1 => fid5.gain;

"/gitSmurf/fmurf/3rdParties/samples/bank_01/01_sax.wav" => fid8.read;
0 => fid8.pos;
20 => fid8.gain;
1 => fid8.rate;
1 => fid8.loop;

"/gitSmurf/fmurf/3rdParties/samples/bank_01/01_jungle.wav" => fid9.read;
0 => fid9.pos;
20 => fid9.gain;
1 => fid9.rate;
1 => fid9.loop;

"/gitSmurf/fmurf/3rdParties/samples/bank_01/02_drums.wav" => fid10.read;
0 => fid10.pos;
20 => fid10.gain;
1 => fid10.rate;
1 => fid10.loop;

//
// Live data feedback
//
OscSend send;

send.setHost("localhost", 4445);

fun void sendLivedata(int _fid, UAnaBlob _blob) {
    send.startMsg("/smurf/fid/" + _fid + "/livedata","f");
    _blob.fval(0) => send.addFloat;
}

fun void computeFlux(int _fid) {
    while(true) {
        25::ms => now;
        if (_fid == 0) {
            flux0.upchuck() @=> blob0;
            sendLivedata(_fid, blob0);
        } else if (_fid == 1) {
            flux1.upchuck() @=> blob1;
            sendLivedata(_fid, blob1);
        } else if (_fid == 2) {
            flux2.upchuck() @=> blob2;
            sendLivedata(_fid, blob2);
        } else if (_fid == 3) {
            flux3.upchuck() @=> blob3;
            sendLivedata(_fid, blob3);
        } else if (_fid == 4) {
            flux4.upchuck() @=> blob4;
            sendLivedata(_fid, blob4);
        } else if (_fid == 5) {
            flux5.upchuck() @=> blob5;
            sendLivedata(_fid, blob5);
        } else if (_fid == 6) {
            flux6.upchuck() @=> blob6;
            sendLivedata(_fid, blob6);
        } else if (_fid == 7) {
            flux7.upchuck() @=> blob7;
            sendLivedata(_fid, blob7);
        } else if (_fid == 8) {
            flux8.upchuck() @=> blob8;
            sendLivedata(_fid, blob8);
        } else if (_fid == 9) {
            flux9.upchuck() @=> blob9;
            sendLivedata(_fid, blob9);
        } else if (_fid == 10) {
            flux10.upchuck() @=> blob10;
            sendLivedata(_fid, blob10);
        }
    }
}

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
    } else if (_fid == 8) {
        if (status == 0) { // DISCONNECTION
            fid8 =< dac;
        } else {
            fid8 => dac;
        }
    } else if (_fid == 9) {
        if (status == 0) { // DISCONNECTION
            fid9 =< dac;
        } else {
            fid9 => dac;
        }
    } else if (_fid == 10) {
        if (status == 0) { // DISCONNECTION
            fid10 =< dac;
        } else {
            fid10 => dac;
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
    } else if (_from == 0 && _to == 8) {
        fid0 => fid8;
    } else if (_from == 0 && _to == 9) {
        fid0 => fid9;
    } else if (_from == 0 && _to == 10) {
        fid0 => fid10;
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
    } else if (_from == 1 && _to == 8) {
        fid1 => fid8;
    } else if (_from == 1 && _to == 9) {
        fid1 => fid9;
    } else if (_from == 1 && _to == 10) {
        fid1 => fid10;
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
    } else if (_from == 2 && _to == 8) {
        fid2 => fid8;
    } else if (_from == 2 && _to == 9) {
        fid2 => fid9;
    } else if (_from == 2 && _to == 10) {
        fid2 => fid10;
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
    } else if (_from == 3 && _to == 8) {
        fid3 => fid8;
    } else if (_from == 3 && _to == 9) {
        fid3 => fid9;
    } else if (_from == 3 && _to == 10) {
        fid3 => fid10;
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
    } else if (_from == 4 && _to == 8) {
        fid4 => fid8;
    } else if (_from == 4 && _to == 9) {
        fid4 => fid9;
    } else if (_from == 4 && _to == 10) {
        fid4 => fid10;
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
    } else if (_from == 5 && _to == 8) {
        fid5 => fid8;
    } else if (_from == 5 && _to == 9) {
        fid5 => fid9;
    } else if (_from == 5 && _to == 10) {
        fid5 => fid10;
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
    } else if (_from == 6 && _to == 8) {
        fid6 => fid8;
    } else if (_from == 6 && _to == 9) {
        fid6 => fid9;
    } else if (_from == 6 && _to == 10) {
        fid6 => fid10;
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
    } else if (_from == 7 && _to == 8) {
        fid7 => fid8;
    } else if (_from == 7 && _to == 9) {
        fid7 => fid9;
    } else if (_from == 7 && _to == 10) {
        fid7 => fid10;
    } else if (_from == 8 && _to == 0) {
        fid8 => fid0;
    } else if (_from == 8 && _to == 1) {
        fid8 => fid1;
    } else if (_from == 8 && _to == 2) {
        fid8 => fid2;
    } else if (_from == 8 && _to == 3) {
        fid8 => fid3;
    } else if (_from == 8 && _to == 4) {
        fid8 => fid4;
    } else if (_from == 8 && _to == 5) {
        fid8 => fid5;
    } else if (_from == 8 && _to == 6) {
        fid8 => fid6;
    } else if (_from == 8 && _to == 7) {
        fid8 => fid7;
    } else if (_from == 8 && _to == 9) {
        fid8 => fid9;
    } else if (_from == 8 && _to == 10) {
        fid8 => fid10;
    } else if (_from == 9 && _to == 0) {
        fid9 => fid0;
    } else if (_from == 9 && _to == 1) {
        fid9 => fid1;
    } else if (_from == 9 && _to == 2) {
        fid9 => fid2;
    } else if (_from == 9 && _to == 3) {
        fid9 => fid3;
    } else if (_from == 9 && _to == 4) {
        fid9 => fid4;
    } else if (_from == 9 && _to == 5) {
        fid9 => fid5;
    } else if (_from == 9 && _to == 6) {
        fid9 => fid6;
    } else if (_from == 9 && _to == 7) {
        fid9 => fid7;
    } else if (_from == 9 && _to == 8) {
        fid9 => fid8;
    } else if (_from == 9 && _to == 10) {
        fid9 => fid10;
    } else if (_from == 10 && _to == 0) {
        fid10 => fid0;
    } else if (_from == 10 && _to == 1) {
        fid10 => fid1;
    } else if (_from == 10 && _to == 2) {
        fid10 => fid2;
    } else if (_from == 10 && _to == 3) {
        fid10 => fid3;
    } else if (_from == 10 && _to == 4) {
        fid10 => fid4;
    } else if (_from == 10 && _to == 5) {
        fid10 => fid5;
    } else if (_from == 10 && _to == 6) {
        fid10 => fid6;
    } else if (_from == 10 && _to == 7) {
        fid10 => fid7;
    } else if (_from == 10 && _to == 8) {
        fid10 => fid8;
    } else if (_from == 10 && _to == 9) {
        fid10 => fid9;
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
    } else if (_from == 0 && _to == 8) {
        fid0 =< fid8;
    } else if (_from == 0 && _to == 9) {
        fid0 =< fid9;
    } else if (_from == 0 && _to == 10) {
        fid0 =< fid10;
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
    } else if (_from == 1 && _to == 8) {
        fid1 =< fid8;
    } else if (_from == 1 && _to == 9) {
        fid1 =< fid9;
    } else if (_from == 1 && _to == 10) {
        fid1 =< fid10;
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
    } else if (_from == 2 && _to == 8) {
        fid2 =< fid8;
    } else if (_from == 2 && _to == 9) {
        fid2 =< fid9;
    } else if (_from == 2 && _to == 10) {
        fid2 =< fid10;
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
    } else if (_from == 3 && _to == 8) {
        fid3 =< fid8;
    } else if (_from == 3 && _to == 9) {
        fid3 =< fid9;
    } else if (_from == 3 && _to == 10) {
        fid3 =< fid10;
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
    } else if (_from == 4 && _to == 8) {
        fid4 =< fid8;
    } else if (_from == 4 && _to == 9) {
        fid4 =< fid9;
    } else if (_from == 4 && _to == 10) {
        fid4 =< fid10;
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
    } else if (_from == 5 && _to == 8) {
        fid5 =< fid8;
    } else if (_from == 5 && _to == 9) {
        fid5 =< fid9;
    } else if (_from == 5 && _to == 10) {
        fid5 =< fid10;
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
    } else if (_from == 6 && _to == 8) {
        fid6 =< fid8;
    } else if (_from == 6 && _to == 9) {
        fid6 =< fid9;
    } else if (_from == 6 && _to == 10) {
        fid6 =< fid10;
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
    } else if (_from == 7 && _to == 8) {
        fid7 =< fid8;
    } else if (_from == 7 && _to == 9) {
        fid7 =< fid9;
    } else if (_from == 7 && _to == 10) {
        fid7 =< fid10;
    } else if (_from == 8 && _to == 0) {
        fid8 =< fid0;
    } else if (_from == 8 && _to == 1) {
        fid8 =< fid1;
    } else if (_from == 8 && _to == 2) {
        fid8 =< fid2;
    } else if (_from == 8 && _to == 3) {
        fid8 =< fid3;
    } else if (_from == 8 && _to == 4) {
        fid8 =< fid4;
    } else if (_from == 8 && _to == 5) {
        fid8 =< fid5;
    } else if (_from == 8 && _to == 6) {
        fid8 =< fid6;
    } else if (_from == 8 && _to == 7) {
        fid8 =< fid7;
    } else if (_from == 8 && _to == 9) {
        fid8 =< fid9;
    } else if (_from == 8 && _to == 10) {
        fid8 =< fid10;
    } else if (_from == 9 && _to == 0) {
        fid9 =< fid0;
    } else if (_from == 9 && _to == 1) {
        fid9 =< fid1;
    } else if (_from == 9 && _to == 2) {
        fid9 =< fid2;
    } else if (_from == 9 && _to == 3) {
        fid9 =< fid3;
    } else if (_from == 9 && _to == 4) {
        fid9 =< fid4;
    } else if (_from == 9 && _to == 5) {
        fid9 =< fid5;
    } else if (_from == 9 && _to == 6) {
        fid9 =< fid6;
    } else if (_from == 9 && _to == 7) {
        fid9 =< fid7;
    } else if (_from == 9 && _to == 8) {
        fid9 =< fid8;
    } else if (_from == 9 && _to == 10) {
        fid9 =< fid10;
    } else if (_from == 10 && _to == 0) {
        fid10 =< fid0;
    } else if (_from == 10 && _to == 1) {
        fid10 =< fid1;
    } else if (_from == 10 && _to == 2) {
        fid10 =< fid2;
    } else if (_from == 10 && _to == 3) {
        fid10 =< fid3;
    } else if (_from == 10 && _to == 4) {
        fid10 =< fid4;
    } else if (_from == 10 && _to == 5) {
        fid10 =< fid5;
    } else if (_from == 10 && _to == 6) {
        fid10 =< fid6;
    } else if (_from == 10 && _to == 7) {
        fid10 =< fid7;
    } else if (_from == 10 && _to == 8) {
        fid10 =< fid8;
    } else if (_from == 10 && _to == 9) {
        fid10 =< fid9;
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
        _freq => fid4.freq;
    } else if (_id == 5) {
        _freq => fid5.freq;
    }
}

fun void setOscGain(int _id, float _gain) {
    if (_id == 0) {
        _gain*25 => fid0.gain;
    } else if(_id == 1) {
        _gain*25 => fid1.gain;
    } else if (_id == 2) {
        _gain*25 => fid2.gain;
    } else if (_id == 3) {
        _gain*25 => fid3.gain;
    } else if (_id == 4) {
        _gain*25 => fid4.gain;
    } else if (_id == 5) {
        _gain*25 => fid5.gain;
    } else if (_id == 8) {
        _gain => fid8.gain;
    } else if (_id == 9) {
        _gain => fid9.gain;
    } else if (_id == 10) {
        _gain => fid10.gain;
    } else if (_id == -440) {
        _gain => dac.gain;
    }
}


OscRecv recv;

4444 => recv.port;

recv.listen();

recv.event( "/smurf/connection/add, i, i, i" ) @=> OscEvent connAddListener;
recv.event( "/smurf/connection/update, i, i, i" ) @=> OscEvent connUpdateListener;
recv.event( "/smurf/connection/remove, i, i, i" ) @=> OscEvent connRemoveListener;

recv.event( "/smurf/beat" ) @=> OscEvent beat;

recv.event( "/smurf/fid/0/bang, f, f, f, f" ) @=> OscEvent fidBang0;
recv.event( "/smurf/fid/0/add, f, f, f" ) @=> OscEvent fidAdd0;
recv.event( "/smurf/fid/0/update, f, f, f, f" ) @=> OscEvent fidUpdate0;
recv.event( "/smurf/fid/0/remove, f, f, f" ) @=> OscEvent fidRemove0;

recv.event( "/smurf/fid/1/bang, f, f, f, f" ) @=> OscEvent fidBang1;
recv.event( "/smurf/fid/1/add, f, f, f" ) @=> OscEvent fidAdd1;
recv.event( "/smurf/fid/1/update, f, f, f, f" ) @=> OscEvent fidUpdate1;
recv.event( "/smurf/fid/1/remove, f, f, f" ) @=> OscEvent fidRemove1;

recv.event( "/smurf/fid/2/bang, f, f, f, f" ) @=> OscEvent fidBang2;
recv.event( "/smurf/fid/2/add, f, f, f" ) @=> OscEvent fidAdd2;
recv.event( "/smurf/fid/2/update, f, f, f, f" ) @=> OscEvent fidUpdate2;
recv.event( "/smurf/fid/2/remove, f, f, f" ) @=> OscEvent fidRemove2;

recv.event( "/smurf/fid/3/bang, f, f, f, f" ) @=> OscEvent fidBang3;
recv.event( "/smurf/fid/3/add, f, f, f" ) @=> OscEvent fidAdd3;
recv.event( "/smurf/fid/3/update, f, f, f, f" ) @=> OscEvent fidUpdate3;
recv.event( "/smurf/fid/3/remove, f, f, f" ) @=> OscEvent fidRemove3;

recv.event( "/smurf/fid/4/bang, f, f, f, f" ) @=> OscEvent fidBang4;
recv.event( "/smurf/fid/4/add, f, f, f" ) @=> OscEvent fidAdd4;
recv.event( "/smurf/fid/4/update, f, f, f, f" ) @=> OscEvent fidUpdate4;
recv.event( "/smurf/fid/4/remove, f, f, f" ) @=> OscEvent fidRemove4;

recv.event( "/smurf/fid/5/bang, f, f, f, f" ) @=> OscEvent fidBang5;
recv.event( "/smurf/fid/5/add, f, f, f" ) @=> OscEvent fidAdd5;
recv.event( "/smurf/fid/5/update, f, f, f, f" ) @=> OscEvent fidUpdate5;
recv.event( "/smurf/fid/5/remove, f, f, f" ) @=> OscEvent fidRemove5;

recv.event( "/smurf/fid/6/bang, f, f, f, f" ) @=> OscEvent fidBang6;
recv.event( "/smurf/fid/6/add, f, f, f" ) @=> OscEvent fidAdd6;
recv.event( "/smurf/fid/6/update, f, f, f, f" ) @=> OscEvent fidUpdate6;
recv.event( "/smurf/fid/6/remove, f, f, f" ) @=> OscEvent fidRemove6;

recv.event( "/smurf/fid/7/bang, f, f, f, f" ) @=> OscEvent fidBang7;
recv.event( "/smurf/fid/7/add, f, f, f" ) @=> OscEvent fidAdd7;
recv.event( "/smurf/fid/7/update, f, f, f, f" ) @=> OscEvent fidUpdate7;
recv.event( "/smurf/fid/7/remove, f, f, f" ) @=> OscEvent fidRemove7;

recv.event( "/smurf/fid/8/bang, f, f, f, f" ) @=> OscEvent fidBang8;
recv.event( "/smurf/fid/8/add, f, f, f" ) @=> OscEvent fidAdd8;
recv.event( "/smurf/fid/8/update, f, f, f, f" ) @=> OscEvent fidUpdate8;
recv.event( "/smurf/fid/8/remove, f, f, f" ) @=> OscEvent fidRemove8;

recv.event( "/smurf/fid/9/bang, f, f, f, f" ) @=> OscEvent fidBang9;
recv.event( "/smurf/fid/9/add, f, f, f" ) @=> OscEvent fidAdd9;
recv.event( "/smurf/fid/9/update, f, f, f, f" ) @=> OscEvent fidUpdate9;
recv.event( "/smurf/fid/9/remove, f, f, f" ) @=> OscEvent fidRemove9;

recv.event( "/smurf/fid/10/bang, f, f, f, f" ) @=> OscEvent fidBang10;
recv.event( "/smurf/fid/10/add, f, f, f" ) @=> OscEvent fidAdd10;
recv.event( "/smurf/fid/10/update, f, f, f, f" ) @=> OscEvent fidUpdate10;
recv.event( "/smurf/fid/10/remove, f, f, f" ) @=> OscEvent fidRemove10;

recv.event( "/smurf/fid/-440/update, f, f, f, f" ) @=> OscEvent dacUpdate;
recv.event( "/smurf/fid/-440/bang, f, f, f, f" ) @=> OscEvent dacBang;

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
            _fidAdd.getFloat() => float fX;
            _fidAdd.getFloat() => float fY;
            _fidAdd.getFloat() => float fAngle;
            <<< "got ADD fid #" + _fid + " (via OSC):" >>>;
             if (_fid < 6) {
                 setOscFreq(_fid, fAngle);
             }
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
            _fidUpdate.getFloat() => float fLevel;
            <<< "got UPDATE fid #" + _fid + " (via OSC):" >>>;
            if (_fid < 6) {
                setOscFreq(_fid, 500 * fAngle);
            } else if (_fid == 8) {
                fAngle => fid8.rate;
            } else if (_fid == 9) {
                fAngle => fid9.rate;
            } else if (_fid == 10) {
                fAngle => fid10.rate;
            }
            setOscGain(_fid, fLevel);
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
            if (_fid == 8) {
                "/gitSmurf/fmurf/3rdParties/samples/bank_01/01_sax.wav" => fid8.read;
                0 => fid8.pos;
            } else if (_fid == 9) {
                "/gitSmurf/fmurf/3rdParties/samples/bank_01/01_jungle.wav" => fid9.read;
                0 => fid9.pos;
            } else if (_fid == 10) {
                "/gitSmurf/fmurf/3rdParties/samples/bank_01/02_drums.wav" => fid10.read;
                0 => fid10.pos;
            } 
        }            
    }
}

//
// 
//
fun void bang(OscEvent _fidBang, int _fid) {
    while ( true )
    {
        _fidBang => now;
        while(_fidBang.nextMsg() != 0) 
        {
            _fidBang.getFloat() => float fX;
            _fidBang.getFloat() => float fY;
            _fidBang.getFloat() => float fAngle;
            _fidBang.getFloat() => float fLevel;
            <<< "got BANG fid #" + _fid + " (via OSC):" >>>;
            if (_fid < 6) {
                setOscFreq(_fid, 0.9*500 * fAngle);
            } else if (_fid == 8) {
                0.9 * fAngle => fid8.rate;
            } else if (_fid == 9) {
                0.9 * fAngle => fid9.rate;
            } else if (_fid == 10) {
                0.9 * fAngle => fid10.rate;
            }
            //setOscGain(_fid, 2 * fLevel);
                        
            50::ms => now;

            if (_fid < 6) {
                setOscFreq(_fid, 500 * fAngle);
            } else if (_fid == 8) {
                fAngle => fid8.rate;
            } else if (_fid == 9) {
                fAngle => fid9.rate;
            } else if (_fid == 10) {
                fAngle => fid10.rate;
            }
            //setOscGain(_fid, fLevel);
        }            
    }
}

fun void handleBeat(OscEvent _beat) {

}

// Listeners
spork ~ connAdd(connAddListener);
spork ~ connUpdate(connUpdateListener);
spork ~ connRemove(connRemoveListener);

spork ~ add(fidAdd0, 0);
spork ~ update(fidUpdate0, 0);
spork ~ remove(fidRemove0, 0);
spork ~ bang(fidBang0, 0);
spork ~ computeFlux(0);

spork ~ add(fidAdd1, 1);
spork ~ update(fidUpdate1, 1);
spork ~ remove(fidRemove1, 1);
spork ~ bang(fidBang1, 1);
spork ~ computeFlux(1);

spork ~ add(fidAdd2, 2);
spork ~ update(fidUpdate2, 2);
spork ~ remove(fidRemove2, 2);
spork ~ bang(fidBang2, 2);
spork ~ computeFlux(2);

spork ~ add(fidAdd3, 3);
spork ~ update(fidUpdate3, 3);
spork ~ remove(fidRemove3, 3);
spork ~ bang(fidBang3, 3);
spork ~ computeFlux(3);

spork ~ add(fidAdd4, 4);
spork ~ update(fidUpdate4, 4);
spork ~ remove(fidRemove4, 4);
spork ~ bang(fidBang4, 4);
spork ~ computeFlux(4);

spork ~ add(fidAdd5, 5);
spork ~ update(fidUpdate5, 5);
spork ~ remove(fidRemove5, 5);
spork ~ bang(fidBang5, 5);
spork ~ computeFlux(5);

spork ~ add(fidAdd6, 6);
spork ~ update(fidUpdate6, 6);
spork ~ remove(fidRemove6, 6);
spork ~ bang(fidBang6, 6);
spork ~ computeFlux(6);

spork ~ add(fidAdd7, 7);
spork ~ update(fidUpdate7, 7);
spork ~ remove(fidRemove7, 7);
spork ~ bang(fidBang7, 7);
spork ~ computeFlux(7);

spork ~ add(fidAdd8, 8);
spork ~ update(fidUpdate8, 8);
spork ~ remove(fidRemove8, 8);
spork ~ bang(fidBang8, 8);
spork ~ computeFlux(8);

spork ~ add(fidAdd9, 9);
spork ~ update(fidUpdate9, 9);
spork ~ remove(fidRemove9, 9);
spork ~ bang(fidBang9, 9);
spork ~ computeFlux(9);

spork ~ add(fidAdd8, 10);
spork ~ update(fidUpdate10, 10);
spork ~ remove(fidRemove10, 10);
spork ~ bang(fidBang10, 10);
spork ~ computeFlux(10);

spork ~ handleBeat(beat);

spork ~ bang(dacBang, -440);
spork ~ update(dacUpdate, -440);
spork ~ computeFlux(-440);

while(true) {
    25::ms => now;
}

