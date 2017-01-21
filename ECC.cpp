#include"ECC.h"
ECC::ECC()
{
	p = 751;
	a4 = -1;
	a6 = 188;
	g.x = 0;
	g.y = 376;
	pk.x = 201;
	pk.y = 5;
	k = 386;

}

ECC::ECC(Num p)
{
	this->p = p;
}

ECC::ECC(Num p, Num a4, Num a6)
{
	this->p = p;
	this->a4 = a4;
	this->a6 = a6;
}
zb ECC::add1(zb a, int kk)//形如K=kG的加法
{
	zb *aa;
	aa = new zb[kk + 10];
	if (aa == NULL) { cout << "内存分配失败!" << endl; exit(1); }
	Num e1, mu;
	int i, j;
	aa[2].x = a.x; aa[2].y = a.y;
	for (j = 2, i = 1; i<kk; i++, j++)
	{
		if (a.x == aa[j].x)
		{
			mu = mulinverse((a.y) * 2, p);
			e1 = (a.x*a.x * 3 % p + a4) % p*mu%p;
		}
		else
		{
			mu = mulinverse((aa[j].x - a.x), p);
			e1 = (aa[j].y - a.y) % p*mu%p;
		}

		aa[j + 1].x = (e1*e1%p - a.x - aa[j].x) % p;
		aa[j + 1].y = (e1*(a.x - aa[j + 1].x) - a.y) % p;
	}
	a.x = (aa[j].x + p) % p; a.y = (aa[j].y + p) % p;
	delete aa;
	return a;
}

zb ECC::add2(zb b1, zb b2)  //形如K=M+G的加法
{
	zb b3;
	Num e2, mu;
	if (b1.x == b2.x)
	{
		mu = mulinverse(b1.y * 2, p);
		e2 = (b1.x*b1.x * 3 % p + a4) % p*mu;
	}
	else
	{
		mu = mulinverse((b2.x - b1.x), p);
		e2 = (b2.y - b1.y) % p*mu;
	}
	b3.x = ((e2*e2%p - b1.x - b2.x) % p + p) % p;
	b3.y = ((e2*(b1.x - b3.x) - b1.y) % p + p) % p;

	return b3;
}
Num ECC::tworesidue(Num a)
{
	Num a1, p1, n, b, n3;
	p1 = p - 1;
	if (modexpon(a, p1 / 2, p) != 1) { cout << "原二次同于式无解!"; exit(1); }

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

void ECC::genekey()
{
	cout << "是用默认的基点？ y/n :";
	char xz;
	while (1)
	{
		cin >> xz;
		if (xz == 'y' || xz == 'n' || xz == 'Y' || xz == 'N')break;
		cout << "输入错误，请重新选择： ";
	}
	if (xz == 'y' || xz == 'Y')
	{
		cout << "请输入私钥：";  cin >> k;
		pk = add1(g, k);
		displayPK();
	}
	else
	{
		cout << "请输入基点的x坐标值：";  cin >> g.x;
		g.y = tworesidue(g.x*g.x*g.x + a4*g.x + a6);
		cout << "请输入私钥：";  cin >> k;
		pk = add1(g, k);
		displayPK();
	}
}

void ECC::encrypt(zb m)
{
	cout << "输入随机数r，r=";  cin >> r;
	zb c0;
	c0 = add1(pk, r);  // 加密过程，计算C1和C2
	c1 = add2(m, c0);
	c2 = add1(g, r);
}

void ECC::decrypt()
{
	zb kc2, kc21;
	kc2 = add1(c2, k);//计算K*C2
	kc21.x = kc2.x;   kc21.y = kc2.y - kc2.y - kc2.y;  //求得-kC2

	m = add2(c1, kc21);
}

void ECC::displayC()
{
	cout << "加密后的密文对应的坐标为，C1(" << c2.x << "," << c2.y << ")  ";
	cout << "C2(" << c1.x << "," << c1.y << ")" << endl;
}

void ECC::displayM()
{
	cout << "解密后的明文对应的坐标为，M(" << m.x << "," << m.y << ")" << endl;
}

void ECC::displayPK()
{
	cout << "公钥信息为：" << endl;
	cout << "公钥对应的坐标为:PK(" << pk.x << "," << pk.y << ")   ";
	cout << "基点对应的坐标为:G(" << g.x << "," << g.y << ")" << endl;

}
