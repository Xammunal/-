#include <stdio.h> 
#include <stdbool.h> 
#include <string.h> 
#include <stdlib.h>
#include <time.h> 

int isSimple(long long num) {  
    if (num % 2 != 0) { 
        for (long long del = 3; del * del <= num; del += 2) { 
            if (num % del == 0) {
                return 0; 
            }
        }
    }
    return 1; 
}  
void simple(long long num, unsigned long long lim_f, long long hypers_f[], int* count) { 
    if (0 < num && num <= lim_f) { 
        hypers_f[*count] = num; 
        *count += 1; 
    } 

    for (int i = 1; i <= 9; i += 2) { 
        if (num * 10 + i <= lim_f && isSimple(num * 10 + i)) { 
           simple(num * 10 + i, lim_f, hypers_f, count); 
        } 
    } 
}

int main(int argX, char* limArg[]) { 
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    unsigned long long lim = 4294967296; 
    long long hypers[1000]; 
    int count = 0; 

    if (argX > 1) lim = atoll(limArg[1]); 

    printf("Введите диапазон поиска гиперпростых (до 2 ^ 32): "); 

    simple(1, lim, hypers, &count); 
    simple(2, lim, hypers, &count); 
    simple(3, lim, hypers, &count); 
    simple(5, lim, hypers, &count); 
    simple(7, lim, hypers, &count); 

    printf("Суперпростые числа до %lld:\n", lim); 

    for (int i = 0; i < count; i++){
        printf("%lld\n",hypers[i]);
    }

    printf("Всего суперпростых чисел: %d\n", count); 
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время выполнения: %f секунд\n", cpu_time_used);
} 

//cd "/Users/ivansalukhov/Documents/projects vs/" && gcc forTestSmth.c -o forTestSmth && "/Users/ivansalukhov/Documents/projects vs/"forTestSmth