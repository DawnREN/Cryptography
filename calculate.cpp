#include"base.h"
//#include<randomize.h>

//��b����ģm�ĳ˷���Ԫ
Num mulinverse(Num b, Num m)
{
	b = (b%m + m) % m;///��֤bΪ����
	Num a1, a2, a3, b1, b2, b3, q, t1, t2, t3;
	a1 = 1; a3 = m; b2 = 1; b3 = b;  //��ʼ��a2=0,b1=0;
	while (b3 != 0 && b3 != 1)
	{
		q = a3 / b3;
		t1 = a1 - q*b1;
		t2 = a2 - q*b2;
		t3 = a3 - q*b3;
		a1 = b1; a2 = b2; a3 = b3;
		b1 = t1; b2 = t2; b3 = t3;
	}
	if (b3 == 1) { if (b2>0) return b2; else return b2 + m; }
	else { cout << b << "����ģ" << m << "�ĳ˷���Ԫ������"; exit(1); }
}

//���ö��ֲ��ҵ�˼���n2��ƽ��
Num sqrt(Num n)
{
	Num n1, n2, n12, n3;
	n1 = 1; n2 = n;
	while (n1 <= n2)
	{
		n12 = (n1 + n2) / 2;
		n3 = n12*n12;
		if (n3>n&&n2>n12)n2 = n12;
		else if (n3<n&&n1<n12)n1 = n12;
		else break;
	}
	return n12;

}

Num gcd(Num a, Num b)  //�����Լ��
{
	if (b == 0)return a;
	if (a == b)return 1;
	Num n(1);
	while (n != 0)
	{
		n = a%b;
		a = b;
		b = n;
	}
	return a;
}



//�����Ϊa,ָ��Ϊb2����ģm����
Num modexpon(Num a, Num b2, Num m)
{
	Num f, b1[MaxSize];
	f = 1;
	int i = 0;
	while (b2 != 0)//��ָʮ����ָ��ת���ɶ�����
	{
		b1[i] = b2 % 2;
		b2 = b2 / 2;
		i++;
	}
	for (i = i - 1; i >= 0; i--)//����
	{
		f = (f*f) % m;
		if (b1[i] == 1)f = (f*a) % m;

	}
	return f;
}


