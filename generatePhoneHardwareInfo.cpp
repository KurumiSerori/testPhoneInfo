#include <iostream>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <ctype.h>

using namespace std;

#define FORMAT
#define NUMBERED

const int MAX_RESULTS_NUM = 1005;
const char ALPHABET[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',};
const int SERIALNUM_LENGTH = 16;

int main()
{
	srand( time(NULL) );
	cout << "Case NUM(<=1000): ";
	int T, i, j, turn, _T;
	cin >> T;
	if(T > 1000) return -1;

	char randomInt[SERIALNUM_LENGTH+1] = {'\0'};
	char randomChar[SERIALNUM_LENGTH+1] = {'\0'};



	/* --------------------Serial Num-------------------- */

	for(i = 0; i < SERIALNUM_LENGTH+1; ++i) randomChar[i] = '\0';
	char serialnum_results[MAX_RESULTS_NUM][SERIALNUM_LENGTH+1];
	turn = -1;
	_T = T;
	int length;	// 16:15:14:13 = 6:2:1:1;
	while(_T--) {
		turn++;
		int choice = rand() % 10;
		if(choice < 6) {
			length = 16;
		}
		else if(choice < 8) {
			length = 15;
		}
		else if(choice < 9) {
			length = 14;
		}
		else if(choice < 10) {
			length = 13;
		}
		//cout << length << endl;
		for(i = 0; i < length; ++i) {
			randomChar[i] = ALPHABET[rand() % 16];
		}
		randomChar[i] = '\0';
		strcpy(serialnum_results[turn], randomChar);
	}

	int serialnum_count = 0;
	for(i = 0; i < T; ++i) {
		if(serialnum_results[i][0] == '\0') continue;
		for(j = i + 1; j < T; ++j) {
			if(!strcmp(serialnum_results[j], serialnum_results[i])) {
				serialnum_results[j][0] = '\0';
				serialnum_count++;
			}
		}
	}
#ifndef FORMAT
	cout << "Serial Num: " << endl;
	for(i = 0; i < T; ++i) {
		if(serialnum_results[i][0] != '\0') 
			cout << serialnum_results[i] << endl;
	}
	cout << "duplicate: " << serialnum_count << endl << endl << endl;
#endif



	/* --------------------FORMAT Output-------------------- */

#ifdef FORMAT
	cout << " Android Serial Num" << endl;
	for(i = 0; i < T; ++i) {
		cout << "{\"";
		if(serialnum_results[i][0] != '\0')
			cout << serialnum_results[i];
		cout << "\", },";
#ifdef NUMBERED
		cout << "\t//" << i;
#endif
		cout << endl;
	}
	if(serialnum_count != 0) cout << "Android Serial Num duplicate: " << serialnum_count << endl;
#endif

	return 0;
}
