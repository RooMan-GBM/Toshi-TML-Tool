/*
File: tml.c 
Created on: Wed 26 May 01:57:55 BST 2021
By: Ray
Brief: Extraction of .TML (Toshi Material Library) files.
TODO: Export files [I]
TODO: Convert to BMP for 16 [N]
TODO: Import files [N]
*/

#include <stdio.h>
#include <stdlib.h>
#include "tml.h"

int main(int argc,char *argv[]){
 FILE *fp;
 int fCount;
 struct TmlHeader Header;
 struct TmlFile File;
 struct TmlBlock* Block;
 // Check arguments
 if(argc<=1){
  printf("Usage: tml [options] [file]\n");
  return 1;
 }
 // Assuming the last argument is the TML file
 fp=fopen(argv[argc-1],"rb");
 // check for existing file
 if(NULL==fp){
  return 1;
 }
 // Read file header
 fread(&Header,sizeof(struct TmlHeader),1,fp);
 // Check magic number (0x314C4D54(le) / "TML1")
 if(Header.magic!=MAGIC){
  return 1;
 }
 // Allocate memory for file blocks
 Block=malloc(sizeof(struct TmlBlock)*Header.count);
 // Read the block header
 for(int i=0;i<Header.count;i++){
  fread(&File,sizeof(struct TmlFile),1,fp);
  Block[i].id=i;
  Block[i].size=File.size;
  Block[i].offset=(int)ftell(fp);
  Block[i].width=File.width;
  Block[i].height=File.height;
  // Jump to next block header
  fseek(fp,(long)File.size,SEEK_CUR);
 }
 // Read the total block name count (seems redundant BT)
 fread(&fCount,sizeof(int),1,fp);
 // Read the block names (written in desending order)
 for(int i=fCount;i>0;i--){
  fread(&Block[i-1].name,32,1,fp);
 }
 return 0;
}

