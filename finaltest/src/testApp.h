


#include "ofMain.h"

//Particle class
class Particle {
public:
    Particle();
    void setup();
    void update( float dt );
    void draw();
    
    ofPoint pos;
    ofPoint vel;
    float time;
    float lifeTime;
    bool live;
};


class Params {
public:
    void setup();
    ofPoint eCenter;
    float eRad;
    float velRad;
    float lifeTime;
    
    float rotate;
    
    float force;
    float spinning;
    float friction;
};

extern Params params; 


//------------ GUI --------------
//Slider class
class Slider {
public:
    string title;        //Title
    ofRectangle rect;    //Rectangle for drawing
    float *value;       //Pointer to value which the slider changes
    float minV, maxV;   //Minimum and maximum values
};

//Interface class, which manages sliders
class Interface {
public:
    void setup();
    void addSlider( string title, float *value, float minV, float maxV );
    void draw();
    
    void save( int index );        //Save preset
    void load( int index );        //Load preset
    
    void mousePressed( int x, int y );
    void mouseDragged( int x, int y );
    void mouseReleased (int x, int y );
    
    vector<Slider> slider;    //Array of sliders
    int selected;            //Index of selected slider
};
//-------------------------------

//openFrameworks' class
class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    vector<Particle> p;
    ofFbo fbo;          
    
    float history;
    float time0;
    
    float bornRate;
    float bornCount;
    
    
    Interface interf;
    bool drawInterface;
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};

