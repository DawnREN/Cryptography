#include "base.h"

Num::Num()
{
	int i;
	tag = 0;  length = 1;
	str[0] = '0';
	for (i = 1; i<MaxSize; i++)str[i] = '\0';
}


Num::Num(int n)
{
	int m, i;
	char c[MaxSize] = { '\0' };
	if (n >= 0)tag = 0;
	else
	{
		tag = 1;
		n = (-1)*n;
	}
	for (i = 0; n>0; i++)
	{
		m = n % 10;  n = n / 10;
		c[i] = m + 48;
	}
	if (i == 0)
	{
		length = 1;  str[0] = '0';
		for (i = 1; i<MaxSize; i++)str[i] = '\0';
	}
	else
	{
		length = i;
		for (i = 0; i<length; i++)str[i] = c[length - i - 1];
		for (i = length; i<MaxSize; i++)str[i] = '\0';
	}
}


Num Num::operator+(Num &num)
{
	Num c;
	if (tag == 0 && num.tag == 1)//正+负
	{
		c = num;
		c.tag = 0;
		return (*this) - c;
	}
	else if (tag == 1 && num.tag == 0)//负+正
	{
		c = (*this);
		c.tag = 0;
		return num - c;
	}
	else
	{

		int d, i, k;
		//char t[MaxSize]={'\0'},a[MaxSize]={'\0'},b[MaxSize]={'\0'};
		char *t, *a, *b;
		t = new char[MaxSize]; a = new char[MaxSize]; b = new char[MaxSize];
		for (int ii = 0; ii<MaxSize; ii++) { t[ii] = '\0';   a[ii] = '\0';   b[ii] = '\0'; }
		if (length >= num.length)
		{
			strcpy(a, str);
			d = length;
			for (i = 0; i<length - num.length; i++)b[i] = '0';
			strcpy_s(&b[i], MaxSize - i, num.str);
		}
		else
		{
			strcpy(a, num.str);
			d = num.length;
			for (i = 0; i<num.length - length; i++)b[i] = '0';
			strcpy_s(&b[i], MaxSize - i, str);
		}

		for (k = d; k>0; k--)
		{
			t[k] += a[k - 1] + b[k - 1] - 48;
			if (t[k]>57) { t[k - 1]++;  t[k] -= 10; }
		}

		if (t[0] == '\0')
		{
			strcpy(c.str, &t[1]);
			c.length = d;
		}
		else
		{
			t[0] += 48;
			strcpy(c.str, t);
			c.length = d + 1;
		}
		if (this->tag == 1)c.tag = 1;
		delete t; delete a; delete b;
		return c;
	}
}

Num Num::operator+(int n)
{
	Num c(n);
	return (*this) + c;
}




Num Num::operator-(Num &num)
{
	Num h;
	if (tag == 0 && num.tag == 1)//正—负
	{
		h = num;
		h.tag = 0;
		return (*this) + h;
	}
	else if (tag == 1 && num.tag == 0)//负—正
	{
		h = num;
		h.tag = 1;
		return (*this) + h;
	}
	else
	{
		if (strcmp(str, num.str) == 0) return h;

		//char a[MaxSize]={'\0'},b[MaxSize]={'\0'},c[MaxSize]={'\0'};
		char *c, *a, *b;
		c = new char[MaxSize]; a = new char[MaxSize]; b = new char[MaxSize];
		for (int ii = 0; ii<MaxSize; ii++) { c[ii] = '\0';   a[ii] = '\0';   b[ii] = '\0'; }
		int i, j, t, tag1 = 0;

		if ((length == num.length&&strcmp(str, num.str)<0) || length<num.length)//把绝对值大的复制到a数组
		{
			strcpy(b, str);
			strcpy(a, num.str);
			tag1 = 1;//说明结果为负
		}
		else
		{
			strcpy(a, str);
			strcpy(b, num.str);
		}
		h.length = strlen(a);
		for (i = strlen(a) - 1, j = strlen(b) - 1; j >= 0; i--, j--)
		{
			t = i;
			if (a[t]<b[j])
			{
				a[t] += 10;
				while (a[t - 1] == 48)
				{
					a[t - 1] = 57;
					t--;
				}
				a[t - 1]--;
			}
			c[i] = a[i] - b[j] + 48;
		}
		if (i >= 0)
			for (; i >= 0; i--)
				c[i] = a[i];
		for (i = 0; c[i] == 48; i++)   h.length--;
		if ((tag1 == 0 && tag == 1) || (tag1 == 1 && tag == 0)) h.tag = 1;
		strcpy(h.str, &c[i]);
		delete c; delete a; delete b;
		return h;
	}
}



