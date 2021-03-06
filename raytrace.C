#include <iostream>

#include <TVector3.h>
#include <TCanvas.h>
#include <TBox.h>
#include <TColor.h>
#include <TF1.h>

#include "rays.h"
#include "box.h"

int main()
{
	//Number of pixels in x and y-direction
	int nx = 500;
	int ny = 500;

	//Position of the spectator
	double x0 = 0;
	double y0 = 0;
	double z0 = 0;

	TVector3 camera(x0, y0, z0);

	//Position of the grid
	double x1 = -1;
	double y1 = -1;
	double z1 = 1;

	double z = z1;

	TCanvas *c1 = new TCanvas("c1", "c1", nx, ny);
	c1->SetFillColor(kBlack);

	//TBox *pixel[nx][ny];

	TBox *pixel[nx*ny];

	TF1 *prob = new TF1("prob", "gaus", 0, 1);
	TF1 *lamb = new TF1("lamb", "2/TMath::Pi()*cos(x)", 0, TMath::Pi()/2);

	Box *box = new Box(0, 0, 20);

	Rays *rays = new Rays();

	for(int i = 0; i < nx; i++)
	{
		double x = x1 + double(i)/double(nx)*2;

		for(int j = 0; j < ny; j++)
		{
			double y = y1 + double(j)/double(ny)*2;

			TVector3 grid(x, y, z);

			rays->SetPosition(grid);
			rays->SetDirection(grid - camera);

			rays->AddRay(grid, grid-camera);

			pixel[j+ny*i] = new TBox(x-1./nx+0.5,y-1./ny+0.5,x+1./nx+0.5,y+1./ny+0.5);
		}
	}

	box->SetRays(*rays);

	for(int i = 0; i < rays->GetNRays(); i++)
	{
		//pixel[i][j] = new TBox(x-1./nx+0.5,y-1./ny+0.5,x+1./nx+0.5,y+1./ny+0.5);

		pixel[i]->SetFillColor(kBlack);
		//pixel[i][j]->Draw();

		TVector3 grid(rays->GetPosition(i).X(), rays->GetPosition(i).Y(), rays->GetPosition(i).Z());

		rays->SetPosition(grid);
		rays->SetDirection(grid - camera);

		TVector3 p = grid - camera;

		p = p.Unit();

		double px = rays->GetDirection(i).X();
		double py = rays->GetDirection(i).Y();
		double pz = rays->GetDirection(i).Z();

		//cout << diff.X() << " " << diff.Y() << " " << diff.Z() << endl;

		double dx = 10.;
		double dy = 10.;
		double dz = 1.;

		TVector3 norm(0,0,-1);

		//Scattering angle
		double alpha = 0.2;

		//Calculate intersection between light rays and Disc DIRC
		//double lambda = (((xe0-x)*ye1-xe1*ye0+xe1*y)*ze2+((x-xe0)*ye2+xe2*ye0-xe2*y)*ze1+(xe1*ye2-xe2*ye1)*ze0+(xe2*ye1-xe1*ye2)*z)/((px*ye1-py*xe1)*ze2+(py*xe2-px*ye2)*ze1+pz*xe1*ye2-pz*xe2*ye1);


		double lambda = box->GetLambda(i, grid, p);

		TColor *color = new TColor();
		//color->SetRGB(0.1, 0.2, 0.3);
		//int colval = TColor::GetColor(100, 100, 100);

		double r = 1.0;
		double g = 0.2;
		double b = 0.0;

		TVector3 light(0., 5., 10.);

		//Light source
		TVector3 inter(x1 + lambda*px, y1 + lambda*py, z1 + lambda*pz);

		if(x1 + lambda*px > -dx/2 && x1 + lambda*px < dx/2)
		{
			if(y1 + lambda*py > -dy/2 && y1 + lambda*py < dy/2)
			{
				//std::cout << i << " " << j << " " << lambda << std::endl;

				//pixel[i][j]->SetFillColor(colval);

				//Calculate reflection
				px = -2*(px*0+py*0+pz*1)*0+px;
				py = -2*(px*0+py*0+pz*1)*0+py;
				pz = -2*(px*0+py*0+pz*1)*1+pz;

				TVector3 refl(px, py, pz);

				TVector3 conn = light - inter;

				double angle = refl.Angle(conn);

				//std::cout << angle << std::endl;

				prob->SetParameter(0,1);
				prob->SetParameter(1,0);
				prob->SetParameter(2,alpha);

				float value = prob->Eval(angle)/prob->GetMaximum(0,1);

				double vallamb = lamb->Eval(angle);

				value = 0.5*(vallamb+value);

				//std::cout << vallamb << std::endl;

				int ci = TColor::GetFreeColorIndex();
				float r, g, b;
				TColor::HSV2RGB(0, 1, value, r, g, b);
				TColor *color = new TColor(ci, r, g, b);
				pixel[i]->SetFillColor(ci);
			}
		}

		pixel[i]->Draw();
	}

	c1->Print("detector.png");
}
