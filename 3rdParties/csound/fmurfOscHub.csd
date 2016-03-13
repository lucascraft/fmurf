<CsoundSynthesizer>
<CsOptions>
</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 128
nchnls = 2
0dbfs = 1

  gihandle OSCinit 4444

instr 1
kfreq line 100, p3, 1000
aout oscil 0.2, kfreq, 1
outvalue "freqsweep", kfreq
outs aout, aout

    kf1 init 0
    kf2 init 0
nxtmsg:
    kk  OSClisten gihandle, "/smurf/", "ff", kf1, kf2
if (kk == 0) goto ex
    printk 0,kf1
    printk 0,kf2
    kgoto nxtmsg
ex:

endin



</CsInstruments>
<CsScore>
f 1 0 1024 10 1
i 2 0 20
e
</CsScore>


        
</CsoundSynthesizer>
<MacOptions>
Version: 3
Render: Real
Ask: Yes
Functions: ioObject
Listing: Window
WindowBounds: 1130 63 314 341
CurrentView: io
IOViewEdit: On
Options: -b128 -A -s -m167 -R
</MacOptions>
<MacGUI>
ioView background {32125, 41634, 41120}
ioSlider {266, 7} {20, 98} 0.000000 1.000000 0.153061 amp
ioSlider {10, 29} {239, 22} 100.000000 1000.000000 841.841004 freq
ioGraph {8, 112} {265, 116} table 0.000000 1.000000 
ioListing {279, 112} {266, 266}
ioText {293, 44} {41, 24} label 0.000000 0.00100 "" left "Lucida Grande" 8 {0, 0, 0} {65280, 65280, 65280} background noborder Amp:
ioText {333, 44} {70, 24} display 0.000000 0.00100 "amp" left "Lucida Grande" 8 {0, 0, 0} {65280, 65280, 65280} background noborder 0.1837
ioText {66, 57} {41, 24} label 0.000000 0.00100 "" left "Lucida Grande" 8 {0, 0, 0} {65280, 65280, 65280} background noborder Freq:
ioText {106, 57} {69, 24} display 841.841004 0.00100 "freq" left "Lucida Grande" 8 {0, 0, 0} {65280, 65280, 65280} background noborder 841.8410
ioText {425, 6} {120, 100} label 0.000000 0.00100 "" left "Lucida Grande" 8 {0, 0, 0} {65280, 65280, 65280} nobackground border 
ioText {449, 68} {78, 24} display 0.000000 0.00100 "freqsweep" center "DejaVu Sans" 8 {0, 0, 0} {14080, 31232, 29696} background border 999.6769
ioButton {435, 24} {100, 30} event 1.000000 "Button 1" "Sweep" "/" i1 0 10
ioGraph {8, 233} {266, 147} scope 2.000000 -1.000000 
</MacGUI>

<EventPanel name="" tempo="60.00000000" loop="8.00000000" name="" x="360" y="248" width="596" height="322"> 








</EventPanel>