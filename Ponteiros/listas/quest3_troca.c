#include <stdio.h>
#include <string.h>


int main() {
    char str[50]; // String
    char str_inv[50]; // String invertida
    char *ptr_str = str;
    char *ptr_inv = str_inv;
    int i = -1;
    scanf(" %s", str);

    //solução
    while (*ptr_str != '\0') {
        ptr_str++;
        i++;
    }
    //ptr_str já está apontando para o último caractere (o nulo) da string original

    //string sendo invertida
    while (i >= 0) {
        ptr_str--;
        *ptr_inv = *ptr_str;
        ptr_inv++;
        i--;
    }
    
    *ptr_inv = '\0'; //caracter nulo no final para printar

    //saída
    printf(" O inverso da string : %s\n\n", str_inv);


    return 0;
}