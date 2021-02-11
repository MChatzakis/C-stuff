/**
*  HY - 240, November 2019
*  PROJECT, PHASE 1
*  Manos Chatzakis, 4238
*  csd4238@csd.uoc.gr, chatzakis@ics.forth.gr
*  NOTE: There are some extra functions apart from the function the file contained, in order to make the code more readable.
*  Project tried (and worked properly with all test files) on "firiki" (firiki.csd.uoc.gr) using "gcc main.c".
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Darwin.h"

#define BUFFER_SIZE 1024  /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */


/**
  Predefined printing functions.
*/
int print_populations(); 
int print_continents(); 
int print_homo_sapiens(); 
int print_continents_after_delete();  
int print_single_species();
int print_species_gids();
int print_continent();

/**
 **** INITIALIZING FUNCTIONS ****
*/

/** 
  Function to initialize continents.
*/
int initialize_continents(){
	int i;
	for (i=0; i<5; i++){
		continents[i] = malloc(sizeof(struct ContinentList)); //reserve size for every cell of the array.
		continents[i]->sentinel= malloc(sizeof(struct ContinentPopulation)); //reserve size for the sentinel
		(continents[i]->sentinel)->gid = -1; //sentinel's gid is -1.
		(continents[i]->sentinel)->next = NULL; //sentinel is the last element of the continent population.
		continents[i]->populationList = continents[i]->sentinel; //after initialization the sentinel is the only node of the continent population.
	}
	return 1;
}

/**
  Function to initialize head and tail pointers
 */
int initialize_species(){
	Species_head = NULL; //Create the species list.
	Species_tail = NULL;
	return 1;
}	

/**
  Function to initalize Homo Sapiens list.
*/
int initialize_HS(){
	hs_L = NULL;
	return 1;
}

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize (void) 
{
	hs_L = NULL;
	initialize_species();
	initialize_continents(); //Initialize continent array.
	return 1;
}

/**
 **** INSERTING FUNCTIONS ****
*/

/**
 * @brief insert new species in Species' list with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_species (int sid) 
{
	struct Species *q; //Pointer to the current node.
	struct Species *pq; //Pointer to the previous node.
	struct Species *p; //Pointer to the node to be added.

	q = Species_head; //Initializing the pointer so as to start from the beggining of the list.
	pq = NULL; //The previous node should be NULL, for the case the sid value is the smallest.

	//Iterating the species till we find a species with sid >= of the species sid we want to insert. (Species DLL is sorted). 
	while(q!=NULL && q->sid<sid){ 
		pq = q;
		q = q->next;
	}

	//If the species with the demanded sid is already in the list,we exit so as to avoid duplicates.
	if(q!=NULL && q->sid == sid){
		//Uncomment next line to throw a message when a duplicate is found.
		//printf("The species already exist.\n");
		//Also here we could call print functions, but there is no point in it.
		return 0; 
	}

	//Here we are at the right place to add the new node.
	//Make the new node and set the proper values to its fields.
	p = malloc(sizeof(struct Species));
	p->next = q; 
	p->prev = pq;
	p->sid = sid;
	
	//At the begging, every species has empty population list.
	p->Population_head = NULL; 
	p->Population_tail = NULL;

	//If q = NULL then we want to add a species to the end of the list, so we need to change the tail.
	if(q!=NULL) q->prev = p; 
	else Species_tail = p; //If the new species needs to places at the end of the list.

	//If pq = NULL then we want to add a species to the beggining of the list, so we need to change the head.
	if(pq == NULL) Species_head = p; //If the new species need to be places at the beggining of the list.
	else pq->next = p; 
	
	//Printing the demanded output.
	print_species_gids();
	printf("DONE\n");
	
	return 1;
}

/**
Works the same as insert species but is does not print info about the species list. Will be used inside merge.
*/
int insert_species_noprint(int sid){
	
	struct Species *q; //Pointer to the current node.
	struct Species *pq; //Pointer to the previous node.
	struct Species *p; //Pointer to the node to be added.

	q = Species_head; //Initializing the pointer so as to start from the beggining of the list.
	pq = NULL; //The previous node should be NULL, for the case the sid value is the smallest.

	//Iterating the species till we find a species with sid >= of the species sid we want to insert. (Species DLL is sorted). 
	while(q!=NULL && q->sid<sid){ 
		pq = q;
		q = q->next;
	}

	//If the species with the demanded sid is already in the list,we exit so as to avoid duplicates.
	if(q!=NULL && q->sid == sid){
		//Uncomment next line to throw a message when a duplicate is found.
		//printf("The species already exist.\n");
		//Also here we could call print functions, but there is no point in it.
		return 0; 
	}

	//Here we are at the right place to add the new node.
	//Make the new node and set the proper values to its fields.
	p = malloc(sizeof(struct Species));
	p->next = q; 
	p->prev = pq;
	p->sid = sid;
	
	//At the begging, every species has empty population list.
	p->Population_head = NULL; 
	p->Population_tail = NULL;

	//If q = NULL then we want to add a species to the end of the list, so we need to change the tail.
	if(q!=NULL) q->prev = p; 
	else Species_tail = p; //If the new species needs to places at the end of the list.

	//If pq = NULL then we want to add a species to the beggining of the list, so we need to change the head.
	if(pq == NULL) Species_head = p; //If the new species need to be places at the beggining of the list.
	else pq->next = p; 
	
	return 1;
}

