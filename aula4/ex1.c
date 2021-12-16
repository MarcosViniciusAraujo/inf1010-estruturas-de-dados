/*
Marcos Vinicius Araujo Alemida - Questão 1
*/
int strtam(char s[]){

    int i;
    for ( i = 0; s[i] != '\0'; i++)

    return i;
}

int strtam1(char *s){

    int i;
    for ( i = 0; *(s + i) != '\0'; i++)

    return i;
}

int strtam2(char *s){
    /*
    int n = sizeof(s) / sizeof(char);

    return n;
    */

    int i;
    char *p = s;

    for ( i = 0; *(s + i) != '\0'; i++){

        p++;
    }

    return p - s;
}

int main(){


    return 0;
}