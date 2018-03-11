#include<iostream>
using namespace std;

struct
{
	char data;
	int pri;
}lsv[] = { {'=',0},{ '(',1 },{ '+',3 },{ '-',3 },{ '*',5 },{ '/',5},{ ')',6 } },
rsv[]={ { '=',0 },{ '(',6},{ '+',2 },{ '-',2 },{ '*',4 },{ '/',4 },{ ')',1 } } ;

int lpri(char exp)
{
	for (int i = 0; i < 7; i++)
		if (lsv[i].data == exp)
			return lsv[i].pri;
}

int rpri(char exp)
{
	for (int i = 0; i < 7; i++)
		if (rsv[i].data == exp)
			return rsv[i].pri;
}

bool InFo(char exp)
{
	if (exp == '+' || exp == '-' || exp == '*' || exp == '/'|| exp == '(' || exp == ')')
		return true;
	else
		return false;
}

int PriCompare(char op1, char op2)
{
	if (lpri(op1) < rpri(op2))
		return -1;
	else if (lpri(op1) == rpri(op2))
		return 0;
	else
		return 1;
}

void transPostexp(char *exp, char postexp[])
{
	struct
	{
		char data[50];
		int top;
	}op;
	int i = 0;
	op.top = -1;
	op.top++;
	op.data[op.top]='=';
	while (*exp != '\0')
	{
		if (InFo(*exp))
			switch (PriCompare(op.data[op.top], *exp))
			{
			case -1:
				op.top++;
				op.data[op.top] = *exp;
				exp++;
				break;
			case 0:
				op.top--;
				exp++;
				break;
			case 1:
				postexp[i++] = op.data[op.top];
				op.top--;
				break;
			default:
				break;
			}
		else
		{
			while (*exp>='0'&&*exp<='9')
			{
				postexp[i++] = *exp;
				exp++;
			}
			postexp[i++] = '#';
		}
	}
	while (op.data[op.top]!='=')
	{
		postexp[i++] = op.data[op.top];
		op.top--;
	}
	postexp[i] = '\0';
}

float findConsult(char postexp[])
{
	struct 
	{
		float data[50];
		int top;
	}st;
	st.top = -1;
	while (*postexp != '\0')
	{
		float a, b, c;
		switch (*postexp)
		{
		case '+':
			a = st.data[st.top];
			st.top--;
			b = st.data[st.top];
			st.top--;
			c = a + b;
			st.top++;
			st.data[st.top] = c;
			break;
		case '-':
			a = st.data[st.top];
			st.top--;
			b = st.data[st.top];
			st.top--;
			c = b - a;
			st.top++;
			st.data[st.top] = c;
			break;
		case '*':
			a = st.data[st.top];
			st.top--;
			b = st.data[st.top];
			st.top--;
			c = a * b;
			st.top++;
			st.data[st.top] = c;
			break;
		case '/':
			a = st.data[st.top];
			st.top--;
			b = st.data[st.top];
			st.top--;
			if (a == 0)
			{
				cout << "\n\t³ýÊýÎªÁã!" << endl;
				exit(0);
			}
			else
			{
				c = b / a;
				st.top++;
				st.data[st.top] = c;
			}
			break;
		default:
			float p = 0;
			while (*postexp >= '0'&&*postexp <= '9')
			{
				p = 10 * p + *postexp - '0';
				postexp++;
			}
			st.top++;
			st.data[st.top] = p;
			break;
		}
		postexp++;
		
	}
	return st.data[st.top];
}

int main()
{
	char com[] = "3+7*(3+5)/2";
	char postexp[50];
	transPostexp(com, postexp);
	cout << postexp << endl;
	cout << findConsult(postexp)<<endl;
}


