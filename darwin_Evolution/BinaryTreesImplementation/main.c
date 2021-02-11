/**
*	Data Structures Project, Phase 2.
*	Name : Manos Chatzakis
*	AM   : 4238
*   eMail: csd4238@csd.uoc.gr, chatzakis@ics.forth.gr  
*	Project tried and worked on firiki, using "gcc main.c".
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Darwin.h"
#include "Declarations.h"

#define BUFFER_SIZE 1024  /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */



//NOTE: Its important to include the header file contained in the folder sent in order to work.


/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize(void)
{
	Species_root = NULL;
	Homo_Sapiens_root = NULL;
	initialize_continents(); //Initializing continents with the sentinel.
	return 1;
}

/**
*
*  ***Inserting Functions***
*
*/

/**
 * @brief insert new species in Species' list with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_species (int sid)
{
	struct Species *P; //The current pointer to traverse a path of a tree.
	struct Species *Prev; //A pointer of the previous node of P.
	struct Species *Q; //A pointer to the struct to add.
	
	Prev = NULL; //Init with null.
	P = Species_root; //Path starts from the root.

	//Traversing the path. The "=" is to catch duplicates inside the loop and not after it. 
	while(P!=NULL && P->sid>=sid){ //P!=null stands for 
		
		Prev = P; //Prev gets the previous node of P.
		
		if(P->sid == sid){ //Duplicate is found so the insert in not valid.
			printf("%d is already in species tree.\n",sid);
			return 0; //Function fails.
		}
		
		if(P->lc != NULL && (P->lc)-> sid < sid) P = P->rc; //If the left child exist and its value is smaller than the value to add, we go right.
		else P = P->lc; //Going left is the default choice.
	}

	Q = malloc(sizeof(struct Species)); //Creating a new struct.
	Q->sid = sid;
	Q->rc = NULL;
	Q->lc = NULL;
	Q->population_root = NULL; //Population root is empty in the beggining.

	if(P == Species_root){ //If P stayed on species root and did not proceed, then is either NULL or smaller than the sid to add.
		Species_root = Q; //So the new root should be Q(the new species).
	}

	else{
		if(Prev->lc != NULL && (Prev->lc)->sid < sid) { //If there exists a left child and its value is smaller than the sid to add
			Prev->rc = Q; //then the new species becomes the right child of the Prev species.
		}
		else {
			Prev->lc = Q; //Else it becomes the left child.
		}
	}

	//Always the species with the smaller sid is placed on the left of the new species.
	//If P is NULL there is not a problem.
	//Etc. When Q is to become the new root, the old root is placed on the left of it.
	Q->lc = P; 

	//Printing the demanded output.
	print_species();

	return 1;
}

/**
 * @brief insert new population with ID <gid> in Species' with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_population(int gid, int sid, int cid){

	struct Species *locate = Species_root; //A pointer to locate the species to insert the population.

	while(locate!=NULL && locate->sid>sid){ //Same algorithm as insert species.
		if(locate->lc != NULL && (locate->lc)->sid < sid) locate = locate->rc;
		else locate = locate ->lc;
	}

	if(locate == NULL || locate->sid != sid){ //Error check, to validate if the species to add a population exists.
		printf("The species to add a population does not exist.\n");
		return 0;
	}

	struct Population *P = locate->population_root; //Pointer to traverse the population tree.
	struct Population *Prev = NULL; //Pointer to the previous population of P.

	while(P!=NULL){
		Prev = P; //Keeping the previous population.
		
		if(P->gid == gid){ //Check for duplicates.
			printf("This population already exists.\n");
			return 0;
		}

		//Traversing a path in a BS tree.
		if(gid<P->gid) P = P->lc; 
		else P = P->rc;
	}

	//Creating the struct of the new population to add.
	struct Population *Q = malloc(sizeof(struct Population)); 
	Q->sid = sid;
	Q->gid = gid;
	Q->cid = cid;
	Q->parent = Prev; //The parent of the prev pointer.
	Q->rc = NULL; 
	Q->lc = NULL;

	if(Prev == NULL){ //If the tree is empty.
		locate->population_root = Q; //The root is now Q.
	}
	else if (gid < Prev->gid) Prev->lc = Q;  //The new population should be placed right if the gid is bigger than than the prev gid, else left.
 	else Prev->rc = Q;

 	//Printing the demanded output.
 	printf("  <%d>\n    ",locate->sid);
 	showPopulations(locate->population_root);
 	printf("\b \nDONE\n");

	return 1;
}

/**
 * @brief same as insert species but does not print info.
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_species_noprint(int sid)
{
	struct Species *P; //The current pointer to traverse a path of a tree.
	struct Species *Prev; //A pointer of the previous node of P.
	struct Species *Q; //A pointer to the struct to add.
	
	Prev = NULL; //Init with null.
	P = Species_root; //Path starts from the root.

	//Traversing the path. The "=" is to catch duplicates inside the loop and not after it. 
	while(P!=NULL && P->sid>=sid){ //P!=null stands for the case that the tree is empty.
		
		Prev = P; //Prev gets the previous node of P.
		
		if(P->sid == sid){ //Duplicate is found so the insert in not valid.
			printf("%d is already in species tree.\n",sid);
			return 0; //Function fails.
		}
		
		if(P->lc != NULL && (P->lc)-> sid < sid) P = P->rc; //If the left child exist and its value is smaller than the value to add, we go right.
		else P = P->lc; //Going left is the default choice.
	}

	Q = malloc(sizeof(struct Species)); //Creating a new struct.
	Q->sid = sid;
	Q->rc = NULL;
	Q->lc = NULL;
	Q->population_root = NULL; //Population root is empty in the beggining.

	if(P == Species_root){ //If P stayed on species root and did not proceed, then is either NULL or smaller than the sid to add.
		Species_root = Q; //So the new root should be Q(the new species).
	}

	else{
		if(Prev->lc != NULL && (Prev->lc)->sid < sid) { //If there exists a left child and its value is smaller than the sid to add
			Prev->rc = Q; //then the new species becomes the right child of the Prev species.
		}
		else {
			Prev->lc = Q; //Else it becomes the left child.
		}
	}

	//Always the species with the smaller sid is places on the left of the new species.
	//If P is NULL there is not a problem.
	//Etc. When Q is to become the new root, the old root is placed on the left of it.
	Q->lc = P; 
	return 1;
}

/**
*
* @brief insert a species to homo sapiens tree.
*
* @return 1 on success 
*		  0 on failure
*/
int insert_homoSapiens(struct Species *R){
	
	if(R==NULL) return 0; //Error check.
	
	struct HomoSapiens *P = Homo_Sapiens_root; //Current pointer.
	struct HomoSapiens *Prev = NULL; //Previous pointer.
	
	while(P!=NULL && (P->rc != NULL)){ //Searching the species.
		Prev = P;
		if(R->sid <= P->sid) P = P->lc;
		else P = P->rc;
	}
	
	//NOTE: This function always seeks species that belong to the tree so there is no need to error check.
	
	//Creating the subtree with the two nodes.
	struct HomoSapiens *Q,*K;

	Q = malloc(sizeof(struct HomoSapiens)); //Q is the parent node.
	
	Q->population_root = R->population_root;
	Q->sid = R->sid;
	Q->next = NULL;
	Q->lc = NULL;
	Q->rc = NULL;
	
	if(P == NULL){ //If the tree is empty.
		Homo_Sapiens_root = Q; 
		R->population_root = NULL; //The population tree should be ampty after the homo sapiens event.
		return 1;
	}
 
	K = malloc(sizeof(struct HomoSapiens)); //K is the right child of subtree with root Q.
	K->population_root = R->population_root;
	K->sid = R->sid;
	K->next = P->next;
	K->rc = NULL;
	K->lc = NULL;

	P->next = K; //P will be the left sibling.

	if(R->sid<P->sid){ //Setting the proper values, as described for the leaf oriented trees.
		K->sid = P->sid; K->population_root = P->population_root;
		P->sid = R->sid; P->population_root = R->population_root;
	}
	else {
		Q->population_root = P->population_root;
		Q->sid = P->sid;
	}
	
	//Finishing the set of the subtree.
	Q->lc = P;
	Q->rc = K;

	//Inserting the subtree to the homo sapiens tree, in the place that we had P pointer before.
	if(Prev == NULL){	
		Homo_Sapiens_root = Q;
		Homo_Sapiens_root -> population_root = Q->population_root;
	}
	else if(Prev->sid >= Q->sid) Prev->lc = Q;
	else Prev->rc = Q;

	R->population_root = NULL; //The population is deleted from the population tree of the species.

	//Debuging print. Uncomment to debug.
	/*printf("-------------\n");
	printf("Q = %d P = %d K = %d\n",Q->sid,P->sid,K->sid);
	printf("-------------\n");*/
	return 1;
}

