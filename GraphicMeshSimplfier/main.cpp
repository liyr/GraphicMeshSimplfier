#include <fstream>
#include "SimpleObject.h"
#include "Vec3f.h"
#include "Vector3d.h"


int main(int argc, char *argv[])
{
    if (argc < 3) return 0;
    SimpleOBJ::CSimpleObject input, output;
    if (!input.LoadFromObj(argv[0])) std::cout << "error, load failed" << std::endl;

    double ratio = atof(argv[2]);


    input.simplify(ratio);


    if (!output.SaveToObj(argv[1])) std::cout << "error, save failed" << std::endl;
	return 0;
}