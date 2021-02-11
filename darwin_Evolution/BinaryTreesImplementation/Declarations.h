/**
*
* This file contains the declarations of some functions to use for the main file.
* @author Manos Chatzakis
*
*/
	
		
	//Functions:
	void showSpeciesPopulationsGids();
	void showSpecies();
	void showSpeciesPopulations();
	void showPopulations(struct Population *p);
	void showPopulationsGids(struct Population *p);

	int print_species();
	int print_continents();
	int print_populations();
	int print_homo_sapiens();
	int print_continents_tabbed();
	int print_continent(int cid);

	void delete_all_populations(struct Population *P);
	int delete_continent_population(int cid,int gid);
	int remove_species(int sid);
	int delete_population_noprint(int gid,int sid);
	
	int initialize_continents();
	int insert_continents(int gid,int cid);
	
	//Global variables:
	int firstCall = 1; //A flag to know if the fucntion is called recursively or its called normally, for delete event.
	int Index = 0; //The index of array to fill for merge event.
