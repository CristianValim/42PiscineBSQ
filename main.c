#include <stdio.h>
#define ROWS 10 // Define o número de linhas do mapa
#define COLS 10 // Define o número de colunas do mapa

// Função que verifica se um quadrado de tamanho 'size x size' pode ser colocado na posição (i, j) do mapa.
// Parâmetros:
// - mapa: matriz 2D representando o mapa com '.' para espaços livres e 'o' para obstáculos.
// - i: linha inicial para verificar o quadrado.
// - j: coluna inicial para verificar o quadrado.
// - size: tamanho do quadrado (ex: 2 para 2x2, 3 para 3x3, etc.).
// Retorna 1 se o quadrado pode ser colocado, e 0 caso contrário.
int cabe_quadrado(char mapa[ROWS][COLS], int i, int j, int size)
{
    // Verifica se o quadrado de tamanho 'size x size' cabe dentro dos limites do mapa
    // Por exemplo: se 'i' = 3, 'j' = 4 e 'size' = 2, verificamos se 3+2 <= 10 e 4+2 <= 10 (verdadeiro)
    if (i + size <= ROWS && j + size <= COLS)
    {
        int x = 0; // Variável para iterar sobre as linhas do quadrado
        // Itera pelas células dentro do quadrado para verificar se todas estão livres ('.')
        while (x < size) // Exemplo: se size = 2, x tomará os valores 0 e 1
        {
            int y = 0; // Variável para iterar sobre as colunas do quadrado
            while (y < size) // Exemplo: se size = 2, y tomará os valores 0 e 1
            {
                // Se qualquer célula dentro do quadrado contiver algo diferente de '.', retorna 0 (não cabe)
                // Por exemplo, se mapa[3][4] == 'o', retornará 0
                if (mapa[i + x][j + y] != '.')
                {
                    return 0; // Não cabe, pois encontrou um obstáculo
                }
                y++; // Incrementa a coluna
            }
            x++; // Incrementa a linha
        }
        return 1; // Retorna 1 se todas as células estiverem livres
    }
    return 0; // Retorna 0 se o quadrado ultrapassar os limites do mapa
}

// Função que marca um quadrado de tamanho 'size x size' com 'X' na posição (i, j) do mapa.
// Parâmetros:
// - mapa: matriz 2D representando o mapa.
// - i: linha inicial para marcar o quadrado.
// - j: coluna inicial para marcar o quadrado.
// - size: tamanho do quadrado a ser marcado.
void marcar_quadrado(char mapa[ROWS][COLS], int i, int j, int size)
{
    int x = 0; // Variável para iterar sobre as linhas do quadrado
    // Itera pelas células dentro do quadrado e marca com 'X'
    while (x < size) // Exemplo: se size = 2, x tomará os valores 0 e 1
    {
        int y = 0; // Variável para iterar sobre as colunas do quadrado
        while (y < size) // Exemplo: se size = 2, y tomará os valores 0 e 1
        {
            mapa[i + x][j + y] = 'X'; // Marca a célula (i+x, j+y) como 'X'
            y++; // Incrementa a coluna
        }
        x++; // Incrementa a linha
    }
}

