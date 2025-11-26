#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constantes globais
#define MAX 5
int removida;

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

typedef struct
{
    Peca itens[MAX];
    int topo;
} PilhaPecas;

// Variável global para gerar IDs únicos
int proximoId = 1;

//-------------------------------------
// PROTÓTIPOS DAS FUNÇÕES
//-------------------------------------

void limparBufferdeEntrada();

void inicializarFila(FilaPecas *f);
void inicializarPilha(PilhaPecas *p);

int filaCheia(FilaPecas *f);
int filaVazia(FilaPecas *f);

int pilhaCheia(PilhaPecas *p);
int pilhaVazia(PilhaPecas *p);

int queue(FilaPecas *f, Peca p);
int dequeue(FilaPecas *f, Peca *removida);
void mostrarFila(FilaPecas *f);

int push(PilhaPecas *p, Peca removida);
int pop(PilhaPecas *p, Peca *removida);
void peek(PilhaPecas *p);

void gerarPeca(Peca *p);
void preencherFilaComPecas(FilaPecas *fila);

void menu(FilaPecas *fila, PilhaPecas *pilha);

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
    // Inicializa a pilha de peças
    PilhaPecas pilha;
    inicializarPilha(&pilha);
    // Preenche a fila com peças iniciais
    preencherFilaComPecas(&fila);
    mostrarFila(&fila);
    // Chama o menu de interação
    menu(&fila, &pilha);

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
int queue(FilaPecas *f, Peca p)
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
int dequeue(FilaPecas *f, Peca *removida)
{
    if (filaVazia(f))
    {
        return 0;
    }
    *removida = f->itens[f->inicio];
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
// FUNÇÕES DA PILHA
//-------------------------------------

// inicializar pilha
void inicializarPilha(PilhaPecas *p)
{
    p->topo = -1;
}
// vazia
int pilhaVazia(PilhaPecas *p)
{
    return p->topo == -1;
}
// cheia
int pilhaCheia(PilhaPecas *p)
{
    return p->topo == MAX - 1;
}

// inserir na pilha
int push(PilhaPecas *p, Peca removidaDaFila)
{
    if (pilhaCheia(p))
    {
        return 0;
    }

    p->topo++;                          // Avança o topo
    p->itens[p->topo] = removidaDaFila; // Insere o novo elemento que foi removido da fila
    return 1;
}

// remover da pilha
int pop(PilhaPecas *p, Peca *removidaDaPilha)
{
    if (pilhaVazia(p))
    {
        return 0;
    }

    *removidaDaPilha = p->itens[p->topo]; // Copia o valor do topo
    p->topo--;                            // Decrementa o topo
    return 1;
}

// Mostrar pilha
void peek(PilhaPecas *p)
{
    printf("Pilha (topo -> base): ");
    for (int i = p->topo; i >= 0; i--)
    {
        printf("[%s, %d] ", p->itens[i].forma, p->itens[i].id);
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
        queue(fila, nova);
    }
}
//-------------------------------------
// MENU
//-------------------------------------
void menu(FilaPecas *fila, PilhaPecas *pilha)
{
    int opcao;

    do
    {
        printf("=== Menu do Tetris ===\n");
        printf("1. Jogar peça (Remover a peça da frente)\n");
        printf("2. Reservar peça (Mover o primeiro da fila para o topo da pilha)\n");
        printf("3. Usar peça reservada (Remover a peça do topo da pilha)\n");
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
            Peca removida, nova;
            if (dequeue(fila, &removida))
            {
                printf("\nPeça removida: [%s, %d]\n\n", removida.forma, removida.id);
            }
            // Gera nova peça para repor na fila
            gerarPeca(&nova);
            queue(fila, nova);

            mostrarFila(fila);
            peek(pilha);
            break;
        case 2:
        {
            Peca reservada, nova2;

            // Antes de remover da fila, verificar se a pilha tem espaço
            if (pilhaCheia(pilha))
            {
                printf("\nPilha cheia! Não é possível reservar peça.\n\n");
                mostrarFila(fila);
                peek(pilha);
                break;
            }

            // pode remover da fila
            if (dequeue(fila, &reservada))
            {
                // Envia para o topo da pilha
                push(pilha, reservada);
                printf("\nPeça reservada: [%s, %d]\n\n", reservada.forma, reservada.id);

                // Gera nova peça para repor na fila
                gerarPeca(&nova2);
                queue(fila, nova2);
            }

            mostrarFila(fila);
            peek(pilha);
            break;
        }
        case 3:
            Peca usada;
            if (pop(pilha, &usada))
            {
                printf("\nPeça usada: [%s, %d]\n\n", usada.forma, usada.id);
            }
            else
            {
                printf("\nPilha vazia! Falha ao usar peça.\n\n");
            }
            mostrarFila(fila);
            peek(pilha);
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