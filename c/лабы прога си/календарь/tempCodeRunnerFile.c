
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