/**
 * @brief insert new population with ID <gid> in Species' with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_population(int gid, int sid, int cid){ 
	
	struct Species *qq; //A pointer to iterate the species list to find species with ID <sid>.
	struct Population *q; //Pointer to the current population node.
	struct Population *pq;	//Pointer to the previous population node.
	struct Population *p; //Pointer to the population struct to be added.

	qq = Species_head; //Initialiaze the pointer to the head to iterate the species list from the beggining.
	
	//Iterating the species till we find a species with sid >= of the species sid we want to insert a population. (Species DLL is sorted).
	while(qq!=NULL && qq->sid<sid){ //
		qq = qq->next;
	}

	//If the sid does not exist we exit the function and terminate the event.
	if(qq == NULL || qq->sid!=sid){ 
		//Comment or uncomment next line to print an error message.
		printf("The species does not exist\n");
		//We could alse call print functions here but there is no point on that.
		return 0; 
	}

	//Iterating the population list of the species to place the new population.
	q = qq->Population_head;
	pq = NULL;

	//Iteration here is using the precious technique, as the population list is also sorted by gids.
	while(q!=NULL && q->gid<gid){
		pq = q;
		q = q->next;
	}

	//If the population with the given gid alredy exists, we exit the function and terminate the event.
	if(q!=NULL && q->gid == gid){
		//Comment or uncomment next line to print an error message.
		printf("Population with gid: %d of the species with sid: %d already exists.\n",sid,gid);
		//We could alse call print functions here but there is no point on that.
		return 0;
	}

	//Now this is the time to add the new population.
	p = malloc(sizeof(struct Population)); //We create a struct, and assing the demanded values on its fields.
	p->sid = sid;
	p->cid = cid;
	p->gid = gid;
	p->next = q;
	p->next_species = NULL; //This will be propably changed in evolution.

	if(q == NULL) qq->Population_tail = p; //If this population is added in an empty population list, or in the end of the list.
	
	if(pq == NULL) qq->Population_head = p; //If this population is added at the beggining of the list, or in an empty population list.
	else pq->next = p; 

	//Printing the demanded output.
	print_populations();

	return 1;
}

/**
 * @brief merge species with IDs <sid1> and <sid2> into new species with ID <sid3>
 *
 * @return 1 on success
 *         0 on failure
 */
