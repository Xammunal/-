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
void inputed(){

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
    char *menu[4] = {
        "1. Ввести строку",
        "2. Редактировать строку",
        "3. Найти пoлиндром",
        "4. Выход"
        };
    for (int i = 0; i < 4; i++){
        if (i + 1 == position){
            printf("%s <--\n", menu[i]);
        }
        else {
            printf("%s\n", menu[i]);
        }
    }
    
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
                    if (position < 4){
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
        if (digit >= 1 && digit <= 4) {
            newPosition = digit; 
        }
    } 
    return newPosition;
}

int main() {
    int position = 1;
    char stroka[1000] = {};
    while (position != 0){
        menuPrinting(position);
        position = menuControl(position);
        if (position >= 49){
            switch(position){
                case '1':
                    printf("Ввод строки: ");
                    int user = 1;
                    int ind = 0;
                    while (user != '\n'){
                        user = getchar();
                        stroka[ind] = user;
                        ind++;
                    }
                    
                    
                    exitAnyProcces();
                    break;

                case '2':
                    printf("Редактирование строки: \n");
                    exitAnyProcces();
                    break;
                case '3':
                    printf("Палиндром: \n");
                    exitAnyProcces();
                    break;
                case '4':
                    printf("Выход\n");
                    position = '0';
                    break;
                default:
                    break;
            }
            position -= 48;
            
        }
    }
    
    return 0;
}
