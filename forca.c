#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.h"

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;


int letraexiste(char letra) {

    for(size_t j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}

int chuteserrados() {
    int erros = 0;

    for(int i = 0; i < chutesdados; i++) {

        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}

int enforcou() {
    return chuteserrados() >= 5;
}

int ganhou() {
    for (size_t i = 0; i < strlen(palavrasecreta); i++) {  // alterado para size_t
        if (!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }
    return 1;
}


void abertura() {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    if(letraexiste(chute)) {
        printf("Voce acertou: a palavra tem a letra %c\n\n", chute);
    } else {
        printf("\nVoce errou: a palavra NAO tem a letra %c\n\n", chute);
    }

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra) {
    int achou = 0;
    for(int j = 0; j < chutesdados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaforca() {
    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for (size_t i = 0; i < strlen(palavrasecreta); i++) {  // alterado para size_t
        if (jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            if (palavrasecreta[i] == ' ') {
                printf("  ");  // Para exibir um espaço
            } else {
                printf("_ ");
            }
        }
    }
    printf("\n");
}


void escolhepalavra() {
    FILE* f;

    f = fopen("C:\\Users\\Ana\\Desktop\\C\\palavras.txt", "r");    if(f == 0) {
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%19s", palavrasecreta);
    }

    fclose(f);
}


void adicionapalavra() {
    char quer;

    // Pergunta ao jogador se deseja adicionar uma nova palavra
    printf("Voce deseja adicionar uma nova palavra no jogo (S/N)? ");
    scanf(" %c", &quer);

    // Se a resposta for 'S', permite que o jogador adicione a palavra
    if(quer == 'S') {
        char novapalavra[TAMANHO_PALAVRA];

        // Solicita a nova palavra
        printf("Digite a nova palavra, em letras MAIUSCULAS: ");
        scanf("%s", novapalavra);

        FILE *f;
        f = fopen("C:/Users/Ana/Desktop/C/palavras.txt", "r+");
        
        if(f == NULL) {
            perror("Erro ao abrir o arquivo");
            exit(1);
        }

        // Lê a quantidade atual de palavras no arquivo
        int qtd;
        fscanf(f, "%d", &qtd);
        
        // Atualiza a quantidade de palavras
        qtd++;

        // Volta para o início do arquivo e escreve a nova quantidade de palavras
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        // Vai até o final do arquivo e adiciona a nova palavra
        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        // Fecha o arquivo
        fclose(f);

        printf("Palavra adicionada com sucesso!\n");
    }
}


int main() {

    abertura();
    escolhepalavra();

    do {

        desenhaforca();
        chuta();

    } while (!ganhou() && !enforcou());

    if(ganhou()) {
        printf("\nParabens, você ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

    } else {
        printf("\nPuxa, voce foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    adicionapalavra();
}