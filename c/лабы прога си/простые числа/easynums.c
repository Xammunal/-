# include <stdio.h>
# include <math.h>
# include <time.h>
# include <stdbool.h>

bool isSimple(int num){
    int countDel = 0;
    for (int del = 2; del < num - 1; del++){
        if (num % del == 0){
            countDel++;
        }
    }
    if (countDel == 0){
        return true;
    }
    else{
        return false;
    }
}
int main(){
    int count = 0;
    int lim;
    printf("Введите верхний предел диапазона: ");
    scanf("%d", &lim);
    int start = clock();
    for(int num = 3; num < pow(lim, 0.5); num += 2){
        bool is = true;
        while (num / 10 / 10 != 0 && isSimple(num)){
            is = true;
            if (isSimple(num)){
                num /= 10;
            }
            else{
                is = false;
                break;
            }
        }
        if (is){
            count++;
        }
    }
    printf("Количество супер простых чисел в диапазоне от 3 до %d: %d\n", lim, count);
    int end = clock();
    printf("Выполнилось за %d ms", end - start);
    return 0;

}