#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo
{
  int valor;
  struct Nodo *proximo;
} Nodo;

Nodo *criarNodo(int valor)
{
  Nodo *novoNodo = (Nodo *)malloc(sizeof(Nodo));
  if (novoNodo == NULL)
  {
    fprintf(stderr, "Erro ao alocar memória para o nó.\n");
    exit(EXIT_FAILURE);
  }

  novoNodo->valor = valor;
  novoNodo->proximo = NULL;

  return novoNodo;
}

void liberarLista(Nodo *cabeca)
{
  Nodo *atual = cabeca;
  while (atual != NULL)
  {
    Nodo *temp = atual;
    atual = atual->proximo;
    free(temp);
  }
}

int main()
{
  // Abrir o arquivo para leitura
  FILE *arquivo = fopen("numeros.txt", "r");

  if (arquivo == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo.\n");
    return 1;
  }

  // Inicializar a lista encadeada
  Nodo *cabeca = NULL;
  Nodo *atual = NULL;

  int valor;

  // Ler os valores do arquivo e adicionar à lista encadeada
  while (fscanf(arquivo, "%d", &valor) == 1)
  {
    Nodo *novoNodo = criarNodo(valor);

    if (cabeca == NULL)
    {
      cabeca = novoNodo;
      atual = novoNodo;
    }
    else
    {
      atual->proximo = novoNodo;
      atual = novoNodo;
    }
  }

  // Fechar o arquivo após a leitura
  fclose(arquivo);

  // Realizar a busca na lista encadeada
  int comparacoes = 0;
  int busca;

  printf("Digite o valor a ser buscado: ");
  scanf("%d", &busca);

  atual = cabeca;

  printf("Valor armazenado no arquivo!");

  while (atual != NULL)
  {
    comparacoes++;
    if (atual->valor == busca)
    {
      FILE *arquivoSaida = fopen("resultados_lista.txt", "a");
      if (arquivoSaida == NULL)
      {
        fprintf(stderr, "Erro ao abrir o arquivo de saída.\n");
        exit(EXIT_FAILURE);
      }
      fprintf(arquivoSaida, "%d\n", comparacoes);
      fclose(arquivoSaida);
      liberarLista(cabeca);
      return 0;
    }

    atual = atual->proximo;
  }

  FILE *arquivoSaida = fopen("resultados_lista.txt", "a");
  if (arquivoSaida == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo de saída.\n");
    exit(EXIT_FAILURE);
  }
  fprintf(arquivoSaida, "Valor nao encontrado na lista.\n", comparacoes);
  fclose(arquivoSaida);

  liberarLista(cabeca);

  return 0;
}