// Função que procura o maior quadrado possível no mapa e marca a posição dele com 'X'.
// Parâmetros:
// - mapa: matriz 2D representando o mapa.
void procurar_maior_quadrado(char mapa[ROWS][COLS])
{
    int size;       // Tamanho atual do quadrado sendo testado
    int max_size;   // Maior tamanho de quadrado encontrado
    int max_i;      // Linha inicial do maior quadrado encontrado
    int max_j;      // Coluna inicial do maior quadrado encontrado
    int encontrado; // Flag para verificar se foi encontrado um quadrado do tamanho atual
    int i, j;

    // Inicializa variáveis
    size = 1;       // Começa procurando quadrados de tamanho 1x1
    max_size = 0;   // Inicializa o tamanho máximo como 0 (nenhum quadrado encontrado ainda)
    max_i = -1;     // Inicializa a linha máxima como -1 (não encontrada)
    max_j = -1;     // Inicializa a coluna máxima como -1 (não encontrada)

    while (1) // Inicia um loop infinito que será interrompido quando não houver mais quadrados
    {
        encontrado = 0; // Reseta a flag de encontrado a cada nova iteração
        i = 0; // Reinicia 'i' para percorrer as linhas do mapa
        // Percorre todas as linhas possíveis para o quadrado atual
        while (i <= ROWS - size) // Exemplo: se size = 2, vai até 8 (10-2)
        {
            j = 0; // Reinicia 'j' para percorrer as colunas do mapa
            // Percorre todas as colunas possíveis para o quadrado atual
            while (j <= COLS - size) // Exemplo: se size = 2, vai até 8 (10-2)
            {
                // Chama a função cabe_quadrado para verificar se o quadrado pode ser colocado
                if (cabe_quadrado(mapa, i, j, size)) // Exemplo: se i = 3, j = 4 e size = 2
                {
                    // Verifica se é a primeira vez que encontramos um quadrado
                    if (!encontrado) // Se ainda não encontramos um quadrado
                    {
                        max_size = size; // Guarda o tamanho do quadrado encontrado
                        max_i = i;       // Guarda a linha inicial
                        max_j = j;       // Guarda a coluna inicial
                        encontrado = 1;  // Marca que um quadrado foi encontrado
                    }
                    else
                    {
                        // Se já encontramos um quadrado, apenas verificamos se é maior ou mais próximo
                        // Se o tamanho do novo quadrado é maior ou se é do mesmo tamanho mas em uma posição mais próxima
                        if (size > max_size || (size == max_size && (i < max_i || (i == max_i && j < max_j))))
                        {
                            max_size = size; // Atualiza o tamanho do maior quadrado encontrado
                            max_i = i;       // Atualiza a linha inicial do maior quadrado
                            max_j = j;       // Atualiza a coluna inicial do maior quadrado
                        }
                    }
                }
                j++; // Incrementa a coluna
            }
            i++; // Incrementa a linha
        }
        // Se não encontrar um quadrado desse tamanho, sair do loop
        if (!encontrado) // Se não encontramos nenhum quadrado na iteração atual
        {
            break; // Sai do loop
        }
        size++; // Incrementa o tamanho do quadrado a ser testado
    }

    // Verifica se algum quadrado foi encontrado
    if (max_size > 0) // Se encontramos um quadrado maior que 0
    {
        // Imprime o tamanho e a posição do maior quadrado encontrado
        printf("Maior quadrado encontrado é %dx%d na posição (%d, %d)\n",
               max_size, max_size, max_i, max_j);
        // Marca o maior quadrado encontrado no mapa
        marcar_quadrado(mapa, max_i, max_j, max_size);
    }
    else
    {
        // Se não encontrou nenhum quadrado, imprime mensagem
        printf("Não há espaço para nenhum quadrado no mapa.\n");
    }
}

// Função para imprimir o mapa
// Parâmetros:
// - mapa: matriz 2D representando o mapa.
void imprimir_mapa(char mapa[ROWS][COLS])
{
    int i = 0; // Variável para iterar sobre as linhas do mapa
    // Percorre todas as linhas do mapa
    while (i < ROWS)
    {
        int j = 0; // Variável para iterar sobre as colunas do mapa
        // Percorre todas as colunas do mapa para imprimir cada célula
        while (j < COLS)
        {
            printf("%c ", mapa[i][j]); // Imprime o caractere da célula seguida de um espaço
            j++; // Incrementa a coluna
        }
        printf("\n"); // Imprime uma nova linha após terminar uma linha do mapa
        i++; // Incrementa a linha
    }
}

int main(void)
{
char mapa[ROWS][COLS] = {
    {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
    {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
    {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
    {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
    {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
    {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
    {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
    {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
    {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
    {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
};

    printf("Mapa original:\n");
    imprimir_mapa(mapa);
    procurar_maior_quadrado(mapa);
    printf("\nMapa atualizado com o maior quadrado marcado:\n");
    imprimir_mapa(mapa);
    return (0);
}
