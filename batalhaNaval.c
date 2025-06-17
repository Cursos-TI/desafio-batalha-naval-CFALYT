#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define OCUPADO 3
#define AGUA 0

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Exibe o tabuleiro no terminal
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Verifica se pode posicionar o navio sem sair do tabuleiro e sem sobreposição
int podePosicionar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (direcao == 'H') c += i;              // Horizontal
        else if (direcao == 'V') l += i;         // Vertical
        else if (direcao == 'D') { l += i; c += i; }     // Diagonal \
        else if (direcao == 'A') { l += i; c -= i; }     // Diagonal /

        // Verifica limites e se já há navio no local
        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO || tabuleiro[l][c] == OCUPADO) {
            return 0;
        }
    }
    return 1;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        else if (direcao == 'A') { l += i; c -= i; }

        tabuleiro[l][c] = OCUPADO;
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    inicializarTabuleiro(tabuleiro);

    // Navio 1: horizontal na linha 1, coluna 2
    if (podePosicionar(tabuleiro, 1, 2, 'H')) {
        posicionarNavio(tabuleiro, 1, 2, 'H');
    } else {
        printf("Erro: navio horizontal não pôde ser posicionado.\n");
    }

    // Navio 2: vertical na linha 4, coluna 6
    if (podePosicionar(tabuleiro, 4, 6, 'V')) {
        posicionarNavio(tabuleiro, 4, 6, 'V');
    } else {
        printf("Erro: navio vertical não pôde ser posicionado.\n");
    }

    // Navio 3: diagonal principal (linha 0, coluna 0)
    if (podePosicionar(tabuleiro, 0, 0, 'D')) {
        posicionarNavio(tabuleiro, 0, 0, 'D');
    } else {
        printf("Erro: navio diagonal \\ não pôde ser posicionado.\n");
    }

    // Navio 4: diagonal secundária (linha 0, coluna 9)
    if (podePosicionar(tabuleiro, 0, 9, 'A')) {
        posicionarNavio(tabuleiro, 0, 9, 'A');
    } else {
        printf("Erro: navio diagonal / não pôde ser posicionado.\n");
    }

    // Exibe o tabuleiro com os navios
    printf("\nTabuleiro com os navios posicionados:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
