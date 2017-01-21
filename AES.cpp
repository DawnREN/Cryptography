// AES.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
/*
 S_box定义字节代替变换ByteSub的S盒
*/
int s_box[256] =
{ 0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16};

/*
 InverS_box定义字节代替变换的S盒的逆
*/
int Invers_box[256] =
{ 0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D};
const int rcon[10]=
{
	0x01,0x02,0x04,
    0x08,0x10,0x20,0x40,
    0x80,0x1B,0x36
};
int b[4][4]=
{
	0x02,0x03,0x01,0x01,
	0x01,0x02,0x03,0x01,
    0x01,0x01,0x02,0x03,
    0x03,0x01,0x01,0x02
};
int c[4][4]=
{
	0x0E,0x0B,0x0D,0x09,
    0x09,0x0E,0x0B,0x0D,
    0x0D,0x09,0x0E,0x0B,
    0x0B,0x0D,0x09,0x0E
};
/*字节替代*/
void SubBytes(int a[4][4],int s_box[256])/*s_box[256]是s盒*/
{
	int i,j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			a[i][j] =s_box[a[i][j]];
}
/*行移位和逆行移位*/
void ShiftRows(int a[4][4],int decrypt)
{
	int i,j,b;
	if(decrypt==0)
	{ /* 此时实现加密行移位功能 */
  
		for(i=1;i<4;i++)
		{ 
			if(i==1)
			{
				j=a[i][0];
                a[i][0]=a[i][1];
				a[i][1]=a[i][2];
				a[i][2]=a[i][3];
				a[i][3]=j;
			}
            if(i==2)
			{
				j=a[i][0];
				b=a[i][1];
		        a[i][0]=a[i][2];
		        a[i][1]=a[i][3];
                a[i][2]=j;
		        a[i][3]=b;
			}
            if(i==3)
			{ 
				j= a[i][3];
                a[i][3]=a[i][2];
                a[i][2]=a[i][1];
                a[i][1]=a[i][0];
                a[i][0]=j;
			}
		}
	}
    if(decrypt==1)
	{ /* 此时实现解密行移位功能 */
		for(i=1;i<4;i++)
		{ 
			if(i==1)
			{
				j=a[i][3];
                a[i][3]=a[i][2];
                a[i][2]=a[i][1];
                a[i][1]=a[i][0];
                a[i][0]=j;
			}
			if(i==2)
			{
				j=a[i][0];
                b=a[i][1];
                a[i][0]=a[i][2];
                a[i][1]=a[i][3];
                a[i][2]=j;
                a[i][3]=b;
			}
			if(i==3)
			{
				j=a[i][0];
                a[i][0]=a[i][1];
                a[i][1]=a[i][2];
                a[i][2]=a[i][3];
                 a[i][3]=j;
			}
		}
	}
}


