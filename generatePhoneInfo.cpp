/* 
 *	randomly generates valid phone info tuples
 *	generate and then test
 *
 *	Kurumi
 *	2017/12/15
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <ctype.h>
// use <random> to replace the current logic in the future to support more drastic need.

using namespace std;

const int IMEI_LENGTH = 15;
const int IMSI_LENGTH = 15;
const int ICCID_LENGTH = 20;

int luhn_checksum(const char* data)
{
    if (data == NULL) return -1;

    int even = 1;
    int sum = 0;
    int double_digit;
    char p;
    int i;

    for (i = 13; i >= 0; i--) {
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

int sumTable[2][10] = {
	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	{0, 2, 4, 6, 8, 1, 3, 5, 7, 9},
};

int ValidLuhn(char* number)
{
	char* nstring = number;
	int sum = 0, flip = 0;
	int i;
	for(i = strlen(nstring) - 1; i >= 0; --i) {
		if(i == strlen(nstring) - 1) {
			flip++;
			continue;
		}
		sum += sumTable[flip++ & 0x1][nstring[i]-'0'];
	}
	return (sum % 10);
}


int main()
{
	srand( time(NULL) );
	cout << "Case NUM(<=1000): ";
	int T, i, j;
	cin >> T;
	if(T > 1000) return -1;

	char randomInt[ICCID_LENGTH+1] = {'\0'};

	for(i = 0; i < IMSI_LENGTH+1; ++i) randomInt[i] = '\0';
	char imei_results[1005][IMEI_LENGTH+1];
	memset(imei_results, 0, sizeof(imei_results));
	int turn = -1;
	int _T = T;
	while(_T--) {
		turn++;
		int choice1 = rand() % 2;
		if (choice1 == 0) { // 35*
			randomInt[0] = '3';
			randomInt[1] = '5';
			int choice2 = rand() % 4;
			switch(choice2) {
				case 0: randomInt[2] = '3'; break;
				case 1: randomInt[2] = '5'; break;
				case 2: randomInt[2] = '7'; break;
				case 3: randomInt[2] = '9'; break;
				default: return 1;
			}
			for(i = 3; i < IMEI_LENGTH - 1; ++i) {
				randomInt[i] = rand() % 10 + '0';
			}
			int cd = luhn_checksum(randomInt);
			if (cd != -1)
				randomInt[IMEI_LENGTH - 1] = cd;
			else
				return 2;
		}
		else {	// 86*
			randomInt[0] = '8';
			randomInt[1] = '6';
			for(i = 2; i < IMEI_LENGTH - 1; ++i) {
				randomInt[i] = rand() % 10 + '0';
			}
			int cd = luhn_checksum(randomInt);
			if(cd != -1)
				randomInt[IMEI_LENGTH - 1] = cd;
			else 
				return 2;
		}
		strcpy(imei_results[turn], randomInt);
	}

	int count = 0;
	for(i = 0; i < T; ++i) {
		// if(!strcmp(imei_results[i], "")) continue;
		if(imei_results[i][0] == '\0') continue;
		for(j = i + 1; j < T; ++j) {
			if(!strcmp(imei_results[j], imei_results[i])) {
				imei_results[j][0] = '\0';
				count++;
			}
		}
	}
	cout << "IMEI: " << endl;
	for(i = 0; i < T; ++i) {
		if(imei_results[i][0] != '\0')
			cout << imei_results[i] << endl;
	}
	cout << "duplicate: " << count << endl << endl << endl;




	for(i = 0; i < IMSI_LENGTH+1; ++i) randomInt[i] = '\0';
	char imsi_results[1005][IMSI_LENGTH+1];
	memset(imsi_results, 0, sizeof(imsi_results));
	turn = -1;
	_T = T;
	while(_T--) {
		turn++;
		randomInt[0] = '4';
		randomInt[1] = '6';
		randomInt[2] = '0';
		randomInt[3] = '0';
		int choice = rand() % 4;
		switch(choice) {
			case 0: randomInt[4] = '0'; break;
			case 1: randomInt[4] = '1'; break;
			case 2: randomInt[4] = '2'; break;
			case 3: randomInt[4] = '3'; break;
			default: return 1;
		}
		for(i = 5; i < IMSI_LENGTH; ++i) {
			randomInt[i] = rand() % 10 + '0';
		}
		strcpy(imsi_results[turn], randomInt);
	}

	count = 0;
	for(i = 0; i < T; ++i) {
		if(imsi_results[i][0] == '\0') continue;
		for(j = i + 1; j < T; ++j) {
			if(!strcmp(imsi_results[j], imsi_results[i])) {
				imsi_results[j][0] = '\0';
				count++;
			}
		}
	}
	cout << "IMSI: " << endl;
	for(i = 0; i < T; ++i) {
		if(imsi_results[i][0] != '\0')
			cout << imsi_results[i] << endl;
	}
	cout << "duplicate: " << count << endl << endl << endl;




	for(i = 0; i < ICCID_LENGTH+1; ++i) randomInt[i] = '\0';
	char iccid_results[1005][ICCID_LENGTH+1];
	memset(iccid_results, 0, sizeof(iccid_results));
	turn = -1;
	_T = T;
	while(_T--){
		turn++;
		randomInt[0] = '8';
		randomInt[1] = '9';
		randomInt[2] = '8';
		randomInt[3] = '6';
		randomInt[4] = '0';
		int choice = rand() % 5;
		switch(choice) {
			case 0: randomInt[5] = '0'; break;
			case 1: randomInt[5] = '1'; break;
			case 2: randomInt[5] = '6'; break;
			case 3: randomInt[5] = '7'; break;
			case 4: randomInt[5] = '9'; break;
			default: return 1;
		}
		for(i = 6; i < ICCID_LENGTH; ++i) {
			randomInt[i] = rand() % 10 + '0';
		}
		int cd = (10 - ValidLuhn(randomInt)) % 10;
		randomInt[ICCID_LENGTH-1] = (char)(cd + '0');
		strcpy(iccid_results[turn], randomInt);
	}

	count = 0;
	for(i = 0; i < T; ++i) {
		if(iccid_results[i][0] == '\0') continue;
		for(j = i + 1; j < T; ++j) {
			if(!strcmp(iccid_results[j], iccid_results[i])) {
				iccid_results[j][0] = '\0';
				count++;
			}
		}
	}
	cout << "ICCID: " << endl;
	for(i = 0; i < T; ++i) {
		if(iccid_results[i][0] != '\0')
			cout << iccid_results[i] << endl;
	}
	cout << "duplicate: " << count << endl;


	return 0;
}
