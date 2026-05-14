#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LIMITE_MSG 128
#define LIMITE_CHAVE 64

void limparNovaLinha(char texto[]) {
    size_t tamanho = strlen(texto);
    if (tamanho > 0 && texto[tamanho - 1] == '\n') {
        texto[tamanho - 1] = '\0';
    }
}

int chaveValida(const char chave[]) {
    int i;

    if (strlen(chave) == 0) {
        return 0;
    }

    for (i = 0; chave[i] != '\0'; i++) {
        if (!isalpha((unsigned char) chave[i])) {
            return 0;
        }
    }

    return 1;
}

void criptografarVigenere(const char mensagem[], const char chave[], char resultado[]) {
    int i;
    int j = 0;
    int deslocamento;
    int tamanhoChave = strlen(chave);
    char base;

    for (i = 0; mensagem[i] != '\0'; i++) {
        if (isalpha((unsigned char) mensagem[i])) {
            base = isupper((unsigned char) mensagem[i]) ? 'A' : 'a';
            deslocamento = toupper((unsigned char) chave[j % tamanhoChave]) - 'A';
            resultado[i] = (char) (((mensagem[i] - base + deslocamento) % 26) + base);
            j++;
        } else {
            resultado[i] = mensagem[i];
        }
    }

    resultado[i] = '\0';
}

void descriptografarVigenere(const char mensagem[], const char chave[], char resultado[]) {
    int i;
    int j = 0;
    int deslocamento;
    int tamanhoChave = strlen(chave);
    char base;

    for (i = 0; mensagem[i] != '\0'; i++) {
        if (isalpha((unsigned char) mensagem[i])) {
            base = isupper((unsigned char) mensagem[i]) ? 'A' : 'a';
            deslocamento = toupper((unsigned char) chave[j % tamanhoChave]) - 'A';
            resultado[i] = (char) (((mensagem[i] - base - deslocamento + 26) % 26) + base);
            j++;
        } else {
            resultado[i] = mensagem[i];
        }
    }

    resultado[i] = '\0';
}

void lerMensagem(char mensagem[]) {
    int tamanho;

    do {
        printf("Digite a mensagem, com ate 128 caracteres: ");
        fgets(mensagem, LIMITE_MSG + 2, stdin);
        limparNovaLinha(mensagem);
        tamanho = strlen(mensagem);

        if (tamanho > LIMITE_MSG) {
            printf("Erro: a mensagem ultrapassou o limite de 128 caracteres. Tente novamente.\n");
            while (getchar() != '\n') {
                /* limpa o restante do buffer */
            }
        }
    } while (tamanho > LIMITE_MSG);
}

void lerChave(char chave[]) {
    do {
        printf("Digite a chave alfabetica: ");
        fgets(chave, LIMITE_CHAVE, stdin);
        limparNovaLinha(chave);

        if (!chaveValida(chave)) {
            printf("Erro: a chave deve conter apenas letras e nao pode ficar vazia.\n");
        }
    } while (!chaveValida(chave));
}

int main(void) {
    int opcao;
    char mensagem[LIMITE_MSG + 2];
    char chave[LIMITE_CHAVE];
    char resultado[LIMITE_MSG + 2];

    do {
        printf("\n===== APS - CIFRA DE VIGENERE =====\n");
        printf("1 - Criptografar mensagem\n");
        printf("2 - Descriptografar mensagem\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Encerrando o programa.\n");
            return 1;
        }
        getchar();

        switch (opcao) {
            case 1:
                lerMensagem(mensagem);
                lerChave(chave);
                criptografarVigenere(mensagem, chave, resultado);
                printf("\nMensagem original: %s\n", mensagem);
                printf("Chave utilizada: %s\n", chave);
                printf("Mensagem criptografada: %s\n", resultado);
                break;

            case 2:
                lerMensagem(mensagem);
                lerChave(chave);
                descriptografarVigenere(mensagem, chave, resultado);
                printf("\nMensagem cifrada: %s\n", mensagem);
                printf("Chave utilizada: %s\n", chave);
                printf("Mensagem descriptografada: %s\n", resultado);
                break;

            case 0:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida. Escolha 1, 2 ou 0.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
