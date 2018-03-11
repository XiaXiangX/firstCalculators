#include<iostream>
#include<string>

using namespace std;

struct
{
	char ch;
	int pri;
}lpri[] = { {'=',0},{ '(',1 },{ '*',5 },{ '/',5 },{ '+',3 },{ '-',3 },{ ')',6 } },
rpri[] = { { '=',0 },{ '(',6 },{ '*',4 },{ '/',4 },{ '+',2 },{ '-',2 },{ ')',1} };

int leftpri(char op)
{
	int i;
	for (i = 0; i < 7; i++)
		if (lpri[i].ch == op)
			return lpri[i].pri;
}

int rightpri(char op)
{
	int i;
	for (i = 0; i < 7; i++)
		if (rpri[i].ch == op)
			return rpri[i].pri;
}

bool InOp(char ch)
{
	if (ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return true;
	else
		return false;
}

int Precede(char op1, char op2)
{
	if (leftpri(op1) == rightpri(op2))
		return 0;
	else if (leftpri(op1) < rightpri(op2))
		return -1;
	else
		return 1;
}

void trans(char *exp, char postexp[])
{
	struct 
	{
		char data[50];
		int top;
	}op;
	int i = 0;
	op.top = -1;
	op.top++;
	op.data[op.top] = '=';
	while (*exp != '\0')
	{
		if (!InOp(*exp))
		{
			while (*exp >= '0'&&*exp <= '9')
			{
				postexp[i++] = *exp;
				exp++;
			}
			postexp[i++] = '#';
		}
		else
			switch (Precede(op.data[op.top],*exp))
			{
			case -1:
				op.top++; op.data[op.top] = *exp;
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
	}
	while (op.data[op.top] != '=')
	{
		postexp[i++] = op.data[op.top];
		op.top--;
	}
	postexp[i] = '\0';
}

float compvalue(char *postexp)
{
	struct
	{
		float data[50];
		int top;
	}st;
	float d, a, b, c;
	st.top = -1;
	while (*postexp != '\0')
	{
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
			c = b * a;
			st.top++;
			st.data[st.top] = c;
			break;
		case '/':
			a = st.data[st.top];
			st.top--;
			b = st.data[st.top];
			st.top--;
			if (a != 0)
			{
				c = b / a;
				st.top++;
				st.data[st.top] = c;
			}
			else
			{
				printf("\n\t除零错误!\n");
				exit(0);
			}
			break;
			break;
		default:
			d = 0;
			while (*postexp >= '0'&&*postexp <= '9')
			{
				d = 10 * d + *postexp - '0';
				postexp++;
			}
			st.top++;
			st.data[st.top] = d;
			break;
		}
		postexp++;
	}
	return(st.data[st.top]);
}

int main()
{
	/*string exp1;
	cin >> exp1;
	char *exp=new char[exp1.size()];
	for (int i = 0; i < exp1.size(); i++)
	{
		exp[i] = exp1[i];
	}*/
	char exp[] = "(56-20)/(4+2)";
	char postexp[50];
	trans(exp, postexp);
	cout << "中缀表达式:" << exp << endl;
	cout << "后缀表达式:" << postexp << endl;
	cout << "表达式的值:" << compvalue(postexp) << endl;
	system("pause");
}