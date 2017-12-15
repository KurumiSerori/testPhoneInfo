#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int sumTable[2][10] = {
	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	{0, 2, 4, 6, 8, 1, 3, 5, 7, 9},
};

/*
char* toString(int number)
{
	char* nstring = (char*) malloc(25);
}
*/

// int isValidLuhn(long long number)
int isValidLuhn(char* number)
{
	// char* nstring = toString(number);
	// char nstring[25];
	char* nstring = number;
	// sprintf(nstring, "%lld", number);
	int sum = 0, flip = 0;
	int i;
	for(i = strlen(nstring) - 1; i >= 0; --i) {
		sum += sumTable[flip++ & 0x1][nstring[i]-'0'];
	}
	return (sum % 10) == 0 ? 0 : 1;
}

int main()
{
	printf("testICCID\n");
	// long long input;
	char input[25];
	// while(scanf("%lld", &input) != EOF) {
	while(scanf("%s", input) != EOF) {
		printf("%s\n", isValidLuhn(input) == 0 ? "true" : "false");
	}
	return 0;
}
