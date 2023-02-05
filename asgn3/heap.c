#include "stats.h" 
#include <stdbool.h>

uint32_t max_child( Stats *stats, uint32_t *A, uint32_t first, uint32_t last){

	uint32_t left = 2 * first;
	
	uint32_t right = left + 1;

	if( right <= last && cmp(stats, A[right - 1], A[left - 1]) == 1 ){
	

	
		return right;
	}
	

	return left; 

}

void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last){

	bool found = false;
	
	uint32_t mother  = first;
	
	uint32_t great = max_child(stats, A,  mother, last);
	
	while(mother <= last/2  && found == false){
		
		
		if(cmp(stats, A[mother - 1], A[great - 1]) == -1){
			

		
			//uint32_t temp = A[mother -1];
			
			//A[mother -1] = A[great - 1];
			
			//A[great - 1] = temp;
			
			swap(stats, &A[mother-1], &A[great-1]);
			
			mother = great;
			
			great = max_child(stats, A, mother, last);
			
		}else{	
			

		
			found = true;
		
		}
	}

}

void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last){

	for(uint32_t father = last; father > first - 1; father = father-1){
		

		fix_heap(stats, A, father, last);
	
	}

}


void heap_sort(Stats *stats, uint32_t *A, uint32_t n){

	reset(stats);

	uint32_t first = 1;
	uint32_t last = n; 
	build_heap(stats, A, first, last);
	for(uint32_t leaf = last; leaf > first; leaf = leaf-1){
	
		//uint32_t temp = A[first -1];
		
		//A[first -1] = A[leaf - 1];
		
		//A[leaf-1] =temp;
		
		
		swap(stats, &A[first -1], &A[leaf-1]);
		
		fix_heap(stats, A, first, leaf - 1);
		
		
	}
}

