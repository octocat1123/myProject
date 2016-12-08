#include <stdio.h>
#include <climits>
#include <windows.h>

class EBaseError{
public:
	virtual void Print() = 0;
	virtual void Read() = 0;
};

class EAccessViolation : public EBaseError{
	void* m_badAddr;
public:
	void Print();
	void Read();
	EAccessViolation(void* badAddr);
};

class EMathError : public EBaseError{};

class EZeroDivide : public EMathError{
	double m_divident;
public:
	void Print();
	void Read();
	EZeroDivide(const double &divident);
};

class EOverflow : public EMathError{
	int m_operand1, m_operand2;
public:
	void Print();
	void Read();
	EOverflow(const int &operand1, const int &operand2);
};

EAccessViolation::EAccessViolation(void* badAddr){
	m_badAddr = badAddr;
}

int main(){
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	EBaseError* e = NULL;
	char c = 0, tmp;
	while (c != 27){
		printf("\n�������� ��������: \n 1 - ����������� ������ �������\n");
		printf(" 2 - ���������� �������� ��� �����\n 3 - ���������� �������� ��� �����\n");
		printf(" <esc> - ����� �� ���������\n");
		scanf("%c", &c);
		switch(c){
			case '1': 
				e = new EAccessViolation((void*)&c); 
				break;
			case '2' : 
				double a, b;
				printf("\n������� ������� ");
				scanf("%lf", &a);
				printf("\n������� �������� ");
				scanf("%lf", &b);
				if (b == 0.0) e = new EZeroDivide(a);
				else printf("\n��������� = %lf", a / b);
				break;
			case '3' : 
				int i, j;
				long long res;
				printf("\n������� ������ ��������� ");
				scanf("%d", &i);
				printf("\n������� ������ ��������� ");
				scanf("%d", &j);
				res = i;
				res *= j;
				if (res > INT_MAX || res < INT_MIN) e = new EOverflow(i, j);
				else printf("\n��������� = %d", res);
				break;
			case '0':
				c = 27;
		}
		scanf("%c", &tmp); // ��������� Enter ���������� � ������ ����� ����������� scanf
		if (e != NULL){
			printf("\n>\t");
			e->Print();
			printf("\n");
		}
		disposeError(&e);
	}
	return 0;
};