/**
*
* @brief insert a population to the continent tree.
*
* @return 1 on success 
*		  0 on failure
*/
int insert_continents(int gid,int cid){
	
	struct ContinentPopulation *P = continents[cid]->population_root; //Pointer to traverse the tree.
	struct ContinentPopulation *Prev = NULL; //Pointer to the previous node of P.

	//Searching the right place to insert the new population.
	while(P!=continents[cid]->sentinel){ //Till we reach the last population before sentinel.
		Prev = P;
		if(P->gid == gid){ //Duplicate check.
			printf("Population already distributed.\n");
			return 0;
		}
		if(P->gid<gid){
			P = P->rc;
		}
		else P = P->lc;
	}

	//Creating a new CP struct.
	struct ContinentPopulation *Q = malloc(sizeof(struct ContinentPopulation));
	Q->gid = gid;
	//The rc/lc pointers are initialized woth the sentinel, not null.
	Q->rc = continents[cid]->sentinel;
	Q->lc = continents[cid]->sentinel;

	//If the tree is empty.
	if(Prev == NULL){
		continents[cid]->population_root = Q;
	}
	
	//If the tree is not empty properly connect the new population to the tree.
	else if(Prev->gid > gid){
		Prev->lc = Q;
	}
	else{
		Prev->rc = Q;
	}

	return 1;
}

/**
*
*  ***Common Ancestor Function***
*
*/

