#include"base.h"
#include"ECC.h"

void main()
{
	ECC e;
	e.genekey();//������Կ��
	zb m;
	m.x = 562;   m.y = 201;
	e.encrypt(m);//����
	e.displayC();//��ʾ����
	e.decrypt();//����
	e.displayM();//��ʾ���ܺ������
	system("pause");
}

