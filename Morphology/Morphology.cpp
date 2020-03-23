//Monika Wielgus
#include <iostream>
#include <queue>
#include "Morphology.h"

using namespace std;

class BitmapExt:public Bitmap{
public:
    unsigned int rangeX;
    unsigned int rangeY;
    unsigned int rangeZ;
    bool ***morphology;

    BitmapExt(unsigned int x, unsigned int y, unsigned int z){
        rangeX=x;
        rangeY=y;
        rangeZ=z;
        morphology=new bool**[x];
        for (unsigned int i=0; i<x; i++){
            morphology[i]= new bool*[y];
            for (unsigned int j=0; j<y; j++){
                morphology[i][j] = new bool[z];
            }
        }

        for(unsigned int i=0; i<rangeX; i++)
            for(unsigned int j=0; j<rangeY; j++)
                for(unsigned int k=0; k<rangeZ; k++)
                    morphology[i][j][k]=false;
    }

    BitmapExt(const BitmapExt &map): rangeX(map.rangeX), rangeY(map.rangeY), rangeZ(map.rangeZ){
        this->morphology=new bool**[map.rangeX];
        for(unsigned int i=0; i<map.rangeX; i++){
            this->morphology[i]=new bool*[map.rangeY];
            for(unsigned int j=0; j<map.rangeY; j++){
                this->morphology[i][j] = new bool[map.rangeZ];
            }
        }
        for(unsigned int i=0; i<map.rangeX; i++)
            for(unsigned int j=0; j<map.rangeY; j++)
                for(unsigned int k=0; k<map.rangeZ; k++)
                    this->morphology[i][j][k]=map.morphology[i][j][k];
    }

    ~BitmapExt(){
        for(unsigned int i=0; i!=rangeX; i++){
            for(unsigned int j=0; j!=rangeY; j++){
                delete []morphology[i][j];
            }
            delete []morphology[i];
        }
        delete []morphology;
    }

    unsigned int sx() const{
        return rangeX;
    }

    unsigned int sy() const{
        return rangeY;
    }

    unsigned int sz() const{
        return rangeZ;
    }

    bool operator()(unsigned int x, unsigned int y, unsigned int z) const{
        return morphology[x][y][z];
    }

    bool& operator()(unsigned int x, unsigned int y, unsigned int z){
        return morphology[x][y][z];
    }

    BitmapExt& operator=(const BitmapExt &map){
        bool ***array=new bool**[map.rangeX];
        for(unsigned int i=0; i<map.rangeX; i++){
            array[i]=new bool*[map.rangeY];
            for(unsigned int j=0; j<map.rangeY; j++){
                array[i][j] = new bool[map.rangeZ];
            }
        }
        for(unsigned int i=0; i<map.rangeX; i++)
            for(unsigned int j=0; j<map.rangeY; j++)
                for(unsigned int k=0; k<map.rangeZ; k++)
                    array[i][j][k]=map.morphology[i][j][k];

        for(unsigned int i=0; i<rangeX; i++){
            for(unsigned int j=0; j<rangeY; j++){
                delete []morphology[i][j];
            }
            delete []morphology[i];
        }

        delete []morphology;


        this->rangeX=map.rangeX;
        this->rangeY=map.rangeY;
        this->rangeZ=map.rangeZ;

        this->morphology=array;

        return *this;
    }
};

ostream& operator<<(ostream& out, const Bitmap& map){
    out << "{\n";
    for(unsigned int x=0; x<map.sx(); x++){
        out << " {\n";
        for(unsigned int y=0; y<map.sy(); y++){
            out << "  {";
            for(unsigned int z=0; z<map.sz()-1; z++){
                out << map(x,y,z) << ",";
            }
            out << map(x,y,map.sz()-1);
            if(y<map.sy()-1) out << "},\n";
            else out << "}\n";
        }
        if(x<map.sx()-1) out << " },\n";
        else out << " }\n";
    }
    out << "}";
    return out;
}

class Inversion: public Transformation{
    public:
    void transform(Bitmap& map){
        for(unsigned int i=0; i<map.sx(); i++){
            for(unsigned int j=0; j<map.sy(); j++){
                for(unsigned int k=0; k<map.sz(); k++){
                    if(map(i,j,k)==false) map(i,j,k)=true;
                    else map(i,j,k)=false;
                }
            }
        }
    }
    ~Inversion(){}
};

