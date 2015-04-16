#ifndef VECTORFIELD_H
#define VECTORFIELD_H

#include "ofMain.h"

class VectorField
{
    public:
        VectorField();
        virtual ~VectorField();

        void setup(int _w, int _h, int _d, int _res);

        int width, height, res;
        int cols, rows;

        ofPoint getForce(ofPoint _pos);
        void setNoise();
        void addRepulsionForce(ofPoint _pos, float _rad, float _scale);

        void draw();
        vector < vector<ofPoint> > table;


    protected:
    private:
};

#endif // VECTORFIELD_H
