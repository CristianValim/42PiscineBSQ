/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:03:08 by cvalim-d          #+#    #+#             */
/*   Updated: 2024/10/09 19:11:21 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "bsq_header.h"

char *check_lines(char *buffer, char **header, char ***map, int *total_lines) {
    printf("[check_lines] Iniciando verificação de linhas.\n");
    char *newline = ft_strchr(buffer, '\n'); // Encontra o primeiro newline
    if (newline) {
        printf("[check_lines] Newline encontrado, separando cabeçalho e mapa.\n");
        *header = ft_strndup(buffer, newline - buffer); // Aloca e copia o cabeçalho
        char *map_start = newline + 1; // Posição onde o mapa começa

        // Faz uma cópia do buffer para usar na contagem de linhas
        char *buffer_copy = ft_strdup(map_start);
        if (!buffer_copy) {
            printf("Erro ao duplicar o buffer");
            return NULL;
        }

        // Contando as linhas do mapa
        printf("[check_lines] Contando as linhas do mapa.\n");
        char *line = ft_tiktok(buffer_copy, '\n');
        while (line != NULL) {
            (*total_lines)++;
            line = ft_tiktok(NULL, 10);
        }
        printf("[check_lines] Total de linhas no mapa: %d\n", *total_lines);

        // Aloca memória para o mapa baseado no total de linhas contadas
        *map = malloc((*total_lines) * sizeof(char *));
        if (*map == NULL) {
            printf("Erro ao alocar memória para o mapa");
            free(buffer_copy);
            return NULL;
        }

        // Segunda passagem para armazenar as linhas no mapa (usando o buffer original)
        printf("[check_lines] Armazenando as linhas do mapa.\n");
        line = ft_tiktok(map_start, 10); // Reinicia a tokenização no buffer original
        for (int i = 0; i < *total_lines; i++) {
            if (line) {
                (*map)[i] = ft_strdup(line); // Duplica a linha
                if ((*map)[i] == NULL) {
                    printf("Erro ao duplicar linha do mapa");
                    // Libera a memória alocada em caso de erro
                    for (int j = 0; j < i; j++) {
                        free((*map)[j]);
                    }
                    free(*map);
                    free(buffer_copy);
                    return NULL;
                }
                line = ft_tiktok(NULL, 10);
            }
        }

        free(buffer_copy); // Libera a cópia do buffer
        printf("[check_lines] Linhas do mapa processadas com sucesso.\n");
        return buffer; // Retorna o buffer se o processamento for bem-sucedido
    }

    printf("[check_lines] Formato inválido: nenhum newline encontrado.\n");
    return NULL; // Formato inválido
}
char *read_file(char *file_name, char **header, char ***map, int *total_lines, size_t *total_bytes) {
    printf("[read_file] Abrindo arquivo: %s\n", file_name);
    int file_descriptor = open(file_name, O_RDONLY);
    if (file_descriptor == -1) {
        printf("Erro ao abrir o arquivo");
        return NULL;
    }

    // Passo 1: Contar o número total de bytes no arquivo
    printf("[read_file] Contando o número total de bytes no arquivo.\n");
    char temp;
    *total_bytes = 0;
    while (read(file_descriptor, &temp, 1) > 0) {
        (*total_bytes)++;
    }

    // Verifica se ocorreu um erro durante a leitura ou se o arquivo está vazio
    if (*total_bytes == 0) {
        printf("[read_file] Arquivo vazio ou erro ao ler o arquivo.\n");
        close(file_descriptor);
        return NULL;
    }
    printf("[read_file] Total de bytes lidos: %zu\n", *total_bytes);

    // Fechar e reabrir o arquivo para resetar o ponteiro de leitura para o início
    close(file_descriptor);
    file_descriptor = open(file_name, O_RDONLY);
    if (file_descriptor == -1) {
        printf("Erro ao reabrir o arquivo");
        return NULL;
    }

    // Passo 2: Aloca o buffer com base no tamanho calculado + 1 para o caractere nulo
    printf("[read_file] Alocando buffer para leitura do arquivo.\n");
    char *buffer = malloc(*total_bytes + 1);
    if (buffer == NULL) {
        printf("Erro ao alocar memória para o buffer final");
        close(file_descriptor);
        return NULL;
    }

    // Ler o conteúdo do arquivo para o buffer alocado
    printf("[read_file] Lendo o conteúdo do arquivo.\n");
    size_t bytes_read = read(file_descriptor, buffer, *total_bytes);
    if (bytes_read != *total_bytes) {
        printf("Erro ao ler o conteúdo do arquivo");
        free(buffer);
        close(file_descriptor);
        return NULL;
    }
    buffer[*total_bytes] = '\0'; // Adiciona o caractere nulo ao final
    printf("[read_file] Conteúdo do arquivo lido com sucesso.\n");

    // Fecha o arquivo após a leitura
    close(file_descriptor);

    // Passo 3: Processar o conteúdo
    printf("[read_file] Processando o conteúdo do arquivo.\n");
    char *result = check_lines(buffer, header, map, total_lines);
    if (result == NULL) {
        printf("[read_file] Erro ao processar o conteúdo do arquivo.\n");
        free(buffer); // Libera buffer se o processamento falhar
    } else {
        printf("[read_file] Arquivo processado com sucesso.\n");
    }

    return result; // Retorna o buffer ou NULL se houver erro
}

int	check_header(char *header, int *max_lines, char *empty,
		char *obstacle, char *full)
{
	printf("[check_header] Verificando cabeçalho: %s\n", header);
	// Verifica se o cabeçalho é válido
	if (header == NULL || ft_strlen(header) < 4)
	{
		printf("[check_header] Cabeçalho inválido: NULL ou tamanho menor que 4\n");
		return (0);
	}
	// A última parte da string contém as variáveis do mapa
	*empty = header[ft_strlen(header) - 3];
	*obstacle = header[ft_strlen(header) - 2];
	*full = header[ft_strlen(header) - 1];

	// O número de linhas é tudo antes dos últimos três caracteres
	char *line_count_str = ft_strndup(header, ft_strlen(header) - 3); // Copia tudo exceto os últimos 3 caracteres

	// Verifica se todos os caracteres em line_count_str são dígitos
	int i = 0;
	while (line_count_str[i] != '\0')
	{
		if (!(line_count_str[i] >= '0' && line_count_str[i] <= '9'))
		{
			printf("[check_header] Cabeçalho inválido: '%s' contém caracteres não numéricos.\n", line_count_str);
			free(line_count_str); // Libera a memória alocada
			return (0);
		}
		i++;
	}

	*max_lines = atoi(line_count_str);
	free(line_count_str); // Libera a memória alocada

	// Verifica se os caracteres são válidos e diferentes
	if (*empty == *obstacle || *empty == *full || *obstacle == *full)
	{
		printf("[check_header] Cabeçalho inválido: caracteres variáveis devem ser diferentes\n");
		return (0);
	}

	printf("[check_header] Cabeçalho válido: max_lines=%d, empty='%c', obstacle='%c', full='%c'\n", *max_lines, *empty, *obstacle, *full);
	return (1); // Cabeçalho válido
}
int	check_map(char **map, int total_lines, int max_lines, char empty,
		char obstacle, char full)
{
	size_t	line_length;
	char	current_char;

	printf("[check_map] Verificando mapa: total_lines=%d, max_lines=%d\n",
		total_lines, max_lines);
	if (total_lines != max_lines)
	{
		printf("[check_map] Erro: Número de linhas lidas (%d) difere do número esperado (%d)\n", total_lines, max_lines);
		return (0); // Mapa inválido
	}
	for (int i = 0; i < total_lines; i++)
	{
		line_length = ft_strlen(map[i]);
		printf("[check_map] Linha %d: %s (comprimento: %zu)\n", i, map[i],
			line_length);
		if (line_length == 0)
		{
			printf("[check_map] Erro: Linha %d está vazia.\n", i);
			return (0); // Mapa inválido
		}
		for (size_t j = 0; j < line_length; j++)
		{
			current_char = map[i][j];
			if (current_char != empty && current_char != obstacle
				&& current_char != full)
			{
				printf("[check_map] Erro: Caractere inválido '%c' encontrado na linha %d\n", current_char, i);
				return (0); // Mapa inválido
			}
		}
	}
	return (1); // Mapa válido
}

int	check_length(char **map, int total_lines)
{
	size_t	first_line_length;

	printf("[check_length] Verificando comprimento das linhas, total_lines=%d\n", total_lines);
	if (total_lines == 0)
	{
		printf("[check_length] Mapa vazio é considerado válido\n");
		return (1); // Um mapa vazio é considerado válido
	}
	first_line_length = ft_strlen(map[0]);
	for (int i = 0; i < total_lines; i++)
	{
		if (ft_strlen(map[i]) != first_line_length)
		{
			printf("[check_length] Erro: Comprimento da linha %d (%zu) difere do comprimento da primeira linha (%zu)\n", i,
				ft_strlen(map[i]), first_line_length);
			return (0); // Mapa inválido
		}
	}
	printf("[check_length] Todas as linhas têm o mesmo comprimento\n");
	return (1); // Todas as linhas têm o mesmo comprimento
}

int main(void)
{
    int     fd;
    char    *header;
    int     total_lines;
    char    *buffer;
    int     max_lines;

    // Nome do arquivo como variável
    char *file_name = "map7";

    // Abre o arquivo usando a variável file_name
    printf("[main] Abrindo o arquivo: %s\n", file_name);
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
        printf("Erro ao abrir o arquivo");
        return (1);
    }

    header = NULL;
    char **map = NULL; // Ponteiro para o mapa
    total_lines = 0;
    size_t total_bytes = 0; // Adicionando total_bytes aqui

    // Lê o arquivo e obtém o cabeçalho, variáveis e mapa
    printf("[main] Lendo o arquivo e processando o mapa.\n");
    buffer = read_file(file_name, &header, &map, &total_lines, &total_bytes);
    if (buffer)
    {
        printf("[main] Header: %s\n", header);
        char empty, obstacle, full;
        if (check_header(header, &max_lines, &empty, &obstacle, &full))
        {
            if (check_map(map, total_lines, max_lines, empty, obstacle, full))
            {
                if (check_length(map, total_lines))
                {
                    printf("[main] Mapa verificado com sucesso e todas as linhas têm o mesmo comprimento.\n");
                }
                else
                {
                    printf("[main] Mapa inválido: linhas de comprimentos diferentes.\n");
                }
            }
            else
            {
                printf("[main] Mapa inválido.\n");
            }
        }
        else
        {
            printf("[main] Cabeçalho inválido.\n");
        }
    }
    else
    {
        printf("[main] Erro ao ler o arquivo ou arquivo vazio.\n");
    }

    // Liberar memória
    printf("[main] Liberando memória.\n");
    free(header);
    for (int i = 0; i < total_lines; i++)
    {
        free(map[i]); // Libera cada linha do mapa
    }
    free(map); // Libera o array de ponteiros do mapa
    free(buffer); // Libera o buffer
    close(fd);
    printf("[main] Execução finalizada.\n");
    return (0);
}
