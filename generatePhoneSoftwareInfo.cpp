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

#define FORMAT

const int MAX_RESULTS_NUM = 1005;
const int IMEI_LENGTH = 15;
const int IMSI_LENGTH = 15;
const int ICCID_LENGTH = 20;
const int MAC_LENGTH = 17;
const int WIFIMAC_LENGTH = 17;
const int BLUETOOTHMAC_LENGTH = 17;
const int ANDROIDID_LENGTH = 16;

int luhn_checksum(const char* data)
{
    if (data == NULL) return -1;

    int even = 1;
    int sum = 0;
    int double_digit;
    char p;
    int i;

    for (i = IMEI_LENGTH - 2; i >= 0; i--) {
        p = data[i];
        p -= '0';
        if (even) {
            double_digit = p + p;
            sum += double_digit / 10 + double_digit % 10;
        } else {
            sum += p;
        }

        even = 1 - even;
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
	char randomChar[WIFIMAC_LENGTH+1] = {'\0'};



	/* --------------------IMEI-------------------- */

	for(i = 0; i < IMEI_LENGTH+1; ++i) randomInt[i] = '\0';
	char imei_results[MAX_RESULTS_NUM][IMEI_LENGTH+1];
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
				randomInt[IMEI_LENGTH - 1] = (char)(cd + '0');
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
				randomInt[IMEI_LENGTH - 1] = (char)(cd + '0');
			else 
				return 2;
		}
		strcpy(imei_results[turn], randomInt);
	}

	int imei_count = 0;
	for(i = 0; i < T; ++i) {
		// if(!strcmp(imei_results[i], "")) continue;
		if(imei_results[i][0] == '\0') continue;
		for(j = i + 1; j < T; ++j) {
			if(!strcmp(imei_results[j], imei_results[i])) {
				imei_results[j][0] = '\0';
				imei_count++;
			}
		}
	}
#ifndef FORMAT
	cout << "IMEI: " << endl;
	for(i = 0; i < T; ++i) {
		if(imei_results[i][0] != '\0')
			cout << imei_results[i] << endl;
	}
	cout << "duplicate: " << imei_count << endl << endl << endl;
#endif



	/* --------------------IMSI-------------------- */

	for(i = 0; i < IMSI_LENGTH+1; ++i) randomInt[i] = '\0';
	char imsi_results[MAX_RESULTS_NUM][IMSI_LENGTH+1];
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

	int imsi_count = 0;
	for(i = 0; i < T; ++i) {
		if(imsi_results[i][0] == '\0') continue;
		for(j = i + 1; j < T; ++j) {
			if(!strcmp(imsi_results[j], imsi_results[i])) {
				imsi_results[j][0] = '\0';
				imsi_count++;
			}
		}
	}
#ifndef FORMAT
	cout << "IMSI: " << endl;
	for(i = 0; i < T; ++i) {
		if(imsi_results[i][0] != '\0')
			cout << imsi_results[i] << endl;
	}
	cout << "duplicate: " << imsi_count << endl << endl << endl;
#endif



	/* --------------------ICCID-------------------- */

	for(i = 0; i < ICCID_LENGTH+1; ++i) randomInt[i] = '\0';
	char iccid_results[MAX_RESULTS_NUM][ICCID_LENGTH+1];
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

	int iccid_count = 0;
	for(i = 0; i < T; ++i) {
		if(iccid_results[i][0] == '\0') continue;
		for(j = i + 1; j < T; ++j) {
			if(!strcmp(iccid_results[j], iccid_results[i])) {
				iccid_results[j][0] = '\0';
				iccid_count++;
			}
		}
	}
#ifndef FORMAT
	cout << "ICCID: " << endl;
	for(i = 0; i < T; ++i) {
		if(iccid_results[i][0] != '\0')
			cout << iccid_results[i] << endl;
	}
	cout << "duplicate: " << iccid_count << endl << endl << endl;
