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
void clear() {
    printf("\033[H\033[J");
}

void mapPrinting(int m, int n, char a[m][n], int y, int x) {
    clear();

    printf("w - закончить действие \nq/esc - выход\n");
    for (int i = 0; i < m ; i++) {
        for (int j = 0; j < n ; j++) {
            if (i == x && j == y){
                printf("%c", '@');
            }
            else{
                printf("%c", a[i][j]);
            }
        }
        printf("\n");
    }
}

int main(){
    int m = 50, n = 100;
    char labirint[m][n];
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
    int x = 0, y = 0;
    int command = 0;

    while (command != 'q'){
        command = getch();
        if (command == '\033') {
            command = getch();
            if (command == '[') {             
                command = getch();            
                switch (command) {
                    case 'A': // Up arrow
                        if (y > 1){y--;}
                        break;
                    case 'B': // Down arrow
                        if (y < m - 2){y++;}
                        break;
                    case 'C': // Right arrow
                        if (x < n - 2){x++;}
                        break;
                    case 'D': // Left arrow
                        if (x > 1){x--;}
                        break;
                    default:
                        break;
                }
            }
            else{
                command = 'q';
            }
        }
        if (command == '\n'){
            printf("enter");
        }


        mapPrinting(m, n, labirint, x, y);
    }
    
    return 0;
}