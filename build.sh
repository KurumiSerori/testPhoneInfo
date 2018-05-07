#!/bin/sh
gcc -o imei.out testIMEI.C -g
gcc -o iccid.out testICCID.c -g
g++ -o generateSoft.out generatePhoneSoftwareInfo.cpp -g
g++ -o generateHard.out generatePhoneHardwareInfo.cpp -g