/**
 * @brief find the lowest (earliest) common ancestor of populations with ID <gid1> and <gid2> of species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int lowest_common_ancestor(int sid, int gid1, int gid2){
	
	struct Species *P = Species_root; //Pointer to find the species we seek.

	if(P == NULL) {
		printf("The species list is empty");
		return 0; //Error check for the case of empty tree.
	}
	while(P!=NULL && P->sid>sid){ //Searching the sid, same as before.
		if(P->lc != NULL && (P->lc)-> sid < sid) P = P->rc;
		else P = P->lc;
	}

	if(P == NULL || P->sid != sid){ //Error check for the success of the search.
		printf("The sid %d does not exist in species list.\n",sid);
		return 0;
	}

	//Now we have located the demanded species.
	//We will seek the populations.
	struct Population *P1 = P->population_root; //Pointer to find population with gid1.
	struct Population *P2 = P->population_root; //Pointer to find population with gid2.

	int d1 = 0; //Depth of population 1.
	int d2 = 0; //Depth of population 2.

	while(P1!=NULL && P1->gid!=gid1){ //Searching popualtion with gid1 while counting and it's depth also.
		d1++;
		if(P1->gid<gid1) P1 = P1->rc;
		else P1 = P1->lc;
	}

	if(P1 == NULL) { //Check if gid1 is found.
		printf("Could not locate gid %d\n",gid1);
		return 0;
	}

	while(P2!=NULL && P2->gid!=gid2){ //Same as before.
		d2++;
		if(P2->gid<gid2) P2 = P2->rc;
		else P2 = P2->lc;
	}	

	if(P2 == NULL){
		printf("Could not locate gid %d\n",gid2);
		return 0;
	}

	//Finding lowest common ancestor algorithm.
	//Its possible that the 2 populations have different depths we get them to be in the same depth.
	while(d1!=d2){
		if(d1>d2){
			P1 = P1->parent;
			d1--;
		}
		else if(d2>d1){
			P2 = P2->parent;
			d2--;
		}
	}

	//Now that the 2 populations have the same depth, we procced by goinf to the parent populations, while we find the same parent.
	while(P1!=P2){
		P2 = P2->parent;
		P1 = P1->parent;
	}
	//Another solution could be tracing the path and return the pointer at where the two paths changed ways.

	//Printing the demanded output.
	printf("  Lowest Common Ancestor:<%d>\nDONE\n",P1->gid);
	return 1;
}

/**
*
*  ***Merge Functions***
*
*/

/**
 * @brief Fills arrays from a population's tree cids and gids.
 *
 */
void fillArrayFromTree(int *gids,int *cids,struct Population *tree){	
	if(tree == NULL) return;
	fillArrayFromTree(gids,cids,tree->lc); //Inorder traversal.
	gids[Index] = tree->gid;
	cids[Index] = tree->cid;
	Index++;
 	fillArrayFromTree(gids,cids,tree->rc);
}

/**
 * @brief Fills a tree with the gids and cids from arrays, using devie and conquer sceptic.
 *
 */
struct Population *efficientInsert(int *gids,int *cids,int min,int max,struct Population *tree,int sid){
	if(max>=min){
		//Its the same logic as binary search.
		int indexx = min+(max-min)/2;
		tree = malloc(sizeof(struct Population));
		tree->gid = gids[indexx];
		tree->cid = cids[indexx];
		tree->sid = sid;
		tree->lc = efficientInsert(gids,cids,min,indexx-1,tree,sid); 
		tree->rc = efficientInsert(gids,cids,indexx+1,max,tree,sid);
	}
	else{
		return NULL;
	}
	return tree;
}

/**
 * @brief Counts the nodes of a tree.
 *
 */
int countNodes(struct Population *p){
	int count = 0;
	if(p==NULL) return 0;
	count += countNodes(p->lc);
	count += countNodes(p->rc);
	count++;
	return count;
}

/**
 * @brief Merges two sorted arrays in a third, sorted too.
 *
 */
void mergeArrays(int *arr1Gids,int *arr1Cids,int *arr2Gids,int *arr2Cids,int *arr3Gids,int *arr3Cids, int size1,int size2){
	
	int size3 = size1+size2;

	int i = 0; //index of arr3.
	int j = 0; //index of arr1.
	int k = 0; //index of arr2.

	while(i<size3){
		//based on the index values, the aray3 is filled.
		if(arr1Gids[j]>=arr2Gids[k]){
			arr3Gids[i] = arr2Gids[k];
			arr3Cids[i] = arr2Cids[k];
			k++;
			i++;
			if(k == size2) break;
		}
		if(arr1Gids[j]<arr2Gids[k]){
			arr3Gids[i] = arr1Gids[j];
			arr3Cids[i] = arr1Cids[j];
			j++;
			i++;
			if(j == size1) break;
		}
	}
	
	//If there are remaining indexes left(etc. bigger arrays)/
	while(j<size1){
		arr3Gids[i] = arr1Gids[j];
		arr3Cids[i] = arr1Cids[j];
		j++;
		i++;
	}
	
	while(k<size2){
		arr3Gids[i] = arr2Gids[k];
		arr3Cids[i] = arr2Cids[k];
		k++;
		i++;
	}
	
} 

/**
 * @brief merge species with IDs <sid1> and <sid2> into new species with ID <sid3>
 *
 * @return 1 on success
 *         0 on failure
 */
