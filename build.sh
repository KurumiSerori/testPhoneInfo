#!/bin/sh
gcc -o imei.out testIMEI.C -g
gcc -o iccid.out testICCID.c -g
g++ -o generate.out generatePhoneInfo.cpp -g
