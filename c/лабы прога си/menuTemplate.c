#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h> 
#include <stdbool.h>

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt); // Сохраняем текущие настройки терминала
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Отключаем канонический режим и эхо
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Применяем новые настройки
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Восстанавливаем старые настройки
    return ch;
}
void inputed(bool is_m, int m, bool is_n, int n){
    if (is_m){
        printf("\n\n\nВведенное значениe M: %d\n", m);
    }
    else{
        printf("\n\n\n");
    }
    if (is_n){
        printf("Введенное значениe N: %d\n", n);
    }
}
void clear() {
    printf("\033[H\033[J");
}
void exitAnyProcces(){
    printf("\n\nНажмите Enter для продолжения");
    int user;
    do {
        user = getchar(); 
    } while (user != '\n'); 
}
void menuPrinting(int position){
    clear();
    char *menu[7] = {
        "1. ",
        "2. ",
        "3. ",
        "4. ",
        "5. ",
        "6. ",
        "7. "
        };
    for (int i = 0; i < 7; i++){
        if (i + 1 == position){
            printf("%s <--\n", menu[i]);
        }
        else{
            printf("%s\n", menu[i]);
        }
    }
    // inputed(isM, m, isN, n);
    
}
int isValidValue(int value, bool isValue){
    if (value <= 11 && value >= 1){
        isValue = true;
        printf("Значениe успешно введено\n");
    }
    else{
        isValue = false;
        printf("Значение не коректно\n");
    }
    return isValue;
}
int menuControl(int position){
    int newPosition = position;
    int user = getch();
    if (user == '\033') {             
        user = getch();
        if (user == '[') {             
            user = getch();            
            switch (user) {
                case 'A': // Up arrow
                    if (position > 1){
                        newPosition--;
                    }
                    break;
                case 'B': // Down arrow
                    if (position < 7){
                        newPosition++;
                    }
                    break;
                default:
                    break;
            }
        }
        else {
            return 0;
        }
    }
    else if (user == 10) {   
        return newPosition + '0';
    }
    else if (isdigit(user)) {  
        int digit = user - '0';
        if (digit >= 1 && digit <= 7) {
            newPosition = digit; 
        }
    } 
    return newPosition;
}
int inputValue(int value){
    clear();
    printf("Введите значение: ");
    scanf("%d", &value);
    return value;
}

int main() {
    int position = 1;
    while (position != 0){
        menuPrinting(position);
        position = menuControl(position);
        if (position >= 49){
            switch(position){
                case '1':
                    printf("Первое задание\n");
                    break;
                case '2':
                    printf("Второе задание\n");
                    break;
                case '3':
                    printf("Третье задание\n");
                    break;
                case '4':
                    printf("Четвертое задание\n");
                    break;
                case '5':
                    printf("Пятое задание\n");
                    break;
                case '6':
                    printf("Шестое задание\n");
                    break;
                case '7':
                    printf("Седьмое задание\n");
                    break;;
                default:
                    break;
            }
            position -= 48;
            exitAnyProcces();
        }
    }
    
    return 0;
}
