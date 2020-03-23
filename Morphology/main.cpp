//Monika Wielgus
#include <iostream>
#include <queue>
#include "Morphology.h"
#include "Morphology.cpp"

int main()
{
    BitmapExt b(3,4,5);
    b(0,1,0)= b(0,2,2) = b(0,2,3) = b(0,1,2)= true;
    b(1,2,1) = b(1,2,2) = b(1,2,3) = b(1,1,1) = b(2,1,2)= true;
    b(2,2,1) = b(2,2,2) = b(2,2,3) = b(2,1,1) = true;

    std::cout << "Original bitmap:\n" <<  b << "\n\n";

    Averaging a;
    Dilatation d;
    Reset r;
    Erosion e;

    a.transform(b);
    std::cout << "Transformed bitmap:\n" << b << "\n";

    CombinationOfTransformations z;
    z.addTransformation(&a);
    z.addTransformation(&d);
    z.addTransformation(&r);
    z.addTransformation(&e);
    z.addTransformation(&r);
    z.transform(b);

    std::cout << "Transformed bitmap:\n" << b << "\n";
}
