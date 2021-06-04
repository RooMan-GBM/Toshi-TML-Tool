/*
File tml.h 
Created on: Wed 26 May 01:57:55 BST 2021
By: Ray
*/
#ifndef __TML_H__
#define __TML_H__

#define MAGIC 0x314C4D54
// This is frowned apon but I'm lazy
#pragma pack (1)
// Header
struct TmlHeader{
 // Magic number ("TML1")
 int magic;
 // unknown possibly padding or version (0x00)
 int unk;
 // Number of entries/files
 int count;
};
//File
struct TmlFile{
 // File ID (starts at zero)
 int id;
 // The size of the file
 int size;
 // Unknown
 char unk[10];
 // Image width
 short width;
 // Image height
 short height;
 // unknown (0xFFFF0000)
 int unk2;
 // unknown, assumed end flag (0x4300)
 short end;
 };
 // Simplified internal file infomation
 struct TmlBlock{
 // block name
 char name[32];
 // File ID
 int id;
 // Image width
 int width;
 // Image height
 int height;
 // precalculated absolute offset
 int offset;
 // file size
 int size;
 };
 
#endif

