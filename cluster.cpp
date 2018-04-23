#include "cluster.h"
#include <math.h>

cluster::cluster(){}
//--------------------------------------------------------------------------
Bitmap^ cluster::toGrayScale(Bitmap^ bitPict)
{
	Bitmap^ picture = bitPict;

	for (int y = 0; y < picture->Height; y++)
		for (int x = 0; x < picture->Width; x++)
		{
			Color p = picture->GetPixel(x, y);
			//extract pixel component ARGB
			int a = p.A;
			int r = p.R;
			int g = p.G;
			int b = p.B;

			//find average
			int avg = 0.299*r + 0.587*g + 0.114*b;
			
			if (avg < 128) avg = 0;
			else avg = 255;

			//set new pixel value
			picture->SetPixel(x, y, Color::FromArgb(a, avg, avg, avg));
		}
	
	return picture;
}
//--------------------------------------------------------------------------
P cluster::vectorization(Bitmap^ pict)
{
	P vectP; //amount of koordinates in one vector
		
	unsigned int pictWidth = pict->Width; //borders--> must least some pixels in the end
	unsigned int pictHeight = pict->Height;
	//steps
	unsigned int pW = (unsigned int)pictWidth / 10;
	unsigned int pH = (unsigned int)pictHeight / 10;
	unsigned int xWbegin, xWend, yHbegin, yWend; //borders of 100th arrays
												 //vsogo diagonalej = 9+1(golovna)+9 =>19
	unsigned int numbArrI = 0, numbArrJ = 0; //numeracija aarrs
	unsigned int counter = 0;
	
	//up left -> like pinetree to end nomain diag
	for (unsigned int diag = 0; diag < 10; diag++) 
	{
		if (diag % 2 == 0) // parni diag
		{
			numbArrI = 0; // i-coordinate of diag
			numbArrJ = diag; //  j-coordinate of diag

			while (numbArrJ >= 0 && numbArrJ < 10) // while j is in up
			{
				xWbegin = numbArrI * pW, xWend = numbArrI * pW + pW;
				yHbegin = numbArrJ * pH, yWend = numbArrJ * pH + pH;

				counter = 0;
				for (unsigned int x = xWbegin; x < xWend; x++)
					for (unsigned int y = yHbegin; y < yWend; y++)
					{  
						if (pict->GetPixel(x,y) == Color::FromArgb(0, 0, 0))
							counter++; //if black pixel  0->BLACK   255->WHITE
					}
				vectP.x.push_back(counter);
				
				numbArrI++;     // horizontal left
				numbArrJ--;    // vertical down
			}
		}
		else // ne parni diag
		{
			numbArrI = diag; // i-coordinate of diag
			numbArrJ = 0; // j-coordinate of diag
			while (numbArrI >= 0 && numbArrI < 10) // while i in left part of diag
			{
				xWbegin = numbArrI * pW, xWend = numbArrI * pW + pW;
				yHbegin = numbArrJ * pH, yWend = numbArrJ * pH + pH;

				counter = 0;
				for (unsigned int x = xWbegin; x < xWend; x++)
					for (unsigned int y = yHbegin; y < yWend; y++)
					{ 
						if (pict->GetPixel(x, y) == Color::FromArgb(0, 0, 0))
							counter++; //if black pixel 0->BLACK   255->WHITE
					}
				vectP.x.push_back(counter);

				numbArrI -= 1;  // horizontal right
				numbArrJ += 1; // vertical up
			}
		}
	} // end for
	
	//**********************************************************************
	
	// left up to lastest element
	for (unsigned int diag = 1; diag < 10; diag++)
	{
		if (diag % 2 == 0) // parni diag
		{
			numbArrI = 9; //j of diag
			numbArrJ = diag;  // i of diag

			while (numbArrJ <= 9 && numbArrJ > 0) // while end diag
			{
				xWbegin = numbArrI * pW, xWend = numbArrI * pW + pW;
				yHbegin = numbArrJ * pH, yWend = numbArrJ * pH + pH;

				counter = 0;
				for (unsigned int x = xWbegin; x < xWend; x++)
					for (unsigned int y = yHbegin; y < yWend; y++)
					{ 
						if (pict->GetPixel(x, y) == Color::FromArgb(0, 0, 0))
							counter++; //if black pixel 0->BLACK   255->WHITE
					}
				vectP.x.push_back(counter);
				numbArrI--; // horizontal left
				numbArrJ++; // vertical down
			}
		}
		else // ne parni diag
		{
			numbArrI = diag; // i-coordinate of 1st k-diag
			numbArrJ = 9;  // j-coordinate of 1st k-diag

			while (numbArrI <= 9 && numbArrI > 0) // while end of diag
			{
				xWbegin = numbArrI * pW, xWend = numbArrI * pW + pW;
				yHbegin = numbArrJ * pH, yWend = numbArrJ * pH + pH;

				counter = 0;
				for (unsigned int x = xWbegin; x < xWend; x++)
					for (unsigned int y = yHbegin; y < yWend; y++)
					{ 
						if (pict->GetPixel(x, y) == Color::FromArgb(0, 0, 0))
							counter++; //if black pixel  0->BLACK   255->WHITE
					}
				vectP.x.push_back(counter);

				numbArrI++; // horizont right
				numbArrJ--; // vertical up
			}
		} // end if-else
	} // end for

	//----normalization-----
	double max = vectP.x[0];
	for (unsigned int i = 0; i < vectP.x.size(); i++)
	{
		if (vectP.x[i] > max) {
			max = vectP.x[i];
		}
	}
	for (unsigned int i = 0; i < vectP.x.size(); i++)
	{
		vectP.x[i] /= max;
	}
	
	return vectP;
}
//-------------------vybir pochatkovyh centriv centrojidiv------------------
void cluster::choosecenters()
{
	centry.clear();
	for (unsigned int j = 0; j < k; j++)//----cykl po kilkosti centriv  | k
	{
		bool t;
		unsigned int bb;
		do
		{
			t = 0;
			unsigned int gh = rand() % (koord.size());
			centry.push_back(koord[gh]);
			for (unsigned int gg = 0; gg < j; gg++)
			{
				bb = 0;
				for (unsigned int i = 0; i < centry[j].x.size(); i++)
				{   //po koordynatam
					if (centry[j].x[i] == centry[gg].x[i]) bb++;
				}
				if (bb == centry[j].x.size())
				{
					centry.pop_back(); t = 1;
				}//vsi x[i] spivpadajut
			}
		} while (t);
	}//cykl po centrah	
}
//--------------------------------------------------------------------------
double cluster::dosqrt(P ks, P kd) //koordynaty  v tochkah
{
	double sum = 0;
	for (unsigned int i = 0; i < n; i++)
	{
		sum = sum + (ks.x[i] - kd.x[i])*(ks.x[i] - kd.x[i]); //po koordynatam
	}
	return fabs(sum);
}
//------------------zv'jazka tochok | rozkyd po klasteram-------------------
void cluster::bindpoints()
{
	//nulovi elementy == vybrani pochatkovi centry
	for (unsigned int g = 0; g < k; g++)
	{
		std::vector<P> pp;//perekydna komirka
		pp.push_back(previouscentry[g]); //velychyna previouscentry
		kser.push_back(pp);
		pp.clear();
	}
	for (unsigned int j = 0; j < koord.size(); j++)//po vsim tochkam
	{
		double dist = dosqrt(kser[0][0], koord[j]);
		std::vector< P > *kh = &kser[0];// v 1st klaster
		for (unsigned int g = 1; g < k; g++)//mozhe v inshyj klaster
		{
			double neardist = dosqrt(kser[g][0], koord[j]);
			if (dist > neardist)
			{
				dist = neardist;
				kh = &kser[g];
			}// search the nearest cluster and push
		}
		(*kh).push_back(koord[j]);// a->b == (*a).b.
	}
	centermass();
}
//-------------------centr mass---------------------------------------------
void cluster::centermass()
{
	for (unsigned int g = 0; g < k; g++)//ruh po centram klasteriv
	{
		std::vector<unsigned int> cm(n, 0); //dlja kozhnoji koordynaty n
		for (unsigned int j = 0; j < kser[g].size(); j++)//po vsim tochkam pidklusteru
			for (unsigned int i = 0; i < n; i++)
				cm[i] = cm[i] + kser[g][j].x[i];
		
		P ppoint;
		for (unsigned int i = 0; i < n; i++)
		{
			ppoint.x.push_back(((unsigned int)cm[i] / kser[g].size()));
		}   //rozrahovanyj novyj centr mass
		previouscentry[g] = kser[g][0];
		kser[g][0] = ppoint; //new centers
		ppoint.x.clear();
	}
	//chy dali zv'jazuvaty, chy ni ? | tak pry pershomy prohodi
	unsigned int t = 0;
	for (unsigned int g = 0; g < k; g++)
	{
		unsigned int bb = 0;
		for (unsigned int i = 0; i < n; i++)//1 tochka-centr
		{  //koordynaty tochky-centru } jih je n shtuk
			if (kser[g][0].x[i] == previouscentry[g].x[i]) bb++;
		}
		if (bb == n) t++;//vsi x[i] spivpadajut
	}
	end++;
	if (t != k && end < 1000)
	{   // t -> kilkist spivpavshyh centriv
		for (unsigned int g = 0; g < k; g++) previouscentry[g] = kser[g][0];
		kser.clear();
		bindpoints();
	}
}
//-------------algorithm k-nearest neighbours 1 tochka----------------------
void cluster::kNearest()
{
	for (unsigned int g = 0; g < k; g++)//po vsim klasteram
	{
		for (unsigned int j = 0; j < kser[g].size(); j++)//po vsim tochkam klasteru
		{
			vids pp;//perekydna komirka
			pp.distance = sqrt(dosqrt(kser[g][j], pointkNN));
			pp.gg = g;
			vidstani.push_back(pp);
		}
	}

	//sort(vidstany);
	for (unsigned int i = 0; i < vidstani.size(); i++)
		for (unsigned int j = i; j < vidstani.size(); j++)
			if (vidstani[i].distance > vidstani[j].distance)
			{   //po zrostannju
				float tmp = vidstani[i].distance;
				vidstani[i].distance = vidstani[j].distance;
				vidstani[j].distance = tmp;
				unsigned int tmp2 = vidstani[i].gg;
				vidstani[i].gg = vidstani[j].gg;
				vidstani[j].gg = tmp2;

			}

	std::vector<unsigned int> lichylnyk(k, 0); //vid 0 do k
	for (unsigned int d = 0; d < ksusidy; d++)
	{
		int gg2 = vidstani[d].gg;
		lichylnyk[gg2]++;// kser[g]+ golos
	}
	
	unsigned int maxgolos = lichylnyk[0];
	ki = 0;
	for (unsigned int g = 0; g < lichylnyk.size(); g++)
	{
		if (lichylnyk[g] > maxgolos)
		{
			maxgolos = lichylnyk[g];
			ki = g;// indeks maxgolos  | jakyj klaster
		}
	}
	//zanesennja tochky v klaster
	kser[ki].push_back(pointkNN);
	lichylnyk.clear();
	vidstani.clear();
}
//----------------------------------------------------------------------------

//--------------------------------------------------------------------------
cluster::~cluster(){}
