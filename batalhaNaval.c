#include <stdio.h>
#include <stdlib.h> // para a função abs()


#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Inicializa o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Exibe o tabuleiro com legenda
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA)       printf(" ~ ");
            else if (tabuleiro[i][j] == NAVIO) printf(" N ");
            else if (tabuleiro[i][j] == HABILIDADE) printf(" * ");
        }
        printf("\n");
    }
}

// Posiciona um navio horizontal de tamanho 3
void posicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < 3; i++) {
        if (coluna + i < TAM_TABULEIRO)
            tabuleiro[linha][coluna + i] = NAVIO;
    }
}

// Posiciona um navio vertical de tamanho 3
void posicionarNavioVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < 3; i++) {
        if (linha + i < TAM_TABULEIRO)
            tabuleiro[linha + i][coluna] = NAVIO;
    }
}

// Cria a matriz de habilidade em forma de cone (ponta pra baixo)
void criarMatrizCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // A linha 0 só tem o meio, depois vai expandindo
            int meio = TAM_HABILIDADE / 2;
            if (j >= meio - i && j <= meio + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria a matriz de habilidade em cruz
void criarMatrizCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria a matriz de habilidade em octaedro (losango)
void criarMatrizOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int centro = TAM_HABILIDADE / 2;
            if (abs(centro - i) + abs(centro - j) <= centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica uma matriz de habilidade no tabuleiro em torno de um ponto (linha, coluna)
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int li = linha - offset + i;
            int co = coluna - offset + j;

            // Verifica se está dentro dos limites do tabuleiro
            if (li >= 0 && li < TAM_TABULEIRO && co >= 0 && co < TAM_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[li][co] == AGUA)
                    tabuleiro[li][co] = HABILIDADE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posiciona navios de exemplo
    posicionarNavioHorizontal(tabuleiro, 2, 3);
    posicionarNavioVertical(tabuleiro, 5, 7);

    // Matrizes das habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // Aplica habilidades no tabuleiro em pontos específicos
    aplicarHabilidade(tabuleiro, 1, 5, cone);       // Cone no topo
    aplicarHabilidade(tabuleiro, 7, 4, cruz);       // Cruz no meio-baixo
    aplicarHabilidade(tabuleiro, 5, 5, octaedro);   // Octaedro no centro

    // Mostra o resultado
    printf("\nLegenda: ~ = Água, N = Navio, * = Habilidade\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
