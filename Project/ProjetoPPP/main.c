//
//  main.c
//  PPP_LinkedList
//
//  Created by Amanda Menezes on 4/04/2022.
//
 

#include "structure.h"

/* Functions to manage database */
int writeToFileScreen (student this_student);
int read_from_file(struct Node** head_ref);

/* Driver program to test above functions*/
int main()
{
    //setlocale(LC_ALL, "portuguese-brazilian");
    /* Start with the empty list */
    struct Node* head = NULL;
    student* estudante = malloc(sizeof(student)); // aux struct
    int choice;
    char buffer[MAXCHAR];
    long aux_num_est;// aux_num_est_2;
    char *bufferPtr;
    double valor_carreg, valor_saldo;
    int active = 1;
    
    
    // carregar a lista com base na informação atual da base de dados (BD_Config.txt).
    if(read_from_file(&head) != 0){ // success
        puts("Não foi possível acessar a base de dados\n");
    }
    
    puts("Bem-vindx à Consola de Administração!");
    while(active){
        
        puts("\nMENU\n1- Introduzir dados de um(a) alunx\n2- Eliminar um(a) alunx existente\n3- Listar todxs xs alunxs\n4- Listar xs alunxs com saldo abaixo de um determinado valor\n5- Apresentar toda a informação de um(a) determinadx alunx\n6- Efetuar uma despesa por um(a) determinadx alunx\n7- Carregar a conta de um(a) alunx com um valor\n8- Alteração de turma\n9- Sair\n");
        scanf("%d", &choice);
        // fgetc -> get \n -> getline(&choice)
        switch(choice){
                
            case 1: // OKAY
                fgetc(stdin);
                puts("Nome:");
                // melhora scanf string aqui
                fgets(estudante->nome, MAXCHAR, stdin);
                if (*estudante->nome && estudante->nome[strlen(estudante->nome)-1] == '\n')
                    estudante->nome[strlen(estudante->nome)-1] = '\0';
                puts("Data de nascimento:");
                fgets(estudante->data_nasc, MAXCHAR, stdin);
                if (*estudante->data_nasc && estudante->data_nasc[strlen(estudante->data_nasc)-1] == '\n')
                    estudante->data_nasc[strlen(estudante->data_nasc)-1] = '\0';
                puts("Turma:");
                fgets(estudante->turma, MAXCHAR, stdin);
                if (*estudante->turma && estudante->turma[strlen(estudante->turma)-1] == '\n')
                    estudante->turma[strlen(estudante->turma)-1] = '\0';
                puts("Número de estudante:");
                scanf("%ld",&estudante->num_estudante);
                if(check_num(head, estudante->num_estudante) != -1){
                    break;
                }
                fgetc(stdin);
                // non-string inputs
                puts("Ano:");
                fgets(buffer, MAXCHAR, stdin);
                if (*buffer && buffer[strlen(buffer)-1] == '\n')
                    buffer[strlen(buffer)-1] = '\0';
                estudante->ano = strtol(buffer, &bufferPtr, 10);
                puts("Saldo atual:");
                fgets(buffer, MAXCHAR, stdin);
                if (*buffer && buffer[strlen(buffer)-1] == '\n')
                    buffer[strlen(buffer)-1] = '\0';
                estudante->saldo = strtod(buffer, &bufferPtr);
                push_after(&head, *estudante);
                if(writeToFileScreen(*estudante) != 1){ // success
                    puts("\nSucesso");
                }
                break;
            case 2: // OKAY 
                puts("Por favor insira o número de estudante a ser deletado:\n");
                scanf("%ld", &aux_num_est);
                if(deleteNode(&head, aux_num_est)== 1){
                    refreshBD(head);
                    puts("Sucesso");
                }
                else{
                    puts("Estudante não encontrado");
                }
                break;
            case 3: // OKAY
                // print list in alphabetical order
                bubbleSort(head);
                printList(head);
                break;
            case 4: // OKAY
                puts("Por favor insira o valor de saldo a ser consultado:\n");
                scanf("%lf", &valor_saldo);
                //print list in decres order of value
                printf("\nEstudantes com saldo inferior a %.2f:\n", valor_saldo);
                bubbleSort_saldo(head);
                printList_saldo(head, valor_saldo);
                break;
            case 5: // OKAY
                puts("Por favor insira o número de estudante:");
                scanf("%ld", &aux_num_est);
                if(print_info(head, aux_num_est) == -1){
                    printf("Estudante não encontrado(a)\n");
                };
                break;
            case 6: // OKAY 
                puts("Por favor insira o número de estudante:\n");
                scanf("%ld", &aux_num_est);
                puts("Por favor insira o valor da despesa:\n");
                scanf("%lf", &valor_carreg);
                if(payment(head, aux_num_est, valor_carreg) == -1){
                    printf("Estudante não encontrado(a)\n");
                }
                refreshBD(head);
                break;
            case 7: // OKAY
                puts("Por favor insira o número de estudante:\n");
                scanf("%ld", &aux_num_est);
                puts("Por favor insira o valor a carregar:\n");
                scanf("%lf", &valor_carreg);
                if(recharge(head, aux_num_est, valor_carreg) == -1){
                    printf("Estudante não encontrado(a)\n");
                }
                refreshBD(head);
                break;
            case 8: // OKAY 
                puts("Por favor insira o número de estudante:\n");
                scanf("%ld", &aux_num_est);
                fgetc(stdin);
                puts("Por favor insira a nova turma:\n");
                fgets(buffer, MAXCHAR, stdin);
                if (*buffer && buffer[strlen(buffer)-1] == '\n')
                    buffer[strlen(buffer)-1] = '\0';
                if(change_class(head, aux_num_est, buffer) == -1){
                    printf("Estudante não encontrado(a)\n");
                }
                refreshBD(head);
                break;
            case 9: // OKAY
                active = 0;
                break;
                
        }
        
    }

    return 0;
}


/*
 • Introduzir dados de um novo aluno. X
 • Eliminar um aluno existente. X
 • Listar todos os alunos por ordem alfabética. X
 • Listar os alunos com saldo abaixo de um determinado valor (por ordem decrescente de saldos). X
 • Apresentar toda a informação de um determinado aluno. X
 • Efetuar uma despesa por um determinado aluno. X
 • Carregar a conta de um aluno com um valor. X
 */