Num Num::operator-(int n)
{
	Num c(n);
	return *this - c;
}

Num Num::operator*(Num &num)
{
	Num h;
	if ((length == 1 && str[0] == '0') || (num.length == 1 && num.str[0] == '0'))return h;
	else
	{
		char c[MaxSize] = { '\0' };
		int i, j, t, k, l;
		k = length + num.length - 1;
		for (j = num.length - 1; j >= 0; j--)
			for (i = length - 1; i >= 0; i--)
			{
				c[i + j + 1] += (str[i] - 48)*(num.str[j] - 48);
				c[i + j] += c[i + j + 1] / 10;
				c[i + j + 1] = c[i + j + 1] % 10;
			}
		if (tag + num.tag == 1) h.tag = 1;
		for (t = 0; c[t] == '\0'; t++);
		h.length = k + 1 - t;
		for (l = t; l <= k; l++)
			c[l] += 48;
		strcpy(h.str, &c[t]);
		return h;
	}

}


Num Num::operator*(int n)
{
	Num c(n);
	return (*this)*c;
}

Num Num::operator/(Num &num)
{
	if (num.length == 1 && num.str[0] == '0')
	{
		cout << "数据有误,分母为零!" << endl;
		exit(0);
	}
	Num q;
	if (length<num.length || (length == num.length&&strcmp(str, num.str)<0))return q;
	else
	{
		q.length = 0;
		Num a, b, c, k;
		int l, i;
		a = (*this);
		b = num;
		if (tag == 1)  a.tag = 0;
		if (num.tag == 1)   b.tag = 0;
		for (i = num.length; i<length; i++)
		{
			b.str[i] = '0';
			b.length++;
		}
		for (l = 0; l <= length - num.length; l++)
		{
			k.str[0] = '1';
			for (; k.str[0] <= 58; k.str[0]++)
			{
				if (k.str[0] == 58)
				{
					q.str[l] = 57;
					q.length++;
					break;
				}
				c = b*k;
				if (a >= c) continue;
				else
				{
					q.str[l] = k.str[0] - 1;
					q.length++;
					break;
				}
			}
			k.str[0]--;
			c = b*k;
			a = a - c;
			b.str[b.length - 1] = '\0';
			b.length--;
		}

		if (q.str[0] == '0')
		{
			for (i = 0; i <= q.length - 2; i++)
				q.str[i] = q.str[i + 1];
			q.str[i] = '\0';
			q.length--;
		}
		if (tag != num.tag) q.tag = 1;
		return q;
	}
}



Num Num::operator/(int n)
{
	Num c(n);
	return (*this) / c;
}

Num Num::operator%(Num &num)
{
	return (*this) - (*this) / num*num;
}


Num Num::operator%(int n)
{
	Num c(n);
	return (*this) % c;
}

Num Num::operator=(int n)
{
	int m, i, j;
	char c[11] = { '\0' };
	if (n >= 0)
		tag = 0;
	else
	{
		tag = 1;
		n = (-1)*n;
	}
	for (i = 0; n>0; i++)
	{
		m = n % 10;
		n = n / 10;
		c[i] = m + 48;
	}
	if (i == 0)
	{
		length = 1;
		str[0] = '0';
		for (j = 1; j<MaxSize; j++)
			str[j] = '\0';
		return *this;
	}
	else
	{
		length = i;
		for (i = 0; i<length; i++)
			str[i] = c[length - i - 1];
		for (; i<MaxSize; i++)
			str[i] = '\0';
		return  *this;
	}

}






