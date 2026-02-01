# Filter Image - Inversão de Cores em Imagens BMP

Um programa em C que aplica o filtro de inversão de cores (efeito negativo) em imagens no formato BMP de 24 bits.

## Introdução

Este projeto demonstra como manipular imagens a nível de bytes, lendo e escrevendo arquivos binários diretamente. O algoritmo implementado inverte as cores de cada pixel, produzindo um efeito similar ao negativo de fotografias analógicas.

---

## 🎬 Demonstração

<p align="center">
  <img src="presentation.gif" alt="Demonstração do Filter Image" width="100%" />
</p>

---

## O Algoritmo de Inversão de Cores

### Fundamento Matemático

Em imagens digitais, cada componente de cor (vermelho, verde e azul) é representado por um valor inteiro de 0 a 255. O zero representa ausência total daquela cor, enquanto 255 representa sua intensidade máxima.

A inversão de uma cor é calculada subtraindo seu valor de 255:

```
Cor Invertida = 255 - Cor Original
```

Aplicando esta operação aos três canais de cor de cada pixel, obtemos o efeito de negativo.

**Exemplos:**

| Cor Original | Valores RGB | Cálculo | Resultado |
|-------------|-------------|---------|-----------|
| Preto | (0, 0, 0) | (255-0, 255-0, 255-0) | Branco (255, 255, 255) |
| Branco | (255, 255, 255) | (255-255, 255-255, 255-255) | Preto (0, 0, 0) |
| Vermelho | (255, 0, 0) | (255-255, 255-0, 255-0) | Ciano (0, 255, 255) |
| Azul | (0, 0, 255) | (255-0, 255-0, 255-255) | Amarelo (255, 255, 0) |

---

## Estrutura do Formato BMP

### Visão Geral

O formato BMP (Bitmap) é um dos mais simples para armazenamento de imagens. Sua estrutura sem compressão o torna ideal para estudos de processamento de imagens.

Um arquivo BMP é dividido em três seções:

```
+----------------------------------+
|         FILE HEADER              |  14 bytes
|   - Assinatura "BM" (0x4D42)     |
|   - Tamanho total do arquivo     |
|   - Offset para os dados         |
+----------------------------------+
|         INFO HEADER              |  40 bytes (BITMAPINFOHEADER)
|   - Dimensões da imagem          |
|   - Bits por pixel               |
|   - Tipo de compressão           |
+----------------------------------+
|         DADOS DOS PIXELS         |  Variável
|   - Pixels em formato BGR        |
|   - Padding para alinhamento     |
+----------------------------------+
```

### Representação de Cores: 24 Bits por Pixel

Neste formato, cada pixel ocupa 3 bytes (24 bits):

- 1 byte para o canal azul (Blue)
- 1 byte para o canal verde (Green)
- 1 byte para o canal vermelho (Red)

Nota: a ordem de armazenamento é BGR, não RGB. Esta é uma característica específica do formato BMP.

Com 8 bits por canal, cada um pode assumir 256 valores distintos, totalizando 16.777.216 combinações de cores possíveis.

### Alinhamento de Linhas (Padding)

O formato BMP exige que cada linha de pixels tenha um tamanho em bytes múltiplo de 4. Quando isso não ocorre naturalmente, bytes de preenchimento (padding) são adicionados ao final de cada linha.

O cálculo do padding é feito pela seguinte fórmula:

```c
int padding = (4 - (largura * 3) % 4) % 4;
```

Por exemplo, uma imagem com 5 pixels de largura:
- 5 pixels × 3 bytes = 15 bytes por linha
- 15 mod 4 = 3 (resta 3 para chegar em 16)
- Padding necessário: 1 byte

---

## Fluxo de Execução do Programa

O programa segue os seguintes passos:

1. Abre o arquivo de entrada (`input.bmp`) em modo binário
2. Lê e valida os headers do arquivo BMP
3. Verifica se o arquivo possui 24 bits por pixel
4. Aloca memória para armazenar todos os pixels
5. Carrega os dados da imagem, respeitando o padding
6. Aplica a inversão de cores em cada pixel
7. Grava a imagem resultante em `output.bmp`
8. Libera a memória alocada

### Implementação da Inversão

O trecho de código responsável pela inversão:

```c
for (int i = 0; i < width * height; i++)
{
    image[i].red   = 255 - image[i].red;
    image[i].green = 255 - image[i].green;
    image[i].blue  = 255 - image[i].blue;
}
```

O loop percorre linearmente todos os pixels da imagem (armazenados em um array unidimensional) e aplica a operação de inversão a cada canal de cor.

---

## Detalhes Técnicos

### Empacotamento de Estruturas

O código utiliza `#pragma pack(push, 1)` para desabilitar o alinhamento automático de memória feito pelo compilador. Por padrão, o compilador insere bytes de padding entre os campos de uma struct para otimizar o acesso à memória.

No entanto, os headers do BMP têm tamanhos fixos e precisos: o File Header deve ter exatamente 14 bytes e o Info Header, 40 bytes. Qualquer byte adicional corromperia a leitura do arquivo.

### Tratamento de Altura Negativa

O campo `height` no Info Header pode ser negativo, indicando que a imagem está armazenada de cima para baixo (ao invés do padrão de baixo para cima). O programa utiliza `abs(height)` para tratar ambos os casos.

---

## Compilação e Execução

### Requisitos

- Compilador GCC
- Arquivo `input.bmp` no formato BMP de 24 bits

### Comandos

```bash
# Usando Make
make run

# Ou manualmente
gcc main.c -o main && ./main
```

O programa gerará o arquivo `output.bmp` com a imagem invertida.

---

## Estrutura do Projeto

```
filter_image/
├── main.c          # Código fonte
├── Makefile        # Automação de build
├── input.bmp       # Imagem de entrada
├── output.bmp      # Imagem processada
└── README.md       # Documentação
```

---

## Conceitos Abordados

Este projeto aborda os seguintes conceitos de programação em C:

- Manipulação de arquivos binários (`fopen`, `fread`, `fwrite`, `fseek`)
- Definição de estruturas com tamanhos precisos
- Alocação dinâmica de memória
- Aritmética com ponteiros e arrays
- Processamento de dados binários

---

## Extensões Possíveis

O código pode ser expandido para implementar outros filtros:

- Conversão para escala de cinza
- Ajuste de brilho e contraste
- Efeito de desfoque (blur)
- Rotação e espelhamento
- Suporte a outros formatos de imagem

---

## Licença

Projeto disponível para uso educacional.