/*列混合*/
void MixColumns(int a[4][4],int b[4][4]) /*b[4][4]为列混合时的固定矩阵*/
{
	int temp[4][4]={0};
	int d[3]={0x80,0x1B,0x02};
	int i,j,m,k;
	for(m=0;m<4;m++)
		for (i = 0; i<4;i++)
			for (j = 0;j<4;j++)
			{
				if(b[i][j]==1)
					temp[i][m]=a[j][m]^temp[i][m];
				else
					if(b[i][j]==2)
						if(a[j][m]<d[0])
							temp[i][m]=(b[i][j]*a[j][m])^temp[i][m];
						else
						{
							k=a[j][m]^d[0];
                            temp[i][m]=((b[i][j]*k)^d[1])^temp[i][m];
						}
					else
					{   
						if(a[j][m]<d[0])
							temp[i][m]=((a[j][m]*d[2])^a[j][m])^temp[i][m];
						else
						{
							k=a[j][m]^d[0];
		                    temp[i][m]=(((k*d[2])^d[1])^a[j][m])^temp[i][m];
						}
					}
			}
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					a[i][j]=temp[i][j];
}
/*与密钥异或*/
void AddRoundKey(int a[4][4],int roundKey[4][4])
{
	int i,j;
    for (i = 0;i < 4; i++)
		for (j = 0; j < 4; j++)
			a[i][j] = a[i][j] ^ roundKey[i][j];
}
/*密钥扩展 */
void KeyExpansion(int roundkey[4][4],int s_box[256], int temp[4][44])
{
	int i,j,n,m,a,b,x,y;
    int w[4],r[4],q[4];
    for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			temp[i][j]= roundkey[i][j];
		}
		for(i=4;i<44;i++)
		{ 
			a=i-4;b=i-1;
			if(i%4!=0)/*i不是4的倍数*/
			{
				for(j=0;j<4;j++)
					q[j]=temp[j][a]^temp[j][b];
				for(y=0;y<4;y++)
					temp[y][i]=q[y];
			}
            else
			{  
				for(x=0;x<4;x++)
					w[x]=temp[x][b];
                n = w[0]; /*左移一位*/
                w[0] = w[1];
                w[1] = w[2];
                w[2] = w[3];
                w[3] = n;
                for(j=0;j<4;j++)
					w[j]=s_box[w[j]];/*字节替代*/
				w[0]= rcon[(i-4)/4]^w[0];
				for(m=0;m<4;m++)
					r[m]=temp[m][a]^w[m];
				for(y=0;y<4;y++)
					temp[y][i]=r[y];
			}
		}
}
/*获取轮密钥*/
void GetRoundKey(int roundKey[4][4], int temp[4][44],int n)
{  
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			roundKey[i][j]=temp[i][j+4*n];
}
/*逆字节替代*/
void InvSubBytes(int a[4][4],int InverS_box[256])/* InverS_box[256]是逆S盒*/
{
	int i,j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			a[i][j] = InverS_box [a[i][j]];
}
/*逆列混乱*/
void InvMixColumns(int a[4][4],int c[4][4]) /*c[4][4]为逆列混合时的固定矩阵*/
{
	int temp[4][4]={0};
	int d[7]={0x80,0x1B,0x02,0x0e,0x0b,0x0d,0x09};
	int i,j,m,n,e,k,p,q,x,y;
	for(m=0;m<4;m++)
		for (i = 0; i<4;i++)
			for (j = 0;j<4;j++)
			{ 
				e=a[j][m];
				y=a[j][m];
				if(c[i][j]==d[3])
				{
					for(n=0;n<3;n++)
					{
						if(y<d[0])
							y=y*d[2];
						else
						{
							k=y^d[0];
		                    y=(k*d[2])^d[1];
						}
		                if(n==0)
						{
							p=y;
						}
		                else
			                if(n==1)
							{
								q=y;
							}
			                else
							{ 
								x=y;
							}
					}
	                temp[i][m]=p^q^x^temp[i][m];
				}
				if(c[i][j]==d[4])
				{
					for(n=0;n<3;n++)
					{
						if(y<d[0])
							y=y*d[2];
						else
						{
							k=y^d[0];
		                    y=(k*d[2])^d[1];
						}
		                if(n==0)
							q=y;
					    if(n==2)
							x=y;
					}
					temp[i][m]=e^q^x^temp[i][m];}
				if(c[i][j]==d[5])
				{
					for(n=0;n<3;n++)
					{
						if(y<d[0])
							y=y*d[2];
						else
						{
							k=y^d[0];
							y=(k*d[2])^d[1];
						}
						if(n==1)
							q=y;
						if(n==2)
							x=y;
					}
					temp[i][m]=e^q^x^temp[i][m];
				}
				if(c[i][j]==d[6])
				{
					for(n=0;n<3;n++)
					{
						if(y<d[0])
							y=y*d[2];
						else
						{
							k=y^d[0];
							y=(k*d[2])^d[1];
						}
					}
					temp[i][m]=e^y^temp[i][m];
				}
		}
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				a[i][j]=temp[i][j];
}