int merge_species(int sid1, int sid2, int sid3){
	
	if(sid1 == sid2){
		printf("Invalid merge arguments.\n");
		return 0;
	}

	if(Species_root == NULL) { //Error check
		printf("The species tree is empty.\n");
		return 0;
	}

	struct Species *s1 = Species_root; //Pointer to locate the species with sid1.
	struct Species *s2 = Species_root; //Pointer to locate the species with sid2.
	
	while(s1!=NULL && s1->sid>sid1){ //Traversing the tree to locate species with sid1.
		if(s1->lc != NULL && (s1->lc)->sid <sid1){
			s1 = s1->rc;
		}
		else{
			s1 = s1->lc;
		}
	}

	while(s2!=NULL && s2->sid >sid2){ //Traversing the tree to locate species with sid2.
		if(s2->lc != NULL && (s2->lc)->sid <sid2){
			s2 = s2->rc;
		}
		else{
			s2 = s2->lc;
		}
	}

	//If one of the species does not exist there is no point in merge.
	if(s1==NULL || s2 == NULL || s1->sid != sid1 || s2->sid != sid2){
		printf("Species do not exist.\n");
		return 0;
	}

	//If both species exist, we insert the sid3 species, and keep a pointer to it.
	if(!insert_species_noprint(sid3)) return 0; 
	//printf("------------------------------------------------------\n");
	struct Species *s3 = Species_root;

	while(s3!=NULL && s3->sid > sid3){
		if(s3->lc != NULL && (s3->lc)->sid < sid3){
			s3 = s3->rc;
		}
		else{
			s3 = s3->lc;
		}
	}

	int i; //The variable to use for the for loops.

	//Counting the populations of specied with sid1 and sid2.
	int size1 = countNodes(s1->population_root);
	int size2 = countNodes(s2->population_root);

	//Uncomment next line for debugging reasons.
	//printf("First sid is %d with %d populations.\nSecond sid is %d with %d populations.\nSid to be added is %d.\n",s1->sid,size1,s2->sid,size2,s3->sid);
	int size3 = size1+size2; //The populations of species with sid3 is the sum of the popualations od sid1 and sid2.

	//For every species, we hold an array for the gids of it's populations and another one for the cids of the populations.
	//Then we allocate them properly.
	int *arr1Gid = malloc(size1*sizeof(int));
	int *arr1Cid = malloc(size1*sizeof(int));

	int *arr2Gid = malloc(size2*sizeof(int));
	int *arr2Cid = malloc(size2*sizeof(int));

	int *arr3Gid = malloc(size3*sizeof(int));
	int *arr3Cid = malloc(size3*sizeof(int));

	//Αrr1 and Αrr2 are for the species with sid1 and s2. 
	//The populations of these species are passed to the arrays using the next function.
	//The filling function is defined in a plugin file.
	fillArrayFromTree(arr1Gid,arr1Cid,s1->population_root); 
	Index = 0; //The counter should be re-initialized for the next array.
	fillArrayFromTree(arr2Gid,arr2Cid,s2->population_root);
	Index = 0;

	//After both arrays are filled we merge them into the third one using the plug in function that follows.
	//The complexity of the function is O(n+m).
	mergeArrays(arr1Gid,arr1Cid,arr2Gid,arr2Cid,arr3Gid,arr3Cid,size1,size2);

	//Uncomment next lines for debugging reasons.
/*	printf("First Population:\n");
	for(i=0; i<size1; i++){
		printf("<%d,%d>\n",arr1Gid[i],arr1Cid[i]);
	}

	printf("Second Population:\n");
	for(i=0; i<size2; i++){
		printf("<%d,%d>\n",arr2Gid[i],arr2Cid[i]);
	}

	printf("Merged Populations:\n");
	for(i=0; i<size3; i++){
		printf("<%d,%d>\n",arr3Gid[i],arr3Cid[i]);
	}*/

	//We add all the populations to the tree in a way the tree wont become a list, using this function from the merge plugin file.
	s3->population_root = efficientInsert(arr3Gid,arr3Cid,0,size3-1,s3->population_root,sid3);

	//After everything is added to the new species, the old ones should be removed.
	//Note that they are only removed from the species tree.
	if((!remove_species(sid1))||(!remove_species(sid2))){
		printf("Could not remove the merged species from the tree species tree.\n");
		return 0;
	}

	//Printing the demanded output.
	showSpeciesPopulationsGids(Species_root);
	printf("DONE\n");

	return 1; 
}


/**
*
*  ***Continent Functions***
*
*/

/**
 * @brief Initializes the continets with the sentinel.
 *
 */
int initialize_continents(){
	int i=0;
	//Initialing all five continents with the sentinel.
	for(i=0; i<5; i++){ 
		continents[i] = malloc(sizeof(struct ContinentTree));
		(continents[i])->sentinel = malloc(sizeof(struct ContinentPopulation));
		((continents[i])->sentinel)->gid = -1;
		((continents[i])->sentinel)->lc = NULL;
		((continents[i])->sentinel)->rc = NULL;
		(continents[i])->population_root = (continents[i])->sentinel; //When a population is empty, the root is the same to the sentinel.
	}
} 

/**
 * @brief traverses a population tree and inserts its populations to the prpoper continents.
 *
 */
void distribute_populations(struct Population *p){
	if(p==NULL) return;
	//Traversing the population tree of a species and distributing the populations to continents.
	insert_continents(p->gid,p->cid); //Inserting with preorder traversal.
	distribute_populations(p->lc);
	distribute_populations(p->rc);
}

/**
 * @brief traverses all the species tree to put all population to continents.
 *
 */
void distribute_species(struct Species *p){
	if(p == NULL) return;
	//Traverse the species and for every species traverse the population tree.
	distribute_populations(p->population_root); //PreOrder traversal.
	distribute_species(p->lc);
	distribute_species(p->rc);
} 

