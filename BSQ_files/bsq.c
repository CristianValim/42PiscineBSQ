#include "bsq_header.h"
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    int total_bytes;
    char *buffer;
    t_map map; // Declare a variável t_map corretamente

    fd = open("map", O_RDONLY); // Tente abrir o arquivo
    if (fd < 0)
    {
        print_map_error(); // Imprima um erro se não puder abrir o arquivo
        return (1);
    }

    map = (t_map){0}; // Inicialize a variável map
    buffer = read_file("map", &map, &total_bytes); // Leia o conteúdo do arquivo
    if (!buffer)
    {
        print_map_error(); // Erro se a leitura do buffer falhar
        cleanup(&map, buffer, fd);
        return (1); // Retorne erro se o buffer estiver vazio
    }

    // Verificações do mapa
    if (!check_header(map.header, &map))
    {
        cleanup(&map, buffer, fd);
        return (1); // Retorne erro se o cabeçalho do mapa estiver incorreto
    }

    if (!check_map(&map))
    {
        cleanup(&map, buffer, fd);
        return (1); // Retorne erro se o mapa não for válido
    }

    if (!check_length(&map))
    {
        cleanup(&map, buffer, fd);
        return (1); // Retorne erro se o comprimento do mapa estiver incorreto
    }

    cleanup(&map, buffer, fd); // Limpeza de recursos
    return (0); // Retorne 0 para indicar sucesso
}
