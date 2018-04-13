#pragma once
# include<vector>

using namespace std;
class P { public: vector<unsigned int> x;       };
class vids { public: float distance; int gg; };//dlja vidstanej

class clasterization
{
public:
	clasterization();
	vector<P> koord; //vsi tochky | N-rozmir
	vector<P> centry; //pochatkovi dlja kmeans
	unsigned int k, n, np, ksusidy, ki; //kilkist klasteriv, Rprostoru, nTochok
	vector<P> previouscentry;
	vector< vector<P> > kser;//mnozhyna klasteriv "kmeans" | kser[k]
	unsigned int end;
	bool fg; //chy natysnuly knopku
	P pointkNN; //rombik
	vector<vids> vidstani;

	bool correct(); ///perevirka edits
	void randoming();  //random tochky
	void choosecenters();//vybir pochatkovyh centriv
	void bindpoints(); //rozkyd po klasteram kmeans
	float dosqrt(P, P);
	void centermass();
	void vyvidkmeans(); //output kmeans
	void vyvidkanva(unsigned int, unsigned int); //na kanvu "kmeans"
	bool correctsus(); //perevirka kilkosti susidiv
	void kNearest(); //kNN
	void vyvidkNN(); // output kNN
	void cleaning();  //Clear kanvas\memos\vectors
};

