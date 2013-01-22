SynthDef("particleFx", {
	var in, out;
	in = In.ar(0, 2);
	2.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.01, 0.1),rrand(0.01, 0.1)],0.05,0.15), 1) });
	//out = (in*0.8).softclip;
	//out = (in*0.1).softclip;
	out = in;
	Out.ar(0, out.softclip);
}).store;

SynthDef("particle", {
	arg amp=0.02, pan = 0.0, freq=440, detune=2.0, decay=0.1;
	var env, out;
	out = Pan2.ar(SinOsc.ar(freq), pan);
	env = EnvGen.kr(Env.perc(0.01,decay,1,-4), doneAction: 2);
	out = out * env * amp;
	Out.ar(0, out);
}).store;
