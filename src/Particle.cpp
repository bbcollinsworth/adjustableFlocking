
//
//  Particle.cpp
//  myFlocking
//
//  Thanks to Regina Flores for basic flocking code.
//
//

#include "Particle.h"
//#include "Tail.h"


Particle::Particle(){

    radius = 5; //ofRandomuf()*5;

}

void Particle::init(){

    //defining the position and velocity of the particles

    pos = ofPoint(ofRandomWidth(),ofRandomHeight());
    vel = ofPoint(ofRandomf(), ofRandomf());


    //IF 3-D, DO THIS, BECAUSE
     //using easy cam changes (0,0) to middle of screen
    //pos = ofPoint(ofRandom(-ofGetWidth()/2, ofGetWidth()/2),ofRandom(-ofGetHeight()/2, ofGetHeight()/2));


}

ofPoint Particle::infiniteWalls(ofPoint _pos){
    if( _pos.x < 0.0 ){
        _pos.x = ofGetWidth()-1;

    }

    if( _pos.x > ofGetWidth()){
        _pos.x = 1;

    }

    if( _pos.y < 0){
        _pos.y = ofGetHeight()-1;

    }

    if( _pos.y > ofGetHeight()){
        _pos.y = 1;

    }
    return _pos;
}

void Particle::bounding(){

    //keeping the particles inside the screen
    //note: if 3d, the new screen width is (-w/2,w/2), same for height
    if(pos.y > ofGetHeight()){
        vel = -vel;
    }
    if(pos.y < 0){
        vel = -vel;
    }

    if(pos.x > ofGetWidth()){
        vel = -vel;
    }
    if(pos.x < 0){
        vel = -vel;
    }

}

//NOTE: Flocking Rules
// each particle compares his state (i.e position and vel) to others to change velocity
//we pass the vector of particles into the update function
//http://www.kfish.org/boids/pseudocode.html

ofPoint Particle::cohesion(vector<Particle> &particles, float _cValue){

    //RULE 1
    //finding the center of mass of the system
    ofPoint centerMass;
    for(int i = 0; i < particles.size(); i++){
        //determining if the particle in the loop is itself
        //to avoid itself
        if (&particles[i] == this) {
            continue;
        }

        centerMass += particles[i].pos;

    }

    centerMass = centerMass/(particles.size()-1);

    //APPLYING INFINITEWALLS TO CENTER MASS TURNS OUT A LOT LIKE BOUNDING, BUT LESS COOL LOOKING
    //centerMass = infiniteWalls(centerMass);

    ofPoint cohesion_velocity;
    cohesion_velocity = (centerMass-pos)/_cValue; // was 100.0f
    return cohesion_velocity;
}

ofPoint Particle::separation(vector<Particle> &particles, float _sValue){
    //RULE 2
    //particles keep a small distance from each other

    ofPoint displace;
    for(int i = 0; i < particles.size(); i++){
        //determining if the particle in the loop is itself
        //to avoid itself
        if (&particles[i] == this) {
            continue;
        }

        // distance between me and particles[i]
        float dist = pow(particles[i].pos.x - pos.x, 2) + pow(particles[i].pos.y - pos.y, 2);// + pow(particles[i].pos.z - pos.z, 2);
        dist = sqrt(dist);

        if (dist < _sValue){   //+sin(ofGetFrameNum()*0.1)*ofRandom(8,10)) {
            displace  = displace - (particles[i].pos - pos);
        }

    }

    ofPoint separation_velocity;
    separation_velocity = displace;
    return separation_velocity;
}

ofPoint Particle::allignment(vector<Particle> &particles, float _aValue){

    //RULE 3
    //match velocity

    ofPoint aveVel;
    for(int i = 0; i < particles.size(); i++){
        //determining if the particle in the loop is itself
        //to avoid itself
        if (&particles[i] == this) {
            continue;
        }

        aveVel += particles[i].vel;

    }

    aveVel = aveVel/(particles.size()-1);

    ofPoint allignment_velocity;
    //allignment_velocity = (aveVel - vel)/8.0f;
    allignment_velocity = (aveVel - vel)/_aValue;
    return allignment_velocity;

}

void Particle:: update( vector<Particle> &particles, float cValue, float sValue, float aValue){
    //& pointer notation (ref of the array)

    ofPoint v1 = cohesion(particles,cValue);
    ofPoint v2 = separation(particles,sValue);
    ofPoint v3 = allignment(particles,aValue);

    vel = vel + v1 + v2 + v3;
    pos = pos + vel;


}


void Particle::draw(){

    int rad = radius*2;

    for (int j = 0; j < rad; j++){
    ofSetColor(255-(j*20),255-(j*20),255/(rad-j),50);
    ofCircle(pos.x, pos.y, (rad-j)*(rad-j)*0.1); //pos.z, radius);
    }

}

