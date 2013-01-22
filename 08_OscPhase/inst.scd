(
SynthDef("col_sine", {
	arg outbus=0, freq=440, pan=0.0, lfoFreq=1.0, amp=0.5, gate=0;
	var mix, env, lfo;
	lfo = SinOsc.kr(lfoFreq,0,0.5);
	env = EnvGen.kr(Env.new([0,1], [10], 'sine'));
	mix = Pan2.ar(SinOsc.ar(freq,0,amp*lfo),pan) * env;
	mix = mix * EnvGen.kr(Env.adsr(releaseTime:10), gate, doneAction: 2);
	Out.ar(3, mix);
}).store;

SynthDef("col_saw", {
	arg amp=0.02, pan = 0.0, freq=50, detune=2.0, decay=0.1;
	var env, out;
	out = Pan2.ar(Saw.ar(freq)+Saw.ar(freq*1.002), pan);
	env = EnvGen.kr(Env.perc(0.001,decay,1,-4), doneAction: 2);
	out = out * env * amp;
	Out.ar(3, out);
}).store;

SynthDef("col_fx", {
	var in, out;
	in = In.ar(3, 2);
	4.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.01, 0.1),rrand(0.01, 0.1)], 0.04, 0.08), 4.0) });
	out = (in*0.8).softclip;
	Out.ar(0, out);
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
	z = [`[p, nil, FloatArray.rand(3*n, 0, 2pi)],
		`[q, nil, FloatArray.rand(3*n, 0, 2pi)]];	
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
	Out.ar(0, out);
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
	out = out * Decay2.ar(pul, 0.01, 0.3);
	out = out * EnvGen.kr(Env.new([0,1], [30], 'sine'));
	Out.ar(0, out.softclip);

}).store;

)

//---------------------------------------------------
a = Synth("harmony");		
a.free;

a = Synth("sawbass");
a.free;























SynthDef(\gfx, {
	var in, out;
	in = In.ar(0, 2);
	in = GVerb.ar(in, 1);
	out = (in*0.8).softclip;
	Out.ar(0, out);
}).store;


SynthDef(\reverb, {
	arg wet=0.1;
	var in, fx;
	in = In.ar(0, 2);
	fx = in;
	12.do({ fx = AllpassN.ar(fx, 0.05, [0.05.rand, 0.05.rand], 2); });
	//fx = GVerb.ar(fx, 10, 3);
	fx = fx*wet + in*(1.0-wet);
	ReplaceOut.ar(0, (fx * 0.8).softclip);
}).store;




80.do({ arg i;

  n = rrand(1, 24);
  SynthDef(
    "glitch" ++ i.asString, 
    {
	    arg dur = 0.1, amp = 0.1;
	    var out, mix;
		out = RLPF.ar(
			Pan2.ar(
			Klang.ar(`[ Array.exprand(n, 50.0, 4000.0), 
				Array.exprand(n, 1.0, 4.0), nil ], 1, 0), rrand(-0.5, 0.5))
				//,
Ê Ê Ê Ê Ê Ê Ê 	//* EnvGen.kr(Env.sine(0.8), 1, 1.0, doneAction: 2),
				* EnvGen.kr(Env.linen(0.001, dur, 0.01), 1, exprand(0.1,1.0), doneAction: 2),
			exprand(50, 20000), 1.0
		).ring1(
			SinOsc.ar(exprand(1, 100), [0,0.5pi])
		) * amp;
		Out.ar(0, out);
		
Ê Ê Ê Ê }).store
});

a = Synth("reverb");
b = Synth("glitch" ++ 20.rand.asString);
b.free;

c = Synth("harmonize");
c.free;

(// glitch testcode
var s;
s = Server.local;
Task({
  var dur=0.1, inst = \glitch0, amp = 0.05;
  inf.do({	// do forever
  	// 30% chance of picking new synth
    if (0.9.coin, { 
      inst = "glitch" ++ 20.rand.asString;
      amp = exprand(0.3,1.0);
    });
    // allocate new synth on server
    s.sendBundle(0.2, [ 
      \s_new, inst, -1, 0, 0, 
      \amp, amp,
      \dur, dur,
      \rate, exprand(0.5,2)
    ]);
    if (dur.coin, { 
  	  dur = rrand(0.2, 0.5);
    });
    dur.wait;
  }); // inf.do
}).play(TempoClock.default);
)



SynthDef(\midi_sine, {
	arg outbus=0, freq=20, pan=0.0, lfoFreq=1.0, amp=0.5;
	var mix, lfo;
	lfo = SinOsc.kr(lfoFreq,0,0.5);
	mix = Pan2.ar(SinOsc.ar(freq.midicps , 0, amp*lfo),pan);
	Out.ar(0, mix);
}).store;


SynthDef(\perc, {
	arg amp=0.02, pan = 0.0, freq=440, detune=2.0, decay=0.1;
	var env, out;
	out = Pan2.ar(SinOsc.ar(freq), pan);
	env = EnvGen.kr(Env.perc(0.001,decay,1,-4), doneAction: 2);
	out = out * env * amp;
	Out.ar(0, out);
}).store;


SynthDef(\harmonize, {
	arg ring = 1000, comb = 0.1;
	var in, out;
	in = (In.ar(0, 2)*2).clip2.ring1(
			SinOsc.ar(ring, [0,0.5pi])
		); 
	out = CombL.ar(
		in,
		0.5, 
		comb, // mouse y controls delay time
		4,
		1,
		in
	) + In.ar(0, 2);
	ReplaceOut.ar(0, out);
}).store;


p = Impulse.ar(8.0);
a = Latch.kr(WhiteNoise.kr(1.5, 3.0), p);
a.postln;
