#ifndef RAYS_H
#define RAYS_H

#include <iostream>

#include <TVector3.h>

class Rays
{
	public:
		Rays();
		~Rays();

		void SetDirection(TVector3 _dir) { dir = _dir.Unit(); };
		void SetPosition(TVector3 _pos) { pos = _pos; };

		void AddRay(TVector3 _pos, TVector3 _dir);

		TVector3 GetDirection(int _i) { return rays[_i][1]; };
		TVector3 GetPosition(int _i) { return rays[_i][0]; };

		double GetNRays() { return rays.size(); }

	private:
		TVector3 pos, dir;
		std::vector<std::vector<TVector3> > rays;
};

#endif //RAYS_H
