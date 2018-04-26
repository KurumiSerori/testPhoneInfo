#!/bin/sh
gcc -o imei.out testIMEI.C -g
gcc -o iccid.out testICCID.c -g
g++ -o generateSoft.out generatePhoneSoftInfo.cpp -g
