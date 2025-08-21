#include <stdio.h>
#include <stdlib.h> // Para system("clear") ou system("cls")
#include <string.h> // Para strcpy

// Define a estrutura para armazenar os dados de uma carta (país)
typedef struct {
    char nome[50];
    unsigned long int populacao;
    float area;
    double pib; // Produto Interno Bruto em trilhões de USD
    float idh; // Índice de Desenvolvimento Humano
    float densidade_demografica; // Campo calculado
} CartaPais;

// --- Protótipos das Funções Auxiliares ---

// Exibe o menu de atributos, ocultando uma opção já escolhida
void exibirMenu(int atributo_ja_escolhido);

// Retorna o nome de um atributo com base no seu número
const char* getNomeAtributo(int escolha);

// Retorna o valor de um atributo específico de uma carta
double getValorAtributo(CartaPais carta, int escolha);

// Limpa o buffer de entrada para evitar problemas com scanf
void limpar_buffer();

// --- Função Principal ---
int main() {
    // 1. PREPARAÇÃO: Pré-cadastra as duas cartas
    CartaPais carta1, carta2;

    // Carta 1: Brasil
    strcpy(carta1.nome, "Brasil");
    carta1.populacao = 215300000;
    carta1.area = 8516000.0f;
    carta1.pib = 1.608;
    carta1.idh = 0.754f;
    carta1.densidade_demografica = (float)carta1.populacao / carta1.area;

    // Carta 2: Japão
    strcpy(carta2.nome, "Japão");
    carta2.populacao = 125700000;
    carta2.area = 377975.0f;
    carta2.pib = 4.231;
    carta2.idh = 0.925f;
    carta2.densidade_demografica = (float)carta2.populacao / carta2.area;

    int escolha1 = 0;
    int escolha2 = 0;
    int entrada_valida;

    // system("clear"); // Use "cls" no Windows
    
    printf("========================================\n");
    printf("      SUPER TRUNFO - Desafio Final\n");
    printf("========================================\n\n");
    printf("Carta 1: %s\n", carta1.nome);
    printf("Carta 2: %s\n", carta2.nome);

    // 2. ESCOLHA DO PRIMEIRO ATRIBUTO
    do {
        entrada_valida = 1; // Assume que a entrada será válida
        exibirMenu(0); // Mostra o menu completo (0 = nenhum atributo escolhido ainda)
        printf("Escolha o PRIMEIRO atributo para comparar (1-5): ");
        
        if (scanf("%d", &escolha1) != 1) { // Verifica se a entrada é um número
            limpar_buffer();
            escolha1 = 0; // Reseta a escolha para forçar repetição
        }

        switch (escolha1) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                // Escolha válida, sai do switch
                break;
            default:
                printf("\nOpção inválida! Por favor, escolha um número de 1 a 5.\n");
                entrada_valida = 0; // Força a repetição do loop
        }
    } while (!entrada_valida);

    printf("\nVocê escolheu: %s\n", getNomeAtributo(escolha1));

    // 3. ESCOLHA DO SEGUNDO ATRIBUTO (MENU DINÂMICO)
    do {
        entrada_valida = 1;
        exibirMenu(escolha1); // Mostra o menu ocultando o primeiro atributo escolhido
        printf("Escolha o SEGUNDO atributo para comparar (1-5): ");

        if (scanf("%d", &escolha2) != 1) {
            limpar_buffer();
            escolha2 = 0;
        }

        if (escolha2 == escolha1) {
            printf("\nAtributo já selecionado! Por favor, escolha um atributo diferente.\n");
            entrada_valida = 0;
        } else {
            switch (escolha2) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    break;
                default:
                    printf("\nOpção inválida! Por favor, escolha um dos atributos disponíveis.\n");
                    entrada_valida = 0;
            }
        }
    } while (!entrada_valida);

    printf("\nVocê escolheu: %s\n", getNomeAtributo(escolha2));
    
    // 4. COMPARAÇÃO E CÁLCULO
    double valor1_carta1 = getValorAtributo(carta1, escolha1);
    double valor2_carta1 = getValorAtributo(carta1, escolha2);
    double soma_carta1 = valor1_carta1 + valor2_carta1;

    double valor1_carta2 = getValorAtributo(carta2, escolha1);
    double valor2_carta2 = getValorAtributo(carta2, escolha2);
    double soma_carta2 = valor1_carta2 + valor2_carta2;

    // 5. EXIBIÇÃO CLARA DOS RESULTADOS
    printf("\n========================================\n");
    printf("          RESULTADO DA RODADA\n");
    printf("========================================\n");
    printf("Países: %s vs %s\n", carta1.nome, carta2.nome);
    printf("Atributos: %s e %s\n", getNomeAtributo(escolha1), getNomeAtributo(escolha2));
    printf("--------------------------------------------------\n");
    // Usando formatação para alinhar a saída em colunas
    printf("%-22s | %-12s | %-12s\n", "Atributo", carta1.nome, carta2.nome);
    printf("--------------------------------------------------\n");
    printf("%-22s | %-12.0f | %-12.0f\n", getNomeAtributo(escolha1), valor1_carta1, valor1_carta2);
    printf("%-22s | %-12.2f | %-12.2f\n", getNomeAtributo(escolha2), valor2_carta1, valor2_carta2);
    printf("--------------------------------------------------\n");
    printf("%-22s | %-12.2f | %-12.2f\n", "SOMA TOTAL", soma_carta1, soma_carta2);
    printf("========================================\n\n");
    
    // Lógica para determinar o vencedor com base na SOMA
    if (soma_carta1 > soma_carta2) {
        printf("VENCEDOR: %s venceu a rodada com a maior soma de atributos!\n", carta1.nome);
    } else if (soma_carta2 > soma_carta1) {
        printf("VENCEDOR: %s venceu a rodada com a maior soma de atributos!\n", carta2.nome);
    } else {
        printf("RESULTADO: Empate! A soma dos atributos é idêntica.\n");
    }

    return 0;
}


// --- Implementação das Funções Auxiliares ---

void exibirMenu(int atributo_ja_escolhido) {
    printf("\n--- Escolha um Atributo ---\n");
    // A condição (atributo_ja_escolhido != X) garante que a opção não apareça se já foi escolhida
    if (atributo_ja_escolhido != 1) printf("1 - População\n");
    if (atributo_ja_escolhido != 2) printf("2 - Área (km²)\n");
    if (atributo_ja_escolhido != 3) printf("3 - PIB (em trilhões USD)\n");
    if (atributo_ja_escolhido != 4) printf("4 - IDH (Índice de Dev. Humano)\n");
    if (atributo_ja_escolhido != 5) printf("5 - Densidade Demográfica\n"); // Lembre-se: menor é melhor
}

const char* getNomeAtributo(int escolha) {
    switch (escolha) {
        case 1: return "População";
        case 2: return "Área (km²)";
        case 3: return "PIB (em trilhões USD)";
        case 4: return "IDH";
        case 5: return "Densidade Demográfica";
        default: return "Desconhecido";
    }
}

double getValorAtributo(CartaPais carta, int escolha) {
    // Este switch é a chave para obter o valor correto de forma limpa
    // Retornar double simplifica os cálculos, pois todos os tipos numéricos podem ser convertidos para ele
    switch (escolha) {
        case 1: return (double)carta.populacao;
        case 2: return (double)carta.area;
        case 3: return carta.pib;
        case 4: return (double)carta.idh;
        case 5: return (double)carta.densidade_demografica;
        default: return 0.0;
    }
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}