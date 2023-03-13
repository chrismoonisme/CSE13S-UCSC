#include "io.h"
#include "code.h"
#include "word.h"
#include "trie.h"
#include "endian.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>


#define OPTIONS "hi:o:v"

int bitlength(int x){

    int bits = 0;
    
    while (x > 0){
    
        bits++;
        
        x >>= 1;
        
    }
    
    return bits;
    
}

char *name;

int main(int argc, char **argv) {

  int infile = STDIN_FILENO;
  
  int outfile = STDOUT_FILENO;
  //FILE *outfile = stdout;
  //int inheader = STDIN_FILENO;
  
  int opt = 0;
  
  //stats toggle
  int v = 0;
  
  while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
  
    switch (opt) {
    
      case 'h': {

          printf("SYNOPSIS \n"); 
          printf("   Compresses files using the LZ78 compression algorithm. \n"); 
          printf("   Compressed files are decompressed with the corresponding decoder. \n"); 
          printf("\n"); 
          printf("USAGE \n"); 
          printf("   ./encode [-vh] [-i input] [-o output] \n"); 
          printf("\n"); 
          printf("OPTIONS \n"); 
          printf("   -v          Display compression statistics \n"); 
          printf("   -i input    Specify input to compress (stdin by default) \n"); 
          printf("   -o output   Specify output of compressed input (stdout by default) \n"); 
          printf("   -h          Display program usage \n");
          return 1;
      }
      
      case 'i': {

            infile = open(optarg, O_RDONLY);
            
            if(infile == -1){
            
              printf("bad file\n");
              return 1;
            
            }

            break;
      }
      
      case 'o': {

            outfile = open(optarg, O_WRONLY| O_CREAT | O_TRUNC, 0600);
            
            if(outfile == -1){
            
              printf("bad file\n");
              return 1;
            
            }
            
            break;
      }
      
      case 'v': {

            v = 1;
            break;
      }

    }
  
  }
  
  //-- code --
  
  //file header
  struct stat sbuf;
  
  fstat(infile, &sbuf);
  
  fchmod(outfile, sbuf.st_mode);
  
  FileHeader header = {0, 0};
  
  header.magic = MAGIC;
  
  header.protection = sbuf.st_mode;
  
  write_header(outfile, &header);
  
  //create root
  TrieNode *rootnode = trie_create();
  
  //current node
  TrieNode *currentnode = rootnode;
  
  //previous node
  TrieNode *prevnode = NULL;
  
  //symbols
  uint8_t currentsym = 0;
  
  uint8_t prevsym = 0;
  
  uint16_t nextcode = START_CODE;
  
  while(read_sym(infile, &currentsym)){
    //printf("among us");
    TrieNode *nextnode = trie_step(currentnode, currentsym);
    
    if(nextnode != NULL){
    
      prevnode = currentnode;
      
      currentnode = nextnode;
    
    }else{
    
      write_pair(outfile, currentnode->code, currentsym, bitlength(nextcode) );
      
      currentnode->children[currentsym] = trie_node_create(nextcode);
      
      currentnode = rootnode;
      
      nextcode++;
    
      if(nextcode == MAX_CODE){
    
        trie_reset(rootnode);
      
        currentnode = rootnode;
      
        nextcode = START_CODE;
    
      }
    
    }
    
    prevsym = currentsym;
  
  }
  
  if(currentnode != rootnode){
  
    write_pair(outfile, prevnode->code, prevsym, bitlength(nextcode) );
    
    nextcode++;
    
    nextcode = nextcode % MAX_CODE;
  
  }
  
  write_pair(outfile, STOP_CODE, 0, bitlength(nextcode));
  
  flush_pairs(outfile);
  
  close(infile);
  
  close(outfile);
  
  trie_delete(rootnode);
  
  return 0;

}
