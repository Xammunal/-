#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

int getch() {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

void clear_screen() {
    printf("\033[H\033[J"); 
}

bool is_user_input_correct(char for_verification, char ok[]) {
    for (int j = 0; j < 11; j++) {
        if (for_verification == ok[j]) {
            return true;
        }
    }
    return false;
}

int isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return 1; 
            }
            return 0; 
        }
        return 1; 
    }
    return 0; 
}

int calculateDayOfWeek(int day, int month, int year) {
    // Если месяц январь или февраль, изменяем месяц и год
    if (month < 3) {
        month += 12;
        year--;
    }

    int K = year % 100;       // Год века
    int J = year / 100;       // Нулевая часть века

    // Формула Зеллера
    int h = (day + (13 * (month + 1)) / 5 + K + K / 4 + J / 4 - 2 * J) % 7;

    // Приводим h к диапазону [0,6] (где 0 - суббота)
    h = (h + 7) % 7;

    return h;
}

const char* getDayName(int dayOfWeek) {
    switch (dayOfWeek) {
    case 0: return "суббота";
    case 1: return "воскресенье";
    case 2: return "понедельник";
    case 3: return "вторник";
    case 4: return "среда";
    case 5: return "четверг";
    case 6: return "пятница";
    default: return "ошибка";
    }
}

void inputed(bool is_time3, char *time3, bool is_count_days, int count_days, bool is_time1, char *time1, bool is_time2, char *time2,bool is_date1, char *date1, bool is_date2, char *date2, int day1, int month1, int year1, int day2, int month2, int year2) {
    if (is_time1) {
        printf("\n\n\nВведенное время 1: ");
        for (int i = 0; i < 8; i++) {
            printf("%c", time1[i]);
        }
    }
    if (is_time2) {
        printf("\nВведенное время 2: ");
        for (int i = 0; i < 8; i++) {
            printf("%c", time2[i]);
        }
    }
    if (is_date1) {
        printf("\n\nВведенная дата 1: ");
        for (int i = 0; i < 10; i++) {
            printf("%c", date1[i]);
        }
        int day_of_week1 = calculateDayOfWeek(day1, month1, year1);
        const char *day_name1 = getDayName(day_of_week1);
        printf(" (%s)", day_name1);
    }
    if (is_date2) {
        printf("\nВведенная дата 2: ");
        for (int i = 0; i < 10; i++) {
            printf("%c", date2[i]);
        }
        int day_of_week2 = calculateDayOfWeek(day2, month2, year2);
        const char* day_name2 = getDayName(day_of_week2);
        printf(" (%s)\n", day_name2);
    }
    if (is_count_days) {
        printf("\n\nВведенное количество дней: %d", count_days);
    }
    if (is_time3) {
        printf("\n\nВведенное время 3: ");
        for (int i = 0; i < 8; i++) {
            printf("%c", time3[i]);
        }
    }
}