#endif



	/* --------------------Wi-Fi & Bluetooth Mac-------------------- */
	/* Bluetooth Mac is generated by 7:7:3:1:1:1
	 * 7: 3 terms same with Wi-Fi Mac
	 * 7: 2 terms same with Wi-Fi Mac
	 * 3: 1 terms same with Wi-Fi Mac
	 * 1: totally different with Wi-Fi Mac
	 * 1: "null"
	 * 1: ""
	 */

	for(i = 0; i < MAC_LENGTH+1; ++i) randomChar[i] = '\0';
	char wifimac_results[MAX_RESULTS_NUM][WIFIMAC_LENGTH+1];
	memset(wifimac_results, 0, sizeof(wifimac_results));
	char bluetoothmac_results[MAX_RESULTS_NUM][BLUETOOTHMAC_LENGTH+1];
	memset(bluetoothmac_results, 0, sizeof(bluetoothmac_results));
	int bluetoothmackind[6] = {0};
	turn = -1;
	_T = T;
	while(_T--) {
		turn++;
		int choice2 = rand() % 2;
		for(i = 0; i < 6; ++i) {
			for(j = 0; j < 2; ++j) {
				int choice = rand() % 2;
				if(choice == 0) {	// 0 ~ 9
					randomChar[i*3+j] = rand() % 10 + '0';
				}
				else {	// a ~ f || A ~ F
					if(choice2 == 0) 
						randomChar[i*3+j] = rand() % 6 + 'a';
					else
						randomChar[i*3+j] = rand() % 6 + 'A';
				}
			}
			if(i != 5) randomChar[i*3+2] = ':';
		}
		strcpy(wifimac_results[turn], randomChar);
		int choiceblue = rand() % 20;
		/*
			switch(choiceblue) {
			case 0:
			case 1:
			case 2: 
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			default: return 1;
		*/
		if(choiceblue < 17) { // at least 1 same
			for(i = 0; i < 3; ++i) randomChar[i] = wifimac_results[turn][i];
			if(choiceblue < 14) { // at least 2 same
				for(i = 3; i < 6; ++i) randomChar[i] = wifimac_results[turn][i];
				if(choiceblue < 7) { // 3 same
					bluetoothmackind[0]++;
					for(i = 6; i < 9; ++i) randomChar[i] = wifimac_results[turn][i];
				}
				else { // 2 same
					bluetoothmackind[1]++;
					for(i = 0; i < 1; ++i) {
						for(j = 0; j < 2; ++j) {
							int choice = rand() % 2;
							if(choice == 0) { // 0 ~ 9
								randomChar[i*3+j+6] = rand() % 10 + '0';
							}
							else { // a ~ f || A ~ F
								if(choice2 == 0)
									randomChar[i*3+j+6] = rand() % 6 + 'a';
								else
									randomChar[i*3+j+6] = rand() % 6 + 'A';
							}
						}
						randomChar[i*3+8] = ':';
					}
				}
			}
			else { // 1 same
				bluetoothmackind[2]++;
				for(i = 0; i < 2; ++i) {
					for(j = 0; j < 2; ++j) {
						int choice = rand() % 2;
						if(choice == 0) { // 0 ~ 9
							randomChar[i*3+j+3] = rand() % 10 + '0';
						}
						else { // a ~ f || A ~ F
							if(choice2 == 0)
								randomChar[i*3+j+3] = rand() % 6 + 'a';
							else
								randomChar[i*3+j+3] = rand() % 6 + 'A';
						}
					}
					randomChar[i*3+5] = ':';
				}
			}
			for(i = 0; i < 3; ++i) {
				for(j = 0; j < 2; ++j) {
					int choice = rand() % 2;
					if(choice == 0) { // 0 ~ 9
						randomChar[i*3+j+9] = rand() % 10 + '0';
					}
					else { // a ~ f || A ~ F
						if(choice2 == 0)
							randomChar[i*3+j+9] = rand() % 6 + 'a';
						else
							randomChar[i*3+j+9] = rand() % 6 + 'A';
					}
				}
				if(i != 2) randomChar[i*3+11] = ':';
			}
		}
		else if(choiceblue == 17) {	// totally different
			bluetoothmackind[3]++;
			for(i = 0; i < 6; ++i) {
				for(j = 0; j < 2; ++j) {
					int choice = rand() % 2;
					if(choice == 0) {	// 0 ~ 9
						randomChar[i*3+j] = rand() % 10 + '0';
					}
					else {	// a ~ f || A ~ F
						if(choice2 == 0) 
							randomChar[i*3+j] = rand() % 6 + 'a';
						else
							randomChar[i*3+j] = rand() % 6 + 'A';
					}
				}
				if(i != 5) randomChar[i*3+2] = ':';
			}
		}
		else if(choiceblue == 18) {	// "null"
			bluetoothmackind[4]++;
			randomChar[0] = 'n';
			randomChar[1] = 'u';
			randomChar[2] = 'l';
			randomChar[3] = 'l';
			randomChar[4] = '\0';
		}
		else {	// choice == 19, ""
			bluetoothmackind[5]++;
			randomChar[0] = '\0';
		}
		strcpy(bluetoothmac_results[turn], randomChar);
	}

	int wifimac_count = 0, bluetoothmac_count = 0;
	for(i = 0; i < T; ++i) {
		if(wifimac_results[i][0] == '\0') continue;
		for(j = i + 1; j < T; ++j) {
			if(!strcmp(wifimac_results[i], wifimac_results[j])) {
				wifimac_results[j][0] = '\0';
				wifimac_count++;
			}
		}
	}

	for(i = 0; i < T; ++i) {
		if(bluetoothmac_results[i][0] == '\0') continue;
		if(!strcmp(bluetoothmac_results[i], "null")) continue;	// special judge!!
		for(j = i + 1; j < T; ++j) {
			if(!strcmp(bluetoothmac_results[i], bluetoothmac_results[j])) {
				bluetoothmac_results[j][0] = '\0';
				bluetoothmac_count++;
			}
		}
	}