int merge_species(int sid1, int sid2, int sid3){ 

	//Check if the species list contains species.
	if (Species_head == NULL) { 
		//Comment or uncomment next line to print error message.
		printf("Species list is empty\n");
		return 0;
	} 
	
	//Three pointers, to locate the place of the sid1 and sid2, and if they exist, the third pointer will locate sid3.
	struct Species* s1;
	struct Species* s2;
	struct Species* s3;
	
	//Iterating the list to find the species with sid1 and sid2.
	s1 = Species_head; 
	s2 = Species_head;
	while (s1 != NULL && s1->sid != sid1) {
		s1 = s1->next;
	}
	while (s2 != NULL && s2->sid != sid2) {
		s2 = s2->next;
	}
	
	//Checking if species with sid1 and sid2 exist.
	if (s1 == NULL || s2 == NULL) {
		//Comment or uncomment next line to print error message.
		printf("This (or these) species does not exist.\n");
		return 0;
	}

	//If sid1 and sid2 exist, we add the new species with sid3.
	insert_species_noprint(sid3); //No print function is called in order to not print info about the list right after insterting sid3.
	
	//Iterating the list to find where the species with sid3 is.
	s3 = Species_head;
	while (s3 != NULL && s3->sid != sid3) {
		s3 = s3->next;
	}
	
	//No error check needed as we know that we inserted sid3 previously.
	//Now we have the pointers to sid1 sid2 and sid3. We transfer the populations of sid1 and sid2 to sid3.

	struct Population* popul1; //Temporary pointer to iterate population list of species with sid1.
	struct Population* popul2; //Temporary pointer to iterate population list of species with sid2.
	struct Population* p_popul2; //Temportary pointer to hold the previous population of the sid2 population list.
	
	//Algorithm: Insert every sid1 population to sid2 population list, with complexity m+n.
	//NOTE: The m+n complexity is only about the part of the function where the 2 population lists are connected.
	
	//Iterating every population list, and placing every population in the right place.
	popul2 = s2->Population_head;
	p_popul2 = NULL;
		
	while (s1->Population_head != NULL) {
		
		popul1 = s1->Population_head; //Current population of sid1.
		(s1->Population_head) = (s1->Population_head)->next; //Next population of sid1.
		
		//Finding the right place to insert sid1 population(We need the "new" list to be still sorted).
		while(popul2!=NULL && popul2->gid < popul1->gid){ 
			p_popul2 = popul2;
			popul2->sid = sid3;
			popul2 = popul2->next;
		}
		
		//In case the are populations with same gid. 
		if(popul2!=NULL && popul1->gid == popul2->gid) continue; //Continue to the next population in case of duplicate.
		
		//Placing sid1 population behind popul2.
		//Notice: If sid1 population needs to be placed at the end of the list, popul2 would be NULL so there is no error on this.
		popul1->next = popul2;
		popul1->sid = sid3;
		
		//Here, we have connected the popul1 with popul2, with popul1 behinf popul2.
		//Now, we need to connect popul1 with the rest of the list(The populations behind it).
		
		//If popul1 is supposed to be places at the beggining of the "new" population list, we need to change the head.
		//Notice: popul2 is not changed, and this holds the complexity inside the 0(n+m).
		if(p_popul2 == NULL) {
			s2->Population_head = popul1; //Changing the head. Now popul1 is the first population of the list.
			(s2->Population_head)->sid = sid3;
			p_popul2 = popul1; //This will be useful for the next insertion (in some cases only).
		}
		else { 
			//Connecting the rest of the list with popul1. In this case, it's just a simple insertion.
			p_popul2 -> next = popul1;			
			p_popul2 = p_popul2->next; //We need p_popul2 to be a pointer to the last population inserted.
		}
		//In case population list of species with sid2 is empty, 
		if(popul2 == NULL) { 
			//In case there are population in sid1 which have bigger gid values, sid2 will be NULL after the insert of the specific population.
			//Though, we change popul2 to be a pointer to the tail of the "new" list, so the algorithm will work fine even in this case.
			s2->Population_tail = popul1;
			(s2->Population_tail)->sid = sid3;
			popul2 = popul1;
		}
		//if(s1->Population_head == s1->Population_tail) break;
	}
	
	//There are cases that populations are left in second list with sids unchanged:
	while(popul2!=NULL){
		popul2->sid = sid3;
		if(popul2 == s2->Population_tail) break;
		popul2 = popul2->next;
	}
	
	//NOTE: even with the while loop above, algorithm matches the complexity.
	
	//Now a "new" list is ready. Final step is to transfer it to the new species with sid3.
	s3->Population_head = s2->Population_head; 
	s3->Population_tail = s2->Population_tail;
	
	//Now, the population list of sid3 is ready, last thing is to change all the sids to sid3..
	
	//"Deleting" s2.
	s2->Population_head = NULL;
	s2->Population_tail = NULL;
	
	/*
	//We initialize popul1 pointer to iterate the sid3 species population list to change all the sids to sid3.
	popul1 = s3->Population_head;
	while(popul1!=NULL){
		popul1->sid = sid3; //Change the sid.
		if(popul1 == s3->Population_tail) break; //In case the merge is done after the evolution event.
		popul1 = popul1->next;
	}
	*/
	
	//Deleting the species sid1 and sid2 from the species list **ONLY**.
	//It's done the same way as delete_species() function.
	if(s1 == Species_tail){
		Species_tail = s1->prev;
		if(Species_tail!=NULL) Species_tail->next = NULL;
	}
	
	else if (s1->prev != NULL){
		(s1->next)->prev = s1->prev;
		(s1->prev)->next = s1->next;
	}
	
	else if (s1->prev == NULL){
		Species_head = s1->next;
		Species_head->prev = NULL;
	}
	
	if(s2 == Species_tail){
		Species_tail = s2->prev;
		if(Species_tail!=NULL) Species_tail->next = NULL;
	}
	
	else if (s2->prev != NULL){
		(s2->next)->prev = s2->prev;
		(s2->prev)->next = s2->next;
	}
	
	else if (s2->prev == NULL){
		Species_head = s2->next;
		Species_head->prev = NULL;
	}
	
	if(Species_tail == NULL) Species_head = NULL;
	
	//Printing functions are called for the demanded output.
	print_species_gids();
	printf("DONE\n");
	
	return 1; 
}

