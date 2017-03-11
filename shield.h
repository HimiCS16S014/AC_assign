#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <stdint.h>

#define keysize 64
#define nbytes keysize/8
#define round 10
#define row sqrt(nbytes)
#define ROTL16(x,shift) ((uint16_t) ((x) << (shift)) | ((x) >> (16 - (shift))))
#define ROTR16(x,shift) ((uint16_t) ((x) >> (shift)) | ((x) << (16 - (shift))))


void init_pt();
void print_segment();
void encryption();
void fiestel_func(int r);
void fiestel_xor();
void store();
void AddroundKey(int r);	
void SubByte();
void perm();
uint8_t SubstituteByte(int x);
uint8_t f1(uint8_t s1, uint8_t s2);
uint8_t f2(uint8_t s1, uint8_t s2);
uint8_t f3(uint8_t s1, uint8_t s2);
uint8_t f4(uint8_t s1, uint8_t s2);


	