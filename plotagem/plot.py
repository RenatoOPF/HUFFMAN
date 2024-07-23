import matplotlib.pyplot as plt
import numpy as np

def ler_dados_do_arquivo(nome_arquivo):
    with open(nome_arquivo, 'r') as arquivo:
        # Lê as linhas do arquivo e converte para lista de inteiros
        dados = [int(linha.strip()) for linha in arquivo.readlines()]
    return dados

dados_lista_encadeada = ler_dados_do_arquivo('resultados_lista.txt')
dados_arvore_binaria = ler_dados_do_arquivo('resultados_arvore.txt')

# Array de valores x mais densamente espaçados
x_dense = np.linspace(0, len(dados_lista_encadeada) - 1, 100)

# Interpolação para obter os valores y correspondentes
y_lista_interp = np.interp(x_dense, range(len(dados_lista_encadeada)), dados_lista_encadeada)
y_arvore_interp = np.interp(x_dense, range(len(dados_arvore_binaria)), dados_arvore_binaria)

# Criar uma figura com uma grade de 2 linhas e 2 colunas e tamanho personalizado
plt.figure("Indivídual",figsize=(10, 8))

# Adicionar o primeiro subplot (Lista Encadeada)
plt.subplot(2, 2, 1)
plt.plot(x_dense, y_lista_interp, label='Lista Encadeada', color='red')
plt.title('Lista Encadeada')
plt.xlabel('Tamanho da Entrada')
plt.ylabel('Número Médio de Comparações')
plt.legend()

# Adicionar o segundo subplot (Árvore de Busca Binária)
plt.subplot(2, 2, 2)
plt.plot(x_dense, y_arvore_interp, label='Árvore de Busca Binária', color='green')
plt.title('Árvore de Busca Binária')
plt.xlabel('Tamanho da Entrada')
plt.ylabel('Número Médio de Comparações')
plt.legend()

# Criar uma nova figura para o gráfico de comparação
plt.figure("Comparação",figsize=(10, 4))

# Adicionar o terceiro subplot (Comparação)
plt.plot(x_dense, y_lista_interp, label='Lista Encadeada', color='red')
plt.plot(x_dense, y_arvore_interp, label='Árvore de Busca Binária', color='green')
plt.title('Comparação de Desempenho: Lista Encadeada vs. Árvore de Busca Binária')
plt.xlabel('Tamanho da Entrada')
plt.ylabel('Número Médio de Comparações')
plt.legend()

# Adicionar título e rótulos à figura inteira
plt.xlabel('Tamanho da Entrada')
plt.ylabel('Número Médio de Comparações')

# Exibir as figuras
plt.tight_layout()
plt.show()