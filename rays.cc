#include "rays.h"

Rays::Rays()
{
}

Rays::~Rays()
{
}

void Rays::AddRay(TVector3 _pos, TVector3 _dir)
{
	//vec_pos.push_back(_pos);
	//vec_dir.push_back(_dir.Unit());

	std::vector<TVector3> ray;
	ray.push_back(_pos);
	ray.push_back(_dir.Unit());

	rays.push_back(ray);
}
