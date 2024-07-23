#include <stdio.h>
#include <stdlib.h>

typedef struct NodoArvore
{
  int valor;
  struct NodoArvore *esquerda;
  struct NodoArvore *direita;
} NodoArvore;

NodoArvore *criarNodoArvore(int valor)
{
  NodoArvore *novoNodo = (NodoArvore *)malloc(sizeof(NodoArvore));
  if (novoNodo == NULL)
  {
    fprintf(stderr, "Erro ao alocar memória para o nó da árvore.\n");
    exit(EXIT_FAILURE);
  }

  novoNodo->valor = valor;
  novoNodo->esquerda = NULL;
  novoNodo->direita = NULL;

  return novoNodo;
}

// Função para inserir um valor na árvore
NodoArvore *inserirNaArvore(NodoArvore *raiz, int valor)
{
  if (raiz == NULL)
  {
    // Caso base: árvore vazia ou posição de inserção encontrada
    return criarNodoArvore(valor);
  }

  // Caso recursivo: inserir na subárvore esquerda ou direita
  if (valor < raiz->valor)
  {
    raiz->esquerda = inserirNaArvore(raiz->esquerda, valor);
  }
  else if (valor > raiz->valor)
  {
    raiz->direita = inserirNaArvore(raiz->direita, valor);
  }

  // Se o valor já existir na árvore, não fazemos nada

  return raiz;
}

void liberarArvore(NodoArvore *raiz)
{
  if (raiz != NULL)
  {
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
  }
}

// Função para realizar busca na árvore
int buscarNaArvore(NodoArvore *raiz, int valor, int *comparacoes)
{
  while (raiz != NULL)
  {
    (*comparacoes)++;
    if (valor == raiz->valor)
    {
      FILE *arquivoSaida = fopen("resultados_arvore.txt", "a");
      if (arquivoSaida == NULL)
      {
        fprintf(stderr, "Erro ao abrir o arquivo de saída.\n");
        exit(EXIT_FAILURE);
      }
      fprintf(arquivoSaida, "%d\n", *comparacoes);
      fclose(arquivoSaida);
      return 1;
    }
    else if (valor < raiz->valor)
    {
      raiz = raiz->esquerda;
    }
    else
    {
      raiz = raiz->direita;
    }
  }

  FILE *arquivoSaida = fopen("resultados_arvore.txt", "a");
  if (arquivoSaida == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo de saída.\n");
    exit(EXIT_FAILURE);
  }
  fprintf(arquivoSaida, "Valor nao encontrado.\n");
  fclose(arquivoSaida);

  return 0;
}

int main()
{
  FILE *arquivo = fopen("numeros.txt", "r");

  if (arquivo == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo.\n");
    return 1;
  }

  NodoArvore *raiz = NULL;
  int valor;

  while (fscanf(arquivo, "%d", &valor) == 1)
  {
    raiz = inserirNaArvore(raiz, valor);
  }

  fclose(arquivo);

  int busca;
  int comparacoes = 0;

  printf("Digite o valor a ser buscado: ");
  scanf("%d", &busca);

  printf("Valor armazenado no arquivo!");
  buscarNaArvore(raiz, busca, &comparacoes);

  liberarArvore(raiz);

  return 0;
}