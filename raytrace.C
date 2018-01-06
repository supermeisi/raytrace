#include <iostream>

#include <TVector3.h>
#include <TCanvas.h>
#include <TBox.h>
#include <TColor.h>
#include <TF1.h>

int main()
{
	//Number of pixels in x and y-direction
	int nx = 200;
	int ny = 200;

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

	TCanvas *c1 = new TCanvas("c1", "c1", 500, 500);

	TBox *pixel[nx][ny];

	TF1 *prob = new TF1("prob", "gaus", 0, 1);

	for(int i = 0; i < nx; i++)
	{
		double x = x1 + double(i)/double(nx)*2;

		for(int j = 0; j < ny; j++)
		{
			double y = y1 + double(j)/double(ny)*2;

			pixel[i][j] = new TBox(x-1./nx+0.5,y-1./ny+0.5,x+1./nx+0.5,y+1./ny+0.5);
			pixel[i][j]->SetFillColor(kBlack);

			TVector3 grid(x, y, z);

			TVector3 diff = grid - camera;

			diff = diff.Unit();

			double px = diff.X();
			double py = diff.Y();
			double pz = diff.Z();

			//Position of the box
			double xe0 = 0;
			double ye0 = 0;
			double ze0 = 20;

			double xe1 = 1;
			double ye1 = 0;
			double ze1 = 0;

			double xe2 = 0;
			double ye2 = 1;
			double ze2 = 0;

			//cout << diff.X() << " " << diff.Y() << " " << diff.Z() << endl;

			double dx = 10.;
			double dy = 10.;
			double dz = 1.;

			TVector3 norm(0,0,-1);

			//Scattering angle
			double alpha = 0.15;

			//Calculate intersection between light rays and Disc DIRC
			double lambda = (((xe0-x)*ye1-xe1*ye0+xe1*y)*ze2+((x-xe0)*ye2+xe2*ye0-xe2*y)*ze1+(xe1*ye2-xe2*ye1)*ze0+(xe2*ye1-xe1*ye2)*z)/((px*ye1-py*xe1)*ze2+(py*xe2-px*ye2)*ze1+pz*xe1*ye2-pz*xe2*ye1);

			TColor *color = new TColor();
			//color->SetRGB(0.1, 0.2, 0.3);
			//int colval = TColor::GetColor(100, 100, 100);

			double r = 1.0;
			double g = 0.2;
			double b = 0.0;

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

					double angle = refl.Angle(norm);

					std::cout << angle << std::endl;

					prob->SetParameter(0,1);
					prob->SetParameter(1,0);
					prob->SetParameter(2,alpha);

					int value = prob->Eval(angle)*255;

					std::cout << value << std::endl;

					int colval = TColor::GetColor(int(r*value), int(g*value), int(b*value));

					pixel[i][j]->SetFillColor(colval);
				}
			}

			pixel[i][j]->Draw();
		}
	}

	c1->Print("detector.png");
}
