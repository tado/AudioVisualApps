(

SynthDef(\simple_sine, {
	arg outbus=0, freq=440, pan=0.5, lfoFreq=1.0, amp=0.5;
	var mix, lfo;
	lfo = SinOsc.kr(lfoFreq,0,0.5);
	mix = Pan2.ar(SinOsc.ar(freq,0,amp*lfo),pan);
	Out.ar(0, mix);
}).store;


SynthDef(\fx, {
	var in, out;
	in = In.ar(0, 2);
	5.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.01, 0.1),rrand(0.01, 0.1)],0.05,0.15), 4) });
	//out = (in*0.8).softclip;
	out = (in*0.1).softclip;
	Out.ar(0, out);
}).store;

SynthDef(\gfx, {
	var in, out;
	in = In.ar(0, 2);
	in = GVerb.ar(in, 9);
	out = (in*0.8).softclip;
	Out.ar(0, out);
}).store;


SynthDef("reverb", {
	arg wet=1.0;
	var in, fx;
	in = In.ar(0, 2);
	fx = in;
	//12.do({ fx = AllpassN.ar(fx, 0.05, [0.05.rand, 0.05.rand], 2); });
	fx = GVerb.ar(fx, 100);
	//fx = fx*wet + in*(1.0-wet);
	ReplaceOut.ar(0, fx.softclip);
}).store;

SynthDef("perc", {
	arg amp=0.02, pan = 0.0, freq=440, detune=2.0, decay=0.1;
	var env, out;
	out = Pan2.ar(SinOsc.ar(freq), pan);
	env = EnvGen.kr(Env.perc(0.001,decay,1,-4), doneAction: 2);
	out = out * env * amp;
	Out.ar(0, out);
}).store;


SynthDef("mySaw", {
	arg amp=0.02, pan = 0.0, freq=50, detune=2.0, decay=0.1;
	var env, out;
	out = Pan2.ar(Saw.ar(freq)+Saw.ar(freq*1.002), pan);
	env = EnvGen.kr(Env.perc(0.001,decay,1,-4), doneAction: 2);
	out = out * env * amp;
	Out.ar(0, out);
}).store;

)