int menu(bool is_time3, char *time3, bool is_count_days, int count_days, int pos_of_arrow, bool is_time1, char* time1, bool is_time2, char* time2, bool is_date1, char* date1, bool is_date2, char* date2, int day1, int month1, int year1, int day2, int month2, int year2) {
    int user = getch();
    bool is_ENT = false;
    const char* arrow = "<--";
    if (user == '\33'){
        user = getch();
        if (user == '['){
            user = getch();
            switch (user) {
                case 'A':
                    if (pos_of_arrow > 49) {
                        pos_of_arrow -= 1;
                    }
                    break;
                case 'B':
                    if (pos_of_arrow < 57) {
                        pos_of_arrow += 1;
                    }
                    break;
                default:
                    break;
            }
        }
        else{
            return 0;
        }
    }
    else if (user == '\n'){
        is_ENT = true;
    }
    else if (isdigit(user)){
        switch (user)
        {
        case '1':
            pos_of_arrow = 49;
            break;
        case '2':
            pos_of_arrow = 50;
            break;
        case '3':
            pos_of_arrow = 51;
            break;
        case '4':
            pos_of_arrow = 52;
            break;
        case '5':
            pos_of_arrow = 53;
            break;
        case '6':
            pos_of_arrow = 54;
            break;
        case '7':
            pos_of_arrow = 55;
            break;
        case '8':
            pos_of_arrow = 56;
            break;
        case '9':
            pos_of_arrow = 57;
            break;
        default:
            break;
        }
    }
    
    if (pos_of_arrow == 49)
    {
        clear_screen();
        printf("1) Ввод 1 времени %s\n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
        inputed(is_time3, time3, is_count_days, count_days, is_time1, time1, is_time2, time2, is_date1, date1, is_date2, date2, day1, month1, year1, day2, month2, year2);
    }
    else if (pos_of_arrow == 50)
    {
        clear_screen();
        printf("1) Ввод 1 времени \n2) Ввод 1 даты  %s\n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
        inputed(is_time3, time3, is_count_days, count_days, is_time1, time1, is_time2, time2, is_date1, date1, is_date2, date2, day1, month1, year1, day2, month2, year2);
    }
    else if (pos_of_arrow == 51)
    {
        clear_screen();
        printf("1) Ввод 1 времени \n2) Ввод 1 даты \n3) Ввод 2 времени  %s\n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
        inputed(is_time3, time3, is_count_days, count_days, is_time1, time1, is_time2, time2, is_date1, date1, is_date2, date2, day1, month1, year1, day2, month2, year2);
    }
    else if (pos_of_arrow == 52)
    {
        clear_screen();
        printf("1) Ввод 1 времени \n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты  %s\n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
        inputed(is_time3, time3, is_count_days, count_days, is_time1, time1, is_time2, time2, is_date1, date1, is_date2, date2, day1, month1, year1, day2, month2, year2);
    }
    else if (pos_of_arrow == 53)
    {
        clear_screen();
        printf("1) Ввод 1 времени \n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат %s\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
        inputed(is_time3, time3, is_count_days, count_days, is_time1, time1, is_time2, time2, is_date1, date1, is_date2, date2, day1, month1, year1, day2, month2, year2);
    }
    else if (pos_of_arrow == 54)
    {
        clear_screen();
        printf("1) Ввод 1 времени \n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней  %s\n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
        inputed(is_time3, time3, is_count_days, count_days, is_time1, time1, is_time2, time2, is_date1, date1, is_date2, date2, day1, month1, year1, day2, month2, year2);
    }
    else if (pos_of_arrow == 55)
    {
        clear_screen();
        printf("1) Ввод 1 времени\n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1) %s\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
        inputed(is_time3, time3, is_count_days, count_days, is_time1, time1, is_time2, time2, is_date1, date1, is_date2, date2, day1, month1, year1, day2, month2, year2);
    }
    else if (pos_of_arrow == 56)
    {
        clear_screen();
        printf("1) Ввод 1 времени\n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3 %s\n9) Результат сложения (время 1 и время 3)\n", arrow);
        inputed(is_time3, time3, is_count_days, count_days, is_time1, time1, is_time2, time2, is_date1, date1, is_date2, date2, day1, month1, year1, day2, month2, year2);
    }
    else if (pos_of_arrow == 57)
    {
        clear_screen();
        printf("1) Ввод 1 времени\n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3) %s\n", arrow);
        inputed(is_time3, time3, is_count_days, count_days, is_time1, time1, is_time2, time2, is_date1, date1, is_date2, date2, day1, month1, year1, day2, month2, year2);
    }
    if (is_ENT) {
        return '\n';
    }
    else {
        return pos_of_arrow;
    }
}

void exitProcess() {
    printf("\n\nНажмите Enter для продолжения");
    int user;
    do {
        user = getchar(); 
    } while (user != '\n'); 
}

int isValidTime(int hour, int minute, int second) {
    return hour < 24 && minute < 60 && second < 60;
}

int isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) {
        return 0; 
    }
    int maxDays;
    if (month == 2) {
        maxDays = isLeapYear(year) ? 29 : 28; 
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30; // Апрель, Июнь, Сентябрь, Ноябрь
    }
    else {
        maxDays = 31; // Январь, Март, Май, Июль, Август, Октябрь, Декабрь
    }
    return day >= 1 && day <= maxDays; // Проверка дня
}

int maxDate(int day1, int month1, int year1, int day2, int month2, int year2) {
    int res;
    if (year1 > year2 ||
        (year1 == year2 && month1 > month2) ||
        (year1 == year2 && month1 == month2 && day1 > day2)) {
        res = 1; // date1 больше
    }
    else {
        res = 2; // date2 больше или равна
    }
    return res;
}

int daysInMonth(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    return (month == 4 || month == 6 || month == 9 || month == 11) ? 30 : 31;
}

void subtractionDates(int maxDay, int maxMonth, int maxYear, int day, int month, int year, int maxHour, int maxMinute, int maxSecond, int hour, int minute, int second) {
    // Разница по секундами, минутам и часам
    int diffSecond = maxSecond - second;
    int diffMinute = maxMinute - minute;
    int diffHour = maxHour - hour;

    // Корректируем время, если разница отрицательна
    if (diffSecond < 0) {
        diffSecond += 60;
        diffMinute -= 1;
    }
    if (diffMinute < 0) {
        diffMinute += 60;
        diffHour -= 1;
    }
    if (diffHour < 0) {
        diffHour += 24;
        maxDay -= 1;
    }

    // Разница по дням
    int diffDay = maxDay - day;
    // Корректируем дни и месяцы
    while (diffDay < 0) {
        maxMonth -= 1;
        if (maxMonth <= 0) {
            maxMonth = 12;
            maxYear -= 1;
        }
        diffDay += daysInMonth(maxMonth, maxYear);
    }

    // Выводим результат в формате "дней часы:минуты:секунды"
    printf("%d дней %02d:%02d:%02d\n", diffDay, diffHour, diffMinute, diffSecond);
}

void sumTimes(int hour1, int minute1, int second1, int hour2, int minute2, int second2) {
    int totalSeconds = second1 + second2;
    int totalMinutes = minute1 + minute2 + totalSeconds / 60;
    int totalHours = hour1 + hour2 + totalMinutes / 60;

    totalSeconds %= 60;
    totalMinutes %= 60;

    printf("%02d:%02d:%02d ", totalHours, totalMinutes, totalSeconds);
}

void sumDaysAndDate(int count_days, int day, int month, int year) {
    day += count_days;
    while (day > daysInMonth(month, year)) {
        day -= daysInMonth(month, year);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    while (day <= 0) {
        month--;
        if (month < 1) {
            month = 12;
            year--;
        }
        day += daysInMonth(month, year);
    }
    printf("%02d.%02d.%04d ", day, month, year);
    int day_of_week = calculateDayOfWeek(day, month, year);
        const char *day_name = getDayName(day_of_week);
        printf("(%s)", day_name);
}

int main() {
    setlocale(LC_CTYPE, "Rus");

    int pos_of_arrow = 49;
    int choice;
    const char *arrow = "<--";

    printf("1) Ввод 1 времени %s\n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
    
    bool is_count_days = false;
    int count_days = 0;

    int day1 = 0;
    int month1 = 0;
    int year1 = 0;
    char date1[] = { 'd', 'd', '.', 'm', 'm', '.', 'y', 'y', 'y', 'y'};
    bool is_date1 = false;

    int day2 = 0;
    int month2 = 0;
    int year2 = 0;
    char date2[] = { 'd', 'd', '.', 'm', 'm', '.', 'y', 'y', 'y', 'y'};
    bool is_date2 = false;
    
    char time1[] = { 'h', 'h', ':', 'm', 'm', ':', 's', 's' };
    bool is_time1 = false;

    char time2[] = { 'h', 'h', ':', 'm', 'm', ':', 's', 's' };
    bool is_time2 = false;

    char time3[] = { 'h', 'h', ':', 'm', 'm', ':', 's', 's' };
    bool is_time3 = false;

    char ok_for_time[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':' };
    char ok_for_date[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };
    while (pos_of_arrow != 0) {
        choice = pos_of_arrow;
        pos_of_arrow = menu(is_time3, time3, is_count_days, count_days, pos_of_arrow, is_time1, time1, is_time2, time2, is_date1, date1, is_date2, date2, day1, month1, year1, day2, month2, year2);
        if (pos_of_arrow == '\n') {
            switch (choice - 48)
            {
            case 1: // первое время
                for (int i = 0; i < 8; i++) {
                    clear_screen();
                    printf("Введите время 1 (в формате чч:мм:сс): ");
                    for (int j = 0; j < i; j++) {
                        printf("%c", time1[j]);
                    }
                    if (time1[i] != ':') {
                        time1[i] = getch();
                        if (is_user_input_correct(time1[i], ok_for_time)) {
                            if (time1[i] == ':') {
                                time1[i] = time1[i-1];
                                time1[i - 1] = '0';
                            }
                        }
                        else {
                            i--;
                        }
                    }
                }
                clear_screen();
                printf("Введите время 1 (в формате чч:мм:сс): ");
                for (int j = 0; j < 8; j++) {
                    printf("%c", time1[j]);
                }

                int hour1 = (time1[0] - 48) * 10 + time1[1] - 48;
                int minute1 = (time1[3] - 48) * 10 + time1[4] - 48;
                int second1 = (time1[6] - 48) * 10 + time1[7] - 48;
                if (isValidTime(hour1, minute1, second1)) {
                    is_time1 = true;
                    char worker_time1[] = { hour1, minute1, second1 };
                    printf("\nВремя 1 успешно введено\n");
                }
                else {
                    printf("\nНедопустимое значение времени. Попробуйте еще раз!");
                    is_time1 = false;
                }

                exitProcess();
                clear_screen();
                printf("1) Ввод 1 времени %s\n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
                break;
            case 2: // первая дата
                for (int i = 0; i < 10; i++) {
                    clear_screen();
                    printf("Введите дату 1 (в формате дд.мм.гггг): ");
                    for (int j = 0; j < i; j++) {
                        printf("%c", date1[j]);
                    }
                    if (date1[i] != '.') {
                        date1[i] = getch();
                        if (is_user_input_correct(date1[i], ok_for_date)) {
                            if (date1[i] == '.') {
                                date1[i] = date1[i - 1];
                                date1[i - 1] = '0';
                            }
                        }
                        else {
                            i--;
                        }
                    }
                }

                clear_screen();
                printf("Введите дату 1 (в формате дд.мм.гггг): ");
                for (int j = 0; j < 10; j++) {
                    printf("%c", date1[j]);
                }
                day1 = (date1[0] - 48) * 10 + date1[1] - 48;
                month1 = (date1[3] - 48) * 10 + date1[4] - 48;
                year1 = (date1[6] - 48) * 1000 + (date1[7] - 48) * 100 + (date1[8] - 48) * 10 + date1[9] - 48;
                if (isValidDate(day1, month1, year1)) {
                    is_date1 = true;
                    printf("\nДата 1 успешно введена!");
                    char worker_date1[] = { day1, month1, year1 };
                }
                else {
                    printf("\nНедопустимое значение. Попробуйте еще раз\n");
                    is_date1 = false;
                }
                exitProcess();
                clear_screen();
                printf("1) Ввод 1 времени \n2) Ввод 1 даты %s\n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);

                break;
            case 3: // второе время
                for (int i = 0; i < 8; i++) {
                    clear_screen();
                    printf("Введите время 2 (в формате чч:мм:сс): ");
                    for (int j = 0; j < i; j++) {
                        printf("%c", time2[j]);
                    }
                    if (time2[i] != ':') {
                        time2[i] = getch();
                        if (is_user_input_correct(time2[i], ok_for_time)) {
                            if (time2[i] == ':') {
                                time2[i] = time2[i - 1];
                                time2[i - 1] = '0';
                            }
                        }
                        else {
                            i--;
                        }
                    }
                }
                clear_screen();
                printf("Введите время 2 (в формате чч:мм:сс): ");
                for (int j = 0; j < 8; j++) {
                    printf("%c", time2[j]);
                }

                int hour2 = (time2[0] - 48) * 10 + time2[1] - 48;
                int minute2 = (time2[3] - 48) * 10 + time2[4] - 48;
                int second2 = (time2[6] - 48) * 10 + time2[7] - 48;
                if (isValidTime(hour2, minute2, second2)) {
                    is_time2 = true;
                    char new_time2[] = { hour2, minute2, second2 };
                    printf("\nВремя 2 успешно введено\n");
                }
                else {
                    printf("\nНедопустимое значение времени. Попробуйте еще раз!");
                    is_time2 = false;
                }

                exitProcess();
                clear_screen();
                printf("1) Ввод 1 времени \n2) Ввод 1 даты \n3) Ввод 2 времени %s \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
                break;
            case 4: // вторая дата
                for (int i = 0; i < 10; i++) {
                    clear_screen();
                    printf("Введите дату 2 (в формате дд.мм.гггг): ");
                    for (int j = 0; j < i; j++) {
                        printf("%c", date2[j]);
                    }
                    if (date2[i] != '.') {
                        date2[i] = getch();
                        if (is_user_input_correct(date2[i], ok_for_date)) {
                            if (date2[i] == '.') {
                                date2[i] = date2[i - 1];
                                date2[i - 1] = '0';
                            }
                        }
                        else {
                            i--;
                        }
                    }
                }
                clear_screen();
                printf("Введите дату 2 (в формате дд.мм.гггг): ");
                for (int j = 0; j < 10; j++) {
                    printf("%c", date2[j]);
                }

                day2 = (date2[0] - 48) * 10 + date2[1] - 48;
                month2 = (date2[3] - 48) * 10 + date2[4] - 48;
                year2 = (date2[6] - 48) * 1000 + (date2[7] - 48) * 100 + (date2[8] - 48) * 10 + date2[9] - 48;
                if (isValidDate(day2, month2, year2)) {
                    is_date2 = true;
                    printf("\nДата 2 успешно введена!");
                    char worker_date2[] = { day2, month2, year2 };
                }
                else {
                    printf("\nНедопустимое значение. Попробуйте еще раз\n");
                    is_date2 = false;
                }
                exitProcess();
                clear_screen();
                printf("1) Ввод 1 времени \n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты %s\n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
                break;
            case 5:
                clear_screen();
                if (is_date1 && is_date2 && is_time1 && is_time2) {
                    if (maxDate(day1, month1, year1, day2, month2, year2) == 1) {
                        printf("Результат вычитания даты 1 и даты 2: ");
                        subtractionDates(day1, month1, year1, day2, month2, year2, hour1, minute1, second1, hour2, minute2, second2);
                    }
                    else {
                        printf("Результат вычитания даты 2 и даты 1: ");
                        subtractionDates(day2, month2, year2, day1, month1, year1, hour2, minute2, second2, hour1, minute1, second1);
                    }
                }
                else {
                    printf("Недостаточно введенных данных!\n");
                }
                exitProcess();
                clear_screen();
                printf("1) Ввод 1 времени \n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат %s\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
                break;
            case 6:
                clear_screen();
                printf("Введите количество дней (от -10000 до 10000): ");
                count_days = 0;
                scanf("%d", &count_days);
                if (count_days <= 10000 && count_days >= -10000) {
                    printf("Количество дней успешно введено!");
                    is_count_days = true;
                }
                else {
                    printf("Неверный формат ввода!\n");
                    is_count_days = false;
                }
                exitProcess();
                clear_screen();
                printf("1) Ввод 1 времени \n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней %s\n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
                break;
            case 7:
                clear_screen();
                if (is_count_days && is_date1) {
                    printf("Результат сложения (количество дней к дате 1): ");
                    sumDaysAndDate(count_days, day1, month1, year1);
                }
                else {
                    printf("Недостаточно введенных данных!\n");
                }
                exitProcess();
                clear_screen();
                printf("1) Ввод 1 времени \n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1) %s\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3)\n", arrow);
                break;
            case 8:
                for (int i = 0; i < 8; i++) {
                    clear_screen();
                    printf("Введите время 3 (в формате чч:мм:сс): ");
                    for (int j = 0; j < i; j++) {
                        printf("%c", time3[j]);
                    }
                    if (time3[i] != ':') {
                        time3[i] = getch();
                        if (is_user_input_correct(time3[i], ok_for_time)) {
                            if (time3[i] == ':') {
                                time3[i] = time3[i - 1];
                                time3[i - 1] = '0';
                            }
                        }
                        else {
                            i--;
                        }
                    }
                }
                clear_screen();
                printf("Введите время 3 (в формате чч:мм:сс): ");
                for (int j = 0; j < 8; j++) {
                    printf("%c", time3[j]);
                }

                int hour3 = (time3[0] - 48) * 10 + time3[1] - 48;
                int minute3 = (time3[3] - 48) * 10 + time3[4] - 48;
                int second3 = (time3[6] - 48) * 10 + time3[7] - 48;
                if (isValidTime(hour3, minute3, second3)) {
                    is_time3 = true;
                    char worker_time3[] = { hour3, minute3, second3 };
                    printf("\nВремя 3 успешно введено\n");
                }
                else {
                    printf("\nНедопустимое значение времени. Попробуйте еще раз!");
                    is_time3 = false;
                }
                exitProcess();
                clear_screen();
                printf("1) Ввод 1 времени \n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3 %s\n9) Результат сложения (время 1 и время 3)\n", arrow);
                break;
            case 9:
                clear_screen();
                if (is_time1 && is_time3) {
                    printf("Результат сложения (время 1 и время 3): ");
                    sumTimes(hour1, minute1, second1, hour3, minute3, second3);
                }
                else {
                    printf("Недостаточно введенных данных!\n");
                    }
                    exitProcess();
                    clear_screen();
                    printf("1) Ввод 1 времени \n2) Ввод 1 даты \n3) Ввод 2 времени \n4) Ввод 2 даты \n5) Результат вычитания дат\n6) Количество дней \n7) Результат сложения (количество дней к дате 1)\n8) Ввод времени 3\n9) Результат сложения (время 1 и время 3) %s\n", arrow);
                    break;
            default:
                break;
            }
            pos_of_arrow = choice;
        }
    }
    return 0;
}