/**
 **** DISTRIBUTION FUNCTION ****
*/

/**
 * @brief Distribute species' population in continents array
 *
 * @return 1 on success
 *         0 on failure
 */
int distribute(){ 

	initialize_continents(); //In case the distribute event is done more than one time during a session.
	
	//Check if the list is empty.
	if(Species_head == NULL){
		//Comment or uncomment to print and error message.
		printf("The species list empty.\n");
		return 0;
	}
	
	struct Species *q; //Pointer to traverse the species list.
	struct Population *p; //Pointer to traverse the population list.
	struct ContinentPopulation *popul;  //Pointer to the new continentPopulation node to be added to the array.
	
	//Iterating the species list.
	q = Species_head;
	while(q!=NULL){
		//For every species, we iterate the population list and distribute all population to the proper place of the array.
		p = q->Population_head;
		while(p!=NULL){
			popul = malloc(sizeof(struct ContinentPopulation));
			//The new node is placed at the begging of the continentList, as this list in not sorted.
			popul->gid = p->gid;
			popul->next = continents[p->cid] -> populationList;
			continents[p->cid]->populationList = popul;
			if(p == q->Population_tail) break; //I could use a similar thing in the while() but segmentations may occur of a species list is empty.
			p = p->next;
		}
		q = q->next;
	}
	
	//To print the demanded output.
	print_continents();
	
	return 1;
}

/**
 **** DELETING FUNCTIONS ****
*/

