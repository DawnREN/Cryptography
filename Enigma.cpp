// Enigma.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <ctype.h>
FILE *stream;

char rotor[5][27];//ת������ӳ���
char ref[27];//�����
char notch[6]="QEVJZ"; //�ο�ֵ
int flag=0;


int order[3]; //ת�ְڷ�˳��
char rings[3]={ 'W','X','T' };
char pos[3];
char plug[12];    //���Ӱ壬��������6��

void Rotate(char ch)
{
	    int i ,j;
        pos[0]++;        //��һ��ת��ת��
        if (pos[0]>'Z')
            pos[0] -= 26;

        if (flag)   //��p[1]����ο�ֵʱp[1]��p[2]ͬʱ��ʼת��
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

        if (pos[0]==notch[order[0]-1]) //p[0]����ο�ֵʱp[1]��ʼת��
        {
            pos[1]++;
            if (pos[1]>'Z')
                pos[1] -= 26;
            if (pos[1]==notch[order[1]-1])
                flag=1;
        }

        for (i=0; plug[i]; i+=2) //���Ӱ���н���
        {
            if (ch==plug[i])
                ch=plug[i+1];
            else if (ch==plug[i+1])
                ch=plug[i];
        }

        for (i=0; i<3; i++)    //����ͨ��ת��
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

        ch=ref[ch-'A'];   //ͨ��������

        for (i=3; i; i--)   //����ͨ��ת��
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
         //����ͨ��������
        for (i=0; plug[i]; i+=2)
        {
            if (ch==plug[i])
                ch=plug[i+1];
            else if (ch==plug[i+1])
                ch=plug[i];
        }
            putchar(ch);
			//fprintf(stream,"%c",ch);  //���
}
void main()
{
    int i, j;      //ѭ������
    int n=0;      //����ַ�����
    int ch;
    printf("Please enter the rotors\n");//����ת��
    gets(rotor[0]);
    gets(rotor[1]);
    gets(rotor[2]);
	printf("Please enter the Reflector\n");//���뷴����
    gets(ref);
	printf("Please enter the connecting plant\n");
	gets(plug);
	printf("Please enter the order\n");
	scanf("%d %d %d",&order[0],&order[1],&order[2]);
	getchar();
    printf("Please enter the initial value\n");
	gets(pos);
	printf("Please enter the Plaintext or the Ciphertext\n");
    while((ch=getchar())!=EOF) //��ȡ�����ַ�
    {
        ch=toupper(ch);  //��ɴ�д��ĸ
        if (!isalpha(ch)) //�ж��Ƿ�ΪӢ����ĸ��Enigma��ֻ��26����ĸ��û�����ַ�
            continue;
		Rotate(ch);

    }
}
