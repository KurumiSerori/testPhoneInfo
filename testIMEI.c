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

void test_get_imei_cd(const char *testcaseName, const char *imei, int expect)
{
    printf("TESTCASE----%s: ", testcaseName);
    int result = get_imei_cd(imei);
    if (result == expect) {
        printf("PASS\n");
    } else {
        printf("FAIL. expect=0x%02x, real=0x%02x\n", expect, result);
    }
}

int main()
{
    printf("test_is_imei_valid\n");
    // test_is_imei_valid("valid imei 000000000000000", "000000000000000", 1);
    // test_is_imei_valid("valid imei 012550003170164", "012550003170164", 1);
    // test_is_imei_valid("valid imei 123412341234564", "123412341234564", 1);
    // test_is_imei_valid("null imei", NULL, 0);
    // test_is_imei_valid("invalid imei", "123412341234567", 0);
    // test_is_imei_valid("invalid imei", "12341234123456", 0);
    // test_is_imei_valid("invalid imei", "1234123412345678", 0);

    // printf("test_get_imei_cd\n");
    // test_get_imei_cd("valid imei 000000000000000", "000000000000000", '0');
    // test_get_imei_cd("valid imei 012550003170164", "012550003170164", '4');
    // test_get_imei_cd("valid imei 123412341234564", "123412341234564", '4');
    // test_get_imei_cd("null imei", NULL, -1);
    // test_get_imei_cd("invalid imei", "12341234123456", -1);
    // test_get_imei_cd("invalid imei", "1234123412345678", -1);
    char* input;
    while(scanf("%s", input)) {
        printf("%s\n", is_imei_valid(input) == 1 ? "true" : "false");
    }

    return 0;
}

