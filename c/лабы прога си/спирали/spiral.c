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
void exitAnyProcces(){
    printf("\n\nНажмите Enter для продолжения");
    int user;
    do {
        user = getchar(); 
    } while (user != '\n'); 
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
int inputValue(int value){
    clear();
    printf("Введите значение: ");
    scanf("%d", &value);
    if (value >= 3 && value <= 11){
        return value;
    }
    return 0;
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
void menuPrinting(int position, bool isM, int m, bool isN, int n){
    clear();
    char *menu[7] = {
        "1. Введите М",
        "2. Введите N",
        "3. Спираль вправо внутрь",
        "4. Спираль влево внутрь",
        "5. Спираль наружу вправо",
        "6. Спираль наружу влево",
        "7. Выход"
        };
    for (int i = 0; i < 7; i++){
        if (i + 1 == position){
            printf("%s <--\n", menu[i]);
        }
        else{
            printf("%s\n", menu[i]);
        }
    }
    inputed(isM, m, isN, n);
}

void spiralPrinting(int m, int n, int a[m][n]) {
    printf("\n\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", a[i][j]);
        }
        printf("\n");
    }
}
void spiralRightIn(int m, int n) {
    int a[m][n]; 
    int value = 1; 

    int top = 0, bottom = m - 1, left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) {
            a[top][i] = value++;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            a[i][right] = value++;
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                a[bottom][i] = value++;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                a[i][left] = value++;
            }
            left++;
        }
    }

    spiralPrinting(m, n, a);
}
void spiralLeftIn(int m, int n) {
    int a[m][n]; 
    int value = 1; 

    int top = 0, bottom = m - 1, left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        for (int i = right; i >= left; i--) {
            a[top][i] = value++;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            a[i][left] = value++;
        }
        left++;

        if (top <= bottom) {
            for (int i = left; i <= right; i++) {
                a[bottom][i] = value++;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                a[i][right] = value++;
            }
            right--;
        }
    }

    spiralPrinting(m, n, a);
}
void spiralRightOut(int m, int n) {
    int a[m][n]; 
    int value = m*n; 

    int top = 0, bottom = m - 1, left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        for (int i = right; i >= left; i--) {
            a[top][i] = value--;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            a[i][left] = value--;
        }
        left++;

        if (top <= bottom) {
            for (int i = left; i <= right; i++) {
                a[bottom][i] = value--;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                a[i][right] = value--;
            }
            right--;
        }
    }

    spiralPrinting(m, n, a);
}
void spiralLeftOut(int m, int n) {
    int a[m][n];
    int value = m*n;

    int top = 0, bottom = m - 1, left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) {
            a[top][i] = value--;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            a[i][right] = value--;
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                a[bottom][i] = value--;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                a[i][left] = value--;
            }
            left++;
        }
    }
    spiralPrinting(m, n, a);
}

int main() {
    int position = 1;
    int m = 0, n = 0;
    bool isM = false, isN = false;
    while (position != 0){
        menuPrinting(position, isM, m, isN, n);
        position = menuControl(position);
        if (position >= 49){
            switch(position){
                case '1':
                    m = inputValue(m);
                    if (m == 0){
                        printf("Некорректное значение");
                        break;
                    }
                    isM = isValidValue(m, isM);
                    break;
                case '2':
                    n = inputValue(n);
                    if (n == 0){
                        printf("Некорректное значение");
                        break;
                    }
                    isN = isValidValue(n, isN);
                    break;
                case '3':
                    spiralRightIn(m, n);
                    break;
                case '4':
                    spiralLeftIn(m, n);
                    break;
                case '5':
                    spiralRightOut(m, n);
                    break;
                case '6':
                    spiralLeftOut(m, n);
                    break;
                case '7':
                    printf("Выход");
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