Num Num::operator++()
{
	Num e;
	e.str[0] = '1';
	(*this) = (*this) + e;
	return *this;
}

Num Num::operator++(int)
{
	Num a, e;
	e.str[0] = '1';
	a = *this;
	*this = *this + e;
	return a;
}

Num Num::operator--()
{
	Num e;
	e.str[0] = '1';
	(*this) = (*this) - e;
	return *this;
}

Num Num::operator--(int)
{
	Num a, e;
	e.str[0] = '1';
	a = *this;
	*this = *this - e;
	return a;
}

bool Num::operator>(Num &num)
{
	if (tag>num.tag)
		return false;
	if (tag<num.tag)
		return true;
	if (tag == 0)
	{
		if (length>num.length || (length == num.length&&strcmp(str, num.str)>0))
			return true;
		else return false;
	}
	else
	{
		if (length>num.length || (length == num.length&&strcmp(str, num.str) >= 0))
			return false;
		else return true;
	}
}


bool Num::operator>(int n)
{
	Num c(n);
	return ((*this)>c);
}

bool Num::operator>=(Num &num)
{

	if (tag>num.tag)
		return false;
	if (tag<num.tag)
		return true;
	if (tag == 0)
	{
		if (length>num.length || (length == num.length&&strcmp(str, num.str) >= 0))
			return true;
		else return false;
	}
	else
	{
		if (length>num.length || (length == num.length&&strcmp(str, num.str)>0))
			return false;
		else return true;
	}
}

bool Num::operator>=(int n)
{
	Num c(n);
	return (*this >= c);
}


bool Num::operator<(Num &num)
{
	if (tag>num.tag)
		return true;
	if (tag<num.tag)
		return false;
	if (tag == 0)
	{
		if (length<num.length || (length == num.length&&strcmp(str, num.str)<0))
			return true;
		else return false;
	}
	else
	{
		if (length<num.length || (length == num.length&&strcmp(str, num.str) <= 0))
			return false;
		else return true;
	}
}


bool Num::operator<(int n)
{
	Num c(n);
	return (*this<c);
}


bool Num::operator<=(Num &num)
{
	if (tag>num.tag)
		return true;
	if (tag<num.tag)
		return false;
	if (tag == 0)
	{
		if (length<num.length || (length == num.length&&strcmp(str, num.str) <= 0))
			return true;
		else return false;
	}
	else
	{
		if (length<num.length || (length == num.length&&strcmp(str, num.str)<0))
			return false;
		else return true;
	}
}

bool Num::operator<=(int n)
{
	Num c(n);
	return (*this <= c);
}

bool Num::operator==(Num &num)
{

	if (tag == num.tag&&strcmp(str, num.str) == 0)
		return true;
	else return false;
}

bool Num::operator==(int n)
{
	Num c(n);
	return (*this == c);
}

bool Num::operator!=(Num &num)
{

	if (tag == num.tag&&strcmp(str, num.str) == 0)
		return false;
	else return true;
}

bool Num::operator!=(int n)
{
	Num c(n);
	return (*this != c);
}

istream &operator>>(istream &input, Num &num)
{
	char c[MaxSize] = { '\0' };
	input >> c;
	if (c[0] == '-')
	{
		strcpy(num.str, &c[1]);
		num.length = strlen(num.str);
		num.tag = 1;
	}
	else
	{
		strcpy(num.str, c);
		num.length = strlen(num.str);
		num.tag = 0;
	}
	return input;

}


ostream &operator<<(ostream &output, Num &num)
{
	if (num.tag == 0)
		output << num.str;
	else output << '-' << num.str;
	return output;
}


Num random(int Length)
{
	Num a;
	srand((unsigned)time(NULL)); //用系统时间当种子，对随机函数进行初始化
	for (int i = 0; i<Length; i++)
		a.str[i] = rand() % 10 + '0';
	while (a.str[0] == '0') a.str[0] = rand() % 10 + '0';
	a.length = Length;
	return a;
}

