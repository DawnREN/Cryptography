// Enigma.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <ctype.h>
FILE *stream;

char rotor[5][27];//转轮密码映射表
char ref[27];//反射板
char notch[6]="QEVJZ"; //参考值
int flag=0;


int order[3]; //转轮摆放顺序
char rings[3]={ 'W','X','T' };
char pos[3];
char plug[12];    //连接板，最多可以有6对

void Rotate(char ch)
{
	    int i ,j;
        pos[0]++;        //第一个转轮转动
        if (pos[0]>'Z')
            pos[0] -= 26;

        if (flag)   //当p[1]到达参考值时p[1]和p[2]同时开始转动
        {
           /* pos[1]++;
            if (pos[1]>'Z')
                pos[1] -= 26;
				*/
            pos[2]++;
            if (pos[2]>'Z')
                pos[2] -= 26;
            flag=0;
        }

        if (pos[0]==notch[order[0]-1]) //p[0]到达参考值时p[1]开始转动
        {
            pos[1]++;
            if (pos[1]>'Z')
                pos[1] -= 26;
            if (pos[1]==notch[order[1]-1])
                flag=1;
        }

        for (i=0; plug[i]; i+=2) //连接板进行交换
        {
            if (ch==plug[i])
                ch=plug[i+1];
            else if (ch==plug[i+1])
                ch=plug[i];
        }

        for (i=0; i<3; i++)    //正向通过转轮
        {
            ch += pos[i]-'A';
            if (ch>'Z')
                ch -= 26;

            ch -= rings[i]-'A';
            if (ch<'A')
                ch += 26;

            ch=rotor[order[i]-1][ch-'A'];

            ch += rings[i]-'A';
            if (ch>'Z')
                ch -= 26;


            ch -= pos[i]-'A';
            if (ch<'A')
                ch += 26;

        }

        ch=ref[ch-'A'];   //通过反射器

        for (i=3; i; i--)   //反向通过转轮
        {
            ch += pos[i-1]-'A';
            if (ch>'Z')
                ch -= 26;

            ch -= rings[i-1]-'A';
            if (ch<'A')
                ch += 26;

            for (j=0; j<26; j++)
                if (rotor[order[i-1]-1][j]==ch)
                    break;
            ch=j+'A';

            ch += rings[i-1]-'A';
            if (ch>'Z')
                ch -= 26;

            ch -= pos[i-1]-'A';
            if (ch<'A')
                ch += 26;

        }
         //反向通过连接器
        for (i=0; plug[i]; i+=2)
        {
            if (ch==plug[i])
                ch=plug[i+1];
            else if (ch==plug[i+1])
                ch=plug[i];
        }
            putchar(ch);
			//fprintf(stream,"%c",ch);  //输出
}
void main()
{
    int i, j;      //循环变量
    int n=0;      //输出字符计数
    int ch;
    printf("Please enter the rotors\n");//读入转子
    gets(rotor[0]);
    gets(rotor[1]);
    gets(rotor[2]);
	printf("Please enter the Reflector\n");//读入反射器
    gets(ref);
	printf("Please enter the connecting plant\n");
	gets(plug);
	printf("Please enter the order\n");
	scanf("%d %d %d",&order[0],&order[1],&order[2]);
	getchar();
    printf("Please enter the initial value\n");
	gets(pos);
	printf("Please enter the Plaintext or the Ciphertext\n");
    while((ch=getchar())!=EOF) //获取键盘字符
    {
        ch=toupper(ch);  //变成大写字母
        if (!isalpha(ch)) //判断是否为英文字母，Enigma上只有26个字母，没其他字符
            continue;
		Rotate(ch);

    }
}
