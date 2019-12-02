#include <stdio.h>
#include <string.h>

#define MAX_EQUIP 60
#define MAX_AMB 20


float taxa;
struct TEquipamentos {
    int id;
    char nome[20];
    float uso, stand, tempo; /* Potência em uso e stand-by */
} equipamentos[MAX_EQUIP];

struct TAmbientes {
    int id;
    char nome[20];
    float consumo;
    struct TEquipamentos equipamentosambientes[MAX_EQUIP];

} ambientes[MAX_AMB];

void cal_kwh_ambientes() {
    for (int i = 0; i < MAX_AMB; i++) /* Aqui é feito o cálculo do consumo total diário em Kwh de cada ambiente  */ {
        for (int j = 0; j < MAX_AMB; j++) {
            ambientes[i].consumo =
                    (ambientes[i].equipamentosambientes[j].uso * ambientes[i].equipamentosambientes[j].tempo) +
                    (ambientes[i].equipamentosambientes[j].stand * (24 - ambientes[i].equipamentosambientes[j].tempo));
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
            printf("Deseja adicionar mais ambientes?\n");
            printf("1 - Sim\n");
            printf("2 - Não\n");
            printf("-> ");
            scanf("%d", &x);
            if (x == 2)
                i = MAX_AMB;
        }
    }
}

//void adicionarEquipamento(int aux) { // ATENÇÃO : EM PROCESSO DE EDIÇÃO!!!//
//    for (int i = 0; i < MAX_EQUIP; i++) {
//        if (ambientes[aux].equipamentosambientes[i].id == 0)
//            continue;
//        printf("%d - %s  horas consumo: %f, stand-by: %f \n", ambientes[aux].equipamentosambientes[i].id,
//               ambientes[aux].equipamentosambientes[i].uso, ambientes[aux].equipamentosambientes[i].stand);
//    }
//    int x = 1;
//    while (x) {
//        printf("1-    ");
//        printf("0 - Voltar");
//        scanf( % d, &escolha);
//        switch (escolha) {
//            case 1:
//
//                break;
//
//            case 2:
//                x = 0;
//                break;
//        }
//    }
//}

void printaAmbiente(int aux) {
    int escolha;
    char altnome[20];
    int pos = aux - 1;
    int x = 1;
    while (x) {
        printf("Nome: %s\n", ambientes[pos].nome);
        printf("1 - Alterar o nome\n");
        printf("2 - Adicionar equipamento\n");
        printf("3 - Excluir equipamento\n");
        printf("4 - Voltar\n");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                printf("Insira o novo nome: ");
                scanf(" %[^\n]s", altnome);
                strcpy(ambientes[pos].nome, altnome);
                break;

            case 2:
                //adicionarEquipamento(pos);
                break;
            case 3:
                //excluirEquipamento();
                break;
            case 4:
                x = 0;
                break;
            default:
                printf("Opção Inválida");
                break;

        }

    }
}

void editarAmbiente() {  //editado!!!!!!/
    int escolha;

    while (1) {
        int count = 0;
        for (int i = 0; ambientes[i].id != 0; i++) {
            printf("%d - %s\n", ambientes[i].id, ambientes[i].nome);
            count++;
        }
        printf("0 - Voltar\n");
        printf("Digite o id do ambiente que deseja editar: ");
        scanf("%d", &escolha);

        if (escolha == 0) {
            break;
        } else if (escolha > 0 && escolha <= count) {
            printaAmbiente(escolha);
        } else {
            printf("Opção invalida!");
        }
    }
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

void printaEquip() {
    for (int i = 0; i < MAX_EQUIP; i++) {
        if (equipamentos[i].id == 0)
            continue;
        printf("%d - %s Pot. consumo: %f, Pot. stand-by: %f \n", equipamentos[i].id, equipamentos[i].nome,
               equipamentos[i].uso, equipamentos[i].stand);
    }
}
void printaEquipamentos(int aux) {
    int escolha;
    char altnome[20];
    int pos = aux - 1;
    int x = 1;
    while (x) {
        printf("Nome: %s\n", equipamentos[pos].nome);
        printf("1 - Alterar o nome\n");
        printf("2 - Alterar Potência de Uso\n");
        printf("3 - Alterar Potência de stand-by\n");
        printf("4 - Voltar\n");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                printf("Insira o novo nome: ");
                scanf(" %[^\n]s", altnome);
                strcpy(equipamentos[pos].nome, altnome);
                break;

            case 2:
                printf("Insira a nova potência de uso");
                scanf("%f",equipamentos[pos].uso);
                break;
            case 3:
                printf("Insira a nova potência de stand-by");
                scanf("%f", equipamentos[pos].stand);
                break;
            case 4:
                x = 0;
                break;
            default:
                printf("Opção Inválida");
                break;

        }

    }
}

void criarEquip() {
    char nome[20];
    int x;

    for (int i = 0; i < MAX_EQUIP; i++) {
        if (equipamentos[i].id == 0) {
            equipamentos[i].id = i + 1;
            printf("Insira o nome do equipamento: ");
            scanf(" %[^\n]s", nome);
            strcpy(equipamentos[i].nome, nome);
            printf("Informe a Potência do Aparelho em uso?\n");
            scanf("%f", equipamentos[i].uso);
            printf("Informe a Potência do Aparelho em stand-by\n");
            scanf("%f", equipamentos[i].stand);
            printf("Deseja adicionar mais equipamentos?\n");
            printf("1 - Sim\n");
            printf("2 - Não\n");
            printf("-> ");
            scanf("%d", &x);
            if (x == 2)
                i = MAX_EQUIP;
        }
    }
}

void excluirEquip() {

}

void editarEquip() {
    while (1) {
        int escolha;
        int count = 0;
        for (int i = 0; i < MAX_EQUIP; i++) {
            if (equipamentos[i].id == 0)
                continue;
            printf("%d - %s Pot. consumo: %f, Pot. stand-by: %f \n", equipamentos[i].id, equipamentos[i].nome,
                   equipamentos[i].uso, equipamentos[i].stand);
            count++;
        }

        printf("0 - Voltar\n");
        printf("Digite o id do equipamento que deseja editar: \n");
        scanf("%d", &escolha);

        if (escolha == 0) {
            break;
        } else if (escolha > 0 && escolha <= count) {
            printaEquipamentos(escolha);
        } else {
            printf("Opção invalida!");
        }
    }

}


void menuEquipamentos() { // ATENÇÃO EM PROCESSO DE EDIÇÃO!!!//
    int x = 1;
    while (x) {
        int escolha;
        printaEquip();
        printf("1 - Criar\n");
        printf("2 - Excluir\n");
        printf("3 - Editar\n");
        printf("0 - Voltar\n");
        printf("-> ");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                criarEquip();
                break;
            case 2:
                //excluirEquip();
                break;
            case 3:
                editarEquip();
                break;
            case 0:
                x = 0;
                break;
            default:
                printf("Opção Invalida!");
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
                menuEquipamentos();
                break;
            case 4:
                printf("Saindo");
                x = 0;
                break;
            default:
                printf("Opção Inválida\n");
                break;
        }
    }
}
