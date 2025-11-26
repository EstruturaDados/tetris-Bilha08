#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constantes globais
#define MAX 5

//-------------------------------------
// ESTRUTURAS
//-------------------------------------
typedef struct
{
    char forma[2];
    int id;
} Peca;

typedef struct
{
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} FilaPecas;

// Variável global para gerar IDs únicos
int proximoId = 1;

//-------------------------------------
// PROTÓTIPOS DAS FUNÇÕES
//-------------------------------------

void limparBufferdeEntrada();

void inicializarFila(FilaPecas *f);

int filaCheia(FilaPecas *f);
int filaVazia(FilaPecas *f);

int inserir(FilaPecas *f, Peca p);
int remover(FilaPecas *f, Peca *p);
void mostrarFila(FilaPecas *f);

void gerarPeca(Peca *p);
void preencherFilaComPecas(FilaPecas *fila);

void menu(FilaPecas *fila);

//-------------------------------------
// PROGRAMA PRINCIPAL
//-------------------------------------
int main()
{
    // Semente para números aleatórios
    srand(time(NULL));

    // Inicializa a fila de peças
    FilaPecas fila;
    inicializarFila(&fila);
    // Preenche a fila com peças iniciais
    preencherFilaComPecas(&fila);
    mostrarFila(&fila);
    // Chama o menu de interação
    menu(&fila);

    return 0;
}

//-------------------------------------
// FUNÇÕES DA FILA
//-------------------------------------
// função para limpar o buffer de entrada
void limparBufferdeEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
// Inicializa a fila
void inicializarFila(FilaPecas *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}
// Verifica se a fila está cheia
int filaCheia(FilaPecas *f)
{
    return f->total == MAX;
}

// Verifica se a fila está vazia
int filaVazia(FilaPecas *f)
{
    return f->total == 0;
}
// Insere uma peça na fila
int inserir(FilaPecas *f, Peca p)
{
    if (filaCheia(f))
    {
        return 0;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;

    return 1;
}
// Remove uma peça da fila
int remover(FilaPecas *f, Peca *p)
{
    if (filaVazia(f))
    {
        return 0;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;

    return 1;
}

// Mostra as peças na fila
void mostrarFila(FilaPecas *f)
{
    printf("Fila de peças: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX)
    {
        printf("[%s, %d] ", f->itens[idx].forma, f->itens[idx].id);
    }
    printf("\n\n");
}
//-------------------------------------
// GERADOR DE PEÇAS
//-------------------------------------
// Gera uma nova peça aleatória
void gerarPeca(Peca *p)
{
    const char formas[4][2] = {"I", "O", "T", "L"};
    int tipo = rand() % 4;

    p->forma[0] = formas[tipo][0];
    p->forma[1] = '\0';

    p->id = proximoId++;
}
//-------------------------------------
// PREENCHEDOR DA FILA
//-------------------------------------
void preencherFilaComPecas(FilaPecas *fila)
{
    for (int i = 0; i < MAX; i++)
    {
        Peca nova;
        gerarPeca(&nova);
        inserir(fila, nova);
    }
}
//-------------------------------------
// MENU
//-------------------------------------
void menu(FilaPecas *fila)
{
    int opcao;

    do
    {
        printf("=== Menu do Tetris ===\n");
        printf("1. Inserir peça na fila\n");
        printf("2. Remover peça da fila (Jogar peça)\n");
        ;
        printf("0. Sair\n");
        printf("======================\n");

        printf("Escolha uma opção: ");
        int r = scanf("%d", &opcao);
        limparBufferdeEntrada();
        if (r != 1)
        {
            opcao = -1;
        }
        switch (opcao)
        {
        case 1:
            Peca nova;
            gerarPeca(&nova);

            if (inserir(fila, nova))
            {
                printf("\nPeça inserida: [%s, %d]\n\n", nova.forma, nova.id);
            }
            else
            {
                printf("\nFila cheia! Falha ao inserir peça.\n\n");
            }
            mostrarFila(fila);
            break;
        case 2:
            Peca removida;

            if (remover(fila, &removida))
            {
                printf("\nPeça removida: [%s, %d]\n\n", removida.forma, removida.id);
            }
            else
            {
                printf("\nFila vazia! Falha ao remover peça.\n\n");
            }
            mostrarFila(fila);
            break;
        case 0:
            printf("\nSaindo do programa...\n");
            break;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            break;
        }
    } while (opcao != 0);
}