void exitAnyProcces(){
    printf("\n\nНажмите Enter для продолжения\n");
    int user;
    do {
        user = getchar(); 
        clear();
        printf("\n\nНажмите Enter для продолжения\n");
    } while (user != '\n'); 
}
