#include <stdio.h>
#include <stdlib.h>

int main(){
    char x[100];

    fgets(x, 50, stdin);
    printf("%s\n", x);

    freopen("string.txt", "r", stdin);
    fgets(x, 100, stdin);
    printf("%s\n", x);

    return 0;
}

///outra parada do freopen

int main(){
    char x[100], y[100];
    FILE *file = fopen("string.txt", "r");

    fgets(x, 100, file);
    printf("%s\n", x);

    freopen("string2.txt", "r", file);
    fgets(y, 100, file);

    printf("%s\n", y);

    return 0;
}