/**
 * @brief Distribute species' population in continents array
 *
 * @return 1 on success
 *         0 on failure
 */
int distribute(){
	initialize_continents(); //Initialing continents so they contain only the sentinel.
	distribute_species(Species_root); //Distribute all the populations to continents.
	print_continents(); //Printing the demanded output.
	return 1;
}


/**
*
*  ***Deleting Functions***
*
*/

/**
 * @brief delete population with ID <gid> from species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_population(int gid, int sid){
	
	struct Species *P; //Pointer to locate the species with the population to delete.
	P = Species_root; //Statring from the species root.
	
	if(Species_root == NULL) return 0; //Error check.

	//Searching for the species with sid.
	while(P!=NULL && P->sid > sid){
		if(P->lc != NULL && (P->lc)->sid < sid){
			P = P->rc;
		}
		else {
			P = P->lc;
		}
	}

	//Error check.
	if(P==NULL || P->sid!=sid){
		return 0;
	}

	struct Population *R = P->population_root; //Pointer to locate the population to delete.

	if(R == NULL) return 0; //Error check.

	//Searching for the population.
	while(R!=NULL && R->gid != gid){
		if(gid<R->gid) R = R->lc;
		else R =R->rc;
	}

	if(R==NULL) { //Error check.
		return 0;
	}

	int ip = R->cid; //This is there for testing reasons but finally I kept it.

	//If the population is a leaf.
	if(R->rc == NULL && R->lc ==NULL){
		if(R->parent!=NULL){ //If it's not the root.
			if((R->parent)->lc == R){ //If it's the left child.
				(R->parent)->lc = NULL;
			}
			else{
				(R->parent)->rc = NULL;
			}
		}
		else{ //If its the root.
			P->population_root = NULL;
		}
	}
	
	//If the population node has one child.
	else if(R->lc == NULL || R->rc == NULL){
		if(R->parent!=NULL){ //If its not the root.
			if((R->parent)->lc == R){ //If its the left child.
				if(R->rc!=NULL){ 
					(R->parent)->lc = R->rc;
					(R->rc)->parent = R->parent;
				}
				else{
					(R->parent)->lc = R->lc;
					(R->lc)->parent = R->parent;
				}
			}
			else{
				if(R->rc!=NULL){
					(R->parent)->rc = R->rc;
					(R->rc)->parent = R->parent;

				}
				else{
					(R->parent)->rc = R->lc;
					(R->lc)->parent = R->parent;
				}	
			}
		} 
		//If its the root.
		else{
			if(R->rc !=NULL){
				P->population_root = R->rc;
			}
			else{
				P->population_root = R->lc;
	
			}
			(P->population_root)->parent = NULL;
		}

	
	}
	//If population has 2 children.
	else{
		
		//Searching the previous inorder node.
		struct Population *S = R;
		struct Population *SPrev = S;
		
		S = S->lc;
		
		while((S!=NULL)){
			SPrev = S;
			S = S->rc;
		}

		int tmpGid = SPrev->gid;
		int tmpCid = SPrev->cid;

		firstCall = 0;
		if(!delete_population_noprint(SPrev->gid,sid)) return 0; //As the next node in inorder is a leaf or has one child.
		firstCall = 1; 

		R->gid = tmpGid;
		R->cid = tmpCid;
	
	}

	//The use of the global variable to find out if this is the firts call of the function.
	if(firstCall){
		//printf("Diagrafi tou %d apo tin ipeiro %d",gid,R->cid);
		delete_continent_population(ip,gid);
	}

	//Printing the demanded output.
	printf("SPECIES\n");
	printf("  <%d>\n    ",sid);
	showPopulationsGids(P->population_root);
	printf("\b \nCONTINENTS\n");
	print_continent(ip);

	return 1;
}

/**
 * @brief Same as delete population but does not print info.
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_population_noprint(int gid, int sid){
	
	struct Species *P; //Pointer to locate the species with the population to delete.
	P = Species_root; //Statring from the species root.
	
	if(Species_root == NULL) return 0; //Error check.

	//Searching for the species with sid.
	while(P!=NULL && P->sid > sid){
		if(P->lc != NULL && (P->lc)->sid < sid){
			P = P->rc;
		}
		else {
			P = P->lc;
		}
	}

	//Error check.
	if(P==NULL || P->sid!=sid){
		return 0;
	}

	struct Population *R = P->population_root; //Pointer to locate the population to delete.

	if(R == NULL) return 0; //Error check.

	//Searching the population.
	while(R!=NULL && R->gid != gid){
		if(gid<R->gid) R = R->lc;
		else R =R->rc;
	}

	if(R==NULL) { //Error check.
		return 0;
	}

	int ip = R ->cid;
	//If the population is a leaf.
	if(R->rc == NULL && R->lc ==NULL){
		if(R->parent!=NULL){
			if((R->parent)->lc == R){
				(R->parent)->lc = NULL;
			}
			else{
				(R->parent)->rc = NULL;
			}
		}
		else{
			P->population_root = NULL;
		}
	}
	//If the population has one child.
	else if(R->lc == NULL || R->rc == NULL){
		if(R->parent!=NULL){
			if((R->parent)->lc == R){
				if(R->rc!=NULL){
					(R->parent)->lc = R->rc;
					(R->rc)->parent = R->parent;
				}
				else{
					(R->parent)->lc = R->lc;
					(R->lc)->parent = R->parent;
				}
			}
			else{
				if(R->rc!=NULL){
					(R->parent)->rc = R->rc;
					(R->rc)->parent = R->parent;

				}
				else{
					(R->parent)->rc = R->lc;
					(R->lc)->parent = R->parent;
				}	
			}
		}
		else{
			if(R->rc !=NULL){
				P->population_root = R->rc;
			}
			else{
				P->population_root = R->lc;
	
			}
			(P->population_root)->parent = NULL;
		}

	
	}
	//If population has 2 children.
	else{
		
		struct Population *S = R;
		struct Population *SPrev = S;
		
		S = S->lc; //na to xanadw!
		
		while((S!=NULL)){
			SPrev = S;
			S = S->rc;
		}

		int tmpGid = SPrev->gid;
		int tmpCid = SPrev->cid;

		firstCall = 0;
		if(!delete_population_noprint(SPrev->gid,sid)) return 0;
		firstCall = 1;

		R->gid = tmpGid;
		R->cid = tmpCid;
	
	}

	if(firstCall){
		//printf("Diagrafi tou %d apo tin ipeiro %d",gid,R->cid);
		delete_continent_population(ip,gid);
		//firstCall = 1;
	}

	return 1;
}

/**
 * @brief delete the species with lowest id and its populations
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_species(){
	
	struct Species *P = Species_root; //Pointer to the current node.
	struct Species *Prev = NULL; //Pointer to the parent node of the current node.
	struct Species *GPrev = NULL; //Pointer to the grandparent node of the current node.

	if(P == NULL){ //Delete has no point if there are no species left.
		printf("The species population is empty.\n");
		return 0; 
	}

	//Algorithm: The smallest one will be the leaf of the "most" left path of the tree.
	//We locate this leaf, delete its populations and then we replace it with the bigger one, the right sibling of it.
	while(P!=NULL){
		GPrev = Prev;
		Prev = P;
		P = P->lc; //Going all the way to the left path.
	}

	//Uncomment next line for debugging reasons.
    //printf("Oldest species is: <%d>\n",Prev->sid);

	//In this point the Prev node is the species to be deleted.
	//The following function is defined in the plugin file.
	//Its responsible to delete all the populations of a species and remove them from the continent array also.
	delete_all_populations(Prev->population_root);

	//For the case we delete a normal species node.
	if(GPrev!=NULL){
		GPrev->lc = GPrev->rc; //We replace the left child with the right.
		GPrev->rc = NULL; 
	}
	//For the case the root is the only species left.
	else{
		Species_root = NULL;
	}

	//Printing the demanded output.
	printf("SPECIES\n");
	showSpeciesPopulationsGids(Species_root);
	printf("CONTINENTS\n");
	print_continents_tabbed();
	return 1;
}

/**
 * @brief remove the species with given sid
 *
 * @return 1 on success
 *         0 on failure
 */
