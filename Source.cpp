#include<iostream>
#include<fstream>

struct Lifo
{
	static const size_t size = 100;
	char st[size];
	int top;
};

void init(Lifo& stack)
{
	stack.top = 0;
}
bool isEmpty(const Lifo& stack)
{
	if (stack.top == 0) return true;
	else return false;
}
bool isFull(const Lifo& stack)
{
	if (stack.top == stack.size - 1) return true;
	else return false;
}

void push(Lifo& stack, char key)
{
	if (!isFull(stack))
	{
		stack.st[stack.top++] = key;
	}
	else
	{
		std::cout << "Stack is full.\n";
		return;
	}
}
char pop(Lifo& stack)
{
	char key;
	if (!isEmpty(stack))
	{
		key = stack.st[stack.top - 1];
		stack.top--;
		return key;
	}
	else
	{
		std::cout << "Stack is empty.\n";
		return 0;
	}
}

bool check(char* str)
{
	Lifo stack;
	init(stack);
	int i = 0;

	while (str[i])
	{
		char temp = stack.st[stack.top];
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
			push(stack, str[i]);
		}
		else if (str[i] == ')' || str[i] == ']' || str[i] == '}')
		{
			if (!isEmpty(stack) || (str[i] == ')' && temp == '(') ||
				(str[i] == ']' && temp == '[') || (str[i] == '}' && temp == '{')) 
				pop(stack);
			
			else return false;
		}
		temp = pop(stack);
		i++;
	}
	if (isEmpty(stack))
	{
		return true;
	}
	else
	{
		return false;
	}
}

char min(char a, char b)
{
	return a > b ? b : a;
}
char max(char a, char b)
{
	return a > b ? a : b;
}
char solve(char* str)
{
	Lifo stack;
	init(stack);
	int i = 0;
	char val1, val2, operation;

	while (str[i])
	{
		if (str[i] == 'a' || str[i] == 'i' || isdigit(str[i]) != 0)
			push(stack, str[i]);
		else if (str[i] == ')')
		{
			val1 = pop(stack);
			val2 = pop(stack);
			operation = pop(stack);
			if (operation == 'a')
			{
				push(stack, max(val1, val2));
			}
			else push(stack, min(val1, val2));
		}
		i++;
	}
	return pop(stack);
}

int main()
{
	// 1. Use stack to determine if parentheses in expression are arranged in the right order
	char str[100];
	std::ifstream fin("Input.txt");
	fin.getline(str, 100);
	if (check(str))
	{
		std::cout << "Line is correct\n";
	}
	else
	{
		std::cout << "Line is incorrect\n";
	}

	// 2. Formula with no errors given. Syntax <formula> = <digit> | max/min(<formula>, <formula>).
	// For example: 8 or max(4, min(3, 5)) or min(min(3, 5), max(2, max(3, 4))).
	// Evaluate expression using stack.
	/*char str[100];
	std::ifstream fin("Input.txt");
	fin.getline(str, 100);
	std::cout << solve(str) << std::endl;*/



	system("pause");
	return 0;
}