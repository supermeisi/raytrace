#include <iostream>

#include <TVector3.h>

class Box
{
	public:
		Box(double _x0, double _y0, double _z0);
		~Box();

		double GetLambda(TVector3 _pos, TVector3 _mom);

	private:
		double xe0, ye0, ze0;
		double xe1, ye1, ze1;
		double xe2, ye2, ze2;

		TVector3 center, dir1, dir2;
};
