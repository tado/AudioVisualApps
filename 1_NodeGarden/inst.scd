SynthDef("node_fx", {
	var in, out;
	in = In.ar(0, 2);
	5.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.01, 0.1),rrand(0.01, 0.1)],0.05,0.15), 4) });
	//out = (in*0.8).softclip;
	out = in.softclip;
	Out.ar(0, out);
}).store;


SynthDef("node_sine", {
	arg outbus=0, freq=440, pan=0.5, lfoFreq=1.0, amp=0.5;
	var mix, lfo;
	lfo = SinOsc.kr(lfoFreq,0,0.5);
	mix = Pan2.ar(SinOsc.ar(freq,0,amp*lfo),pan);
	Out.ar(0, mix);
}).store;