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
void EAccessViolation::Print(){
	printf("Access violation read of address %p!", m_badAddr);
}

void EAccessViolation::Read(){
}

EZeroDivide::EZeroDivide(const double &divident){
	m_divident = divident;
}

void EZeroDivide::Print(){
	printf("There was a try to divide %lf by zero!", m_divident);
}

void EZeroDivide::Read(){
	//can't read this box
}

EOverflow::EOverflow(const int &operand1, const int &operand2){
	m_operand1 = operand1;
	m_operand2 = operand2;
}

void EOverflow::Print(){
	printf("There was an overflow during some operation between %d and %d!", m_operand1, m_operand2);
}

void EOverflow::Read(){
	//can't read this box
}

void disposeError(EBaseError** e){
	if (*e != NULL) delete *e;
	*e = NULL;
}

int main(){
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	EBaseError* e = NULL;
	char c = 0, tmp;
	while (c != 27){
		printf("\nвыберите действие: \n 1 - эмулировать ошибку доступа\n");
		printf(" 2 - попытаться поделить два числа\n 3 - попытаться умножить два числа\n");
		printf(" <esc> - выйти из программы\n");
		scanf("%c", &c);
		switch(c){
			case '1': 
				e = new EAccessViolation((void*)&c); 
				break;
			case '2' : 
				double a, b;
				printf("\nвведите делимое ");
				scanf("%lf", &a);
				printf("\nвведите делитель ");
				scanf("%lf", &b);
				if (b == 0.0) e = new EZeroDivide(a);
				else printf("\nрезультат = %lf", a / b);
				break;
			case '3' : 
				int i, j;
				long long res;
				printf("\nвведите первый множитель ");
				scanf("%d", &i);
				printf("\nвведите второй множитель ");
				scanf("%d", &j);
				res = i;
				res *= j;
				if (res > INT_MAX || res < INT_MIN) e = new EOverflow(i, j);
				else printf("\nрезультат = %d", res);
				break;
			case '0':
				c = 27;
		}
		scanf("%c", &tmp); // считываем Enter оставшийся в буфере после предыдущего scanf
		if (e != NULL){
			printf("\n>\t");
			e->Print();
			printf("\n");
		}
		disposeError(&e);
	}
	return 0;
};