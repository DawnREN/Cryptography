#include"base.h"
struct zb
{
	Num x;
	Num y;
};

class ECC
{
public:
	zb m;//������
	zb c1;
	zb c2;

	ECC();
	ECC(Num P);
	ECC(Num p, Num a4, Num a6);//���캯��
	void genekey();//��Կ��������
	void encrypt(zb);//���ܺ���
	void decrypt();//���ܺ���
	void displayC();//�������
	void displayM();//�������
	void displayPK();//�����Կ��Ϣ
private:
	Num p;//����p��a4��a6�����߲���
	Num a4;
	Num a6;
	zb g;//����
	int r;//�����õ������
	int k;//��Կ
	zb pk;//��Կ
	zb add1(zb, int);//����K=kG�ļӷ�
	zb add2(zb, zb);//����K=M+G�ļӷ�
	Num tworesidue(Num a);//��a�Ķ���ʣ��
};