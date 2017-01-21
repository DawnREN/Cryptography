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
	friend istream &operator>>(istream &input, Num &num);   //插入流重载        
	friend ostream &operator<<(ostream &output, Num &num);
	friend Num random(int Len);//随机数生成函数
private:
	int tag;////正负标记
	int length;
	char str[MaxSize];
};

//有关函数的声明
Num mulinverse(Num, Num);
Num sqrt(Num);
Num modexpon(Num, Num, Num);
Num gcd(Num, Num);


#endif

