# 🎨 Filter Image - Inversor de Cores BMP

> *Transforme suas imagens em negativos artísticos com um toque de magia binária!*

![C](https://img.shields.io/badge/Linguagem-C-blue?style=for-the-badge&logo=c)
![BMP](https://img.shields.io/badge/Formato-BMP%2024bit-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

## 📖 O que é este projeto?

Este é um programa escrito em **C puro** que pega uma imagem e faz algo mágico: **inverte todas as cores**! Sabe quando você olha o negativo de uma foto antiga de filme? É exatamente isso! O branco vira preto, o vermelho vira ciano, o azul vira amarelo... Uma verdadeira arte digital!

---

## 🧠 Como o algoritmo funciona?

### A Mágica por Trás da Inversão

Imagine que cada cor na sua imagem é um número de **0 a 255**:
- **0** = ausência total de cor (escuro)
- **255** = intensidade máxima da cor (brilhante)

Para inverter uma cor, fazemos uma conta super simples:

```
Nova Cor = 255 - Cor Original
```

**Exemplos práticos:**
| Cor Original | Cálculo | Resultado |
|-------------|---------|-----------|
| Preto (0) | 255 - 0 = 255 | Branco |
| Branco (255) | 255 - 255 = 0 | Preto |
| Vermelho Puro (255, 0, 0) | (0, 255, 255) | Ciano |
| Azul Puro (0, 0, 255) | (255, 255, 0) | Amarelo |

---

## 🖼️ Entendendo Imagens BMP

### O que é um arquivo BMP?

BMP (**BitMap**) é um dos formatos de imagem mais simples que existe! Diferente do JPG ou PNG, ele guarda a imagem quase sem compressão, o que o torna perfeito para aprender manipulação de imagens.

### A Anatomia de um BMP

Um arquivo BMP é como um sanduíche de dados organizado em 3 camadas:

```
┌─────────────────────────────────────┐
│         📋 FILE HEADER              │  ← "Olá, sou um BMP!" (14 bytes)
│   - Assinatura "BM"                 │
│   - Tamanho total do arquivo        │
│   - Onde os pixels começam          │
├─────────────────────────────────────┤
│         📐 INFO HEADER              │  ← Detalhes técnicos (40+ bytes)
│   - Largura e altura da imagem      │
│   - Bits por pixel (24 = colorido)  │
│   - Compressão utilizada            │
├─────────────────────────────────────┤
│         🎨 PIXEL DATA               │  ← A imagem em si!
│   - Cada pixel = 3 bytes (R, G, B)  │
│   - Linhas com padding de 4 bytes   │
└─────────────────────────────────────┘
```

### 🤔 Por que 24 bits?

Cada pixel usa **24 bits** (3 bytes):
- **8 bits** para Vermelho (Red)
- **8 bits** para Verde (Green)  
- **8 bits** para Azul (Blue)

Com 8 bits, cada cor pode ter **256 níveis** (0-255), resultando em:

```
256 × 256 × 256 = 16.777.216 cores possíveis! 🌈
```

### 📏 O Misterioso Padding

Aqui vai um detalhe curioso: o formato BMP exige que **cada linha de pixels tenha um tamanho em bytes divisível por 4**!

Por quê? Por questões de eficiência de memória dos computadores antigos.

**Exemplo:** Se sua imagem tem largura de 5 pixels:
- 5 pixels × 3 bytes = 15 bytes
- 15 não é divisível por 4
- Precisamos adicionar 1 byte de "enchimento" (padding)
- 15 + 1 = 16 ✓ (divisível por 4!)

O programa calcula isso automaticamente com a fórmula:
```c
int padding = (4 - (width * 3) % 4) % 4;
```

---

## 🔧 Como o código funciona?

### Passo a Passo Simplificado

```
1️⃣  Abre o arquivo de imagem (input.bmp)
        ↓
2️⃣  Lê os cabeçalhos (headers) do BMP
        ↓
3️⃣  Verifica se é um BMP válido de 24 bits
        ↓
4️⃣  Carrega todos os pixels na memória
        ↓
5️⃣  Para cada pixel: inverte as cores RGB
        ↓
6️⃣  Salva a imagem modificada (output.bmp)
        ↓
7️⃣  Libera a memória e celebra! 🎉
```

### A Inversão de Cores no Código

Este é o coração do algoritmo:

```c
for (int i = 0; i < width * height; i++)
{
    image[i].red   = 255 - image[i].red;
    image[i].green = 255 - image[i].green;
    image[i].blue  = 255 - image[i].blue;
}
```

**O que está acontecendo:**
1. Percorremos **todos** os pixels da imagem
2. Para cada pixel, pegamos seu valor de vermelho, verde e azul
3. Subtraímos de 255 para obter o valor invertido
4. Guardamos o novo valor de volta

É simples, elegante e **muito rápido**! ⚡

---

## 🚀 Como executar

### Pré-requisitos

- GCC (Compilador C)
- Uma imagem BMP de 24 bits chamada `input.bmp`

### Compilando e Executando

```bash
# Clone o repositório
git clone <url-do-repo>
cd filter_image

# Coloque sua imagem BMP como input.bmp na pasta

# Execute com Make
make run

# Ou compile manualmente
gcc main.c -o main && ./main
```

### Resultado

Se tudo der certo, você verá:
```
Sucesso! Verifique 'output.bmp'.
```

Sua imagem invertida estará em `output.bmp`! 🎨

---

## 📁 Estrutura do Projeto

```
filter_image/
├── main.c          # 🧠 Código fonte principal
├── Makefile        # 🔨 Automação de compilação
├── input.bmp       # 🖼️ Imagem de entrada
├── output.bmp      # 🎨 Imagem processada (gerada)
└── README.md       # 📖 Este arquivo!
```

---

## 🎓 Conceitos Aprendidos

Este projeto é excelente para aprender:

- ✅ **Manipulação de arquivos binários** em C
- ✅ **Estruturas de dados** (`struct`) com empacotamento
- ✅ **Alocação dinâmica de memória** (`malloc`/`free`)
- ✅ **Formato de imagem BMP** e seus headers
- ✅ **Aritmética de ponteiros** e arrays
- ✅ **Processamento de imagens** básico

---

## 💡 Dicas e Curiosidades

### 🔍 O `#pragma pack(push, 1)`

O compilador normalmente alinha dados na memória em múltiplos de 4 bytes para otimização. Mas os headers do BMP precisam de tamanhos **exatos**! O `#pragma pack(1)` força o compilador a usar exatamente o tamanho que definimos.

### 🔄 Ordem invertida: BGR em vez de RGB

Curiosidade: no formato BMP, os pixels são armazenados na ordem **Azul-Verde-Vermelho** (BGR), não RGB! Por isso a struct `Pixel` define `blue` primeiro.

### ↕️ Imagens de cabeça para baixo?

O BMP pode armazenar imagens de baixo para cima (height positivo) ou de cima para baixo (height negativo). Nosso código usa `abs(height)` para lidar com ambos!

---

## 🚧 Próximas Ideias

Quer expandir este projeto? Algumas sugestões:

- [ ] 🖤 Filtro de escala de cinza
- [ ] 🔆 Ajuste de brilho e contraste
- [ ] 🌀 Efeito blur (desfoque)
- [ ] 📐 Rotação de imagem
- [ ] 🖼️ Suporte a outros formatos (PNG, JPG)

---

## 📜 Licença

Este projeto é livre para uso educacional. Divirta-se aprendendo! 🎉

---

<div align="center">

**Feito com ❤️ e bytes**

*"Uma imagem vale mais que mil palavras, mas precisa de milhões de bytes!"*

</div>
