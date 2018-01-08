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

		TVector3 GetDirection() { return dir; };
		TVector3 GetPosition() { return pos; };

	private:
		TVector3 pos, dir;
};

#endif //RAYS_H