/*加密函数*/
void Encrypt(int a[4][4],int roundKey[4][4],int temp[4][44])
{
	int i,j,n;
	int decrypt = 0;
    AddRoundKey(a,roundKey);/* 轮密钥加*/
    for(n=1;n<=10;n++)
	{
		if(n==10)
		{
			SubBytes(a,s_box); /* 字节替代*/
			ShiftRows(a,decrypt); /*行移位*/
			GetRoundKey(roundKey,temp,n); /* 获取轮密钥*/
			AddRoundKey(a,roundKey); /* 轮密钥加*/
			FILE *stream;
			stream = fopen( "2.txt", "w" );
			for(i=0;i<4;i++)
			{ 
				for(j=0;j<4;j++)
				{
					fprintf(stream,"%x",a[i][j]);
				}
			}
			fclose(stream);
		}
        else
		{
			SubBytes(a,s_box); /* 字节替代*/
            ShiftRows(a,decrypt); /*行移位*/
            MixColumns(a,b); /* 列混合*/
			GetRoundKey(roundKey,temp,n); /* 获取轮密钥*/
            AddRoundKey(a,roundKey); /* 轮密钥加*/
		}
	}
}

/*解密函数*/
void Decrypt(int a[4][4],int roundKey[4][4],int temp[4][44])
{
	int i,j,n,m;
    int decrypt = 1;
    int r[10]={0,9,8,7,6,5,4,3,2,1};
    m=10;
	GetRoundKey(roundKey, temp,m);
    AddRoundKey(a,roundKey);
    for(n=1;n<=10;n++)
    {
		if(n==10)
		{ 
			ShiftRows(a,decrypt);
            InvSubBytes(a,Invers_box);
            m=0;
            GetRoundKey(roundKey, temp,m);
			AddRoundKey(a,roundKey);
            FILE *stream;
			stream = fopen( "3.txt", "w" );
            for(i=0;i<4;i++)
			{ 
				for(j=0;j<4;j++)
				{
					fprintf(stream,"%x",a[j][i]);
				}

			}
			fclose(stream);
		}
        else
		{ 
			ShiftRows(a,decrypt);
			InvSubBytes(a,Invers_box);
			m=r[n];
			GetRoundKey(roundKey, temp,m);
            AddRoundKey(a,roundKey);
            InvMixColumns(a,c);
			
		}
	}
}

void x()
{
	int i,j,n,m;
    int Temp[4][44]={0};
    int w[4][4],key[4][4],s[32],l[32];
    char o[32],k[32];
    char p[32],t[32];
	freopen("1.txt","r",stdin);//1.txt用来存放明文
	for(i=0;i<32;i++)
		p[i]='0';
    scanf("%s",o);
    for(i=0;o[i]!='\0';i++)
		p[i]=o[i];
    for(i=0;i<32;i++)
	{   
        if(p[i]<'a')
            s[i]=p[i]-'0';
	    else
			s[i]=10+(p[i]-'a');
	}
    for(n=0;n<32;n=n+2)
	{
		m=n/2;
        s[m]=s[n]*16+s[n+1];
	}
    for(i=0;i<4;i++)
       for(j=0;j<4;j++)
		   w[j][i]=s[j+i*4];

    freopen("KEY.txt","r",stdin);
	for(i=0;i<32;i++)
		t[i]='0';
    scanf("%s",k);
    for(i=0;k[i]!='\0';i++)
		t[i]=k[i];
    for(j=0;j<32;j++)
	{   
        if(t[j]<'a')
			l[j]=t[j]-'0';
		else
			l[j]=10+(t[j]-'a');
	}
    for(n=0;n<32;n=n+2)
	{
		m=n/2;
        l[m]=l[n]*16+l[n+1];
	}
    for(i=0;i<4;i++)
       for(j=0;j<4;j++)
           key[j][i]=l[j+i*4];
    KeyExpansion(key,s_box,Temp);
    Encrypt(w,key,Temp);
    Decrypt(w,key,Temp);
}
void main()
{
	x();
}
