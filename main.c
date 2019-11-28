#include <stdio.h>
#include <string.h>

#define MAX_EQUIP 60
#define MAX_AMB 20


float taxa = 0.3;
struct TEquipamentos {
    int id;
    char nome[20];
    float uso, stand; /* Potência em uso e stand-by */
} equipamentos[MAX_EQUIP];

struct TAmbientes {
    int id;
    char nome[20];
    float consumo;
    float uso[MAX_EQUIP], stand[MAX_EQUIP]; /* Horas em uso e horas em stand-by*/
    struct TEquipamentos equipamentosambientes[MAX_EQUIP];

} ambientes[MAX_AMB];

void cal_kwh_ambientes() {
    for (int i = 0; i < MAX_AMB; i++) /* Aqui é feito o cálculo do consumo total diário em Kwh de cada ambiente  */ {
        for (int j = 0; j < MAX_AMB; j++) {
            ambientes[i].consumo = (ambientes[i].equipamentosambientes[j].uso * ambientes[i].uso[j]) +
                                   (ambientes[i].equipamentosambientes[j].stand * ambientes[i].stand[j]);

        }
    }
}

float somaTotalConsumo() {
    float soma = 0;
    for (int i = 0; i < MAX_AMB; i++) {
        soma = soma + ambientes[i].consumo;
    }
    return soma;
}


void consumo() {
    printf("Diário\n");
    printf("KWh: %.3f", somaTotalConsumo());
    printf("  R$: %.2f\n", somaTotalConsumo() * taxa);
    printf("Semanal\n");
    printf("KWh: %.3f", somaTotalConsumo() * 7);
    printf("  R$: %.2f\n", somaTotalConsumo() * taxa * 7);
    printf("Mensal\n");
    printf("KWh: %.3f", somaTotalConsumo() * 30);
    printf("  R$: %.2f\n", somaTotalConsumo() * taxa * 30);
}

void acessaAmbiente(int aux) {
    for (int i = 0; i < MAX_EQUIP; i++) {
        ambientes[aux].equipamentosambientes[i].nome;
    }
}

void adicionarAmbiente() {  //loop infinito
    char nome[20];
    int x;
    for (int i = 0; i < MAX_AMB; i++) {
        if (ambientes[i].id == 0) {
            ambientes[i].id = i + 1;
            printf("Insira o nome do ambiente: ");
            scanf(" %[^\n]s", nome);
            strcpy(ambientes[i].nome, nome);
            printf("Insira quantas horas a sala fica ativa:");
            scanf("%f", &ambientes[i].uso);
            printf("Insira quantas horas a sala fica inativa:");
            scanf("%f", &ambientes[i].stand);
            printf("Deseja adicionar mais ambientes?\n");
            printf("1 - Sim\n");
            printf("2 - Não\n");
            printf("->");
            scanf("%d", &x);
            if (x == 2)
                i = MAX_AMB;
        }
    }
}

void adicionarEquipamento(int aux) {
    for (int i = 0; i < MAX_EQUIP; i++) {
        if (ambientes[aux].equipamentosambientes[i].id == 0)
            continue;
        printf("%d - %s  horas consumo: %f, stand-by: %f \n", ambientes[aux].equipamentosambientes[i].id,
               ambientes[aux].equipamentosambientes[i].uso, ambientes[aux].equipamentosambientes[i].stand);
    }
}

void printaAmbiente(int aux) {
    int escolha;
    char altnome[20];
    printf("Nome: %s\n", ambientes[aux].nome);
    printf("1 - Alterar o nome");
    printf("2 - Adicionar equipamento");
    printf("3 - Excluir equipamento");
    scanf("%d", &escolha);
    switch (escolha) {
        case 1: {


            scanf(" %[^\n]s", altnome);
            strcpy(ambientes[aux].nome), altnome);
            break;
        }
        case 2:
            adicionarEquipamento(aux);
            break;
        case 3:
            excluirEquipamento();
            break;

    }

}

void editarAmbiente() {
    int escolha;
    char nome[20];
    for (int i = 0; ambientes[i].id != 0; i++) {
        printf("%d - %s\n", ambientes[i].id, ambientes[i].nome);
    }
    printf("Selecione o ambiente que deseja editar");
    scanf("%d", &escolha);


}

void menuAmbientes() {
    int x = 1;
    while (x) {
        int escolha;
        printf("1 - Adicionar\n");
        printf("2 - Editar\n");
        printf("3 - Excluir\n");
        printf("4 - Voltar\n");
        printf("Escolha uma das opções acima: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                adicionarAmbiente();
                break;
            case 2:
                editarAmbiente();
                break;
            case 3:
                //1  removerAmbiente();
                break;
            case 4:
                x = 0;
                break;
            default:
                printf("Escolha não existe");
                break;
        }
    }
}


int main() {
    cal_kwh_ambientes();
    int menu, periodo, opc_cons;
    while (taxa == 0) {
        printf("Informe o valor da tarifa do Kwh de sua cidade");
        scanf("%f", &taxa);
    }

    int x = 1;
    while (x) {
        printf("1 - Consumo Total\n");
        printf("2 - Ambientes\n");
        printf("3 - Equipamentos\n");
        printf("4 - Sair");
        printf("\nEscolha a opção desejada\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                consumo();
                break;
            case 2:
                menuAmbientes();
                break;
            case 3:
                printf("Adicionar equipamentos\n");
                break;
            case 4:
                printf("Saindo");
                x = 0;
                break;
            default:
                printf("Opção Inválida\n");
                break;
        }

        //printf("Semanal %.2fR$", (ambientes[0].consumo) * 7);

    }
}