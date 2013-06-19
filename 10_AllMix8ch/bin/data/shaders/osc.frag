#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform float oscFreq[64];
uniform vec2 mouse;
uniform vec2 resolution;
uniform float num;
#define PI 3.14159
#define TWO_PI (PI*2.0)

void main( void ) {
    float res = resolution.x / 100.0;
    vec2 position = ( gl_FragCoord.xy) * res;// * resolution;
    float r = 0.0, g = 0.0, b = 0.0;
    for(float i = 0.0; i < num; i++) {
        //float a = i * (TWO_PI/num) *(time+200.0)*0.02;
        //float a = i * (time-20000.0)*0.04 + (num - 1.0) * 0.001;       
        float a = i * (time) * 0.04;
        float fres = oscFreq[int(i)];
        r+= cos( ((position.x-resolution.x*res/2.0) * cos(a/res) + (position.y-resolution.y*res/2.0) * sin(a/res) + time)/fres/fres);
        g+= cos( ((position.x-resolution.x*res/2.0) * cos(a*1.001/res) + (position.y-resolution.y*res/2.0) * sin(a*1.01/res) + time)/fres/fres);
        b+= cos( ((position.x-resolution.x*res/2.0) * cos(a*1.002/res) + (position.y-resolution.y*res/2.0) * sin(a*1.02/res) + time)/fres/fres);
        
    }
    float d = 0.2;
    r/= num*d;
    g/= num*d;
    b/= num*d;
    gl_FragColor = vec4( vec3( r, g, b), 1.0 );
}
