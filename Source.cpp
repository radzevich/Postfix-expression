//Преобразователь стандартной записи в обратную польскую
//Программный ввод выражения и его проверка не реализован полностью, 
//поэтому для ввода выражения, задайте его после "#define EXPRESSION"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#define EXPRESSION "w*(a+b+n+c*(y-g*d)^n^k+s*l)/(x-f*t*p+w)^e"

#define OPERANDS true
#define OPERATORS false

struct TTree
{
	char value;
	TTree *left, *right;
};


bool charIsOperand(char symb);
bool findInvalidSymbolsInExpression(char *expression, int size);
bool symbolInEnum(char *charEnum, unsigned int enumSize, char symbol);
char *getExpression();
unsigned int findLowPriority(char *expression, unsigned int leftIndex, unsigned int righntIndex);
TTree *createTree(char *expression, unsigned int leftIndex, unsigned int rightIndex);
void inorderTreeWalk(TTree *tree);


int main()
{
	char *expression = getExpression();
	TTree *tree = createTree(expression, 0, strlen(expression) - 1);
	inorderTreeWalk(tree);
	_getch();
}

char *getExpression()
{
	/*char *expression = (char*)calloc(100 * sizeof(char), 1);
	while (true)
	{
		scanf_s("%s100", expression);
		char *emptyString = "";
		if (!(bool)strcmp(emptyString, expression))
			return NULL;
		else if (!findInvalidSymbolsInExpression(expression, strlen(expression)))
			return expression;
		else
			printf("Invalid input");
	}*/
	char *expression = EXPRESSION;
	return expression;
}

bool findInvalidSymbolsInExpression(char *expression, int size)
{
	short int weight = 0;
	short int bracketCount = 0;
	bool flag = true;
	for (int i = 0; i < size; i++)
	{
		if (flag)
		{
			
		}
	}
	return false;
}

void checkSubstring(char *expression, unsigned int *checkPosition, bool operandsMode)
{
	char *checkArray;
	if (operandsMode)
		checkArray = ("abcdefghijklmnopqrstuvwxyz ");
	else
		checkArray = ("+-*/^ ");	
	while (symbolInEnum(checkArray, strlen(checkArray), expression[*checkPosition]))
		*checkPosition++;
}

bool symbolInEnum(char *charEnum, unsigned int enumSize, char symbol)
{
	for (unsigned int i = 0; i < enumSize; i++)
		if (charEnum[i] == symbol)
			return true;
	return false;
}

TTree *createTree(char *expression, unsigned int leftIndex, unsigned int rightIndex)
{
	TTree *node = (TTree*)malloc(sizeof(TTree));
	node->left = NULL;
	node->right = NULL;
	int position = findLowPriority(expression, leftIndex, rightIndex);
	if (!charIsOperand(expression[position]))
	{
		node->left = createTree(expression, leftIndex, position - 1);
		node->right = createTree(expression, position + 1, rightIndex);
	}
	node->value = expression[position];
	return node;
}

unsigned int findLowPriority(char *expression, unsigned int leftIndex, unsigned int righntIndex)
{
	unsigned int position = leftIndex;
	unsigned int lowPriority = INT_MAX;
    unsigned int breackPriority = 0;
	bool backwardExists = false;
	for (unsigned int i = leftIndex; i <= righntIndex; i++)
	{
		int operationPriority = 5;
		if ('(' == expression[i])
		{
			breackPriority += 3;
			backwardExists = true;
		}
		else if ((')' == expression[i]) & (backwardExists))
		{
			breackPriority -= 3;
			if (0 == breackPriority)
				backwardExists = false;
		}
		else if (('+' == expression[i]) || ('-' == expression[i]))
			operationPriority = 1;
		else if (('*' == expression[i]) || ('/' == expression[i]))
			operationPriority = 2;
		else if ('^' == expression[i])
			operationPriority = 3;
		else if (charIsOperand(expression[i]))
			operationPriority = 4;
		if (lowPriority >= breackPriority + operationPriority)
		{
			position = i;
			lowPriority = breackPriority + operationPriority;
		}
	}
	return position;
}

bool charIsOperand(char symb)
{
	return (((symb >= 'a') & (symb <= 'z')) || ((symb >= 'A') & (symb <= 'Z')));
}

void inorderTreeWalk(TTree *tree)
{
	if (tree != NULL)
	{
		inorderTreeWalk(tree->left);
		inorderTreeWalk(tree->right);
		printf("%c", tree->value);
	}
}