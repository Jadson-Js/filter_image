#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
// Cada atributo destes struct, não podem possuir memorias lixo
// O compilador vai setar multiplos de 4 bytes para cada atributo mesmo quando é desnecessario
#pragma pack(push, 1)
typedef struct
{
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPFileHeader;

typedef struct
{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t size_image;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
} BMPInfoHeader;

typedef struct
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} Pixel;
#pragma pack(pop)

int main()
{
    FILE *file = fopen("./input.bmp", "rb"); // Abri um arquivo novo/existente com permisão de leitura de binarios
    if (!file)
    {
        printf("Erro: Arquivo 'example.bmp' nao encontrado.\n");
        return 1;
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    // Leitura de arquivo
    // Onde será lido? no endereço da variavel fileHeader
    // Qual o tamanho do conteudo? o peso do tipo FileHeader
    // quantos items quero ler
    // Qual a origem do conteudo? o arquivo aberto "File"
    fread(&fileHeader, sizeof(BMPFileHeader), 1, file);
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);
    // Curiosidade, na 1° leitura o file position indicator começa no 0
    // Quando a 1° leitura é finalizada. a 2° começa da position na frente. ex: se fosse um video de 4 minutos, e na 1° leitura fosse lida
    // até o minuto 2, a 2° leitura leria do minuto 2:01 adiente

    // Essa condicional é para saber se o tipo é igual a BM (BitMap)
    if (fileHeader.type != 0x4D42)
    { // o atributo está em Hexadecimal e devido a arquitetura do processador está invertido.
        printf("Erro: Nao e um arquivo BMP valido.\n");
        fclose(file);
        return 1;
    }

    if (infoHeader.bit_count != 24)
    { // Condicional para saber se está 24 bit por pixel
        printf("Erro: Apenas BMPs de 24 bits sao suportados.\n");
        fclose(file);
        return 1;
    }

    int width = infoHeader.width;
    int height = abs(infoHeader.height); // caso o height seje negativo, vira em positivo

    // O tamanho em byte de cada row da imagem deve ser divisivel por 4, esse calculo ver o padding faltando para cumprir o requisito
    int padding = (4 - (width * sizeof(Pixel)) % 4) % 4;

    Pixel *image = malloc(width * height * sizeof(Pixel)); // Alocação de memoria para a image
    if (!image)
    {
        printf("Erro de memoria.\n");
        fclose(file);
        return 1;
    }

    // Vai movimentar o file position indicator para o inicio da imagem
    // 1° O arquivo que será manipulado
    // 2° avance x bytes a frente para ai começar ler somente o conteudo
    // 3° "partir do inicio do arquivo byte 0"
    fseek(file, fileHeader.offset, SEEK_SET);

    // vai copiar o input para settar nessa variavel image temporiariamente
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            fread(&image[y * width + x], sizeof(Pixel), 1, file);
        }
        // Lembra do padding que foi adicionado a memoria do arquivo para ser divisivel por 4
        // Essa function vai pular para ler somente os conteudo da image
        fseek(file, padding, SEEK_CUR);
        // Curiosidade, o SEET_SET é o inicio absoluto do arquivo,
        // SEEK_CUR, é o inicio da position atual
    }
    fclose(file);

    // Aqui será invertido as cores do rgb, esse loop percorre a image temporiaria
    for (int i = 0; i < width * height; i++)
    {
        image[i].red = 255 - image[i].red;
        image[i].green = 255 - image[i].green;
        image[i].blue = 255 - image[i].blue;
    }

    fileHeader.offset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);                // Definição de onde dados começam
    fileHeader.size = fileHeader.offset + (width * sizeof(Pixel) + padding) * height; // Definição do tamanho
    infoHeader.size = sizeof(BMPInfoHeader);                                          // Definição do tamanho do header
    infoHeader.compression = 0;                                                       // Garantia que o arquivo não está duplicado

    FILE *output = fopen("./output.bmp", "wb"); // É aberto um novo/existente arquivo com permisão de escrita binaria
    if (!output)
    {
        printf("Erro ao criar output.bmp\n");
        free(image);
        return 1;
    }

    fwrite(&fileHeader, sizeof(BMPFileHeader), 1, output); // É escrito no arquivo o header nele
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, output);

    uint8_t paddingByte = 0; // Garantia que o tamanho da row em bytes da imagem vai ser divisivel por 4.
    // e caso não for, o padding preenchera o restante com zeros
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            fwrite(&image[y * width + x], sizeof(Pixel), 1, output);
        }

        // Percorre o padding restante e vai preenchendo com zero
        for (int k = 0; k < padding; k++)
        {
            fwrite(&paddingByte, 1, 1, output);
        }
    }

    fclose(output);
    free(image);
    printf("Sucesso! Verifique 'output.bmp'.\n");

    return 0;
}