/**
 * @brief delete population with ID <gid> from species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_population(int gid, int sid){ 
	
	//Check if the species list is empty.
	if(Species_head == NULL){
		//Comment or uncomment next line to print an error check.
		printf("The species list is empty.\n");
		return 0;
	}	
	
	struct Species *q; //Pointer to traverse the species list.
	struct Population *p; //Pointer to the current population node.
	struct Population *pp; //Pointer to the previous population node.
	
	//Iterating the species list to find the species with given sid.
	q = Species_head;
	pp = NULL;
	while(q!=NULL && q->sid<sid){
		q = q->next;
	}
	
	//Check if the species exist.
	if(q==NULL || q->sid!=sid) {
		//Comment or uncomment next line to print an error check.
		printf("Species with sid %d does not exist.\n",sid);
		return 0;
	}
	
	//Iterating the population list of this species to find the demanded population.
	p = q->Population_head;
	while(p!=NULL && p->gid<gid){
		pp = p;
		p = p->next;
	}
	
	//Check if the population exist.
	if(p==NULL || p->gid != gid){
		//Comment or uncomment next line to print an error check.
		printf("Gender with gid %d does not belong to species with sid %d\n",gid,sid);
		return 0; // 
	}
	
	//Delete from array:
	
	struct ContinentPopulation *cont; //Pointer to the current ContinentPopulation node.
	struct ContinentPopulation *p_cont; //Pointer to the previous ContinentPopulation node.
	
	cont = continents[p->cid] -> populationList; //Initiate the current pointer with the head of the continent population list of the continent the population belongs.
	p_cont = NULL; //The previous pointer should be NULL at the begging.
	
	//We will traverse the continent list using the sentinel.
	//We set the sentinel's gid equal to the value of the gid of the population we seek to delete.
	(continents[p->cid]->sentinel)->gid = gid;
	
	//Traverse the list till you find the gid.
	while(cont->gid!=gid){
		p_cont = cont;
		cont = cont -> next;
	}
	
	//if the cont is equal to the sentinel, it means the population is not distributed in the array yet.
	if(cont != continents[p->cid]->sentinel) {
		//Deleting the node as usual.
		if(p_cont!=NULL){
			p_cont->next = cont -> next;
		}
		else continents[p->cid] -> populationList = (continents[p->cid] -> populationList)->next;
	}
	
	(continents[p->cid]->sentinel)->gid = -1; //set sentinel back to its default gid number.
	//delete from array complete

	//Now that we deleted the population from the array, we delete the population from the population list as well.
	if(pp == NULL) q->Population_head = p->next; //If the population is at the beggining of the list.
	else if( p->next != NULL) pp->next = p->next;
	else if( p->next == NULL) {
		pp->next = NULL;
		q->Population_tail = pp;
	}
	
	if(q->Population_head == NULL) q->Population_tail = NULL; //In case this delete left the population list empty.
	
	//Calling and printing in order to match the demanded output.
	printf("SPECIES\n");
	print_single_species(sid);
	printf("CONTINENTS\n");
	print_continent(p->cid);
	printf("DONE\n");
	
	return 1; 
}

/**
Works same as delete population but it does not print information. Made to be used inside delete_species()
*/
int delete_population_noprint(int gid,int sid){
//Check if the species list is empty.
	if(Species_head == NULL){
		//Comment or uncomment next line to print an error check.
		printf("The species list is empty.\n");
		return 0;
	}	
	
	struct Species *q; //Pointer to traverse the species list.
	struct Population *p; //Pointer to the current population node.
	struct Population *pp; //Pointer to the previous population node.
	
	//Iterating the species list to find the species with given sid.
	q = Species_head;
	pp = NULL;
	while(q!=NULL && q->sid<sid){
		q = q->next;
	}
	
	//Check if the species exist.
	if(q==NULL || q->sid!=sid) {
		//Comment or uncomment next line to print an error check.
		//printf("Species with sid %d does not exist.\n",sid);
		return 0;
	}
	
	//Iterating the population list of this species to find the demanded population.
	p = q->Population_head;
	while(p!=NULL && p->gid<gid){
		pp = p;
		p = p->next;
	}
	
	//Check if the population exist.
	if(p==NULL || p->gid != gid){
		//Comment or uncomment next line to print an error check.
		//printf("Gender with gid %d does not belong to species with sid %d\n",gid,sid);
		return 0; // 
	}
	
	//Delete from array:
	
	struct ContinentPopulation *cont; //Pointer to the current ContinentPopulation node.
	struct ContinentPopulation *p_cont; //Pointer to the previous ContinentPopulation node.
	
	cont = continents[p->cid] -> populationList; //Initiate the current pointer with the head of the continent population list of the continent the population belongs.
	p_cont = NULL; //The previous pointer should be NULL at the begging.
	
	//We will traverse the continent list using the sentinel.
	//We set the sentinel's gid equal to the value of the gid of the population we seek to delete.
	(continents[p->cid]->sentinel)->gid = gid;
	
	//Traverse the list till you find the gid.
	while(cont->gid!=gid){
		p_cont = cont;
		cont = cont -> next;
	}
	
	//if the cont is equal to the sentinel, it means the population is not distributed in the array yet.
	if(cont != continents[p->cid]->sentinel) {
		//Deleting the node as usual.
		if(p_cont!=NULL){
			p_cont->next = cont -> next;
		}
		else continents[p->cid] -> populationList = (continents[p->cid] -> populationList)->next;
	}
	
	(continents[p->cid]->sentinel)->gid = -1; //set sentinel back to its default gid number.
	//delete from array complete

	//Now that we deleted the population from the array, we delete the population from the population list as well.
	if(pp == NULL) q->Population_head = p->next; //If the population is at the beggining of the list.
	else if( p->next != NULL) pp->next = p->next;
	else if( p->next == NULL) {
		pp->next = NULL;
		q->Population_tail = pp;
	}
	
	if(q->Population_head == NULL) q->Population_tail = NULL; //In case this delete left the population list empty.
	
	return 1; 
	
}

