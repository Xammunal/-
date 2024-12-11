#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h> 
#include <stdbool.h>
#include <string.h> 
//надо шаги
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
    char *menu[4] = {
        "1. Новый лабиринт",
        "2. Текущий лабиринт",
        "3. Решить",
        "4. Выход"
        };
    for (int i = 0; i < 4; i++){
        if (i + 1 == position){
            printf("%s <--\n", menu[i]);
        }
        else{
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
        if (digit >= 1 && digit <= 3) {
            newPosition = digit; 
        }
    } 
    return newPosition;
}
void labirintPrinting(int m, int n, char labirint[m][n], int y, int x) {
    clear();
    printf("r - поставить игрока\ne - поставить финиш\nw - поставить препядствие\nd - убрать\nq/esc - выход\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == x && j == y){
                printf("%c", '@');
            }
            else{
                printf("%c", labirint[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int position = 1;
    int m = 1, n = 1;
    bool isLabirint = false;
    char labirint[20][20];
    while (position != 0){
        menuPrinting(position);
        position = menuControl(position);
        if (position >= 49){
            switch(position){
                case '1':
                isLabirint = true;
                printf("Введите размер лабиринта (m x n) ");
                scanf("%dx%d", &m, &n);
                labirint[m][n];
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        if (i == 0 || i == m - 1){
                            labirint[i][j] = '-';
                        }
                        else if (j == 0 || j == n - 1){
                            labirint[i][j] = '|';
                        }
                        else{
                            labirint[i][j] = '.';
                        }
                    }
                }       

                case '2':
                if (isLabirint){
                    int x = 0, y = 0;
                    int command = 0;
                    bool isExit = false;
                    bool isStart = false;
                    while (command != 'q'){
                        command = getch();
                        if (command == '\033') {             
                            command = getch();
                            if (command == '[') {             
                                command = getch();            
                                switch (command) {
                                    case 'A': // Up arrow
                                        if (y > 0){y--;}
                                        break;
                                    case 'B': // Down arrow
                                        if (y < m - 1){y++;}
                                        break;
                                    case 'C': // Right arrow
                                        if (x < n - 1){x++;}
                                        break;
                                    case 'D': // Left arrow
                                        if (x > 0){x--;}
                                        break;
                                    default:
                                        break;
                                }
                            }
                            else{
                                command = 'q';
                            }
                        }
                        else if(command == 'e' && isExit == false && (labirint[y][x] == '-' || labirint[y][x] == '|')){
                            labirint[y][x] = 'f';
                            isExit = true;
                        }
                        else if(command == 'w' && labirint[y][x] == '.'){
                            labirint[y][x] = '#';
                        }
                        else if (command == 'd'){
                            if (labirint[y][x] == 'f'){
                                if (y == 0 || y == m - 1){
                                    labirint[y][x] = '-';
                                }
                                else if (x == 0 || x == n - 1){
                                    labirint[y][x] = '|';
                                }
                                isExit = false;
                            }
                            else if (labirint[y][x] != '|' && labirint[y][x] != '-'){
                                if (labirint[y][x] == 'O'){
                                    isStart = false;
                                }
                                labirint[y][x] = '.';
                            }
                            
                        }
                        else if (command == 'r' && isStart == false && labirint[y][x] == '.'){
                            labirint[y][x] = 'O';
                            isStart = true;
                        }

                        labirintPrinting(m, n, labirint, x, y);
                    }
                }
                else{
                    printf("Лабиринт не был создан\n");
                }
                break;
                case '3':
                    if (isLabirint) {
                        printf("Вот тут решение как бы должно быть: "); 
                    } else {
                        printf("Лабиринт не создан.\n");
                    }
                    break;
                case '4':
                    return 0;
                default:
                    break;
            }
            position -= 48;
            exitAnyProcces();
        }
    }
    
    return 0;
}
