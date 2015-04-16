#include "VectorField.h"

VectorField::VectorField(){

}

void VectorField::setup(int _w, int _h, int _d, int _res){
    width = _w;
    height = _h;
    depth = _d;
    res = _res;

    cols = width / res;
    rows = height / res;
    zrows = depth / res;

    for (int z=0; z<zrows; z++){
        vector <vector < vector<ofPoint>>> field;

        for (int x = 0; x < cols ; x++){
            vector <ofPoint> column;
            column.resize(rows);
            table.push_back(column);

            for (int y=0; y< rows; y++){
                table[x][y] = ofPoint(ofRandom(-10,10),ofRandom(-10,10),ofRandom(-10,10));
            }
        }
        field.push_back(table);
    }
}

void VectorField::draw(){
    for (int x=0; x < table.size(); x++){
        for (int y=0; y < table[x].size(); y++){
            ofPushMatrix();
            ofTranslate(x*res, y*res);
            ofLine(ofPoint(0,0),table[x][y]);
            ofPopMatrix();
        }
    }
    //ctor
}

void VectorField::addRepulsionForce(ofPoint _pos, float _rad, float _scale){
    for (int x=0; x < table.size(); x++){
        for (int y=0; y < table[x].size(); y++){
            ofPoint cellPos = ofPoint(x*res, y*res);

            ofPoint diff = cellPos - _pos;
            float dist = diff.length();

            if( dist < _rad ){
                diff *= 1.0 - dist/_rad;
                table[x][y] = diff*_scale;
            }
        }
    }
}

ofPoint VectorField::getForce(ofPoint _pos){
    _pos /= res;

    int x = ofClamp(int(_pos.x),0,cols-1);
    int y = ofClamp(int(_pos.y),0,cols-1);

    return table[x][y];
}

void VectorField::setNoise(){
    for (int x=0; x < table.size(); x++){
        for (int y=0; y < table[x].size(); y++){
                float noise = ofMap(ofNoise(x*0.5,y*0.5),0,1,0,TWO_PI);
                table[x][y]=ofPoint(sin(noise),cos(noise));
                //table[x][y]=ofPoint(ofSignedNoise(float(x)/float(cols)*0.1)*10,ofSignedNoise(float(y)/float(rows)*0.1)*10);
        }
    }
}

VectorField::~VectorField(){
    //dtor
}
