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

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("  ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%d ", j);  // cabeçalho das colunas
    }
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%d ", i);  // número da linha
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se o navio cabe no tabuleiro e se há sobreposição
int podePosicionar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + (direcao == 'V' ? i : 0);
        int c = coluna + (direcao == 'H' ? i : 0);

        if (l >= TAM_TABULEIRO || c >= TAM_TABULEIRO || tabuleiro[l][c] == OCUPADO) {
            return 0; // Não pode posicionar
        }
    }
    return 1; // Pode posicionar
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + (direcao == 'V' ? i : 0);
        int c = coluna + (direcao == 'H' ? i : 0);

        tabuleiro[l][c] = OCUPADO;
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Coordenadas iniciais dos navios
    int linhaHorizontal = 2, colunaHorizontal = 4;
    int linhaVertical = 5, colunaVertical = 7;

    // Inicializar o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Verificar e posicionar navio horizontal
    if (podePosicionar(tabuleiro, linhaHorizontal, colunaHorizontal, 'H')) {
        posicionarNavio(tabuleiro, linhaHorizontal, colunaHorizontal, 'H');
    } else {
        printf("Erro: Não foi possível posicionar o navio horizontal.\n");
    }

    // Verificar e posicionar navio vertical
    if (podePosicionar(tabuleiro, linhaVertical, colunaVertical, 'V')) {
        posicionarNavio(tabuleiro, linhaVertical, colunaVertical, 'V');
    } else {
        printf("Erro: Não foi possível posicionar o navio vertical.\n");
    }

    // Exibir o tabuleiro final
    printf("\nTabuleiro com os navios posicionados:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
