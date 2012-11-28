(
SynthDef("fx", {
	arg lpf=440, rq=0.5, amp=0.8;
	var in, out;
	in = In.ar(3, 2);
	//in = RLPF.ar(in, lpf, rq).clip2 * 0.5;
	32.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.06), 4.0) });
	out = CompanderD.ar(in) * amp;
	Out.ar(0, out);
}).store;

SynthDef("mySaw", {
	arg fadeTime = 30, n = 0, rq = 0.3, detune = 0.001, base = 20, ratio = 1.5, harm = 1.5, amp = 0.2, gate=0;
	var lfo, env, out;
	env = EnvGen.kr(Env.new([0,1], [fadeTime], 'sine'));
	lfo = SinOsc.ar(rrand(0.03, 0.05), 0, 100, 600);
	out = Saw.ar([base+detune.rand, base+detune.rand] * (ratio ** n)) * amp
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand] * (ratio ** n)) * amp;
	out = out * env;
	out = RLPF.ar(out, lfo * (1.5 ** n), rq).clip2 * 0.5;
	out = out * EnvGen.kr(Env.adsr(releaseTime:10), gate, doneAction: 2);
	Out.ar(3, out);
}).store;
)

a = Synth("fx");
b = Synth("mySaw",["n", 0, "gate", 1]);


(
SynthDef(\sawbass, {
	arg detune=1.0, base=20, lpf=20, rq=1.0, amp=0.7;
	var harm, ratio, s1, s2, s3, s4, s5, s6, s7, s8, out;
	ratio = 1.5;
	harm = 1.5;

	s1 = Saw.ar([base+detune.rand, base+detune.rand])*amp
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand])*amp;
	s2 = Saw.ar([base+detune.rand, base+detune.rand]*ratio)*amp
	+Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*ratio)*amp;
	s3 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**2))*amp
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**2))*amp;
	s4 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**3))*amp
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**3))*amp;
	s5 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**4))*amp
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**4))*amp;
	s6 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**5))*amp
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**5))*amp;

	out = s1+s2+s3+s4+s5+s6;
	out = RLPF.ar(out, lpf, rq).clip2 * 0.5;

	24.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.02,0.05), 2.0) });

	//out = out * Decay2.ar(pul, 0.01, 0.3);
	//out = out * EnvGen.kr(Env.new([0,1], [30], 'sine'));
	//out = GVerb.ar(out);
	Out.ar(0, CompanderD.ar(out.clip2));

}).store;
)

a = Synth("sawbass", ["lpf", 12000, "rq", 0.1, "amp", 0.2, "detune", 0.1]);
a.free;