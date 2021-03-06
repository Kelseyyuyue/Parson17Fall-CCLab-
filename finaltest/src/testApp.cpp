#include "testApp.h"



//----------------------  Params -------------------------------

Params param;

void Params::setup() {
    eCenter = ofPoint( ofGetWidth() / 2, ofGetHeight() / 2 );
    eRad = 100;
    velRad = 0;
    lifeTime = 2.0;
    
    rotate = 0;
    force = 1000;
    spinning = 1000;
    friction = 0.05;
}


//----------------------  Particle  ----------------------------

Particle::Particle() {
    live = false;
}


ofPoint randomPointInCircle( float maxRad ){
    ofPoint pnt;
    float rad = ofRandom( 0, maxRad );
    float angle = ofRandom( 0, M_TWO_PI );
    pnt.x = cos( angle ) * rad;
    pnt.y = sin( angle ) * rad;
    return pnt;
}


void Particle::setup() {
    pos = param.eCenter + randomPointInCircle( param.eRad );
    vel = randomPointInCircle( param.velRad );
    time = 0;
    lifeTime = param.lifeTime;
    live = true;
}


void Particle::update( float dt ){
    if ( live ) {
        
        vel.rotate( 0, 0, param.rotate * dt );
        
        ofPoint acc;
        ofPoint delta = pos - param.eCenter;
        float len = delta.length();
        if ( ofInRange( len, 0, param.eRad ) ) {
            delta.normalize();
            
           
            acc += delta * param.force;
            
            
            acc.x += -delta.y * param.spinning;
            acc.y += delta.x * param.spinning;
        }
        vel += acc * dt;
        vel *= (1-param.friction);
        
       
        pos += vel * dt;
        
        
        time += dt;
        if ( time >= lifeTime ) {
            live = false;
        }
    }
}

//--------------------------------------------------------------
void Particle::draw(){
    if ( live ) {
        
        float size = ofMap(
                           fabs(time - lifeTime/2), 0, lifeTime/2, 3, 1 );
        

        ofColor color = ofColor::red;
        float hue = ofMap( time, 0, lifeTime, 128, 255 );
        color.setHue( hue );
        ofSetColor( color );
        
        ofCircle( pos, size );
    }
}


//----------------------  testApp  -----------------------------

void testApp::setup(){
    ofSetFrameRate( 60 );
    
    
    int w = ofGetWidth();
    int h = ofGetHeight();
    fbo.allocate( w, h, GL_RGB32F_ARB );
    
    
    fbo.begin();
    ofBackground(255, 255, 255);
    fbo.end();
    
    
    param.setup();
    history = 0.9;
    bornRate = 1500;
    
    bornCount = 0;
    time0 = ofGetElapsedTimef();
    
   
    interf.setup();
    interf.addSlider( "eRad", &param.eRad, 0, 800 );
   
 

    
    drawInterface = true;
}

