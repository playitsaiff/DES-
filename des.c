#include<stdio.h>
int round_keys[17][49];
static const int DesInitial[64] = {
   58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
   62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
   57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
   61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7
 };
 //des expansion box
 static const int DesExpansion[48] = {
    32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
    8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
   16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
   24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};
 //des s boxes
 static const int DesSbox[8][4][16] = {
  {
   {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
   { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
   { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
   {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
   },
   {
   {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
   { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
   { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
   {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
  },
    {
   {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
   {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
   {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
   { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
   },
   {
   { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
   {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
   {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
   { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
   },
   {
   { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
   {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
   { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
   {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
   },
   {
   {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
   {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
   { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
   { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
   },
   {
   { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
  {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
   { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
   { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
   },
   {
   {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
   { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
   { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
   { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
   },
 };
static const int DesPbox[32] = {
   16,  7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
    2,  8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25
 };
static const int DesFinal[64] = {
    40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
   38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
   36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
   34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25
 };
//key generation function
key_generator(int key[])
{
int key_without_parity[57],left_key[29],right_key[29],count=1,i,j,temp[57],t,u,k;
//shift table generation
static const int shift_table[16] = {
  1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
 };
//permutation of keys table
static const int parity_permutation[56] = {
   57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
 };
//compression from 56 bit to 48 bit table
static const int keycompress[48] = {
   14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
 };
//parity permutation
for(i=0;i<56;i++)
{
	key_without_parity[i+1]=key[(parity_permutation[i])-1];
}
//splitting keys
for(i=1;i<=28;i++)
{
	left_key[i]=key_without_parity[i];
	right_key[i]=key_without_parity[i+28];
}
//generating round keys
for(i=0;i<16;i++)
{
	for(j=1;j<=shift_table[i];j++)
	{
		t=left_key[1];
		u=right_key[1];
		for(k=2;k<=28;k++)
		{
			right_key[k-1]=right_key[k];
			left_key[k-1]=left_key[k];
		}
		right_key[28]=u;
		left_key[28]=t;
	}
	//combining the splitted keys
	for(j=1;j<=56;j++)
	{
		if(j<=28)
		{
		key_without_parity[j]=left_key[j];
		}
		else
			key_without_parity[j]=right_key[j-28];
	}
	//permutate to 56 bits to 48 bits
	for(j=0;j<48;j++)
	{
	round_keys[i+1][j+1]=key_without_parity[keycompress[j]];
	}
}
}
encryption(int message[])
{
	int i,j,ip[65],left[33],right[33],rnew[49],row,colomn;
	int out,right1[33],out_right[33],left1[33],encrypted_code[65],decrypted_code[65];
   //encryption
 //initial permutation
for(i=0;i<64;i++)
{
	ip[i+1]=message[DesInitial[i]-1];
}
//breaking in left and right
for(i=1;i<=32;i++)
{
	left[i]=ip[i];
	right[i]=ip[i+32];
}
for(i=1;i<=16;i++)
{
	//mixer
	for(j=1;j<=48;j++)
	{
		//expanding from 32 to 48 bits
		rnew[j]=right[DesExpansion[j-1]];
	}
	//xor with keys
	for(j=1;j<=48;j++)
	{
		rnew[j]=rnew[j]^round_keys[i][j];
	}
	//s box operation on right of plain text
	for(j=0;j<8;j++)
	{
		row=2*rnew[j*6+1]+rnew[j*6+6];
		colomn=8*rnew[j*6+2]+4*rnew[j*6+3]+2*rnew[j*6+4]+rnew[j*6+5];
		out=DesSbox[j][row][colomn];
		right1[j*4+1]=out/8;
		out=out%8;
		right1[j*4+2]=out/4;
		out=out%4;
		right1[j*4+3]=out/2;
		out=out%2;
		right1[j*4+4]=out;
	}
	//des p box substitution
	for(j=1;j<=32;j++)
	{
		out_right[j]=right1[DesPbox[j-1]];
	}
	for(j=1;j<=32;j++)
	{
		left1[j]=left[j]^out_right[j];
	}
	for(j=1;j<=32;j++)
	{
		left[j]=right[j];
		right[j]=left1[j];
	}
}
for(j=1;j<=32;j++)
		{
			ip[j]=right[j];
			ip[j+32]=left[j];
		}
for(j=1;j<=64;j++)
{
	encrypted_code[j]=ip[DesFinal[j-1]];
}
printf("encrypted_code");
for(j=1;j<=64;j++)
{
	printf("%d",encrypted_code[j]);
}
printf("\n");
}
decrytpion(int message[])
{
	int i,j,ip[65],left[33],right[33],rnew[49],row,colomn;
	int out,right1[33],out_right[33],left1[33],encrypted_code[65],decrypted_code[65];
//initial permutation
for(i=0;i<64;i++)
{
	ip[i+1]=encrypted_code[DesInitial[i]];
}
//breaking in left and right
for(i=1;i<=32;i++)
{
	left[i]=ip[i];
	right[i]=ip[i+32];
}
for(i=1;i<=16;i++)
{
	//mixer
	for(j=1;j<=48;j++)
	{
		//expanding from 32 to 48 bits
		rnew[j]=right[DesExpansion[j-1]];
	}
	//xor with keys
	for(j=1;j<=48;j++)
	{
		rnew[j]=rnew[j]^round_keys[17-i][j];
	}
	//s box operation on right of plain text
	for(j=0;j<8;j++)
	{
		row=2*rnew[j*6+1]+rnew[j*6+6];
		colomn=8*rnew[j*6+2]+4*rnew[j*6+3]+2*rnew[j*6+4]+rnew[j*6+5];
		out=DesSbox[j][row][colomn];
		right1[j*4+1]=out/8;
		out=out%8;
		right1[j*4+2]=out/4;
		out=out%4;
		right1[j*4+3]=out/2;
		out=out%2;
		right1[j*4+4]=out;
	}
	//des p box substitution
	for(j=1;j<=32;j++)
	{
		out_right[j]=right1[DesPbox[j-1]];
	}
	for(j=1;j<=32;j++)
	{
		left1[j]=left[j]^out_right[j];
	}
	for(j=1;j<=32;j++)
	{
		left[j]=right[j];
		right[j]=left1[j];
	}
}
for(j=1;j<=32;j++)
		{
			ip[j]=right[j];
			ip[j+32]=left[j];
		}
for(j=1;j<=64;j++)
{
	decrypted_code[j]=ip[DesFinal[j-1]];
}
printf("decrypted_code");
for(j=1;j<=64;j++)
{
	printf("%d",decrypted_code[j]);
}
printf("\n");
}

int main()
{
	int key[64],message[64];
 int i,j,x,y;
 printf("enter the  64 bit key with parity bits in 4  bits  in decimal form");
 for ( i = 0; i<16; i++)
 {
 	scanf("%d",&x);
 	key[i*4]=x/8;
 	x=x%8;
 	key[i*4+1]=x/4;
 	x=x%4;
 	key[i*4+2]=x/2;
 	x=x%2;
 	key[i*4+3]=x;
 }
  printf("enter the 64 bit message in 4  bits  in decimal form");
 for ( i = 0; i<16; i++)
 {
 	scanf("%d",&x);
 	message[i*4]=x/8;
 	x=x%8;
 	message[i*4+1]=x/4;
 	x=x%4;
 	message[i*4+2]=x/2;
 	x=x%2;
 	message[i*4+3]=x;
 } 
key_generator(key);
encryption(message);
decrytpion(message);
return 0;
}
