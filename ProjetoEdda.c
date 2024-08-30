//Projeto DJA EDDA - Geovanna e Karol 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> // Para isdigit()

//--------------------------------CLIENTES-----------------------------------------------------
// Definição da estrutura para clientes
typedef struct {
    int cdatendimento;
    char dtatendimento[11];
    char hratendimento[6];
    char hrchegada[6];
    char comonosconheceu[40];
    char atendente[40];
    char pessoafisjurid[40];
    char nomepessoa[40];
    char pertencelgbtqiamais[40];
    char endereco[40];
    char celular[15];
    char email[40];
    char cpf[12];
    char genero[40];
    char raca[40];
    char dtnascimento[11];
    char nacionalidade[40];
    char naturalidade[40];
    char rg[10];
    char usa_whatsapp;
    char escolaridade[40];
    char profissao[40];
    char situacao_emprego[40];
    char estado_civil[20];
    char total_fml;
    char tem_filhos;
    int filhosmorando;
    int totalpessoasfamilia;
    char valor_beneficio;
    int rendamensal;
    int rendatotaloutrosfamiliares;
    char temgastosmedicos;
    int valorgastosmedicos;
    char possui_investimento;
    int valorinvestido;
    char possui_casa_propria;
    int valorcasa;
    char possui_apto;
    int valorapto;
    char possui_terreno;
    int valorterreno;
    char possui_imovel_comercial;
    int valorimovelcomercial;
    char possui_automovel;
    int valorautomovel;
    char violencia_domestica;
    char resumocaso[255];
    char ramodireito[40];
    char temperfilassistido;
} clientes;

// Função para verificar se o cliente existe
int verificarCliente(const char *cpf) {
    FILE *file = fopen("CLIENTES.DAT", "rb"); // 'rb' para leitura em binário
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return 0;
    }

    clientes clienteAtual;
    int encontrado = 0;

    while (fread(&clienteAtual, sizeof(clientes), 1, file) == 1) {
        if (strcmp(clienteAtual.cpf, cpf) == 0) {
            encontrado = 1;
            break;
        }
    }

    fclose(file);
    return encontrado;
}

//cria atutomaticamente o código de atendimento
void atualizaCodigoAtendimento() {
    FILE *file = fopen("ultimo_codigo.txt", "r+");
    if (file == NULL) {
        file = fopen("ultimo_codigo.txt", "w+");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo de controle.\n");
            exit(1);
        }
        fprintf(file, "%d", 1); // Começar com 1
        fclose(file);
        return;
    }
    int ultimo_codigo;
    fscanf(file, "%d", &ultimo_codigo);
    fseek(file, 0, SEEK_SET); // Voltar ao início do arquivo
    fprintf(file, "%d", ultimo_codigo + 1); // Atualizar o código
    fclose(file);
}

int getCodigoAtendimento() {
    FILE *file = fopen("ultimo_codigo.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de controle.\n");
        exit(1);
    }
    int codigo;
    fscanf(file, "%d", &codigo);
    fclose(file);
    return codigo;
}

void criaClienteDat(clientes *cliente) {
    FILE *file = fopen("CLIENTES.DAT", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Usando fwrite para gravar a struct no arquivo
    fwrite(cliente, sizeof(clientes), 1, file);

    fclose(file);
}

void obterDataEHoraAtual(char *data, char *hora) {
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    strftime(data, 11, "%d/%m/%Y", tm_info);
    strftime(hora, 6, "%H:%M", tm_info);
}

void inserirNovoCliente() {
    clientes cliente;
    char salvar;
    char repetir;

    // Atualiza e obtém o código de atendimento
    atualizaCodigoAtendimento();
    cliente.cdatendimento = getCodigoAtendimento();

    // Preenche data e horário atuais
    obterDataEHoraAtual(cliente.dtatendimento, cliente.hratendimento);
    strcpy(cliente.hrchegada, cliente.hratendimento); // Inicializa horário de chegada com o horário de atendimento

    printf("Código de Atendimento gerado automaticamente: %d\n", cliente.cdatendimento);
    printf("Data de Atendimento preenchida automaticamente: %s\n", cliente.dtatendimento);
    printf("Horário de Atendimento preenchido automaticamente: %s\n", cliente.hratendimento);
    
    printf("Digite o CPF do cliente (apenas números): ");
    scanf("%11s", cliente.cpf);
    getchar(); // Limpar o buffer

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]%*c", cliente.nomepessoa);

    printf("Digite o horário de chegada (hh:mm): ");
    scanf(" %5[^\n]", cliente.hrchegada);

    printf("Digite como nos conheceu: ");
    scanf(" %[^\n]%*c", cliente.comonosconheceu);
    
    printf("Digite o atendente: ");
    scanf(" %[^\n]%*c", cliente.atendente);
    
    printf("Digite se é pessoa física ou jurídica: ");
    scanf(" %[^\n]%*c", cliente.pessoafisjurid);
    
    printf("Digite se o cliente faz parte da comunidade LGBTQIA+: ");
    scanf(" %[^\n]%*c", cliente.pertencelgbtqiamais);
    
    printf("Digite o endereço do cliente: ");
    scanf(" %[^\n]%*c", cliente.endereco);
    
    printf("Digite o celular do cliente: ");
    scanf(" %[^\n]%*c", cliente.celular);
    
    printf("Digite o email do cliente: ");
    scanf(" %[^\n]%*c", cliente.email);
    
    printf("Digite a data de nascimento (dd/mm/yyyy): ");
    scanf("%10s", cliente.dtnascimento);
    
    printf("Digite a nacionalidade do cliente: ");
    scanf(" %[^\n]%*c", cliente.nacionalidade);
    
    printf("Digite a naturalidade do cliente: ");
    scanf(" %[^\n]%*c", cliente.naturalidade);
    
    printf("Digite o RG do cliente: ");
    scanf("%9s", cliente.rg);
    
    printf("O cliente usa WhatsApp? (s/n): ");
    scanf(" %c", &cliente.usa_whatsapp);
    getchar(); // Limpar o buffer

    printf("Digite a escolaridade do cliente: ");
    scanf(" %[^\n]%*c", cliente.escolaridade);
    
    printf("Digite a profissão do cliente: ");
    scanf(" %[^\n]%*c", cliente.profissao);
    
    printf("Digite a situação de emprego do cliente: ");
    scanf(" %[^\n]%*c", cliente.situacao_emprego);
    
    printf("Digite o estado civil do cliente: ");
    scanf(" %[^\n]%*c", cliente.estado_civil);
    
    printf("O cliente tem filhos? (s/n): ");
    scanf(" %c", &cliente.tem_filhos);
    getchar(); // Limpar o buffer
    if (cliente.tem_filhos == 's') {
        printf("Quantos filhos moram com o cliente? ");
        scanf("%d", &cliente.filhosmorando);
        getchar(); // Limpar o buffer
    }

    printf("Digite o total de pessoas na família: ");
    scanf("%d", &cliente.totalpessoasfamilia);
    
    printf("O cliente recebe benefício? (s/n): ");
    scanf(" %c", &cliente.valor_beneficio);
    getchar(); // Limpar o buffer
    if (cliente.valor_beneficio == 's') {
        printf("Qual o valor do benefício? ");
        scanf("%d", &cliente.valor_beneficio);
        getchar(); // Limpar o buffer
    }

    printf("Digite a renda mensal do cliente: ");
    scanf("%d", &cliente.rendamensal);
    
    printf("Digite a renda total dos outros familiares: ");
    scanf("%d", &cliente.rendatotaloutrosfamiliares);
    
    printf("O cliente tem gastos médicos? (s/n): ");
    scanf(" %c", &cliente.temgastosmedicos);
    getchar(); // Limpar o buffer
    if (cliente.temgastosmedicos == 's') {
        printf("Qual o valor dos gastos médicos? ");
        scanf("%d", &cliente.valorgastosmedicos);
        getchar(); // Limpar o buffer
    }

    printf("O cliente possui investimentos? (s/n): ");
    scanf(" %c", &cliente.possui_investimento);
    getchar(); // Limpar o buffer
    if (cliente.possui_investimento == 's') {
        printf("Qual o valor investido? ");
        scanf("%d", &cliente.valorinvestido);
        getchar(); // Limpar o buffer
    }

    printf("O cliente possui casa própria? (s/n): ");
    scanf(" %c", &cliente.possui_casa_propria);
    getchar(); // Limpar o buffer
    if (cliente.possui_casa_propria == 's') {
        printf("Qual o valor da casa? ");
        scanf("%d", &cliente.valorcasa);
        getchar(); // Limpar o buffer
    }

    printf("O cliente possui apartamento? (s/n): ");
    scanf(" %c", &cliente.possui_apto);
    getchar(); // Limpar o buffer
    if (cliente.possui_apto == 's') {
        printf("Qual o valor do apartamento? ");
        scanf("%d", &cliente.valorapto);
        getchar(); // Limpar o buffer
    }

    printf("O cliente possui terreno? (s/n): ");
    scanf(" %c", &cliente.possui_terreno);
    getchar(); // Limpar o buffer
    if (cliente.possui_terreno == 's') {
        printf("Qual o valor do terreno? ");
        scanf("%d", &cliente.valorterreno);
        getchar(); // Limpar o buffer
    }

    printf("O cliente possui imóvel comercial? (s/n): ");
    scanf(" %c", &cliente.possui_imovel_comercial);
    getchar(); // Limpar o buffer
    if (cliente.possui_imovel_comercial == 's') {
        printf("Qual o valor do imóvel comercial? ");
        scanf("%d", &cliente.valorimovelcomercial);
        getchar(); // Limpar o buffer
    }

    printf("O cliente possui automóvel? (s/n): ");
    scanf(" %c", &cliente.possui_automovel);
    getchar(); // Limpar o buffer
    if (cliente.possui_automovel == 's') {
        printf("Qual o valor do automóvel? ");
        scanf("%d", &cliente.valorautomovel);
        getchar(); // Limpar o buffer
    }

    printf("O cliente sofreu violência doméstica? (s/n): ");
    scanf(" %c", &cliente.violencia_domestica);
    getchar(); // Limpar o buffer

    printf("Digite um resumo do caso: ");
    scanf(" %[^\n]%*c", cliente.resumocaso);
    
    printf("Digite o ramo do direito: ");
    scanf(" %[^\n]%*c", cliente.ramodireito);
    
    printf("O cliente tem perfil assistido? (s/n): ");
    scanf(" %c", &cliente.temperfilassistido);
    getchar(); // Limpar o buffer

    // Solicitar confirmação antes de salvar
    printf("Deseja salvar este registro? (s/n): ");
    scanf(" %c", &salvar);
    getchar(); // Limpar o buffer

    if (salvar == 's') {
        criaClienteDat(&cliente);
        printf("Registro salvo com sucesso!\n");
    } else {
        printf("Registro descartado.\n");
    }

    // Perguntar se deseja cadastrar outro cliente
    printf("Deseja cadastrar outro cliente? (s/n): ");
    scanf(" %c", &repetir);
    getchar(); // Limpar o buffer

    if (repetir == 's') {
        inserirNovoCliente();  // Recursão para cadastrar outro cliente
    } else {
        printf("Cadastro encerrado.\n");
    }
}

