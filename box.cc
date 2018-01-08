#include "box.h"

Box::Box(double _x0, double _y0, double _z0)
{
	xe0 = _x0;
	ye0 = _y0;
	ze0 = _z0;

	xe1 = 1;
	ye1 = 0;
	ze1 = 0;

	xe2 = 0;
	ye2 = 1;
	ze2 = 0;
}

Box::~Box()
{
}

double Box::GetLambda(int _i, TVector3 _pos, TVector3 _mom)
{
	/*double x = _pos.X();
	double y = _pos.Y();
	double z = _pos.Z();

	double px = _mom.X();
	double py = _mom.Y();
	double pz = _mom.Z();*/

	TVector3 pos = rays.GetPosition(_i);
	TVector3 mom = rays.GetDirection(_i);

	double x = pos.X();
	double y = pos.Y();
	double z = pos.Z();

	double px = mom.X();
	double py = mom.Y();
	double pz = mom.Z();

	//Calculate intersection
	double lambda = (((xe0-x)*ye1-xe1*ye0+xe1*y)*ze2+((x-xe0)*ye2+xe2*ye0-xe2*y)*ze1+(xe1*ye2-xe2*ye1)*ze0+(xe2*ye1-xe1*ye2)*z)/((px*ye1-py*xe1)*ze2+(py*xe2-px*ye2)*ze1+pz*xe1*ye2-pz*xe2*ye1);

	//std::cout << xe0 << " " << ye0 << " " << ze0 << std::endl;

	return lambda;
}
