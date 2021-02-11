#ifndef __DARWIN_H__
#define __DARWIN_H__

struct Species{
	int sid;
	struct Species *next;
	struct Species *prev;
	struct Population *Population_head;
	struct Population *Population_tail;
};

struct Population{
	int gid;
	int sid;
	int cid;
	struct Population *next;
	struct Population *next_species;
};

struct ContinentPopulation{
	int gid;
	struct ContinentPopulation *next;
};

struct ContinentList{
	struct ContinentPopulation *populationList;
	struct ContinentPopulation *sentinel;
};

/*
 * Global variables
 *
 */

struct ContinentList *continents[5]; // Continents' array. Each element is a pointer to the continent's first population

struct Species *Species_head; // Pointer to first element of Species' list
struct Species *Species_tail; // Pointer to last element of Species' list

struct Population *hs_L; // Pointer to first element of homo Sapiens list


#endif /* __DARWIN_H__ */
