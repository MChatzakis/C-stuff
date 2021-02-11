#ifndef __DARWIN_H__
#define __DARWIN_H__

struct Species{
	int					sid;	
	struct Population	*population_root;
	struct Species		*lc;
	struct Species		*rc;
};

struct Population{
	int					gid;
	int					sid;
	int					cid;
	struct Population	*parent;
	struct Population	*lc;
	struct Population	*rc;
};

struct ContinentPopulation{
	int 						gid;
	struct ContinentPopulation	*lc;
	struct ContinentPopulation	*rc;
};

struct ContinentTree{
	struct ContinentPopulation *population_root;
	struct ContinentPopulation *sentinel;
};

struct HomoSapiens{
	int					sid;
	struct Population	*population_root;
	struct HomoSapiens	*next;
	struct HomoSapiens	*lc;
	struct HomoSapiens	*rc;
};

/*
 * Global variables
 *
 */

struct ContinentTree *continents[5]; // Continents' array. Each element is two pointers. 
									 // One to the continent's population tree root
									 // and one to the tree's sentinel node

struct Species *Species_root; // Pointer to the root of Species' tree


struct HomoSapiens *Homo_Sapiens_root; // Pointer to the root of Homo Sapiens tree


#endif /* __DARWIN_H__ */
