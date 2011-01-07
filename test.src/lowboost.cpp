#include "lowboost.h"

void filtrePassBas(son& s,double ordre){
int i;
s.data()[0]=1;
s.data()[(int)ordre/2]=1;

  for(i=1;i<(int)(ordre/2);i++){
    s.data()[n]=2;
  }
  
 for(i=(int)(ordre/2);i<s.size();i++){
    s.data()[n]=0;
  }
}


void lowboost::operator()() {
		// lowboost
		son filtre(echantillon_debut()-echantillon_fin(), 44100);
		filtrePassBas(filtre); 
		for(size_t i=echantillon_debut(); i<echantillon_fin(); ++i)
				out().data()[i] = in().data()[i] + in().data()[i]*filtre.data()[i];
}