int remove_species(int sid){
	struct Species *P = Species_root;
	struct Species *Prev = NULL;

	if(Species_root == NULL) return 0;

	while(P!=NULL &&P->sid>sid){
		Prev = P;
		if(P->lc!=NULL && (P->lc)->sid <sid){
			P = P->rc;
		}
		else{
			P = P->lc;
		}
	}

	if(P == NULL || P->sid!=sid){
		return 0;
	}

	//If its the root.
	if(Prev == NULL){
		if(P->rc == NULL && P->lc == NULL) Species_root = NULL;
		else if(P->rc == NULL || P->lc ==NULL){
			if(P->rc!=NULL){
				Species_root = P->rc;
			}
			else{
				Species_root = P->lc;
			}
		}
		else{
			struct Species *transfer;
			transfer = P->lc;
			P = P ->rc;
			Species_root = P;
			while(P!=NULL){
				Prev = P;
				P = P->lc;
			}
			Prev->lc = transfer;
		}
	}
	
	//If its a normal node of the tree.
	else if(P->rc == NULL && P->lc == NULL){
		if(Prev->lc != NULL && (Prev->lc)->sid == sid) Prev->lc = NULL;
		else Prev->rc = NULL;
	}

	else if(P->rc == NULL || P->lc == NULL){
		if(P->rc!=NULL){
			if(Prev->rc!=NULL && (Prev->lc)->sid == P->sid) Prev->lc = P->rc;
			else Prev->rc = P->lc;
		}
		else{
			if(Prev->lc!=NULL && (Prev->lc)->sid == P->sid) Prev->lc = P->lc;
			else Prev->rc = P->lc;
		}
	}

	else{
		struct Species *tmp;
		if(Prev->lc == P){
			Prev->lc = P->rc;
		}
		tmp = P->lc;
		P = P->rc;
		while(P!=NULL){
			Prev = P;
			P = P->lc;
		}
		Prev->lc = tmp;
	}

	return 1;
	
}