/**
 * @brief delete species with ID <sid> and its populations
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_species(int sid){  

	//Check if the species list is empty.
	if(Species_head == NULL) return 0;
	
	struct Species *q; //Pointer to traverse the species list.
	q = Species_tail;
	//Traversing the list, starting from the head.
	while(q!=NULL && q->sid>sid){ 
		q = q->prev;
	}
	
	if(q==NULL||q->sid!=sid) return 0; //In case the species we seek does not exist.
	
	//Here, we have the sid we want to delete.
	//Fisrt, we will delete its population from the population list and the array.
	
	struct Population *popul;
	popul = q->Population_head;
	
	//For every population of the species, we delete it using the delete population function.
	while(popul!=NULL){
		delete_population_noprint(popul->gid,sid); //No print version of delete_populations() so as to not fail the output.
		if(popul == q->Population_tail) break; //For the case that evolution event is done before this.
		popul = popul->next;
	}
	
	//Here every population is deleted.
	//Last step is to remove the sid from the species list.
	
	//If its the last species:
	if(q == Species_tail){
		Species_tail = q->prev;
		if(Species_tail!=NULL) Species_tail->next = NULL;
	}
	
	else if(q->prev!=NULL) {
		(q->next)->prev = q->prev; //Classic way to delete nodes from a DLL.
		(q->prev)->next = q->next;
	}
	
	else if(q->prev == NULL){
		Species_head = q->next;
		Species_head->prev = NULL;
	}
	
	//In case this delete left the species list empty:
	if(Species_tail == NULL) Species_head = NULL;
	
	//Call these print functions to match the output.
	printf("SPECIES\n");
	print_species_gids();
	printf("CONTINENTS\n");
	print_continents_after_delete();
	
	return 1;
}

/**
 **** EVOLUTION FUNCTION ****
*/

/**
 * @brief Remaining species evolve into homo sapiens.
 *
 * @return 1 on success
 *         0 on failure
 */
int evolution(){ 

	//Check if the species list is empty.
	if(Species_head == NULL) return 0; 
	
	//Initialiaze the homo sapiens pointer to the first population of the first species.
	hs_L = Species_head -> Population_head;
	
	struct Species *q; //Pointer to traverse the species.
	q = Species_head;
	
	while(q->next!=NULL){
		
		//There is no point to call the Evolution event if there is a species with empty population list.
		if((q->next)->Population_head == NULL || q->Population_head == NULL){
			printf("A species in the list has empty population list!\n");
			return 0;
		}
		//Connecting the populations: The next field of the last population of a species now points to the first population of the next species.
		(q->Population_head)->next_species = (q->next)->Population_head;
		(q->Population_tail)->next = (q->next)->Population_head;
		q = q->next;
	}
	
	//Calling the print function to match the demanded output.
	print_homo_sapiens();
	
	return 1;
}

/**
 **** PRINTING FUNCTIONS ****
*/

/**
 * @brief Gather statistics on species from homo_sapiens list
 *
 * @return 1 on success
 *         0 on failure
 */
int species_statistics(){ 

	//Checking if the homo sapiens list in empty.
	if (hs_L == NULL) return 0;
	
	struct Population *q; //Pointer to iterate the homo sapiens list.
	int countSpecies = 0; //The species counter
	
	q = hs_L;
	
	while(q!=NULL){
		countSpecies++; //Add 1 to the counter.
		q = q->next_species; //Proceed to the next species, not the next population.
	}
	
	//The demanded print:
	printf("  Homo Sapiens species:<%d>\nDONE\n",countSpecies);
	return 1;
}

/**
 * @brief Gather statistics on population belonging to species with ID <sid> from homo_sapiens list
 *
 * @return 1 on success
 *         0 on failure
 */
int population_statistics(int sid){ 
	
	//Check if the Homo Sapiens list is empty.
	if(hs_L == NULL) return 0;
	
	struct Population *p; //Pointer to iterate the populations of a sid belonging to Homo Sapiens.
	int countPopulations = 0; //The population counter.
	
	p = hs_L;
	
	//Iterating the homo sapiens list, will we find the demanded speicies.
	while(p!=NULL && p->sid!=sid){
			p = p->next_species; //Proceeding by species to do it faster. (Chain lists)
	}	
	
	//if (p == NULL) return 0; 
	
	while(p!=NULL && p->sid == sid){
		countPopulations++; //Increment the counter.
		p = p->next; //Proceed to the next population with sid3.
	}
	
	//The demanded print.
	printf("  Homo Sapiens populations:<%d>\nDONE\n",countPopulations);
	
	return 1;
}

