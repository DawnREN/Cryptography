#include"base.h"
#include"ECC.h"

void main()
{
	ECC e;
	e.genekey();//产生密钥对
	zb m;
	m.x = 562;   m.y = 201;
	e.encrypt(m);//加密
	e.displayC();//显示明文
	e.decrypt();//解密
	e.displayM();//显示解密后的明文
	system("pause");
}

