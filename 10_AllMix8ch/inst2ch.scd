(
SynthDef("col_fx", {
	var in, out;
	in = In.ar(3, 2);
	//8.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.01, 0.1),rrand(0.01, 0.1)], 0.04, 0.08), 1.0) });
	in = GVerb.ar(in, 100, 1, drylevel:0.5);
	out = (in*0.75).softclip;
	Out.ar(0, out);
}).store;

SynthDef("col_sine", {
	arg outbus=0, freq=440, pan=0.0, lfoFreq=1.0, amp=0.5, gate=0;
	var mix, env, lfo;
	lfo = SinOsc.kr(lfoFreq,0,0.5);
	env = EnvGen.kr(Env.new([0,1], [10], 'sine'));
	mix = SinOsc.ar(freq,0,amp*lfo) * env;
	mix = Pan2.ar(SinOsc.ar(freq,0,amp*lfo),pan) * env;
	mix = mix * EnvGen.kr(Env.adsr(releaseTime:10), gate, doneAction: 2);
	Out.ar(0, mix);
	Out.ar(3, mix);
}).store;

SynthDef("col_saw", {
	arg amp=0.02, pan = 0.0, freq=50, detune=2.0, decay=0.1;
	var env, out;
	out = Pan2.ar(Saw.ar(freq)+Saw.ar(freq*1.002), pan);
	env = EnvGen.kr(Env.perc(0.001,decay,1,-4), doneAction: 2);
	out = out * env * amp;
	Out.ar(0, out);
	Out.ar(3, out);
}).store;

SynthDef("col_harmony", {
	arg lpf=1200, rq=1.2,atk=0.001,rel=2.0, modSpeed=8.4,modMix=1.0,fx=0.3, gain=1.0 ,amp = 1.0, gate=1;
	var rfreq, ratio, n, d, p, q, mode, z, w, pul, mod,out;
	n = 64;
	ratio = 1.5;
	pul = Impulse.ar(modSpeed);
	p = FloatArray.new(3*n);
	q = FloatArray.new(3*n);
	//d = 3.0;
	d = 2.0;
	mode = [0, 5, 7, 9];
	n.do({ arg i; var freq;
		freq = (mode.choose).midicps * (ratio ** (i%20));
		p.add(freq);
		p.add(freq + d.rand2);
		p.add(freq + d.rand2);
		});
	n.do({ arg i;
		var freq;
		freq = p.at(3*i);
		q.add(freq + d.rand2);
		q.add(freq + d.rand2);
		q.add(freq + d.rand2);
		});
	z = [`[p, nil, FloatArray.rand(3*n, 0, 2pi)],	`[q, nil, FloatArray.rand(3*n, 0, 2pi)]];
	out = Klang.ar(z, 1, 0)*(1.0/n);
	rfreq = Latch.kr(WhiteNoise.ar(500, 500), pul);
	out = RLPF.ar(out,
				//lpf * (Latch.ar(BrownNoise.ar, Impulse.ar(modSpeed)) * 0.5 + 1.0) + 20 ,
				//lpf + Latch.ar(BrownNoise.ar(90,100), Impulse.ar(modSpeed)),
				lpf * Latch.ar(1.0 + BrownNoise.ar(0.5, 0.6), Impulse.ar(modSpeed)),
				Latch.ar(BrownNoise.ar(1.2, 1.3), Impulse.ar(modSpeed)));
	//out = RLPF.ar(out, lpf, rq);
	out = (out*gain).clip2*amp;
	w = out;
	mod = out * Decay2.ar(pul, atk, rel);
	out = (mod * modMix) + (out * (1-modMix));
	2.do({ w = AllpassL.ar(w, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.15), 2) });
	out = (out * (fx - 1.0)) + (w * fx) * EnvGen.kr(Env.new([0,1], [30], 'sine'));
	out = out * EnvGen.kr(Env.adsr(releaseTime:10), gate, doneAction: 2);
	//out = PanAz.ar(8, out.at(0), LFSaw.kr(1.0)) + PanAz.ar(8, out.at(1), LFSaw.kr(1.5)) ;
	Out.ar(0, out);
	Out.ar(3, out);
}).store;

SynthDef("col_sawbass", {
	arg base=20, lpf=20, rq=0.4, amp=0.7;
	var detune, harm, ratio, s1, s2, s3, s4, s5, s6, s7, s8, w, mod, pul, out;
	ratio = 2;
	harm = 1.5;
	detune = 0.1;
	pul = Impulse.ar(12.0);

	s1 = Saw.ar([base+detune.rand, base+detune.rand])*amp
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand])*amp;
	s2 = Saw.ar([base+detune.rand, base+detune.rand]*ratio)*(amp/2.0)
	+Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*ratio)*(amp/2.0);
	s3 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**2))*(amp/4.0)
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**2))*(amp/4.0);
	s4 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**3))*amp/8.0
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**3))*amp/8.0;
	s5 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**4))*amp/16.0
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**4))*amp/16.0;
	s6 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**5))*amp/16
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**5))*amp/16;

	out = RLPF.ar(s1+s2+s3+s4+s5+s6, lpf, rq);
	2.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.03,0.2), 2) });
	//out = PanAz.ar(8, out.at(0), LFSaw.kr(5.0)) + PanAz.ar(8, out.at(1), LFSaw.kr(6.0));
	out = out * Decay2.ar(pul, 0.01, 0.3);
	out = out * EnvGen.kr(Env.new([0,1], [30], 'sine'));
	Out.ar(0, out.softclip);

}).store;

SynthDef("col_closesaw", {
	arg fadeTime = 30, n = 0, rq = 0.3, detune = 0.001, base = 20, ratio = 1.5, harm = 1.5, amp = 0.4, gate=0;
	var lfo, env, out;
	env = EnvGen.kr(Env.new([0,1], [fadeTime], 'sine'));
	lfo = SinOsc.ar(rrand(0.03, 0.05), 0, 100, 600);
	out = Saw.ar([base+detune.rand, base+detune.rand] * (ratio ** n)) * amp
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand] * (ratio ** n)) * amp;
	out = out * env;
	out = RLPF.ar(out, lfo * (1.5 ** n), rq).clip2 * 0.5;
	out = out * EnvGen.kr(Env.adsr(releaseTime:10), gate, doneAction: 2);
	Out.ar(5, out);
}).store;


SynthDef("col_closefx", {
	/*
	arg lpf=440, rq=0.5, amp=0.8;
	var in, out;
	in = In.ar(5, 2);
	//24.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr(rrand(0.0, 0.1).dup(8),0.01,0.06), 4.0) });
	24.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr(rrand(0.0, 0.1).dup(2),0.01,0.06), 4.0) });
	out = CompanderD.ar(in) * amp;
	Out.ar(0, out);
	*/
	arg lpf=440, rq=0.5, amp=1.0;
	var in, out;
	in = In.ar(5, 2);
	16.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.005,0.03), 4.0) });
	out = CompanderD.ar(in) * amp;
	Out.ar(0, out);
}).store;
)

//---------------------------------------------------
