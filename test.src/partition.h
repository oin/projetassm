#if !defined(PARTITION_H_9BYEBXVV)
#define PARTITION_H_9BYEBXVV

#include <effet.h>
#include <son.h>

struct partition : public effet {
	partition(chaine_effets& s,char* n="partition.midi") : effet(s), nom_fichier_(n){}
	virtual void operator()();
	char* nom_fichier() const { return nom_fichier_; }
	void nom_fichier(char* f) { nom_fichier_ = f; }
	
private:
	char* nom_fichier_;	
};

#endif