/**
 * @brief delete population with gid from the continent sid
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_continent_population(int cid,int gid){

	struct ContinentPopulation *P = continents[cid]->population_root; //Pointer to traverse the tree of this continents.
	struct ContinentPopulation *Prev = NULL; //Pointer to the previous node of the tree.

	if(P == continents[cid]->sentinel) return 0; //Error check.

	(continents[cid]->sentinel)->gid = gid; //Setting the gid we will search to the sentinel to make sure that it will will be found.

	while(P->gid != gid){ //Searching the population.
		Prev = P;
		if(P->gid> gid) P = P->lc;
		else P = P->rc;
	}

	if(P==continents[cid]->sentinel){
		(continents[cid]->sentinel)->gid = -1; //Added last.
		return 0; //If the sentinel is reached the gid does not belong to the continent.
	}
	
	(continents[cid]->sentinel)->gid = -1; //setting the sentinels gid back to default value.

	//The that follows is the classic algorithm of deleting a node from a bs tree.
	if(P->lc == continents[cid]->sentinel && P->rc == continents[cid]->sentinel){
		if(Prev != NULL){
			if(Prev->lc == P){
				Prev->lc = continents[cid]->sentinel;
			}
			else Prev->rc = continents[cid]->sentinel;
		}
		else{
			continents[cid]->population_root = continents[cid]->sentinel;
		}
	}

	else if(P->lc == continents[cid]->sentinel || P->rc == continents[cid]->sentinel){
		if(Prev!=NULL){
			if(Prev->lc == P){
				if(P->lc!=continents[cid]->sentinel){
					Prev->lc = P->lc;
				}
				else Prev->lc = P->rc;
			}
			else{
				if(P->lc!=continents[cid]->sentinel){
					Prev->rc = P->lc;
				}
				else Prev->rc = P->rc;	
			}
		}
		else{
			if(P->lc !=continents[cid]->sentinel){
				continents[cid]->population_root = P->lc;		
			}
			else{
				continents[cid]->population_root = P->rc;
			}
		}
	}
	else{
		struct ContinentPopulation *S = P;
		struct ContinentPopulation *SPrev = P;

		S = S->lc;
		while(S!=continents[cid]->sentinel){
			SPrev = S;
			S = S->rc;
		}

		int tmpGid = SPrev->gid;
		
		if(!delete_continent_population(cid,SPrev->gid)) return 0;
		P->gid = tmpGid;


	}

	return 1;
}

/**
 * @brief Deletes every population of a species, and from the continent array too.
 */
void delete_all_populations(struct Population *p){ 
	if(p==NULL) return;
	delete_all_populations(p->lc);
	delete_all_populations(p->rc);
	delete_population_noprint(p->gid,p->sid);
}


/**
*
*  ***Evolution Functions***
*
*/

/**
 * @brief Traverses the species tree and adds all the species to the homo sapiens tree.
 */
void evolution_species(struct Species *p){
	if(p == NULL) return;
	insert_homoSapiens(p);
	evolution_species(p->lc);
	evolution_species(p->rc);
}

/**
 * @brief Counts the populations of a species.
 */
int countPopulations(struct Population *p){
	int count = 0;
	if(p == NULL) return 0;
	count+=countPopulations(p->lc);
	count+=countPopulations(p->rc);
	count++;
	return count;
}

/**
 * @brief Prints all the populations of homo sapiens species in the desired format.
 */
void print_homo_sapiens_populations(struct Population *p){
	if(p == NULL) return;
	print_homo_sapiens_populations(p->lc);
	printf("<%d,%d>,",p->gid,p->sid);
	print_homo_sapiens_populations(p->rc);	
}

/**
 * @brief Remaining species evolve into homo sapiens.
 *
 * @return 1 on success
 *         0 on failure
 */
int evolution(){
	
	if(Species_root == NULL){ //Error check to make sure that there are any species survived.
		printf("No species survived. Evolution has no point.\n");
		return 0;
	}

	//The next function is defined in the Evolution plug in. It adds all the species to the homo sapiens list.
	evolution_species(Species_root); 
	
	//The species tree should be empty after the evolution event.
	Species_root = NULL; //This is a fast way to do it. We could use remove species and delete population functions also.

	//Printing the demanded output.
	print_homo_sapiens();
	return 1;
}

/**
 * @brief Gather statistics on species from homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int species_statistics(){

	struct HomoSapiens *P = Homo_Sapiens_root; //Pointer to traverse the homo sapiens tree.
	struct HomoSapiens *L = NULL; //Pointer to the previous species of P.
	
	int count = 0; //The species counter.

	while(P!=NULL){ //Traverse the tree till the left leaf is found.
		L = P;
		P = P->lc;
	}

	printf("  Homo Sapiens:");
	
	//Traversing the species.
	while(L!=NULL){ 
		printf("<%d>",L->sid);
		if(L->next!=NULL) printf(",");
		count++;
		L = L->next; //Using the next pointers to procceed.
	}

	printf("\n  Homo Sapiens Species:<%d>\nDONE\n",count); //The demanded print.
	return 1;
}

/**
 * @brief Gather statistics on population belonging to species with ID <sid> from homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int population_statistics(int sid){

	struct HomoSapiens *P = Homo_Sapiens_root; //Pointer to traverse the tree.

	if(P == NULL){ //Error check.
		printf("The homo sapiens list is currently empty.\n");
		return 0; 
	}

	//Searching the tree in order to find the species to count it's populations.
	while(P!=NULL && P->rc!=NULL){ //Every node exceptp leafs have 2 childen, though we just need to check if only one of the child pointers are null.
		if(P->sid<sid) P = P->rc;
		else P = P->lc;
	}
	

	if(P->sid!= sid){
		printf("The species you seek do not belong to homo sapiens list.\n");
		return 0;
	}

	//Printing the demanded output.
	printf("  Homo Sapiens Popualtions:<%d>\nDONE\n",countPopulations(P->population_root));
	return 1;
}


/**
*
*  ***Printing Functions***
*
*/

