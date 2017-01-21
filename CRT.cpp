
#include"base.h"
//解方程ax=b(mod m),并返回其中一个解
Num modequa(Num a, Num b, Num m)
{

	Num n1, gc, z;
	gc = gcd(a, m);
	z = b%gc;
	if (z != 0) { cout << "同余式无解！" << endl; return NULL; }
	Num k1, k2, x0, x1;
	k1 = a / gc; k2 = m / gc;
	x0 = mulinverse(k1, k2);
	z = b / gc;
	x1 = (x0*z + k2) % k2;
	return x1;
}

//用中国剩余定理解形如x=b1(mod m1),x=b1(mod m1),x=b1(mod m1)的方程组，其中m1,m2,m3间两年互素
Num modequas(int k, Num bb[], Num mm[])
{
	int k1, k2;
	for (k2 = 0, k1 = 0; k1<k; k1++)
		for (k2 = k1 + 1; k2<k; k2++)
			if (gcd(mm[k1], mm[k2]) != 1) { cout << "m不两两互素，无解"; return NULL; }

	Num *M, *MM;  	M = new Num[k];  MM = new Num[k];
	for (k1 = 0; k1<k; k1++)M[k1] = 1;
	for (k1 = 0; k1<k; k1++)  //求Mi   
		for (k2 = 0; k2<k; k2++)
			if (k1 != k2) M[k1] = M[k1] * mm[k2];
	for (k1 = 0; k1<k; k1++)
		MM[k1] = mulinverse(M[k1], mm[k1]);  //求Mi的逆

	Num jx, MMM;
	MMM = 1;
	for (k1 = 0; k1<k; k1++) MMM = MMM*mm[k1];
	for (k1 = 0; k1<k; k1++) jx = (jx + MM[k1] * M[k1] * bb[k1]) % MMM;  //最后的结果
	return jx;
}

//解模p的平方根，其中p为基素数
Num tworesidue(Num a, Num p)
{
	Num a1, p1, n, b, n3;
	p1 = p - 1;
	if (modexpon(a, p1 / 2, p) != 1) { cout << "原二次同于式无解!"; return NULL; }

	if (p % 4 == 3)return modexpon(a, (p + 1) / 4, p);//p=4k+3的情况

	int t;
	for (t = 0; p1 % 2 == 0;) { ++t; p1 = p1 / 2; }   //求s和t
	Num s;   s = p1;

	for (n = 3;; n = n + 2)   //求非剩余n
		if (modexpon(n, p1 / 2, p) != 1)break;

	b = modexpon(n, s, p);   //求b
	a1 = mulinverse(a, p);  //求a的逆元

	Num *x;   x = new Num[t];
	x[t - 1] = modexpon(a, (s + 1) / 2, p);
	if (t == 1)return x[0];

	int i, j = 1;
	Num z, zz, y, bb, m0;
	for (int k = 1; k <= t - 1; k++)
	{
		for (i = 1, zz = 1; i<k; i++)zz = zz * 2;
		for (bb = 1, m0 = 0; m0<zz; m0 = m0 + 1)bb = bb*b;
		for (i = 1, z = 1; i<t - k; i++)z = z * 2;
		if (modexpon(a1*x[t - k] * x[t - k], z, p) == 1)x[t - k - 1] = x[t - k];
		else x[t - k - 1] = x[t - k] * bb%p;
	}
	return x[0];
}
