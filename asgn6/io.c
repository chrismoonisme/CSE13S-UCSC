#include "io.h"
#include "endian.h"
#include "word.h"
#include "code.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//initialize externs
uint64_t total_syms = 0;
uint64_t total_bits = 0;

//-- symbol buffer --
static uint8_t cbuf[BLOCK];
static int c = 0;

//-- bit buffer --
static uint8_t bbuf[BLOCK];
static int b = 0;

//READ BYTES
int read_bytes(int infile, uint8_t *buf, int to_read){

  int bytesread = 0;
  
  int val = 1; 
	
  //while total bytesread is not nbytes and read() doesnt return 0
  while(bytesread != to_read && val != 0){
	
    //run read()
    val = read(infile, buf + bytesread, to_read - bytesread);
		
    //add the result of read to total bytes read
    bytesread+= val;
    
  }
	
  return bytesread; 

}

//WRITE BYTES
int write_bytes(int outfile, uint8_t *buf, int to_write){

  int byteswritten = 0;
  int val = 1; 
	
  while(byteswritten != to_write && val > 0){
	
    val = write(outfile, buf + byteswritten, to_write - byteswritten);
    
    byteswritten += val;
	
  }
	
  return byteswritten;
  
}

//READ HEADER
void read_header(int infile, FileHeader *header){

  //reads in sizeof(fileheader) bytes from infile
  read_bytes(infile, (uint8_t *)header, sizeof(FileHeader) );
  
  //if not little endian, swap endianness
  if(little_endian() == false){
  
    header->magic = swap32(header->magic);
    
    header->protection = swap16(header->protection);
  
  }
  
  if (header->magic != MAGIC) {
  
    fprintf(stderr, "bad magic number\n");
    
    exit(1);
    
  }
  
}

//WRITE HEADER
void write_header(int outfile, FileHeader *header){

  if (little_endian() == false){
  
        header->magic = swap32(header->magic);
        
        header->protection = swap16(header->protection);
        
  }
  
  write_bytes(outfile, (uint8_t *)header, sizeof(FileHeader) );
  
}

//READ SYM
bool read_sym(int infile, uint8_t *sym){

    static int end = -1;
    
    if(c == 0){
    
      int read  = read_bytes(infile, cbuf, BLOCK);
      
      if(read < BLOCK){
      
        end = read +1;
      
      }
    
    }
    
    *sym = cbuf[c];
    c++;
    
    //reset if end of block is reached
    if(c == BLOCK){
    
      c = 0;
    
    }
    
    if(c == end){
    
      return false;
    
    }
    
    return true;
    
}

void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen){
  
  //loop through code
  for(int i = 0; i < bitlen; i++){
  
    //if set
    if(((code >> i) & 1) == true){
      
      //set
      bbuf[b / 8] |= (1 <<(b %8));
      
    }else{
      
      //clear
      bbuf[b / 8] &= ~(1 <<(b %8));
      
    }
    
    b++;
    
    if(b/8 == BLOCK){
    
      write_bytes(outfile, bbuf, BLOCK);
      
      b = 0;
    
    }
    
  }
  
  //loop through symbol
  for(int i = 0; i < 8; i++){
  
    //if set
    if(((sym >> i) & 1) == true){
      
      //set
      bbuf[b / 8] |= (1 <<(b %8));
      
    }else{
      
      //clear
      bbuf[b / 8] &= ~(1 <<(b %8));
      
    }
    
    b++;
    
    if(b/8 == BLOCK){
    
      write_bytes(outfile, bbuf, BLOCK);
      
      b = 0;
    
    }
    
  }
  
}

int convert(int x){

  if(x % 8 == 0){
    
    return x/8;
  
  }else{
  
    return (x/8) + 1;
  
  }

}

//FLUSH PAIR
void flush_pairs(int outfile){
    
  
  if(b != 0){
    
    write_bytes(outfile, bbuf, convert(b));
  
  }

}

//READ PAIR
bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen){

  *code = 0;
  *sym = 0;
  
  //loop through code
  for(int i = 0; i < bitlen; i++){
    
    //read when empty
    if(b == 0){
      
      read_bytes(infile, bbuf, BLOCK);
    
    }
    
    //check if bit i of code is set or not
    if(((bbuf[b / 8] >> (b % 8)) & 1) == true){
      //set
      *code |= (1 << i);
    
    }else{
      //clear
      *code &= ~(1 << i);
    
    }
    
    b++;
    
    //reset block when end is reached
    if(b/8 == BLOCK){
    
      flush_pairs(infile);
      
      b = 0;
    
    }
  
  }
  
  //loop through symbol
  for(int i = 0; i < 8; i++){
    
    //read when empty
    if(b == 0){
      
      read_bytes(infile, bbuf, BLOCK);
    
    }
    
    //check if bit i of code is set or not
    if(((bbuf[b / 8] >> (b % 8)) & 1) == true){
      //set
      *sym |= (1 << i);
    
    }else{
      //clear
      *sym &= ~(1 << i);
    
    }
    
    b++;
    
    //reset block when end is reached
    if(b/8 == BLOCK){
    
      flush_pairs(infile);
      
      b = 0;
    
    }
  
  }
  
  if(*code == STOP_CODE){
  
    return false;
  
  }
  
  return true;

}

//WRITE WORD
void write_word(int outfile, Word *w){

  for(int i = 0; i< w->len; i++){
  
    cbuf[c] = w->syms[i];
    
    c++;
    
    if(c == BLOCK){
    
      write_bytes(outfile, cbuf, BLOCK);
      
      c = 0;
    
    }
  
  }

}

//FLUSH WORDS
void flush_words(int outfile){

  if(c > 0){
    
    write_bytes(outfile, cbuf, c);
  
  }

}