/**
 * @brief Print species' list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_species(){ 

	//Check if the Species List is empty.
	if (Species_head == NULL) return 0;
	
	struct Species *q; //Pointer to iterate the species.
	q = Species_head;
	
	//Printing the species, following the demanded input.
	printf("  ");
	while(q!=NULL){
		printf("<%d>",q->sid);
		q = q->next;
		if(q!=NULL) printf(",");
	}
	
	printf("\nDONE\n");
	return 1;
}

/**
 * @brief Print species' list with population lists
 *
 * @return 1 on success
 *         0 on failure
 */
int print_populations(){  
	
	//Check if the Species list is empty.
	if(Species_head == NULL){
		return 0;
	}
	
	struct Species *q; //Pointer to iterate the list.
	struct Population *p; //Pointer to iterate the population list.
	q = Species_head;
	
	//Iterating the species list.
	while(q!=NULL){
		//Printing the demanded output.
		p = q->Population_head;
		printf("   <%d>\n     ",q->sid);
		//Iterating the population list/
		while(p!=NULL){
			printf("<%d,%d>" ,p->gid,p->cid);
			if(p==q->Population_tail) break;
			printf(",");
			p = p->next;
		}
		
		q = q->next;
		printf("\n");
	}
	printf("DONE\n");
	return 1;
}

/**
 * @brief Print continents array with each continent's population list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_continents(){
	int i; //The continent's index.
	struct ContinentPopulation *q; //Pointer to the continentPopulation list.
	//For every continent i, iterate the whole list till you find the sentinel, and print the gids.
	for (i=0; i<5; i++){
		q = continents[i]-> populationList;
		printf("Continent %d:",i);
		while(q!=continents[i]->sentinel){
			printf("<%d>",q->gid);
			q = q->next;
			if(q!=continents[i]->sentinel) printf(",");
		}
		printf("\n");
	}
	
	printf("DONE\n");
	
	return 1;
}

/**
Works the same as print_continents() but leaves a small gap in the beggining. Used inside delete_species() to match the recuired output
*/
int print_continents_after_delete(){
int i;
	struct ContinentPopulation *q;
	for (i=0; i<5; i++){
		q = continents[i]-> populationList;
		printf("  Continent %d:",i); //Here is the difference.....
		while(q!=continents[i]->sentinel){
			printf("<%d>",q->gid);
			q = q->next;
			if(q!=continents[i]->sentinel) printf(",");
		}
		printf("\n");
	}
	printf("DONE\n");
	
	return 1;

}

/**
 * @brief Print homo_sapiens list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_homo_sapiens(){ 

	//Check if the Homo Sapiens list is empty.
	if(hs_L == NULL) return 0;
	
	struct Population *p; //Pointer to iterate the homo sapiens list.
	p = hs_L; //Init
	
	//The demanded output:
	printf("  Homo Sapiens:[");
	
	while(p!=NULL){
		printf("<%d,%d>",p->gid,p->sid);
		if(p->next!=NULL && (p->next)->sid!=p->sid) printf("][");
		else if(p->next!=NULL) printf(",");
		p = p->next;
	}
	printf("]\n");
	printf("DONE\n");
	return 1;
}

/**
  A copy of print_species() but its not printing the continents that the populations belong.
*/
int print_species_gids()
{
	if(Species_head == NULL){
		return 0;
	}
	
	struct Species *q;
	struct Population *p;
	
	q = Species_head;
	
	while(q!=NULL){
		p = q->Population_head;
		printf("   <%d>\n     ",q->sid);
		while(p!=NULL){
			printf("<%d>",p->gid);
			if(p==q->Population_tail) break;
			p = p->next;
			printf(",");
		}
		
		q = q->next;
		printf("\n");
	}
	return 1;
}

/**
  Created to print a single species with its populations.
*/
int print_single_species(int sid)
{
	struct Species *q; //pointer to the current node.
	struct Population *p;
	
	q = Species_head;
	
	while(q!=NULL && q->sid<sid){ //Iterate species 
		q = q->next;
	}

	if(q!=NULL && q->sid != sid){
		printf("The species does not exists.\n");
		return 0; //The does not exists.
	}
	
	p = q->Population_head;
	printf("   <%d>\n     ",q->sid);
		
	while(p!=NULL){
		printf("<%d>",p->gid);
		if(p==q->Population_tail) break;
		p = p->next;
		printf(",");
	}
		
	q = q->next;
	printf("\n");
		
	
	return 1;
}

