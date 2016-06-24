#include <fstream>
#include "SimpleObject.h"
#include "Vec3f.h"
#include "Vector3d.h"


int main(int argc, char *argv[])
{
    if (argc < 3) return 0;
    SimpleOBJ::CSimpleObject input, output;
    if (!input.LoadFromObj(argv[1])) {
        std::cout << "error, load failed" << std::endl;
        return -1;
    }
    double ratio = atof(argv[3]);


    input.simplify(ratio, output);


    if (!output.SaveToObj(argv[2])) std::cout << "error, save failed" << std::endl;
	return 0;
}