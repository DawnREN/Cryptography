#ifndef	BASE_H
#define	BASE_H 1

#include<cstdlib>
#include<cstdio>
#include<string>
#include<iostream>
#include<ctime>
#include<cmath>
using namespace std;

#define MaxSize 200


class Num
{
public:
	Num();
	Num(int n);
	Num operator+(Num &num);
	Num operator+(int n);
	Num operator-(Num &num);
	Num operator-(int n);
	Num operator*(Num &num);
	Num operator*(int n);
	Num operator/(Num &num);
	Num operator/(int n);
	Num operator%(Num &num);
	Num operator%(int n);
	Num operator=(int n);
	Num operator++();
	Num operator++(int);
	Num operator--();
	Num operator--(int);
	bool operator>(Num &num);
	bool operator>(int n);
	bool operator>=(Num &num);
	bool operator>=(int n);
	bool operator<(Num &num);
	bool operator<(int n);
	bool operator<=(Num &num);
	bool operator<=(int n);
	bool operator==(Num &num);
	bool operator==(int n);
	bool operator!=(Num &num);
	bool operator!=(int n);
	friend istream &operator>>(istream &input, Num &num);   //����������        
	friend ostream &operator<<(ostream &output, Num &num);
	friend Num random(int Len);//��������ɺ���
private:
	int tag;////�������
	int length;
	char str[MaxSize];
};

//�йغ���������
Num mulinverse(Num, Num);
Num sqrt(Num);
Num modexpon(Num, Num, Num);
Num gcd(Num, Num);


#endif

