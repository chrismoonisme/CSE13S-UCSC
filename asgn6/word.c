#include "code.h"
#include "word.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//constructor
Word *word_create(uint8_t *syms, uint32_t len){
  
  //allocate mem for word
  Word *word = (Word *) malloc(sizeof(Word));
  
  if(word){

    //set length
    word->len = len;
    
    word->syms = syms;
    
    //printf("among us\n");
  
  }else{
  
    free(word);
    
    word = NULL;
    
  }
  
  return word;

}

//create a word thats a word + one other symbol
Word *word_append_sym(Word *w, uint8_t sym){
  
  //allocate array, of +1 length
  uint8_t *arr = (uint8_t *)calloc(w->len+1, sizeof(uint8_t) );
  
  if(w->syms != NULL){
  
    //copy values from the original word's array into the new array, the last value should be null
    for(int i =0; i< w->len; i++){
      
      arr[i] = w->syms[i];

    }
  
  }
  
  Word *w2 = word_create(arr, w->len+1);
    
  //set final value in the array to the new symbol that should be appended
  w2->syms[w->len] = sym;
    
  //free(arr);
    
  //arr = NULL;
  
  return w2;
  
}

//delete a word
void word_delete(Word *w){

  if(w->syms != NULL){
  
    free(w->syms);
    
    w= NULL;
  
  }
  
  free(w);
  
  w = NULL;

}

//create a word table
WordTable *wt_create(void){

  WordTable *table = (WordTable *) calloc(MAX_CODE, sizeof(WordTable) );
  
  uint8_t *empty = {NULL};
  
  table[EMPTY_CODE] = word_create(empty, 0);
  
  return table;
    
}

//deletes all words in the array except at EMPTY_CODE
void wt_reset(WordTable *wt){

  for(int i = 0; i < MAX_CODE; i++){
  
    if(i != EMPTY_CODE){
    
      wt[i] = NULL;
      
    }
    
  }

}

//deletes all words, and the table
void wt_delete(WordTable *wt){

  for(int i = 0; i < MAX_CODE; i++){
  
    if(wt[i] != NULL){
    
      word_delete(wt[i]);
      wt[i] = NULL;
    
    }
    
  }
  
  free(wt);
  
  wt = NULL;

}


