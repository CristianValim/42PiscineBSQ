#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char	*read_file(int file_descriptor, char **header, char **variables,
		char ***map, int *total_lines, size_t *total_bytes)
{
	size_t	buffer_size;
	char	*buffer;
	ssize_t	bytesRead;
	char	*line;

	buffer_size = BUFFER_SIZE;
	buffer = malloc(buffer_size);
	*total_bytes = 0;
	while ((bytesRead = read(file_descriptor, buffer + *total_bytes, buffer_size
				- *total_bytes - 1)) > 0)
	{
		*total_bytes += bytesRead;
		// Verifica se é necessário aumentar o buffer
		if (*total_bytes + 1 >= buffer_size)
		{
			buffer_size *= 2;
			buffer = realloc(buffer, buffer_size);
			if (buffer == NULL)
			{
				perror("Erro ao realocar memória");
				return (NULL);
			}
		}
	}
	if (bytesRead == -1)
	{
		perror("Erro ao ler o arquivo");
		free(buffer);
		return (NULL);
	}
	buffer[*total_bytes] = '\0'; // Adiciona o caractere nulo
	char *newline = strchr(buffer, '\n'); // Encontra o primeiro newline
	if (newline)
	{
		*header = strndup(buffer, newline - buffer);
		char *map_start = newline + 1; // Posição onde o mapa começa
		// Contando as linhas do mapa
		line = strtok(map_start, "\n");
		while (line != NULL)
		{
			(*total_lines)++;
			*map = realloc(*map, (*total_lines) * sizeof(char *));
			(*map)[*total_lines - 1] = strdup(line); // Duplica a linha
			line = strtok(NULL, "\n");
		}
		// Copia as variáveis (os últimos 3 caracteres)
		*variables = strdup(map_start + strlen(map_start) + 1);
			// Adaptação pode ser necessária aqui
		return (buffer);
			// Retorna o buffer
	}
	free(buffer);
	return (NULL); // Formato inválido
}

int	check_header(const char *header, int *max_lines, char *empty,
		char *obstacle, char *full)
{
	printf("[check_header] Verificando cabeçalho: %s\n", header);
	// Verifica se o cabeçalho é válido
	if (header == NULL || strlen(header) < 4)
	{
		printf("[check_header] Cabeçalho inválido: NULL ou tamanho menor que 5\n");
		return (0);
	}
	// A última parte da string contém as variáveis do mapa
	*empty = header[strlen(header) - 3];
	*obstacle = header[strlen(header) - 2];
	*full = header[strlen(header) - 1];
	// O número de linhas é tudo antes dos últimos três caracteres
	char *line_count_str = strndup(header, strlen(header) - 3);
		// Copia tudo exceto os últimos 3 caracteres
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
		line_length = strlen(map[i]);
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
	first_line_length = strlen(map[0]);
	for (int i = 0; i < total_lines; i++)
	{
		if (strlen(map[i]) != first_line_length)
		{
			printf("[check_length] Erro: Comprimento da linha %d (%zu) difere do comprimento da primeira linha (%zu)\n", i,
				strlen(map[i]), first_line_length);
			return (0); // Mapa inválido
		}
	}
	printf("[check_length] Todas as linhas têm o mesmo comprimento\n");
	return (1); // Todas as linhas têm o mesmo comprimento
}

int	main(void)
{
	int		fd;
	char	*header;
	char	*variables;
	int		total_lines;
	char	*buffer;
		int max_lines;

	fd = open("map", O_RDONLY);
	if (fd < 0)
	{
		perror("Erro ao abrir o arquivo");
		return (1);
	}
	header = NULL;
	variables = NULL;
	char **map = NULL; // Ponteiro para o mapa
	total_lines = 0;
	size_t total_bytes = 0; // Adicionando total_bytes aqui
	// Lê o arquivo e obtém o cabeçalho, variáveis e mapa
	buffer = read_file(fd, &header, &variables, &map, &total_lines,
			&total_bytes);
	if (buffer)
	{
		printf("Header: %s\n", header);
		printf("Variáveis: %s\n", variables);
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
	// Liberar memória
	free(header);
	free(variables);
	for (int i = 0; i < total_lines; i++)
	{
		free(map[i]); // Libera cada linha do mapa
	}
	free(map); // Libera o array de ponteiros do mapa
	close(fd);
	return (0);
}
