#pragma once
# include<vector>
using namespace System::Drawing;

class P { public: std::vector<unsigned int> x; std::string pathToFile;};
class vids { public: float distance; unsigned int gg; };//dlja vidstanej

class cluster
{
public:
	cluster();
	std::vector<P> koord; //vsi tochky | N-rozmir
	std::vector<P> centry; //pochatkovi dlja kmeans
	unsigned int k, n, np, ksusidy, ki; //kilkist klasteriv, Rprostoru, nTochok
	std::vector<P> previouscentry;
	std::vector< std::vector<P> > kser;//mnozhyna klasteriv "kmeans" | kser[k]
	unsigned int end;
	
	bool fg; //chy natysnuly knopku
	
	P pointkNN; //rombik
	std::vector<vids> vidstani;


	Bitmap^ toGrayScale(Bitmap^);
	P vectorization(Bitmap^);

	void choosecenters();//vybir pochatkovyh centriv
	void bindpoints(); //rozkyd po klasteram kmeans
	float dosqrt(P, P);
	void centermass();
	

	//bool correctsus(); //perevirka kilkosti susidiv
	void kNearest(); //kNN
	

	~cluster();
};


