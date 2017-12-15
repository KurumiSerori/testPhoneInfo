#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int IMEI_LENGTH = 15;

/*
  Get the check digit of Luhn algorithm.

  data: the digits to be checked. The last digit is the CD.
  len: the length of data/digits.

  return:
    -1: error occurs
    others('0'..'9'): the check digit
*/
int luhn_checksum(const char *data, int len)
{
    if (data == NULL || len < 2) return -1;

    int even = 1;
    int sum = 0;
    int double_digit; 
    char p;
    int i;

    for (i = len - 2; i >= 0; i--) {
        p = data[i];
        if (!isdigit(p)) return -1;

        p -= '0';
        if (even) {
            double_digit = p + p; 
            sum += double_digit / 10 + double_digit % 10;
        } else {
            sum += p;
        }

        even = !even;
    }

    return sum * 9 % 10;
}

/*
  return:
    -1: error occurs
    others('0'..'9'): the check digit
*/
int get_imei_cd(const char *imei)
{
    if (imei == NULL) return -1;
    if (strlen(imei) != IMEI_LENGTH) return -1;
    int cd = luhn_checksum(imei, IMEI_LENGTH);
    return cd == -1 ? -1 : cd + '0';
}

/*
   0: fail
   1: ok
*/
int is_imei_valid(const char *imei)
{
    int cd = get_imei_cd(imei);
    if (cd == -1) return 0;
    return imei[IMEI_LENGTH - 1] == cd;
}

void test_is_imei_valid(const char *testcaseName, const char *imei, int expect)
{
    printf("TESTCASE----%s: ", testcaseName);
    int result = is_imei_valid(imei);
    if (result == expect) {
        printf("PASS\n");
    } else {
        printf("FAIL. expect=%d, real=%d\n", expect, result);
    }
}

int main()
{
    printf("test_is_imei_valid\n");
    char* input;
    while(scanf("%s", input)) {
        printf("%s\n", is_imei_valid(input) == 1 ? "true" : "false");
    }

    return 0;
}

