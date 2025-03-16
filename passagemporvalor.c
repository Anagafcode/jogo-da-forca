#include <stdio.h>

void alterarValor(int x) {
    printf("Dentro da função: x = %d\n", x);  // Mostrando o valor de x dentro da função
    x = 10;  // Modificando o valor de x dentro da função
    printf("Dentro da função após modificação: x = %d\n", x);  // Mostrando o valor alterado de x
}

int main() {
    int numero = 5;
    printf("Antes de chamar a função: num = %d\n", numero);  // Valor de num antes da função
    alterarValor(numero);  // Passando num para a função, por valor
    printf("Após chamar a função: num = %d\n", numero);  // Valor de num após a função (não alterado)
    return 0;
}
