SynthDef("fall_fx", {
var in, wet, out;
	in = In.ar(0, 2);
	wet = in;
	4.do({ wet = AllpassL.ar(wet, 0.1, LFNoise2.kr([rrand(0.01, 0.1),rrand(0.01, 0.1)], 0.04, 0.08), 4.0) });
	out = ((in * 0.8) + (wet * 0.2)).softclip;
	Out.ar(0, out);
}).store;


SynthDef("fall_perc", {
	arg amp=0.02, pan = 0.0, freq=440, detune=2.0, decay=0.1;
	var env, out;
	out = Pan2.ar(SinOsc.ar(freq), pan);
	env = EnvGen.kr(Env.perc(0.001,decay,1,-4), doneAction: 2);
	out = out * env * amp;
	Out.ar(0, out);
}).store;
