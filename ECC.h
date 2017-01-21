#include"base.h"
struct zb
{
	Num x;
	Num y;
};

class ECC
{
public:
	zb m;//明密文
	zb c1;
	zb c2;

	ECC();
	ECC(Num P);
	ECC(Num p, Num a4, Num a6);//构造函数
	void genekey();//密钥产生函数
	void encrypt(zb);//加密函数
	void decrypt();//解密函数
	void displayC();//输出密文
	void displayM();//输出明文
	void displayPK();//输出公钥信息
private:
	Num p;//素数p，a4，a6是曲线参数
	Num a4;
	Num a6;
	zb g;//基点
	int r;//加密用的随机数
	int k;//密钥
	zb pk;//公钥
	zb add1(zb, int);//形如K=kG的加法
	zb add2(zb, zb);//形如K=M+G的加法
	Num tworesidue(Num a);//求a的二次剩余
};