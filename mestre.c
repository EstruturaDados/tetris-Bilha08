#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constantes
#define MAX 5
#define MAX_PILHA 3
int proximoId = 1;

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
    Peca itens[MAX_PILHA];
    int topo;
} PilhaPecas;

//-------------------------------------
// PROTÓTIPOS
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

int trocarPrimeiroFilaTopoPilha(FilaPecas *fila, PilhaPecas *pilha);
int trocarTresFilaTresPilha(FilaPecas *fila, PilhaPecas *pilha);

void menu(FilaPecas *fila, PilhaPecas *pilha);

//-------------------------------------
// PRINCIPAL
//-------------------------------------
int main()
{
    srand(time(NULL));

    FilaPecas fila;
    PilhaPecas pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    preencherFilaComPecas(&fila);

    mostrarFila(&fila);
    peek(&pilha);

    menu(&fila, &pilha);

    return 0;
}

//-------------------------------------
// LIMPAR BUFFER
//-------------------------------------
void limparBufferdeEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

//-------------------------------------
// FILA
//-------------------------------------
void inicializarFila(FilaPecas *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(FilaPecas *f)
{
    return f->total == MAX;
}

int filaVazia(FilaPecas *f)
{
    return f->total == 0;
}
// Insere uma peça na fila
int queue(FilaPecas *f, Peca p)
{
    if (filaCheia(f))
        return 0;

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
    return 1;
}
// Remove uma peça da fila
int dequeue(FilaPecas *f, Peca *removida)
{
    if (filaVazia(f))
        return 0;

    *removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return 1;
}

void mostrarFila(FilaPecas *f)
{
    printf("Fila de peças (Primeiro -> Último): ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX)
    {
        printf("[%s, %d] ", f->itens[idx].forma, f->itens[idx].id);
    }
    printf("\n\n");
}

//-------------------------------------
// PILHA
//-------------------------------------
void inicializarPilha(PilhaPecas *p)
{
    p->topo = -1;
}
// verifica se a pilha está vazia
int pilhaVazia(PilhaPecas *p)
{
    return p->topo == -1;
}

// verifica se a pilha está cheia
int pilhaCheia(PilhaPecas *p)
{
    return p->topo == MAX_PILHA - 1;
}

// Insere uma peça na pilha
int push(PilhaPecas *p, Peca removida)
{
    if (pilhaCheia(p))
        return 0;

    p->itens[++p->topo] = removida;
    return 1;
}

// Remove uma peça da pilha
int pop(PilhaPecas *p, Peca *removida)
{
    if (pilhaVazia(p))
        return 0;

    *removida = p->itens[p->topo--];
    return 1;
}

// Mostra as peças na pilha
void peek(PilhaPecas *p)
{
    printf("Pilha (Topo -> Base): ");
    for (int i = p->topo; i >= 0; i--)
        printf("[%s, %d] ", p->itens[i].forma, p->itens[i].id);
    printf("\n\n");
}

//-------------------------------------
// GERAR PEÇAS
//-------------------------------------
void gerarPeca(Peca *p)
{
    const char formas[4][2] = {"I", "O", "T", "L"};
    int tipo = rand() % 4;

    p->forma[0] = formas[tipo][0];
    p->forma[1] = '\0';

    p->id = proximoId++;
}

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
// TROCAS
//-------------------------------------
// Troca a primeira peça da fila com a peça do topo da pilha
int trocarPrimeiroFilaTopoPilha(FilaPecas *fila, PilhaPecas *pilha)
{ // Verifica se a fila ou a pilha estão vazias
    if (filaVazia(fila) || pilhaVazia(pilha))
        return 0;
    // armazena os índices da primeira peça da fila e do topo da pilha
    int idxFila = fila->inicio;
    int idxPilha = pilha->topo;
    // realiza a troca
    Peca temp = fila->itens[idxFila];
    fila->itens[idxFila] = pilha->itens[idxPilha];
    pilha->itens[idxPilha] = temp;

    return 1;
}
// Troca as três primeiras peças da fila com as três peças do topo da pilha
int trocarTresFilaTresPilha(FilaPecas *fila, PilhaPecas *pilha)
{
    // Verifica se há pelo menos 3 peças na fila e na pilha
    if (fila->total < 3)
        return 0;
    if ((pilha->topo + 1) < 3)
        return 0;
    // Cria uma fila auxiliar para ajudar na troca
    FilaPecas filaAux;
    inicializarFila(&filaAux);
    // Variáveis temporárias para armazenar as peças
    Peca filaTmp[3];
    Peca pilhaTmp[3];
    Peca temp;
    // Copia as peças da fila e da pilha para as variáveis temporárias
    for (int i = 0; i < 3; i++)
        dequeue(fila, &filaTmp[i]);
    // Copia as peças da pilha para as variáveis temporárias
    for (int i = 0; i < 3; i++)
        pop(pilha, &pilhaTmp[i]);
    // Insere as peças da pilha na fila auxiliar
    for (int i = 0; i < 3; i++)
        queue(&filaAux, pilhaTmp[i]);
    // Restaura as peças restantes da fila original
    while (!filaVazia(fila))
    {
        dequeue(fila, &temp);
        queue(&filaAux, temp);
    }
    // Restaura as peças da fila original com as peças da pilha no início
    while (!filaVazia(&filaAux))
    {
        dequeue(&filaAux, &temp);
        queue(fila, temp);
    }
    // Insere as peças da fila original na pilha
    for (int i = 0; i < 3; i++)
        push(pilha, filaTmp[i]);

    return 1;
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
        printf("1. Jogar peça (remover o primeiro da fila)\n");
        printf("2. Reservar peça (fila -> pilha)\n");
        printf("3. Usar peça reservada (pilha -> descarte)\n");
        printf("4. Trocar primeiro da fila com topo da pilha\n");
        printf("5. Trocar 3 primeiras da fila com 3 da pilha\n");
        printf("0. Sair\n");
        printf("======================\n");
        printf("Escolha: ");

        int r = scanf("%d", &opcao);
        limparBufferdeEntrada();
        if (r != 1)
            opcao = -1;

        switch (opcao)
        {
        case 1:
        {
            if (filaVazia(fila))
            {
                printf("\nFila vazia! Não é possível jogar peça.\n\n");
                break;
            }

            Peca removida, nova;
            dequeue(fila, &removida);
            printf("\nPeça jogada: [%s, %d]\n\n", removida.forma, removida.id);

            gerarPeca(&nova);
            queue(fila, nova);

            mostrarFila(fila);
            peek(pilha);
            break;
        }
        case 2:
        {
            if (filaVazia(fila))
            {
                printf("\nFila vazia! Não é possível reservar.\n\n");
                break;
            }
            if (pilhaCheia(pilha))
            {
                printf("\nPilha cheia! Não é possível reservar.\n\n");
                break;
            }

            Peca reservada, nova2;
            dequeue(fila, &reservada);
            push(pilha, reservada);

            printf("\nPeça reservada: [%s, %d]\n\n", reservada.forma, reservada.id);

            gerarPeca(&nova2);
            queue(fila, nova2);

            mostrarFila(fila);
            peek(pilha);
            break;
        }
        case 3:
        {
            Peca usada;
            if (!pop(pilha, &usada))
            {
                printf("\nPilha vazia! Nada para usar.\n\n");
                break;
            }

            printf("\nPeça usada: [%s, %d]\n\n", usada.forma, usada.id);
            mostrarFila(fila);
            peek(pilha);
            break;
        }
        case 4:
        {
            if (trocarPrimeiroFilaTopoPilha(fila, pilha))
                printf("\nPeças trocadas!\n\n");
            else
                printf("\nFalha: fila ou pilha vazia.\n\n");

            mostrarFila(fila);
            peek(pilha);
            break;
        }
        case 5:
        {
            if (trocarTresFilaTresPilha(fila, pilha))
                printf("\nAs 3 peças foram trocadas!\n\n");
            else
                printf("\nFalha: é necessário ter pelo menos 3 peças na fila e 3 na pilha.\n\n");

            mostrarFila(fila);
            peek(pilha);
            break;
        }
        case 0:
            printf("\nSaindo...\n");
            break;
        default:
            printf("\nOpção inválida!\n\n");
            break;
        }

    } while (opcao != 0);
}
