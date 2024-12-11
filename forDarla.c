#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int power(int smth){
    int res = 1;
    for (int i = 0; i < smth; i++) {
        res *= 10;
    }
    return res;
}

int rightShift(int num, int k, int lenNum){
    while (k > lenNum) k-=lenNum;
    return num%power(k) * power(lenNum - k) + num/power(k);
}

int leftShift(int num, int m, int lenNum){
    while (m > lenNum) m-=lenNum;
    return num%power(lenNum - m) * power(m) + num/power(lenNum - m);
}

int ok(int num, int digit){
    while (num != 0) {
        if (num % 10 == digit) {
            return 0;
        }
        num /= 10;
    }
    return 1;
}

int main() {
    srand((unsigned)time(NULL));

    int n = 5;
    int k = 36, m = 7;

    int numK, numM;
    int resultNum = 0;

    for (int i = 0; i < n; i++) {
        int randomDigit = 1 + rand() % 9;
        if (ok(resultNum, randomDigit)) {
            resultNum = resultNum * 10 + randomDigit;
        }
        else {
            i--;
        }
    }

    numK = rightShift(resultNum, k, n);
    numM = leftShift(resultNum, m, n);
    printf("%d %d %d\n", numK, resultNum, numM);

    return 0;
}