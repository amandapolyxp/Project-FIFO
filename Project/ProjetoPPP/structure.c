//
//  structure.c
//  PPP_LinkedList
//
//  Created by Amanda Menezes on 4/04/2022.
//

#include "structure.h"

/* Given a reference (pointer to pointer) to the head
   of a list and an int, push a new node at the end  */
void push_after(struct Node** head_ref, student new_data)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
 
    struct Node *last = *head_ref;  /* used in step 5*/
  
    /* 2. put in the data  */
    new_node->student_node  = new_data;
 
    /* 3. This new node is going to be the last node, so make next
          of it as NULL*/
    new_node->next = NULL;
 
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }
      
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
  
    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}

int recharge(struct Node *head, long student, double val){
    
    struct Node* current = head;
    int index = 0;

    while (current != NULL){
        if(current->student_node.num_estudante == student){
            current->student_node.saldo += val;
            printf("\n----Transaction done----\n");
            printf("Nome: %s\n", current->student_node.nome);
            printf("Número de estudante: %ld\n", current->student_node.num_estudante);
            printf("Saldo: %.2f\n", current->student_node.saldo);
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

int payment(struct Node *head, long student, double val){
    
    struct Node* current = head;
    int index = 0;
    
    while (current != NULL){
        if(current->student_node.num_estudante == student){
            double valor_atual = current->student_node.saldo;
            valor_atual -= val;
            if(valor_atual < 0){
                printf("Não foi possível realizar a transação. Saldo insuficiente.\n");
                return index;
            }
            else{
                current->student_node.saldo = valor_atual;
                printf("\n----Transaction done----\n");
                printf("Nome: %s\n", current->student_node.nome);
                printf("Número de estudante: %ld\n", current->student_node.num_estudante);
                printf("Saldo: %.2f\n", current->student_node.saldo);
                return index;
            }
        }
        current = current->next;
        index++;
    }
    return -1;
    
    
}
int change_class(struct Node *head, long student, char class[MAXCHAR]){

    struct Node* current = head;
    int index = 0;
    char turma_atual[MAXCHAR];
    strcpy(turma_atual,current->student_node.turma);
    
    while (current != NULL){
        if(current->student_node.num_estudante == student){
            strcpy(turma_atual,class);
            strcpy(current->student_node.turma,turma_atual);
            printf("\n----Turma alterada com sucesso----\n");
            printf("Nome: %s\n", current->student_node.nome);
            printf("Número de estudante: %ld\n", current->student_node.num_estudante);
            printf("Turma: %s\n", current->student_node.turma);
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}


int check_num(struct Node *head, long student){

    struct Node* current = head;
    int index = 0;
    
    while (current != NULL){
        if(current->student_node.num_estudante == student){
            printf("\nOperação anulada: Estudante já está registado na base de dados\n");
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}

// estudante que recebe e o que paga
/*void transaction(struct Node *head, long dest, long pag, double valor){
    
    dest += valor;
    pag -= valor;
    
}*/

// MÉTODO ITERATIVO PARA DELETAR NÓS A PARTIR DO NÚMERO DE ESTUDANTE
/* Given a reference (pointer to pointer) to the head of a
   list and a key, deletes the first occurrence of key in
   linked list */
int deleteNode(struct Node** head_ref, long num_estudante)
{
    // Store head node
    struct Node *temp = *head_ref, *prev;
    prev = NULL;
 
    // If head node itself holds the key to be deleted
    if (temp != NULL && (temp->student_node.num_estudante == num_estudante)) {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return 1;
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->student_node.num_estudante != num_estudante) {
        prev = temp;
        temp = temp->next;
    }
 
    // If key was not present in linked list
    if (temp == NULL)
        return 0;
 
    // Unlink the node from linked list
    prev->next = temp->next;
 
    free(temp); 

    return 1;
}

/* To delete a node of a linked list recursively we need to do the following steps.
 
 1. We pass node* (node pointer) as a reference to the function (as in node* &head)

 2. Now since the current node pointer is derived from the previous node’s next (which is passed by reference) so now if the value of the current node pointer is changed, the previous next node’s value also gets changed which is the required operation while deleting a node (i.e points previous node’s next to current node’s (containing key) next).

 3. Find the node containing the given value.

 4. Store this node to deallocate it later using the free() function.

 5. Change this node pointer so that it points to its next and by performing this previous node’s next also gets properly linked.*/



void printList(struct Node *node){
    int i = 0;
    while (node != NULL){
        printf("\n");
        printf("Nome: %s\n", node->student_node.nome);
        printf("Ano: %ld\n", node->student_node.ano);
        printf("Número de estudante: %ld\n", node->student_node.num_estudante);
        printf("Data de nascimento: %s\n", node->student_node.data_nasc);
        printf("Saldo: %.2f\n", node->student_node.saldo);
        printf("Turma: %s\n", node->student_node.turma);
     node = node->next;
        i++;
    }
}

int refreshBD(struct Node *node){
    FILE *cfPtr;
    if ( ( cfPtr = fopen( "BD_Config.txt", "w" ) ) == NULL ) {
        printf( "Could not refresh database\n" );
        return 1;
    }
    while (node != NULL){
        fprintf(cfPtr," Nome:'%s'\n", node->student_node.nome);
        fprintf(cfPtr,"Data de nascimento:%s\n", node->student_node.data_nasc);
        fprintf(cfPtr,"Ano:%ld\n", node->student_node.ano);
        fprintf(cfPtr,"Turma:%s\n", node->student_node.turma);
        fprintf(cfPtr,"Numero de estudante:%ld\n", node->student_node.num_estudante);
        fprintf(cfPtr,"Saldo:%.2f\n", node->student_node.saldo);
        node = node->next;
    }
    fclose(cfPtr);
    return 0;
}

int printList_saldo(struct Node *node, double valor){
    int i = 0;
    
    while (node != NULL){
        if(node->student_node.saldo < valor){
            printf("Nome: %s\n", node->student_node.nome);
            printf("Ano: %ld\n", node->student_node.ano);
            printf("Número de estudante: %ld\n", node->student_node.num_estudante);
            printf("Data de nascimento: %s\n", node->student_node.data_nasc);
            printf("Saldo: %.2f\n", node->student_node.saldo);
            printf("Turma: %s\n", node->student_node.turma);
            
            printf("\n");
            i++;
        }
        node = node->next;
        i++;
    }
    return i;
}

int print_info(struct Node *temp, long num){
    
    struct Node* current = temp;
    int index = 0;

    while (current != NULL){
        if(current->student_node.num_estudante == num){
            printf("\n-------- Estudante encontradx --------\n");
            printf("Nome: %s\n", current->student_node.nome);
            printf("Ano: %ld\n", current->student_node.ano);
            printf("Número de estudante: %ld\n", current->student_node.num_estudante);
            printf("Data de nascimento: %s\n", current->student_node.data_nasc);
            printf("Saldo: %.2f\n", current->student_node.saldo);
            printf("Turma: %s\n", current->student_node.turma);
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

int print_info_saldo(struct Node *temp, double saldo){
    
    struct Node* current = temp;
    int index = 0;

    while (current != NULL){
        if(current->student_node.saldo == saldo){
            printf(" nome %s\n", temp->student_node.nome);
            printf(" ano %ld\n", temp->student_node.ano);
            printf(" n_st %ld\n", temp->student_node.num_estudante);
            printf(" data %s\n", temp->student_node.data_nasc);
            printf(" saldo %.2f\n", temp->student_node.saldo);
            printf(" turma %s\n", temp->student_node.turma);
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

void swap(struct Node *a, struct Node *b)
{
    char temp[MAXCHAR];
    strcpy(temp,a->student_node.nome);
    strcpy(a->student_node.nome,b->student_node.nome);
    strcpy(b->student_node.nome, temp);
}

void bubbleSort(struct Node *start)
{
    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;
    char temp[MAXCHAR];
    long temp_num;
    char temp_tur[MAXCHAR];
    long temp_ano;
    char temp_dat[MAXCHAR];
    char temp_nome[MAXCHAR];
    char temp_nome_2[MAXCHAR];
    double temp_sal;
    if (start == NULL)
        return;
    
    
    do
    {
        swapped = 0;
        ptr1 = start;
  
        while (ptr1->next != lptr)
        {
            strtobase_u8(temp_nome, ptr1->student_node.nome);
            strtobase_u8(temp_nome_2, ptr1->next->student_node.nome);
            if (strcmp(temp_nome, temp_nome_2) > 0)
            {
                // -------------------- TEMP = CURRENT ----------------------------
                strcpy(temp,ptr1->student_node.nome);
                temp_num = ptr1->student_node.num_estudante;
                strcpy(temp_tur,ptr1->student_node.turma);
                temp_ano = ptr1->student_node.ano;
                strcpy(temp_dat,ptr1->student_node.data_nasc);
                temp_sal = ptr1->student_node.saldo;
                
                // -------------------- CURRENT = NEXT ----------------------------
                strcpy(ptr1->student_node.nome,ptr1->next->student_node.nome);
                ptr1->student_node.num_estudante = ptr1->next->student_node.num_estudante;
                strcpy(ptr1->student_node.turma,ptr1->next->student_node.turma);
                ptr1->student_node.ano = ptr1->next->student_node.ano;
                strcpy(ptr1->student_node.data_nasc,ptr1->next->student_node.data_nasc);
                ptr1->student_node.saldo = ptr1->next->student_node.saldo;
                
                // -------------------- NEXT = TEMP ----------------------------
                strcpy(ptr1->next->student_node.nome, temp);
                ptr1->next->student_node.num_estudante = temp_num;
                strcpy(ptr1->next->student_node.turma, temp_tur);
                ptr1->next->student_node.ano = temp_ano;
                strcpy(ptr1->next->student_node.data_nasc, temp_dat);
                ptr1->next->student_node.saldo = temp_sal;
                    
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
void bubbleSort_saldo(struct Node *start)
{
    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;
    char temp[MAXCHAR];
    long temp_num;
    char temp_tur[MAXCHAR];
    long temp_ano;
    char temp_dat[MAXCHAR];
    double temp_sal;
    /* Checking for empty list */
    if (start == NULL)
        return;
  
    do
    {
        swapped = 0;
        ptr1 = start;
  
        while (ptr1->next != lptr)
        {
            if (ptr1->student_node.saldo < ptr1->next->student_node.saldo)
            {
                // -------------------- TEMP = CURRENT ----------------------------
                strcpy(temp,ptr1->student_node.nome);
                temp_num = ptr1->student_node.num_estudante;
                strcpy(temp_tur,ptr1->student_node.turma);
                temp_ano = ptr1->student_node.ano;
                strcpy(temp_dat,ptr1->student_node.data_nasc);
                temp_sal = ptr1->student_node.saldo;
                
                // -------------------- CURRENT = NEXT ----------------------------
                strcpy(ptr1->student_node.nome,ptr1->next->student_node.nome);
                ptr1->student_node.num_estudante = ptr1->next->student_node.num_estudante;
                strcpy(ptr1->student_node.turma,ptr1->next->student_node.turma);
                ptr1->student_node.ano = ptr1->next->student_node.ano;
                strcpy(ptr1->student_node.data_nasc,ptr1->next->student_node.data_nasc);
                ptr1->student_node.saldo = ptr1->next->student_node.saldo;

                // -------------------- NEXT = TEMP ----------------------------
                strcpy(ptr1->next->student_node.nome, temp);
                ptr1->next->student_node.num_estudante = temp_num;
                strcpy(ptr1->next->student_node.turma, temp_tur);
                ptr1->next->student_node.ano = temp_ano;
                strcpy(ptr1->next->student_node.data_nasc, temp_dat);
                ptr1->next->student_node.saldo = temp_sal;
                    
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

int writeToFileScreen (student this_student) {
    FILE *cfPtr; /* cfPtr = BD_Config.txt file pointer */
    if ( ( cfPtr = fopen( "BD_Config.txt", "a" ) ) == NULL ) {
        printf( "File could not be opened\n" );
        return 1;
    } 
    else {
        fprintf(cfPtr," Nome:'%s'\n", this_student.nome);
        fprintf(cfPtr,"Data de nascimento:%s\n", this_student.data_nasc);
        fprintf(cfPtr,"Ano:%ld\n", this_student.ano);
        fprintf(cfPtr,"Turma:%s\n", this_student.turma);
        fprintf(cfPtr,"Numero de estudante:%ld\n", this_student.num_estudante);
        fprintf(cfPtr,"Saldo:%.2f\n", this_student.saldo);
        fclose(cfPtr); 
    } 
    fclose(cfPtr);
    return 0; /* indicates successful termination */
}

int read_from_file(struct Node** head_ref) {
    student* aux_student = malloc(sizeof(student));
    FILE *cfPtr; 
    
    /* fopen opens file; exits program if file cannot be opened */
    if ( ( cfPtr = fopen( "BD_Config.txt", "r" ) ) == NULL ) {
        printf( "File could not be opened\n" );
        exit(1);
    } 
    else {
        while(fgetc(cfPtr) != EOF){
            if(fscanf(cfPtr," Nome:'%[^']'%*c", aux_student->nome)==EOF)return 2;
            if(fscanf(cfPtr,"Data de nascimento:%s%*c", aux_student->data_nasc)==EOF) return 1;
            if(fscanf(cfPtr,"Ano:%ld%*c", &aux_student->ano)==EOF)return 1;
            if(fscanf(cfPtr,"Turma:%s%*c", aux_student->turma)==EOF) return 1;
            if(fscanf(cfPtr,"Numero de estudante:%ld%*c", &aux_student->num_estudante)==EOF) return 1;
            if(fscanf(cfPtr,"Saldo:%lf%*c", &aux_student->saldo)==EOF) return 1;
            //printf("Num est %s\n", aux_student->num_estudante);
            push_after(head_ref, *aux_student);
        }//ponteiro p eof
        
    } /* end else */
    fclose( cfPtr ); /* fclose closes the file */
    
    return 0; /* indicates successful termination */
}


/*
 • Introduzir dados de um novo aluno.
 • Eliminar um aluno existente.
 • Listar todos os alunos por ordem alfabética.
 • Listar os alunos com saldo abaixo de um determinado valor (por ordem decrescente de saldos).
 • Apresentar toda a informação de um determinado aluno.
 • Efetuar uma despesa por um determinado aluno.
 • Carregar a conta de um aluno com um valor.
 */