#ifndef FORMAT
	cout << "Wi-Fi Mac: " << endl;
	for(i = 0; i < T; ++i) {
		if(wifimac_results[i][0] != '\0')
			cout << wifimac_results[i] << endl;
	}
	cout << "duplicate: " << wifimac_count << endl << endl << endl;

	cout << "Bluetooth Mac: " << endl;
	for(i = 0; i < T; ++i) {
		// if(bluetoothmac_results[i][0] != '\0')
			cout << bluetoothmac_results[i] << endl;
	}
	cout << "duplicate: " << bluetoothmac_count << endl;
	cout << "Bluetooth Mac kind(7:7:3:1:1:1): " << bluetoothmackind[0] << " " << bluetoothmackind[1] << " " << \
		bluetoothmackind[2] << " " << bluetoothmackind[3] << " " << bluetoothmackind[4] << " " << \
		bluetoothmackind[5] << endl << endl << endl;
#endif



	/* --------------------Android ID-------------------- */
	for(i = 0; i < ANDROIDID_LENGTH+1; ++i) randomChar[i] = '\0';
	char androidid_results[MAX_RESULTS_NUM][ANDROIDID_LENGTH+1];
	memset(androidid_results, 0, sizeof(androidid_results));
	turn = -1;
	_T = T;
	while(_T--) {
		turn++;
		for(i = 0; i < ANDROIDID_LENGTH; i++) {
			int choice = rand() % 16;
			if(choice < 10) {
				randomChar[i] = (char)(choice + '0');
			}
			else {
				randomChar[i] = (char)(choice - 10 + 'a');
			}
			strcpy(androidid_results[turn], randomChar);
		}
	}

	int androidid_count = 0;
	for(i = 0; i < T; ++i) {
		if(androidid_results[i][0] == '\0') continue;
		for(j = i + 1; j < T; ++j) {
			if(!strcmp(androidid_results[j], androidid_results[i])) {
				androidid_results[j][0] = '\0';
				androidid_count++;
			}
		}
	}
#ifndef FORMAT
	cout << "Android ID: " << endl;
	for(i = 0; i < T; ++i) {
		if(androidid_results[i][0] != '\0')
			cout << androidid_results[i] << endl;
	}
	cout << "duplicate: " << androidid_count << endl << endl << endl;
#endif




	/* ********************FORMAT output******************** */

#ifdef FORMAT
	cout << "       IMEI\t\t   IMSI\t\t\tICCID\t\t    Wi-Fi Mac\t\tBluetooth Mac\t     Android ID" << endl;
	for(i = 0; i < T; ++i) {
		cout << "{\"";
		if(imei_results[i][0] != '\0')
			cout << imei_results[i];
		cout << "\", \"";
		if(imsi_results[i][0] != '\0')
			cout << imsi_results[i];
		cout << "\", \"";
		if(iccid_results[i][0] != '\0')
			cout << iccid_results[i];
		cout << "\", \"";
		if(wifimac_results[i][0] != '\0')
			cout << wifimac_results[i];
		cout << "\", \"";
			cout << bluetoothmac_results[i];
		cout << "\", \"";
		if(androidid_results[i][0] != '\0')
			cout << androidid_results[i];
		cout << "\", },\t//";
		cout << i;
		cout << endl;
	}
	if(imei_count != 0) cout << "IMEI duplicate: " << imei_count << endl;
	if(imsi_count != 0) cout << "IMSI duplicate: " << imsi_count << endl;
	if(iccid_count != 0) cout << "ICCID duplicate: " << iccid_count << endl;
	if(wifimac_count != 0) cout << "Wi-Fi Mac duplicate: " << wifimac_count << endl;
	if(bluetoothmac_count != 0) cout << "Bluetooth Mac duplicate: " << bluetoothmac_count << endl;
//	cout << "Bluetooth Mac kind(7:7:3:1:1:1): " << bluetoothmackind[0] << " " << bluetoothmackind[1] << " " << \
		bluetoothmackind[2] << " " << bluetoothmackind[3] << " " << bluetoothmackind[4] << " " << \
		bluetoothmackind[5] << endl;
	if(androidid_count != 0) cout << "Android ID duplicate: " << androidid_count << endl;

#endif
	return 0;
}