class Erosion: public Transformation{
public:
    void transform(Bitmap& map){
        int array[500][3];
        int last=0;
        for(unsigned int x=0; x<map.sx(); x++){
            for(unsigned int y=0; y<map.sy(); y++){
                for(unsigned int z=0; z<map.sz(); z++){
                    if(map(x,y,z)==true&&x>0){
                        if(map(x-1,y,z)==false){
                            array[last][0]=x;
                            array[last][1]=y;
                            array[last][2]=z;
                            last++;
                        }
                    }
                    if(map(x,y,z)==true&&x<map.sx()-1){
                        if(map(x+1,y,z)==false){
                            array[last][0]=x;
                            array[last][1]=y;
                            array[last][2]=z;
                            last++;
                        }
                    }
                    if((map(x,y,z)==true&&y>0)){
                        if(map(x,y-1,z)==false){
                            array[last][0]=x;
                            array[last][1]=y;
                            array[last][2]=z;
                            last++;
                        }
                    }
                    if(map(x,y,z)==true&&y<map.sy()-1){
                        if(map(x,y+1,z)==false){
                            array[last][0]=x;
                            array[last][1]=y;
                            array[last][2]=z;
                            last++;
                        }
                    }
                    if(map(x,y,z)==true&&z>0){
                        if(map(x,y,z-1)==false){
                            array[last][0]=x;
                            array[last][1]=y;
                            array[last][2]=z;
                            last++;
                        }
                    }
                    if(map(x,y,z)==true&&z<map.sz()-1){
                        if(map(x,y,z+1)==false){
                            array[last][0]=x;
                            array[last][1]=y;
                            array[last][2]=z;
                            last++;
                        }
                    }
                }

            }
        }

        for(int i=0; i<last; i++){
            map(array[i][0],array[i][1],array[i][2])=false;
        }
    }
    ~Erosion(){}
};

class Dilatation: public Transformation{
public:
    void transform(Bitmap& map){
        int array[500][3];
        int last=0;
        for(unsigned int x=0; x<map.sx(); x++){
            for(unsigned int y=0; y<map.sy(); y++){
                for(unsigned int z=0; z<map.sz(); z++){
                    if(map(x,y,z)==false&&x>0){
                        if(map(x-1,y,z)==true){
                            array[last][0]=x;
                            array[last][1]=y;
                            array[last][2]=z;
                            last++;
                        }
                    }
                    if(map(x,y,z)==false&&x<map.sx()-1){
                        if(map(x+1,y,z)==true){
                            array[last][0]=x;
                            array[last][1]=y;
                            array[last][2]=z;
                            last++;
                        }
                    }
                    if((map(x,y,z)==false&&y>0)){
                        if(map(x,y-1,z)==true){
                            array[last][0]=x;
                            array[last][1]=y;
                            array[last][2]=z;
                            last++;
                        }
                    }
                    if(map(x,y,z)==false&&y<map.sy()-1){
                        if(map(x,y+1,z)==true){
                            array[last][0]=x;
                            array[last][1]=y;
                            array[last][2]=z;
                            last++;
                        }
                    }
                    if(map(x,y,z)==false&&z>0){
                        if(map(x,y,z-1)==true){
                            array[last][0]=x;
                            array[last][1]=y;
                            array[last][2]=z;
                            last++;
                        }
                    }
                    if(map(x,y,z)==false&&z<map.sz()-1){
                        if(map(x,y,z+1)==true){
                            array[last][0]=x;
                            array[last][1]=y;
                            array[last][2]=z;
                            last++;
                        }
                    }
                }
            }
        }

        for(int i=0; i<last; i++){
            map(array[i][0],array[i][1],array[i][2])=true;
        }
    }
    ~Dilatation(){}
};

class Reset: public Transformation{
public:
    void transform(Bitmap& map){
        for(unsigned int x=0; x<map.sx(); x++){
            for(unsigned int y=0; y<map.sy(); y++){
                for(unsigned int z=0; z<map.sz(); z++){
                    map(x,y,z)=false;
                }
            }
        }
    }
    ~Reset(){}
};

class Averaging: public Transformation{
    public:
    void transform(Bitmap& map){
        int array[500][3];
        int last=0;
        int k;
        for(unsigned int x=0; x<map.sx(); x++){
            for(unsigned int y=0; y<map.sy(); y++){
                for(unsigned int z=0; z<map.sz(); z++){
                    k=0;
                    if(x>0){
                        if(map(x-1,y,z)!=map(x,y,z)){
                            k++;
                        }
                    }
                    if(x<map.sx()-1){
                        if(map(x+1,y,z)!=map(x,y,z)){
                            k++;
                        }
                    }
                    if(y>0){
                        if(map(x,y-1,z)!=map(x,y,z)){
                            k++;
                        }
                    }
                    if(y<map.sy()-1){
                        if(map(x,y+1,z)!=map(x,y,z)){
                            k++;
                        }
                    }
                    if(z>0){
                        if(map(x,y,z-1)!=map(x,y,z)){
                            k++;
                        }
                    }
                    if(z<map.sz()-1){
                        if(map(x,y,z+1)!=map(x,y,z)){
                            k++;
                        }
                    }
                    if(k>3){
                        array[last][0]=x;
                        array[last][1]=y;
                        array[last][2]=z;
                        last++;
                    }
                }
            }
        }
        for(int i=0; i<last; i++){
            map(array[i][0],array[i][1],array[i][2])=!map(array[i][0],array[i][1],array[i][2]);
        }
    }
    ~Averaging(){}
};

class CombinationOfTransformations: public Transformation{
public:
    std::queue<Transformation*> array;

    void transform(Bitmap& map){
        while(!array.empty()){
            Transformation* temp=array.front();
            array.pop();
            temp->transform(map);
        }
    }
    void addTransformation(Transformation* p){
        array.push(p);
    }
};