/**
 * @brief Prints the species of the species tree.
 */
void showSpecies(struct Species *p){ 
	if(p == NULL) return;
	showSpecies(p->lc);
	showSpecies(p->rc);
	printf("<%d>",p->sid);
	if(p!=Species_root) printf(",");
}

/**
 * @brief Prints the gids of the populations of a specific species.
 */
void showPopulationsGids(struct Population *p){ 
	if(p == NULL) return;
	showPopulationsGids(p->lc);
	printf("<%d>,",p->gid);
	showPopulationsGids(p->rc);
}

/**
 * @brief Prints the sids of the species with their populations gids.
 */
void showSpeciesPopulationsGids(struct Species *p){   
	if(p == NULL) return;
	showSpeciesPopulationsGids(p->lc);
	showSpeciesPopulationsGids(p->rc);
	printf("  <%d>\n    ",p->sid);
	showPopulationsGids(p->population_root);
	printf("\b \n");
}

/**
 * @brief Prints the gids and the cids of the population of a specific species.
 */
void showPopulations(struct Population *p){
	if(p == NULL) return;
	showPopulations(p->lc);
	printf("<%d,%d>,",p->gid,p->cid);
	showPopulations(p->rc);
}

/**
 * @brief Prints sids of the species tree with ther populations gids and sids.
 */
void showSpeciesPopulations(struct Species *p){   
	if(p == NULL) return;
	showSpeciesPopulations(p->lc);
	showSpeciesPopulations(p->rc);
	printf("  <%d>\n    ",p->sid);
	showPopulations(p->population_root);
	printf("\b \n");
}

/**
 * @brief Print species' leaves list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_species(){

	if(Species_root == NULL) { //Error check.
		printf("The species tree is empty.\n"); //Error message.
		return 0;
	}

	//The demanding output.
	printf("  ");
	showSpecies(Species_root); //This is defined inside the plug in. Traverses the species tree.
	printf("\nDONE\n");
	
	return 1;
}

/**
 * @brief Print species' tree with population trees
 *
 * @return 1 on success
 *         0 on failure
 */
int print_populations(){

	if(Species_root == NULL){ //Error check.
		printf("The species tree is empty, thus there are no populations.\n");
		return 0;
	}

	showSpeciesPopulations(Species_root); //This is defined inside the plugin. Traverses the species tree and traversers every population tree of every node.

	printf("DONE\n");
	return 1;
}

/**
 * @brief Prints the continents in the desired format.
 */
void showContinents(struct ContinentPopulation *p){
	if(p->gid == -1) return;
	showContinents(p->lc);
	printf("<%d>,",p->gid);
	showContinents(p->rc);
}

/**
 * @brief Print continents array with each continent's population tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_continents_tabbed(){
	int i;
	for(i=0; i<5; i++){
		printf("  Continent %d: ",i);
		showContinents(continents[i]->population_root);
		printf("\b \n");
	}
	printf("DONE\n");
	return 1;
}

/**
 * @brief Prints a specific continent.
 */
int print_continent(int cid){
	printf("  Continent %d: ",cid);
	showContinents(continents[cid]->population_root);
	printf("\b \nDONE\n");
	return 1;
}

/**
 * @brief Print continents array with each continent's population tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_continents(){
	//No error check is needed. The continents are initialized when the programm starts.
	int i;
	for(i=0; i<5; i++){ //Printing the species of every continent.
		printf("Continent %d: ",i);
		showContinents(continents[i]->population_root); //This function traverses the continent tree and prints the population that belong to it.
		printf("\b \n");
	}
	printf("DONE\n");
	return 1;
}

/**
 * @brief Print homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_homo_sapiens(){
	
	struct HomoSapiens *P = Homo_Sapiens_root; //Pointer to traverse the homo sapiens tree.
	struct HomoSapiens *L = NULL; //Pointer to the previous node of P.
	if(P== NULL){ //Error check.
		printf("Homo sapiens tree is empty.\n");
		return 0;	
	} 

	//Traversing to find the left leaf of the tree.
	while(P!=NULL){
		L = P;
		P = P->lc;
	}

	printf("  Homo Sapiens:");

	//Then procceed using the next pointers of the tree.
	while(L!=NULL){
		printf("[");
		print_homo_sapiens_populations(L->population_root); //This function prints the populations of every species belonging to the homo sapiens tree.
		if(L->population_root == NULL) printf("[");
		printf("\b]");
		L = L->next;
	}

	printf("\nDONE\n");
	
	return 1;
}

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

				/* Lowest Common Ancestor
				 * L <sid> <gid1> <gid2> */
			 case 'L':
				{
					int sid, gid1, gid2;

					sscanf(buff, "%c %d %d %d", &event, &sid, &gid1, &gid2);
					DPRINT("%c %d %d %d\n", event, sid, gid1, gid2);

					if (lowest_common_ancestor(sid, gid1, gid2)) {
						DPRINT("%c %d %d %d succeeded\n", event, sid, gid1, gid2);
					} else {
						fprintf(stderr, "%c %d %d %d failed\n", event, sid, gid1, gid2);
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
				 * F */
			case 'F':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c \n", event);

					if (delete_species()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
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