//--------------------------------------------------------------
void testApp::update(){

    float time = ofGetElapsedTimef();
    float dt = ofClamp( time - time0, 0, 0.1 );
    time0 = time;
    

    int i=0;
    while (i < p.size()) {
        if ( !p[i].live ) {
            p.erase( p.begin() + i );
        }
        else {
            i++;
        }
    }
    
    
    bornCount += dt * bornRate;
    if ( bornCount >= 1 ) {
        int bornN = int( bornCount );
        bornCount -= bornN;
        for (int i=0; i<bornN; i++) {
            Particle newP;
            newP.setup();
            p.push_back( newP );
        }
    }
    

    for (int i=0; i<p.size(); i++) {
        p[i].update( dt );
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground( 255, 255, 255 );
   
    fbo.begin();
    
   
    ofEnableAlphaBlending();
    
    float alpha = (1-history) * 255;
    ofSetColor( 255, 255, 255, alpha );
    ofFill();
    ofRect( 0, 0, ofGetWidth(), ofGetHeight() );
    
    ofDisableAlphaBlending();
    
  
    ofFill();
    for (int i=0; i<p.size(); i++) {
        p[i].draw();
    }
    
    fbo.end();
    
    
    ofSetColor( mouseX/3, mouseY, 200 );
    fbo.draw( 0, 0 );
    
    
    if ( drawInterface ) {
       
        ofSetColor( 0, 0, 0 );
      
     
        
       
        interf.draw();
        
       
        ofSetCircleResolution( 2 );
        ofNoFill();
        ofSetColor( 128, 128, 128 );
        ofCircle( param.eCenter, param.eRad );
        ofSetCircleResolution( 5 );
    }
}


//----------------------  GUI ----------------------------------

void Interface::setup(){
    selected = -1;
}

void Interface::addSlider( string title, float *value, float minV, float maxV ){
    Slider s;
    s.title = title;
    s.rect = ofRectangle( 20, 60 + slider.size() * 40, 150, 30 );
    s.value = value;
    s.minV = minV;
    s.maxV = maxV;
    slider.push_back( s );
}

void Interface::draw(){
    for (int i=0; i<slider.size(); i++) {
        Slider &s = slider[i];
        ofRectangle r = s.rect;
        ofFill();
        ofSetColor( 255, 255, 255 );
        ofRect( r );
        ofSetColor( 0, 0, 0 );
        ofNoFill();
        ofRect( r );
        ofFill();
        float w = ofMap( *s.value, s.minV, s.maxV, 0, r.width );
        ofRect( r.x, r.y + 15, w, r.height - 15 );
        ofDrawBitmapString( s.title + " " + ofToString( *s.value, 2 ), r.x + 5, r.y + 12 );
    }
}

void Interface::mousePressed( int x, int y ){
    for (int i=0; i<slider.size(); i++) {
        Slider &s = slider[i];
        ofRectangle r = s.rect;
        if ( ofInRange( x, r.x, r.x + r.width ) && ofInRange( y, r.y, r.y + r.height ) ) {
            selected = i;
            *s.value = ofMap( x, r.x, r.x + r.width, s.minV, s.maxV, true );
        }
    }
}

void Interface::mouseDragged( int x, int y ){
    if ( selected >= 0 ) {
        Slider &s = slider[selected];
        ofRectangle r = s.rect;
        *s.value = ofMap( x, r.x, r.x + r.width, s.minV, s.maxV, true );
    }
}

void Interface::mouseReleased (int x, int y ){
    selected = -1;
}


void Interface::save( int index )
{
    vector<string> list;
    for (int i=0; i<slider.size(); i++) {
        list.push_back( ofToString( *slider[i].value ) );
    }
    string text = ofJoinString( list," " );
    string fileName = "preset" + ofToString( index ) + ".txt";
    ofBuffer buffer = ofBuffer( text );
    ofBufferToFile( fileName, buffer );
}

//--------------------------------------------------------------
void Interface::load( int index )
{
    string fileName = "preset" + ofToString( index ) + ".txt";
    string text = string( ofBufferFromFile( fileName ) );
    vector<string> list = ofSplitString( text, " " );
    
    if ( list.size() == slider.size() ) {
        for (int i=0; i<slider.size(); i++) {
            *slider[i].value = ofToFloat( list[i] );
        }
    }
}


//----------------------  testApp again  -----------------------

void testApp::keyPressed(int key){
    if ( key == OF_KEY_RETURN ) {
        drawInterface = !drawInterface;
    }
    
    if ( key == ' ' ) {
        ofImage image;
        image.grabScreen( 0, 0, ofGetWidth(), ofGetHeight() );
        
        
        int n = ofRandom( 0, 1000 );
        string fileName = "screen" + ofToString( n ) + ".png";
        
        image.saveImage( fileName );
    }
    
   
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if ( drawInterface ) {
        interf.mouseDragged( x, y );
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if ( drawInterface ) {
        interf.mousePressed( x, y );
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    interf.mouseReleased( x, y );
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}


