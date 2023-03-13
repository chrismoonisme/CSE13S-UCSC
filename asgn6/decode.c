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
  FileHeader header = {0, 0};

  read_header(infile, &header);
  
  WordTable *table = wt_create();
  
  uint8_t currentsym = 0;
  
  uint16_t currentcode = 0;
  
  uint16_t nextcode = START_CODE;
  
  while(read_pair(infile, &currentcode, &currentsym, bitlength(nextcode))){
  
    table[nextcode] = word_append_sym(table[currentcode], currentsym);
    
    write_word(outfile, table[nextcode]);
    
    nextcode++;
    
    if(nextcode == MAX_CODE){
    
      wt_reset(table);
      nextcode = START_CODE;
    
    }
    
  }
  flush_words(outfile);
  close(outfile);
  
  close(infile);
  
  wt_delete(table);
  //printf("among us\n");
  
  return 0;

}