/**
  Created to print the populations on continent i.
*/
int print_continent(int i)
{
	
	struct ContinentPopulation *q;
	q = continents[i]-> populationList;
	
	printf("   Continent <%d>:",i);
		
	while(q!=continents[i]->sentinel){
		printf("<%d> ",q->gid);
		q = q->next;
	}
		
	printf("\n");
	return 1;
}	

/**
 **** NOT USED FUNCTIONS ****
*/

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
int free_all(void) 
{
	return 1;
}


/**
 **** MAIN FUNCTION ****
*/

/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char** argv) 
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;

	/* Check command buff arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if (( fin = fopen(argv[1], "r") ) == NULL ) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Initializations */
	initialize();

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch(buff[0]) {

			/* Comment */
			case '#':
				break;

				/* Insert Species
				 * S <sid> */
			case 'S':
				{
					int sid;

					sscanf(buff, "%c %d", &event, &sid);
					DPRINT("%c %d\n", event, sid);

					if (insert_species(sid)) {
						DPRINT("%c %d succeeded\n", event, sid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, sid);
					}

					break;
				}

				/* Insert population
				 * G <gid> <sid> <cid> */
			case 'G':
				{
					int gid, sid, cid;

					sscanf(buff, "%c %d %d %d", &event, &gid, &sid, &cid);
					DPRINT("%c %d %d %d\n", event, gid, sid, cid);

					if (insert_population(gid, sid, cid)) {
						DPRINT("%c %d %d %d succeeded\n", event, gid, sid, cid);
					} else {
						fprintf(stderr, "%c %d %d %d failed\n", event, gid, sid, cid);
					}

					break;
				}

				/* Merge species
				 * M <sid1> <sid2> <sid3> */
			case 'M':
				{
					int sid1, sid2, sid3;

					sscanf(buff, "%c %d %d %d", &event, &sid1, &sid2, &sid3);
					DPRINT("%c %d %d %d\n", event, sid1, sid2, sid3);

					if (merge_species(sid1, sid2, sid3)) {
						DPRINT("%c %d %d %d succeeded\n", event, sid1, sid2, sid3);
					} else {
						fprintf(stderr, "%c %d %d %d failed\n", event, sid1, sid2, sid3);
					}

					break;
				}

				/* Distribute species
				 * D */
			case 'D':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (distribute()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Delete population
				 * K <gid> <sid> */
			case 'K':
				{
					int gid, sid;

					sscanf(buff, "%c %d %d", &event, &gid, &sid);
					DPRINT("%c %d %d\n", event, gid, sid);

					if (delete_population(gid, sid)) {
						DPRINT("%c %d %d succeeded\n", event, gid, sid);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, gid, sid);
					}

					break;
				}

				/* Delete species
				 * F <sid> */
			case 'F':
				{
					int sid;

					sscanf(buff, "%c %d", &event, &sid);
					DPRINT("%c %d\n", event, sid);

					if (delete_species(sid)) {
						DPRINT("%c %d succeeded\n", event, sid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, sid);
					}

					break;
				}

				/* Evolution to homo sapiens
				 * E */
			case 'E':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (evolution()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Species' statistics
				 * N */
			case 'N':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (species_statistics()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Population statistics
				 * J <sid> */
			case 'J':
				{
					int sid;

					sscanf(buff, "%c %d", &event, &sid);
					DPRINT("%c %d\n", event, sid);

					if (population_statistics(sid)) {
						DPRINT("%c %d succeeded\n", event, sid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, sid);
					}

					break;
				}

				/* Print species
				 * P */
			case 'P':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_species()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Print populations
				 * X */
			case 'X':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_populations()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Print continents
				 * C */
			case 'C':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_continents()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Print homo sapiens
				 * W */
			case 'W':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_homo_sapiens()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Empty line */
			case '\n':
				break;

				/* Ignore everything else */
			default:
				DPRINT("Ignoring buff: %s \n", buff);

				break;
		}
	}

	free_all();
	return (EXIT_SUCCESS);
}