//PARA A ORDENAÇÃO
// Função de comparação para QuickSort (comparar CPF)
int compararClientesPorCpf(const void *a, const void *b) {
    return strcmp(((clientes*)a)->cpf, ((clientes*)b)->cpf);
}

// Função para realizar busca binária em um array de clientes ordenado por CPF
clientes* buscarClienteBinario(clientes *clientesArray, int numClientes, const char *cpf) {
    int esquerda = 0;
    int direita = numClientes - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(clientesArray[meio].cpf, cpf);

        if (cmp == 0) {
            return &clientesArray[meio];
        }
        if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return NULL; // CPF não encontrado
}

// Função para consultar clientes
void consultarClientes() {
    FILE *file = fopen("CLIENTES.DAT", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Contar o número de registros no arquivo
    fseek(file, 0, SEEK_END);
    long tamanho = ftell(file);
    rewind(file);
    int numClientes = tamanho / sizeof(clientes);

    // Ler todos os registros em um array
    clientes *clientesArray = malloc(tamanho);
    if (clientesArray == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(file);
        return;
    }
    fread(clientesArray, sizeof(clientes), numClientes, file);

    // Ordenar o array de clientes por CPF
    qsort(clientesArray, numClientes, sizeof(clientes), compararClientesPorCpf);

    // Solicitar CPF para busca
    char cpf[12];
    printf("Digite o CPF do cliente que deseja consultar (apenas números): ");
    scanf("%11s", cpf);

    // Buscar o cliente usando busca binária
    clientes *clienteEncontrado = buscarClienteBinario(clientesArray, numClientes, cpf);

    if (clienteEncontrado != NULL) {
        // Exibir dados do cliente encontrado
        printf("\n--- Dados do Cliente ---\n");
        printf("Código de Atendimento: %d\n", clienteEncontrado->cdatendimento);
        printf("Nome: %s\n", clienteEncontrado->nomepessoa);
        printf("CPF: %s\n", clienteEncontrado->cpf);
        printf("Data de Atendimento: %s\n", clienteEncontrado->dtatendimento);
        printf("Horário de Atendimento: %s\n", clienteEncontrado->hratendimento);
        printf("Horário de Chegada: %s\n", clienteEncontrado->hrchegada);
        printf("Como Nos Conheceu: %s\n", clienteEncontrado->comonosconheceu);
        printf("Atendente: %s\n", clienteEncontrado->atendente);
        printf("Pessoa Física ou Jurídica: %s\n", clienteEncontrado->pessoafisjurid);
        printf("Pertence ao LGBTQIA+: %s\n", clienteEncontrado->pertencelgbtqiamais);
        printf("Endereço: %s\n", clienteEncontrado->endereco);
        printf("Celular: %s\n", clienteEncontrado->celular);
        printf("Email: %s\n", clienteEncontrado->email);
        printf("Data de Nascimento: %s\n", clienteEncontrado->dtnascimento);
        printf("Nacionalidade: %s\n", clienteEncontrado->nacionalidade);
        printf("Naturalidade: %s\n", clienteEncontrado->naturalidade);
        printf("RG: %s\n", clienteEncontrado->rg);
        printf("Usa WhatsApp: %c\n", clienteEncontrado->usa_whatsapp);
        printf("Escolaridade: %s\n", clienteEncontrado->escolaridade);
        printf("Profissão: %s\n", clienteEncontrado->profissao);
        printf("Situação de Emprego: %s\n", clienteEncontrado->situacao_emprego);
        printf("Estado Civil: %s\n", clienteEncontrado->estado_civil);
        printf("Tem Filhos: %c\n", clienteEncontrado->tem_filhos);
        if (clienteEncontrado->tem_filhos == 's') {
            printf("Filhos Morando: %d\n", clienteEncontrado->filhosmorando);
        }
        printf("Total de Pessoas na Família: %d\n", clienteEncontrado->totalpessoasfamilia);
        printf("Valor do Benefício: %c\n", clienteEncontrado->valor_beneficio);
        printf("Renda Mensal: %d\n", clienteEncontrado->rendamensal);
        printf("Renda Total dos Outros Familiares: %d\n", clienteEncontrado->rendatotaloutrosfamiliares);
        printf("Tem Gastos Médicos: %c\n", clienteEncontrado->temgastosmedicos);
        if (clienteEncontrado->temgastosmedicos == 's') {
            printf("Valor dos Gastos Médicos: %d\n", clienteEncontrado->valorgastosmedicos);
        }
        printf("Possui Investimento: %c\n", clienteEncontrado->possui_investimento);
        if (clienteEncontrado->possui_investimento == 's') {
            printf("Valor Investido: %d\n", clienteEncontrado->valorinvestido);
        }
        printf("Possui Casa Própria: %c\n", clienteEncontrado->possui_casa_propria);
        if (clienteEncontrado->possui_casa_propria == 's') {
            printf("Valor da Casa: %d\n", clienteEncontrado->valorcasa);
        }
        printf("Possui Apartamento: %c\n", clienteEncontrado->possui_apto);
        if (clienteEncontrado->possui_apto == 's') {
            printf("Valor do Apartamento: %d\n", clienteEncontrado->valorapto);
        }
        printf("Possui Terreno: %c\n", clienteEncontrado->possui_terreno);
        if (clienteEncontrado->possui_terreno == 's') {
            printf("Valor do Terreno: %d\n", clienteEncontrado->valorterreno);
        }
        printf("Possui Imóvel Comercial: %c\n", clienteEncontrado->possui_imovel_comercial);
        if (clienteEncontrado->possui_imovel_comercial == 's') {
            printf("Valor do Imóvel Comercial: %d\n", clienteEncontrado->valorimovelcomercial);
        }
        printf("Possui Automóvel: %c\n", clienteEncontrado->possui_automovel);
        if (clienteEncontrado->possui_automovel == 's') {
            printf("Valor do Automóvel: %d\n", clienteEncontrado->valorautomovel);
        }
        printf("Violência Doméstica: %c\n", clienteEncontrado->violencia_domestica);
        printf("Resumo do Caso: %s\n", clienteEncontrado->resumocaso);
        printf("Ramo do Direito: %s\n", clienteEncontrado->ramodireito);
        printf("Tem Perfil Assistido: %c\n", clienteEncontrado->temperfilassistido);
        printf("--------------------------\n");
    } else {
        printf("Cliente com CPF %s não encontrado.\n", cpf);
    }

    free(clientesArray);
}

//PARA O PROGRAMADOR ---------------------------------------
/*void limparClientesDat() {
    FILE *file = fopen("CLIENTES.DAT", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo CLIENTES.DAT para limpeza.\n");
        return;
    }
    fclose(file); // Apenas abrir e fechar o arquivo em modo "wb" limpa o conteúdo.
    printf("Arquivo CLIENTES.DAT limpo com sucesso.\n");
} */

 //-------------------------------------------------------------------------------------------------
 
 //----------------------------ESTAGIARIOS-----------------------------------------------------------
// Definição da estrutura para estagiários
typedef struct 
{
    int codestag;
    char nomeestag[40];
    char celularestag[15]; // formato: "xxxxxxxxxxx"
    char emailestag[40];
    char tipo; // tipo de estagiário: 'a' - atendente, 'p' - plantonista, 'v' - vareiro
} estag;

// Função para criar/atualizar ESTAG.DAT
void criaEstagDat(estag *estagiario) {
    FILE *file = fopen("ESTAG.DAT", "ab"); // 'ab' para escrita em binário e adicionar ao final do arquivo
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fwrite(estagiario, sizeof(estag), 1, file); // Gravando a estrutura inteira em binário
    fclose(file);
}

// Função para inserir as informações do estagiário
void inserirNovoEstag() {
    estag estagiario;
    char salvar;
    char repetir;

    printf("Digite o codigo do estagiario: ");
    scanf("%d", &estagiario.codestag);

    printf("Digite o nome do estagiario: ");
    scanf("%s", estagiario.nomeestag);

    printf("Digite o numero do estagiario: ");
    scanf("%s", estagiario.celularestag); // Correção aqui para usar %s

    printf("Digite o email do estagiario: ");
    scanf("%s", estagiario.emailestag);

    printf("Digite o tipo de estagiario (plantonista - p ou atendente - a ou vareiro(a) - v): ");
    scanf(" %c", &estagiario.tipo); // Espaço antes de %c para evitar problemas de leitura

    printf("Confirma gravacao do registro? (s - sim): ");
    scanf(" %c", &salvar);

    if (salvar == 's') {
        criaEstagDat(&estagiario);
        printf("Registro gravado com sucesso!\n\n");

        printf("Cadastrar outro? ['s'=sim]: ");
        scanf(" %c", &repetir);

        if (repetir == 's') inserirNovoEstag();

    } else {
        printf("Registro nao foi salvo.\n");
    }
}

// Função para ler os estagiários do arquivo
estag* lerEstagiarios(int *n) {
    FILE *arquivo = fopen("ESTAG.DAT", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    if (tamanhoArquivo % sizeof(estag) != 0) {
        printf("Arquivo corrompido.\n");
        fclose(arquivo);
        return NULL;
    }

    *n = tamanhoArquivo / sizeof(estag);
    estag *estagiarios = malloc(tamanhoArquivo);
    if (estagiarios == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return NULL;
    }

    fread(estagiarios, sizeof(estag), *n, arquivo);
    fclose(arquivo);
    return estagiarios;
}

// Função para trocar dois estagiários
void trocar(estag *a, estag *b) {
    estag temp = *a;
    *a = *b;
    *b = temp;
}

// Função para particionar o array
int particionar(estag arr[], int baixo, int alto) {
    int pivo = arr[alto].codestag;
    int i = baixo - 1;
    int j;

    for (j = baixo; j < alto; j++) {
        if (arr[j].codestag < pivo) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[alto]);
    return (i + 1);
}

// Função para ordenar o array com QuickSort
void quickSort(estag arr[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(arr, baixo, alto);
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

// Função para buscar estagiário por código usando busca binária
int buscaBinaria(estag arr[], int tamanho, int codestag) {
    int esquerda = 0;
    int direita = tamanho - 1;
    int meio;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;
        if (arr[meio].codestag == codestag) {
            return meio;
        }
        if (arr[meio].codestag < codestag) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1;
}

// Função para buscar estagiário por código
void buscarEstagiarioPorCodigo() {
    int n;
    estag *estagiarios = lerEstagiarios(&n);
    if (estagiarios == NULL) {
        return;
    }

    quickSort(estagiarios, 0, n - 1);

    int codestag;
    printf("Digite o codigo do estagiario a ser consultado: ");
    scanf("%d", &codestag);

    int indice = buscaBinaria(estagiarios, n, codestag);
    if (indice != -1) {
        printf("\n--- Estagiario Encontrado ---\n");
        printf("Codigo: %d\n", estagiarios[indice].codestag);
        printf("Nome: %s\n", estagiarios[indice].nomeestag);
        printf("Celular: %s\n", estagiarios[indice].celularestag);
        printf("Email: %s\n", estagiarios[indice].emailestag);
        printf("Tipo: %c\n", estagiarios[indice].tipo);
        printf("-----------------------------\n");
    } else {
        printf("Estagiario com codigo %d nao foi encontrado.\n", codestag);
    }

    free(estagiarios);
}

// Função para verificar se o estagiário existe
int verificarEstagiario(int codestag) {
    FILE *file = fopen("ESTAG.DAT", "rb"); // 'rb' para leitura em binário
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de estagiários.\n");
        return 0;
    }

    estag estagiarioAtual;
    int encontrado = 0;

    while (fread(&estagiarioAtual, sizeof(estag), 1, file) == 1) {
        if (estagiarioAtual.codestag == codestag) {
            encontrado = 1;
            break;
        }
    }

    fclose(file);
    return encontrado;
}
//--------------------------------------------------------------------------------------------------
 
 
 //--------------------------CASOS ATRIBUIDOS-------------------------------------------------------

// Definição da estrutura para casos atribuídos
typedef struct 
{
    char cpf[12]; // 11 caracteres para o CPF + 1 para o terminador nulo
    int cdatendimento;
    int codestag;
    char dtatribuido[11]; // formato: "dd/mm/yyyy"
    char hratribuido[6]; 
} casosatribuidos;

// Função para criar/atualizar CASOSATRIBUIDOS.DAT 
void criaCasosatribuidosDat(casosatribuidos *caso) {
    FILE *file = fopen("CASOSATRIBUIDOS.DAT", "ab"); // 'ab' para escrita em binário e adicionar ao final do arquivo
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fwrite(caso, sizeof(casosatribuidos), 1, file); // Gravando a estrutura inteira em binário
    fclose(file);
}

// Função para consultar e verificar se o cliente existe
int buscaClientes(const char *cpf, clientes *cliente) {
    FILE *file = fopen("CLIENTES.DAT", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    int encontrado = 0;

    while (fread(cliente, sizeof(clientes), 1, file) == 1) {
        if (strcmp(cliente->cpf, cpf) == 0) {
            encontrado = 1;
            break;
        }
    }

    fclose(file);
    return encontrado;
}

// Função para consultar e verificar se o estagiário existe e se é plantonista
int buscaEstagiariosPlantonista(int codestag, estag *estagiario) {
    FILE *file = fopen("ESTAG.DAT", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    int encontrado = 0;

    while (fread(estagiario, sizeof(estag), 1, file) == 1) {
        if (estagiario->codestag == codestag && estagiario->tipo == 'P') {
            encontrado = 1;
            break;
        }
    }

    fclose(file);
    return encontrado;
}

// Função para obter o cdatendimento do cliente
int buscaCdatendimentoCliente(const char *cpf) {
    FILE *file = fopen("CLIENTES.DAT", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1; // Valor de erro
    }

    clientes cliente;
    while (fread(&cliente, sizeof(clientes), 1, file) == 1) {
        if (strcmp(cliente.cpf, cpf) == 0) {
            fclose(file);
            return cliente.cdatendimento; // Retorna o cdatendimento
        }
    }

    fclose(file);
    return -1; // Não encontrado
}

// Estrutura para atribuir o caso 
void atribuirCaso() {
    casosatribuidos caso;
    clientes cliente;
    estag estagiario;

    // Simula a data e hora atuais
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(caso.dtatribuido, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    sprintf(caso.hratribuido, "%02d:%02d", tm.tm_hour, tm.tm_min);

    // Solicita CPF do cliente para atribuição
    printf("Digite o CPF do cliente: ");
    scanf("%11s", caso.cpf);

    // Verifica se o cliente existe em CLIENTES.DAT e obtém o cdatendimento
    caso.cdatendimento = buscaCdatendimentoCliente(caso.cpf);
    if (caso.cdatendimento == -1) {
        printf("Cliente com CPF %s nao encontrado.\n", caso.cpf);
        return;
    }

    // Solicita o código do estagiário
    printf("Digite o codigo do estagiario: ");
    scanf("%d", &caso.codestag);

    // Verifica se o estagiário existe e é plantonista
    if (!buscaEstagiariosPlantonista(caso.codestag, &estagiario)) {
        printf("Estagiario com codigo %d não encontrado ou nao eh plantonista.\n", caso.codestag);
        return;
    }

    // Salva o caso atribuído
    criaCasosatribuidosDat(&caso);
    printf("Caso atribuido com sucesso!\n");
}

// Função para visualizar os casos atribuídos
void visualizarCasosAtribuidos() {
    FILE *file = fopen("CASOSATRIBUIDOS.DAT", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    casosatribuidos caso;
    printf("\n--- Casos Atribuidos ---\n");
    while (fread(&caso, sizeof(casosatribuidos), 1, file) == 1) {
        printf("CPF: %s\n", caso.cpf);
        printf("Data de Atendimento: %d\n", caso.cdatendimento);
        printf("Codigo do Estagiario: %d\n", caso.codestag);
        printf("Data Atribuido: %s\n", caso.dtatribuido);
        printf("Hora Atribuido: %s\n", caso.hratribuido);
        printf("-----------------------------\n");
    }

    fclose(file);
}

//PARA O PROGRAMADOR ---------------------------------

// Função para limpar todos os casos atribuídos
/*void limparCasosAtribuidos() {
    FILE *file = fopen("CASOSATRIBUIDOS.DAT", "wb"); // 'wb' para abrir o arquivo em modo de escrita binária e truncar o arquivo
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para limpeza.\n");
        return;
    }

    // Não é necessário escrever nada no arquivo; apenas a abertura no modo 'wb' já limpa o conteúdo.
    fclose(file);
    printf("Todos os casos atribuídos foram limpos.\n");
} */

//---------------------------------------------------------------------------------------


//-------------------------ADVOGADOS---------------------------------------------------------------
// Definição da estrutura para advogados
typedef struct {
    char oab[10]; // 2 caracteres para UF + 6 dígitos + 1 para o terminador nulo
    char nomeadv[40];
    char especialidade[40];
    char cpfadv[12];
    char emailadv[40];
    char celularadv[15];
    char anoingresso[5];
} advog;

// Função para criar/atualizar ADVOG.DAT usando fwrite
void criaAdvogDat(advog *advogado) {
    FILE *file = fopen("ADVOG.DAT", "ab"); // 'ab' para escrita em binário e adicionar ao final do arquivo
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fwrite(advogado, sizeof(advog), 1, file); // Gravando a estrutura inteira em binário
    fclose(file);
}

// Função para inserir as informações do advogado
void inserirNovoAdvog() {
    advog advogado;
    char salvar;
    char repetir;

    printf("Digite o número da OAB do advogado (UF + 6 dígitos): ");
    scanf("%9s", advogado.oab);

    getchar(); // Limpa o buffer do newline deixado pelo scanf

    printf("Digite o nome completo do advogado: ");
    fgets(advogado.nomeadv, sizeof(advogado.nomeadv), stdin);
    // Remove o newline (\n) no final da string, se presente
    advogado.nomeadv[strcspn(advogado.nomeadv, "\n")] = '\0';

    printf("Digite a especialidade do advogado: ");
    scanf("%s", advogado.especialidade);

    printf("Digite o CPF do advogado: ");
    scanf("%s", advogado.cpfadv);

    printf("Digite o email do advogado: ");
    scanf("%s", advogado.emailadv);

    printf("Digite o celular do advogado: ");
    scanf("%s", advogado.celularadv);

    printf("Digite o ano de ingresso do advogado: ");
    scanf("%s", advogado.anoingresso);

    printf("Confirma gravação do registro? (s - sim): ");
    scanf(" %c", &salvar);

    if (salvar == 's') {
        criaAdvogDat(&advogado);
        printf("Registro gravado com sucesso!\n\n");

        printf("Cadastrar outro? ['s'=sim]: ");
        scanf(" %c", &repetir);

        if (repetir == 's') inserirNovoAdvog();

    } else {
        printf("Registro não foi salvo.\n");
    }
}

// Função para ler advogados do arquivo
advog* lerAdvogados(int *n) {
    FILE *arquivo = fopen("ADVOG.DAT", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    *n = tamanhoArquivo / sizeof(advog);
    advog *advogados = malloc(tamanhoArquivo);
    if (advogados == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return NULL;
    }

    fread(advogados, sizeof(advog), *n, arquivo);
    fclose(arquivo);
    return advogados;
}

// Função para trocar elementos
void trocarAdvog(advog *a, advog *b) {
    advog temp = *a;
    *a = *b;
    *b = temp;
}

// Função particionar para QuickSort
int particionarAdvog(advog arr[], int baixo, int alto) {
    char pivo[10];
    strcpy(pivo, arr[alto].oab);
    int i = (baixo - 1);
    int j;

    for (j = baixo; j < alto; j++) {
        if (strcmp(arr[j].oab, pivo) < 0) {
            i++;
            trocarAdvog(&arr[i], &arr[j]);
        }
    }
    trocarAdvog(&arr[i + 1], &arr[alto]);
    return (i + 1);
}

// Função QuickSort para advogados
void quickSortAdvog(advog arr[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionarAdvog(arr, baixo, alto);
        quickSortAdvog(arr, baixo, pi - 1);
        quickSortAdvog(arr, pi + 1, alto);
    }
}

// Função de busca binária para advogados
int buscaBinariaAdvog(advog arr[], int tamanho, const char *oab) {
    int esquerda = 0;
    int direita = tamanho - 1;
    int meio;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;
        if (strcmp(arr[meio].oab, oab) == 0) {
            return meio;
        }
        if (strcmp(arr[meio].oab, oab) < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1;
}

// Função para buscar advogado por OAB
void buscarAdvogadoPorOAB() {
    int n;
    advog *advogados = lerAdvogados(&n);
    if (advogados == NULL) {
        return;
    }

    quickSortAdvog(advogados, 0, n - 1);

    char oabBuscada[10];
    printf("Digite a OAB do advogado a ser consultado (UF seguido de 6 dígitos): ");
    scanf("%9s", oabBuscada);

    int indice = buscaBinariaAdvog(advogados, n, oabBuscada);
    if (indice != -1) {
        printf("\n--- Advogado Encontrado ---\n");
        printf("OAB: %s\n", advogados[indice].oab);
        printf("Nome: %s\n", advogados[indice].nomeadv);
        printf("Especialidade: %s\n", advogados[indice].especialidade);
        printf("CPF: %s\n", advogados[indice].cpfadv);
        printf("Email: %s\n", advogados[indice].emailadv);
        printf("Celular: %s\n", advogados[indice].celularadv);
        printf("Ano de Ingresso: %s\n", advogados[indice].anoingresso);
        printf("-----------------------------\n");
    } else {
        printf("Advogado com OAB %s não encontrado.\n", oabBuscada);
    }

    free(advogados);
}

//---------------------------------------------------------------------------------------------------------------

//------------PLANTÃO DE ADVOGADOS------------------------------------

//---------------------DISPONIBILIDADE DOS ADVOGADOS--------------------------------------------------------------
// Definição da estrutura para disponibilidade de advogados
typedef struct 
{
    char oab[10];      // Alterado para string para acomodar UF e número
    int diasemana;
    char horaini[6];
    char horafim[6];    // formato (hh:mm)
    char formato;       // escolher entre 'P' ou 'R' = 'P' - presencial e 'R' - remoto 
} dispoadv;

// Função para criar/atualizar DISPOADV.DAT usando fwrite
void criaDispoadvDat(dispoadv *agendaadv) {
    FILE *file = fopen("DISPOADV.DAT", "ab"); // 'ab' para escrita em binário e adicionar ao final do arquivo
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fwrite(agendaadv, sizeof(dispoadv), 1, file); // Gravando a estrutura inteira em binário
    fclose(file);
}

// Para inserir as informações na agenda do advogado 
void inserirNovaAgendaAdv() {
    dispoadv agendaadv;
    char salvar;
    char repetir;

    printf("Digite o número da OAB do advogado (UFNNNNNN): ");
    scanf("%9s", agendaadv.oab);

    printf("Digite o dia da semana (0 = Domingo, 1 = Segunda, ..., 6 = Sábado): ");
    scanf("%d", &agendaadv.diasemana);

    printf("Digite o horário de início (HH:MM): ");
    scanf("%5s", agendaadv.horaini);

    printf("Digite o horário de fim (HH:MM): ");
    scanf("%5s", agendaadv.horafim);

    printf("Digite o formato do atendimento ('P' para presencial, 'R' para remoto): ");
    scanf(" %c", &agendaadv.formato);

    printf("Confirma gravação do registro? (s - sim): ");
    scanf(" %c", &salvar);

    if (salvar == 's') {
        criaDispoadvDat(&agendaadv);
        printf("Registro gravado com sucesso!\n\n");

        printf("Cadastrar outro? ['s'=sim]: ");
        scanf(" %c", &repetir);

        if (repetir == 's') inserirNovaAgendaAdv();

    } else {
        printf("Registro não foi salvo.\n");
    }
}

// Função para exibir a disponibilidade dos advogados
void visualizarDispoAdvs() {
    FILE *fileDispo = fopen("DISPOADV.DAT", "rb");
    FILE *fileAdvog = fopen("ADVOG.DAT", "rb");
    if (fileDispo == NULL || fileAdvog == NULL) {
        printf("Erro ao abrir o(s) arquivo(s).\n");
        if (fileDispo != NULL) fclose(fileDispo);
        if (fileAdvog != NULL) fclose(fileAdvog);
        return;
    }

    dispoadv agendaadv;
    advog advogado;
    const char *diasDaSemana[] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};

    printf("---- Disponibilidade dos Advogados ----\n");

    while (fread(&agendaadv, sizeof(dispoadv), 1, fileDispo) == 1) {
        // Resetamos o ponteiro do arquivo de advogados para o início
        fseek(fileAdvog, 0, SEEK_SET);
        int encontrou = 0;

        while (fread(&advogado, sizeof(advog), 1, fileAdvog) == 1) {
            if (strcmp(advogado.oab, agendaadv.oab) == 0) {
                encontrou = 1;
                break;
            }
        }

        if (encontrou) {
            printf("OAB: %s\n", agendaadv.oab);
            printf("Nome: %s\n", advogado.nomeadv);
            printf("Email: %s\n", advogado.emailadv);
            printf("Dia da Semana: %s\n", diasDaSemana[agendaadv.diasemana]);
            printf("Horario: %s - %s\n", agendaadv.horaini, agendaadv.horafim);
            printf("Formato: %s\n", (agendaadv.formato == 'P') ? "Presencial" : "Remoto");
            printf("---------------------------------------\n");
        } else {
            printf("Advogado com OAB %s não encontrado.\n", agendaadv.oab);
        }
    }

    fclose(fileDispo);
    fclose(fileAdvog);
}
//-------------------------------------------------------------------------------------------------------

//----------------------------AGENDA--------------------------------------------------------------------
// Definição da estrutura para agenda
typedef struct
{
    int codestag;
    char oab[10];          // Alterado para string para acomodar UF e número
    char dtagendada[11];   // formato: "dd/mm/yyyy"
    char hragendado[6];    // formato: hh:mm
    char dtinscrito[11];   // formato: "dd/mm/aaaa"
    char hrinscrito[6];    // formato: hh:mm
    char areadireito[40]; 
    char tipodeorientacao[40]; 
    char prazofatal;       // 's' para sim, 'n' para não
    char dtprazofatal[11]; // formato: "dd/mm/yyyy"
    char observacoes[255];
    char numprocesso[21]; // o numero do processo possui 20 numeros 
    char foiatend;      // s/n
} agenda;

// Definição da estrutura de nó para a lista encadeada
typedef struct No {
    agenda dados;
    struct No *proximo;
} No;

// Definição da estrutura de fila
typedef struct {
    No *frente;
    No *tras;
} Fila;

// Função para inicializar a fila
void inicializarFila(Fila *f) {
    f->frente = NULL;
    f->tras = NULL;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila *f) {
    return f->frente == NULL;
}

// Função para enfileirar um elemento na fila
void enfileirar(Fila *f, agenda ag) {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->dados = ag;
    novoNo->proximo = NULL;
    if (filaVazia(f)) {
        f->frente = novoNo;
    } else {
        f->tras->proximo = novoNo;
    }
    f->tras = novoNo;
}

// Função para desenfileirar um elemento da fila
agenda desenfileirar(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        exit(1);
    }
    No *temp = f->frente;
    agenda ag = temp->dados;
    f->frente = f->frente->proximo;
    if (f->frente == NULL) {
        f->tras = NULL;
    }
    free(temp);
    return ag;
}


// Função para criar/atualizar AGENDA.DAT usando fwrite
void criarAgendaDat(Fila *f) {
    FILE *arquivo = fopen("AGENDA.DAT", "wb"); // 'wb' para escrita em binário
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    
    No *atual = f->frente;
    while (atual != NULL) {
        fwrite(&(atual->dados), sizeof(agenda), 1, arquivo); // Gravando a estrutura inteira em binário
        atual = atual->proximo;
    }

    fclose(arquivo);
}

// Função para carregar a agenda do arquivo para a fila
void carregarAgenda(Fila *f) {
    FILE *arquivo = fopen("AGENDA.DAT", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    agenda agendageral;
    while (fread(&agendageral, sizeof(agenda), 1, arquivo) == 1) {
        enfileirar(f, agendageral);
    }

    fclose(arquivo);
}

// Para inserir as informações na agenda
void inserirNovaAgenda(Fila *f) {
    agenda agendageral;
    char salvar;
    char repetir;

    printf("Digite o código do estagiário: ");
    scanf("%d", &agendageral.codestag);
    getchar();  // Limpar o buffer do teclado

    printf("Digite o número da OAB do advogado (UFNNNNNN): ");
    scanf("%9s", agendageral.oab);
    getchar();  // Limpar o buffer do teclado

    printf("Digite a data agendada (dd/mm/aaaa): ");
    scanf("%10s", agendageral.dtagendada);
    getchar();  // Limpar o buffer do teclado

    printf("Digite o horário agendado (HH:MM): ");
    scanf("%5s", agendageral.hragendado);
    getchar();  // Limpar o buffer do teclado

    printf("Digite a data de inscrição (dd/mm/aaaa): ");
    scanf("%10s", agendageral.dtinscrito);
    getchar();  // Limpar o buffer do teclado

    printf("Digite o horário de inscrição (HH:MM): ");
    scanf("%5s", agendageral.hrinscrito);
    getchar();  // Limpar o buffer do teclado

    printf("Digite a área do direito: ");
    fgets(agendageral.areadireito, sizeof(agendageral.areadireito), stdin);
    agendageral.areadireito[strcspn(agendageral.areadireito, "\n")] = '\0';  // Remover o '\n' da string

    printf("Digite o tipo de orientação: ");
    fgets(agendageral.tipodeorientacao, sizeof(agendageral.tipodeorientacao), stdin);
    agendageral.tipodeorientacao[strcspn(agendageral.tipodeorientacao, "\n")] = '\0';  // Remover o '\n' da string

    printf("Prazo fatal (s/n): ");
    scanf(" %c", &agendageral.prazofatal);
    getchar();  // Limpar o buffer do teclado

    if (agendageral.prazofatal == 's') {
        printf("Digite a data do prazo fatal (dd/mm/aaaa): ");
        scanf("%10s", agendageral.dtprazofatal);
        getchar();  // Limpar o buffer do teclado
    } else {
        strcpy(agendageral.dtprazofatal, ""); // Se não houver prazo fatal
    }

    printf("Digite as observações: ");
    fgets(agendageral.observacoes, sizeof(agendageral.observacoes), stdin);
    agendageral.observacoes[strcspn(agendageral.observacoes, "\n")] = '\0';  // Remover o '\n' da string

    printf("Digite o número do processo: ");
    scanf("%20s", agendageral.numprocesso);
    getchar();  // Limpar o buffer do teclado

    printf("Foi atendido (s/n): ");
    scanf(" %c", &agendageral.foiatend);
    getchar();  // Limpar o buffer do teclado

    printf("Confirma gravação do registro? (s - sim): ");
    scanf(" %c", &salvar);
    getchar();  // Limpar o buffer do teclado

    if (salvar == 's') {
        enfileirar(f, agendageral);
        criarAgendaDat(f);  // Atualizar o arquivo
        printf("Registro gravado com sucesso!\n\n");

        printf("Cadastrar outro? ['s'=sim]: ");
        scanf(" %c", &repetir);
        getchar();  // Limpar o buffer do teclado

        if (repetir == 's') inserirNovaAgenda(f);

    } else {
        printf("Registro não foi salvo.\n");
    }
}

// Função para exibir a agenda dos estagiários
void visualizarAgenda(Fila *f) {
    No *atual = f->frente;
    printf("---- Agenda dos Estagiários ----\n");

    while (atual != NULL) {
        agenda agendageral = atual->dados;
        printf("Código do Estagiário: %d\n", agendageral.codestag);
        printf("OAB: %s\n", agendageral.oab);
        printf("Data Agendada: %s\n", agendageral.dtagendada);
        printf("Horário Agendado: %s\n", agendageral.hragendado);
        printf("Data de Inscrição: %s\n", agendageral.dtinscrito);
        printf("Horário de Inscrição: %s\n", agendageral.hrinscrito);
        printf("Área do Direito: %s\n", agendageral.areadireito);
        printf("Tipo de Orientação: %s\n", agendageral.tipodeorientacao);
        printf("Prazo Fatal: %c\n", agendageral.prazofatal);
        if (agendageral.prazofatal == 's') {
            printf("Data do Prazo Fatal: %s\n", agendageral.dtprazofatal);
        }
        printf("Observações: %s\n", agendageral.observacoes);
        printf("Número do Processo: %s\n", agendageral.numprocesso);
        printf("Foi Atendido: %c\n", agendageral.foiatend);
        printf("--------------------------------\n");
        atual = atual->proximo;
    }
}

// Função para verificar se existe um processo na AGENDA.DAT
int verificarAgenda(Fila *f, char *numprocesso, int *codestag) {
    No *atual = f->frente;
    int encontrado = 0;

    while (atual != NULL) {
        // Usar strcmp para comparar strings
        if (strcmp(atual->dados.numprocesso, numprocesso) == 0) {
            *codestag = atual->dados.codestag;
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    return encontrado;
}

// PARA O PROGRAMADOR TESTAR ------------------------------------------------

// Função para limpar o arquivo AGENDA.DAT
/*void limparAgenda() {
    FILE *file = fopen("AGENDA.DAT", "wb"); // 'wb' para limpar o arquivo
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    fclose(file);
    printf("Arquivo AGENDA.DAT limpo com sucesso.\n");
} */
//-----------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------


//----------------PUBLIS-----------------------------------------------------------------------------------

typedef struct {
    int codestag;
    char dtcircula[11];
    char hrcircula[6];
    char numcnj[21];
    char tipoacao[40];
    char varajuizo[40];
    char foro[40];
    char cpf[12];
    char reclamado[40];
    char advreclamante[40];
    char advreclamado[40];
    char movimentacao[255]; // Ajustado para suportar strings longas
} publis;

void criaPublisDat(publis *publicacoes) {
    FILE *file = fopen("PUBLIS.DAT", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    fwrite(publicacoes, sizeof(publis), 1, file);
    fclose(file);
}


void inserirNovaPublicacao() {
    publis publicacoes;
    char salvar;
    char repetir;

    printf("Digite o código do estagiário: ");
    scanf("%d", &publicacoes.codestag);
    getchar(); 

    printf("Digite a data de circulação (dd/mm/aaaa): ");
    scanf("%s", publicacoes.dtcircula);
    getchar(); 

    printf("Digite a hora de circulação (HH:MM): ");
    scanf("%s", publicacoes.hrcircula);
    getchar(); 

    printf("Digite o número do CNJ: ");
    scanf("%s", publicacoes.numcnj);
    getchar(); 

    printf("Digite o tipo da ação: ");
    fgets(publicacoes.tipoacao, sizeof(publicacoes.tipoacao), stdin);
    publicacoes.tipoacao[strcspn(publicacoes.tipoacao, "\n")] = '\0'; // Remover o '\n' deixado pelo fgets

    printf("Digite a vara do juízo: ");
    fgets(publicacoes.varajuizo, sizeof(publicacoes.varajuizo), stdin);
    publicacoes.varajuizo[strcspn(publicacoes.varajuizo, "\n")] = '\0';

    printf("Digite o foro: ");
    fgets(publicacoes.foro, sizeof(publicacoes.foro), stdin);
    publicacoes.foro[strcspn(publicacoes.foro, "\n")] = '\0';

    printf("Digite o CPF: ");
    scanf("%s", publicacoes.cpf);
    getchar(); 

    printf("Digite o reclamado: ");
    fgets(publicacoes.reclamado, sizeof(publicacoes.reclamado), stdin);
    publicacoes.reclamado[strcspn(publicacoes.reclamado, "\n")] = '\0';

    printf("Digite o advogado reclamante: ");
    fgets(publicacoes.advreclamante, sizeof(publicacoes.advreclamante), stdin);
    publicacoes.advreclamante[strcspn(publicacoes.advreclamante, "\n")] = '\0';

    printf("Digite o advogado reclamado: ");
    fgets(publicacoes.advreclamado, sizeof(publicacoes.advreclamado), stdin);
    publicacoes.advreclamado[strcspn(publicacoes.advreclamado, "\n")] = '\0';

    printf("Digite a movimentação: ");
    fgets(publicacoes.movimentacao, sizeof(publicacoes.movimentacao), stdin);
    publicacoes.movimentacao[strcspn(publicacoes.movimentacao, "\n")] = '\0';

    printf("Confirma gravação do registro? (s - sim): ");
    scanf(" %c", &salvar);
    getchar(); 

    if (salvar == 's') {
        criaPublisDat(&publicacoes);
        printf("Registro gravado com sucesso!\n\n");

        printf("Cadastrar outra publicação? ['s'=sim]: ");
        scanf(" %c", &repetir);
        getchar(); 

        if (repetir == 's') inserirNovaPublicacao();

    } else {
        printf("Registro não foi salvo.\n");
    }
}

// Visualizar as publis 
void visualizarPublicacoes() {
    FILE *file = fopen("PUBLIS.DAT", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo PUBLIS.DAT.\n");
        return;
    }

    publis publicacao;
    int registroEncontrado = 0;

    printf("----- Publicações Registradas -----\n\n");

    while (fread(&publicacao, sizeof(publis), 1, file) == 1) {
        registroEncontrado = 1;
        printf("----------------------------------\n\n");
        printf("Código do Estagiário: %d\n", publicacao.codestag);
        printf("Data de Circulação: %s\n", publicacao.dtcircula);
        printf("Hora de Circulação: %s\n", publicacao.hrcircula);
        printf("Número do CNJ: %s\n", publicacao.numcnj);
        printf("Tipo da Ação: %s\n", publicacao.tipoacao);
        printf("Vara do Juízo: %s\n", publicacao.varajuizo);
        printf("Foro: %s\n", publicacao.foro);
        printf("CPF: %s\n", publicacao.cpf);
        printf("Reclamado: %s\n", publicacao.reclamado);
        printf("Advogado Reclamante: %s\n", publicacao.advreclamante);
        printf("Advogado Reclamado: %s\n", publicacao.advreclamado);
        printf("Movimentação: %s\n", publicacao.movimentacao);
        printf("----------------------------------\n\n");
    }

    if (!registroEncontrado) {
        printf("Nenhuma publicação encontrada.\n");
    }

    fclose(file);
}



//------------------CONTROLE DE PROCESSOS----------------------------------------------------------------

typedef struct {
    char numprocesso[21];
    char tema[40];
    char cpf[12]; // 11 caracteres para o CPF + 1 para o terminador nulo
    char polo[20]; // se é reclamante/reclamado; exequente/executado
    int codeestag;
    char dtcontrole[11]; // formato: "dd/mm/yyyy"
    char proxtarefa[255];
    char temprazodobro; // 's' para sim ou 'n' para não
    char obsprazo[255];
    char audiencia[255];
    char prazosimples[11]; // formato: "dd/mm/yyyy"
    char prazodobrado[11]; // formato: "dd/mm/yyyy"
    char movimentacao[255];
    int diasproxcontrole;
    char dtproposicao[11]; // formato: "dd/mm/yyyy"
    char numcnj[21];
} controle;

//para verificar se existe o processo na PUBLI 
void criaControleDat(controle *controleprocesso) {
    FILE *file = fopen("CONTROLE.DAT", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    fwrite(controleprocesso, sizeof(controle), 1, file);
    fclose(file);
}

int verificarProcessoEmPublis(const char *numprocesso, publis *publicacao) {
    FILE *file = fopen("PUBLIS.DAT", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo PUBLIS.DAT.\n");
        return 0;
    }

    int encontrado = 0;
    while (fread(publicacao, sizeof(publis), 1, file) == 1) {
        if (strcmp(publicacao->numcnj, numprocesso) == 0) {
            encontrado = 1;
            break;
        }
    }

    fclose(file);
    return encontrado;
}


void inserirNovoControle() {
    controle controleprocesso;
    publis publicacao;
    char salvar;
    char repetir;
    int codestag;

    printf("Digite o número do processo: ");
    scanf("%20s", controleprocesso.numprocesso);

    // Verifica se o processo existe em PUBLI.DAT
    if (!verificarProcessoEmPublis(controleprocesso.numprocesso, &publicacao)) {
        printf("Número do processo não encontrado em PUBLI.DAT.\n");
        return;
    }

    controleprocesso.codeestag = publicacao.codestag;
    strcpy(controleprocesso.movimentacao, publicacao.movimentacao);

    printf("Digite o tema do processo: ");
    scanf(" %[^\n]s", controleprocesso.tema);

    printf("Digite o CPF: ");
    scanf("%11s", controleprocesso.cpf);

    if (!verificarCliente(controleprocesso.cpf)) {
        printf("CPF não encontrado no sistema.\n");
        return;
    }

    printf("Digite o polo (reclamante/reclamado ou exequente/executado): ");
    scanf(" %[^\n]s", controleprocesso.polo);

    printf("Digite a data de controle (dd/mm/aaaa): ");
    scanf("%10s", controleprocesso.dtcontrole);

    printf("Digite a próxima tarefa: ");
    scanf(" %[^\n]s", controleprocesso.proxtarefa);

    printf("Prazo do dobro (s = Sim, n = Não): ");
    scanf(" %c", &controleprocesso.temprazodobro);

    printf("Digite observações sobre o prazo: ");
    scanf(" %[^\n]s", controleprocesso.obsprazo);

    printf("Digite a audiência: ");
    scanf(" %[^\n]s", controleprocesso.audiencia);

    printf("Digite o prazo simples (dd/mm/aaaa): ");
    scanf("%10s", controleprocesso.prazosimples);

    printf("Digite o prazo dobrado (dd/mm/aaaa): ");
    scanf("%10s", controleprocesso.prazodobrado);

    printf("Digite os dias para o próximo controle: ");
    scanf("%d", &controleprocesso.diasproxcontrole);

    printf("Digite a data de proposição (dd/mm/aaaa): ");
    scanf("%10s", controleprocesso.dtproposicao);

    printf("Confirma gravação do registro? (s - sim): ");
    scanf(" %c", &salvar);

    if (salvar == 's') {
        criaControleDat(&controleprocesso);
        printf("Registro gravado com sucesso!\n\n");

        printf("Cadastrar outro? ['s'=sim]: ");
        scanf(" %c", &repetir);

        if (repetir == 's') inserirNovoControle();

    } else {
        printf("Registro não foi salvo.\n");
    }
}

void consultarControlePorNumero(char *numprocesso) {
    FILE *file = fopen("CONTROLE.DAT", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    controle controleprocesso;
    int encontrado = 0;

    while (fread(&controleprocesso, sizeof(controle), 1, file) == 1) {
        if (strcmp(controleprocesso.numprocesso, numprocesso) == 0) {
            printf("\n--- Controle Encontrado ---\n");
            printf("Número do Processo: %s\n", controleprocesso.numprocesso);
            printf("Tema: %s\n", controleprocesso.tema);
            printf("CPF: %s\n", controleprocesso.cpf);
            printf("Polo: %s\n", controleprocesso.polo);
            printf("Código do Estagiário: %d\n", controleprocesso.codeestag);
            printf("Data de Controle: %s\n", controleprocesso.dtcontrole);
            printf("Próxima Tarefa: %s\n", controleprocesso.proxtarefa);
            printf("Prazo do Dobro: %c\n", controleprocesso.temprazodobro);
            printf("Observações sobre o Prazo: %s\n", controleprocesso.obsprazo);
            printf("Audiência: %s\n", controleprocesso.audiencia);
            printf("Prazo Simples: %s\n", controleprocesso.prazosimples);
            printf("Prazo Dobrado: %s\n", controleprocesso.prazodobrado);
            printf("Movimentação: %s\n", controleprocesso.movimentacao);
            printf("Dias para o Próximo Controle: %d\n", controleprocesso.diasproxcontrole);
            printf("Data de Proposição: %s\n", controleprocesso.dtproposicao);
            printf("-----------------------------\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Controle não encontrado para o número do processo fornecido.\n");
    }

    fclose(file);
}

void visualizarControles() {
    int opcao;

    printf("Escolha a visualização:\n");
    printf("1. Visualizar todos os controles\n");
    printf("2. Buscar controle por número do processo\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        FILE *file = fopen("CONTROLE.DAT", "rb");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        controle controleprocesso;

        printf("---- Todos os Controles ----\n");

        while (fread(&controleprocesso, sizeof(controle), 1, file) == 1) {
            printf("\nNúmero do Processo: %s\n", controleprocesso.numprocesso);
            printf("Tema: %s\n", controleprocesso.tema);
            printf("CPF: %s\n", controleprocesso.cpf);
            printf("Polo: %s\n", controleprocesso.polo);
            printf("Código do Estagiário: %d\n", controleprocesso.codeestag);
            printf("Data de Controle: %s\n", controleprocesso.dtcontrole);
            printf("Próxima Tarefa: %s\n", controleprocesso.proxtarefa);
            printf("Prazo do Dobro: %c\n", controleprocesso.temprazodobro);
            printf("Observações sobre o Prazo: %s\n", controleprocesso.obsprazo);
            printf("Audiência: %s\n", controleprocesso.audiencia);
            printf("Prazo Simples: %s\n", controleprocesso.prazosimples);
            printf("Prazo Dobrado: %s\n", controleprocesso.prazodobrado);
            printf("Movimentação: %s\n", controleprocesso.movimentacao);
            printf("Dias para o Próximo Controle: %d\n", controleprocesso.diasproxcontrole);
            printf("Data de Proposição: %s\n", controleprocesso.dtproposicao);
            printf("-----------------------------\n");
        }

        fclose(file);

    } else if (opcao == 2) {
        char numprocesso[21];
        printf("Digite o número do processo que deseja buscar: ");
        scanf("%20s", numprocesso);

        consultarControlePorNumero(numprocesso);

    } else {
        printf("Opção inválida.\n");
    }
}


// PARA O PROGRAMADOR --------------------------------------------------------------------------
/*void limparControles() {
    FILE *file = fopen("CONTROLE.DAT", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para limpeza.\n");
        return;
    }
    fclose(file);
    printf("Todos os controles foram removidos do arquivo.\n");
}*/
//---------------------------------------------------------------------------------------------------------



//Atualiza a movimentação 
void atualizarMovimentacao(const char *numcnj, const char *novaMovimentacao) {
    FILE *file = fopen("PUBLIS.DAT", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo PUBLIS.DAT.\n");
        return;
    }

    publis publicacoes;
    int encontrado = 0;

    while (fread(&publicacoes, sizeof(publis), 1, file) == 1) {
        if (strcmp(publicacoes.numcnj, numcnj) == 0) {
            encontrado = 1;
            break;
        }
    }

    fclose(file);

    if (!encontrado) {
        printf("Número CNJ não encontrado em PUBLIS.DAT.\n");
        return;
    }

    FILE *fileCtrl = fopen("CONTROLE.DAT", "r+b");
    if (fileCtrl == NULL) {
        printf("Erro ao abrir o arquivo CONTROLE.DAT.\n");
        return;
    }

    controle controleprocesso;
    int atualizado = 0;

    while (fread(&controleprocesso, sizeof(controle), 1, fileCtrl) == 1) {
        if (strcmp(controleprocesso.numcnj, numcnj) == 0) {
            fseek(fileCtrl, -(long)sizeof(controle), SEEK_CUR); // Corrigido aqui
            if (strlen(controleprocesso.movimentacao) + strlen(novaMovimentacao) + 1 < sizeof(controleprocesso.movimentacao)) {
                strcat(controleprocesso.movimentacao, " ");
                strcat(controleprocesso.movimentacao, novaMovimentacao);
                fwrite(&controleprocesso, sizeof(controle), 1, fileCtrl);
                atualizado = 1;
            } else {
                printf("Erro: Movimentação excede o tamanho máximo permitido.\n");
                fclose(fileCtrl);
                return;
            }
            break;
        }
    }

    fclose(fileCtrl);

    if (atualizado) {
        printf("Movimentação atualizada com sucesso!\n");
    } else {
        printf("Número do processo não encontrado em CONTROLE.DAT.\n");
    }
}

//----------------------------------------------------------------------------------------------------------



//--------------------------MENU PRINCIPAL----------------------------------------------------------
//menu principal
void menu() {
    int opcao;
	clientes cliente;
	Fila filaAgenda;
    inicializarFila(&filaAgenda);
    carregarAgenda(&filaAgenda);
	
    
    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Inserir novo cliente\n");
        printf("2. Consultar clientes\n");
        printf("3. Inserir novo advogado\n");
        printf("4. Consultar advogado\n");
        printf("5. Cadastrar disponibilidade do advogado\n");
        printf("6. Visualizar disponibilidade do advogado\n");
        printf("7. Inserir novo estagiario\n");
        printf("8. Consultar estagiarios\n");
        printf("9. Atribuir caso\n");
        printf("10. Visualizar casos atribuidos\n");
        printf("11. Agendamento com advogado\n");
        printf("12. Visualizar agenda\n");
        printf("13. Inserir novo controle\n");
        printf("14. Visualizar Controles\n");
        printf("15. Inserir nova publicacao\n");
        printf("16. Visualizar as publicacoes\n");
        printf("17. Sair\n");
        //printf("18. Limpar a agenda (AGENDA.DAT)\n");
        //printf("19. Limpar controles (CONTROLE.DAT)\n");
        //printf("20. Limpar casos atribuídos (CASOSATRIBUIDOS.DAT)\n");
        //printf("21. Limpar clientes (CLIENTES.DAT)\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirNovoCliente();
                break;

            case 2:
                consultarClientes();
                break;
            
			case 3:
				inserirNovoAdvog();
				break;
				
			case 4:
				buscarAdvogadoPorOAB();
				break;
			    
            case 5: 
            	inserirNovaAgendaAdv();
				break;
				
			case 6:
				visualizarDispoAdvs();
				break;
				
			case 7:
				inserirNovoEstag();
				break;
				
			case 8:
				buscarEstagiarioPorCodigo();
				break;	
				
            case 9:
            	atribuirCaso();
                break;
                
            case 10:
            	visualizarCasosAtribuidos();
            	break;
                
            case 11: 
				inserirNovaAgenda(&filaAgenda);
				break;
			
			case 12:
				visualizarAgenda(&filaAgenda);
				break;
				
			case 13: 
				inserirNovoControle();
				break;
			
			case 14: 
				visualizarControles();
				break; 
				
			case 15: 
				inserirNovaPublicacao();
				break;
				
			case 16: 
				visualizarPublicacoes();
				break;
				
            case 17:
				printf("Saindo...\n");
				break;  
				
				
		//OPÇÕES PARA LIMPAR OS ARQUIVOS
		/*	case 18:
				limparAgenda();
				break;
			
			case 19:
				limparControles();
				break;
			
			case 20:
				limparCasosAtribuidos();
				break;
				
			case 21:
				limparClientesDat();
				break;
		*/
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 19);
}

//--------------------------FUNÇÃO PRINCIPAL-------------------------------------------
int main() { 
    menu();
    return 0;
}
