//
//  structure.h
//  PPP_LinkedList
//
//  Created by Amanda Menezes on 17/02/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib-utf8.h"
#define MAXCHAR 1024

typedef struct student{
    char nome[MAXCHAR];
    char data_nasc[MAXCHAR];
    long ano;
    char turma[MAXCHAR];
    long num_estudante;
    double saldo;
    
}student;

struct Node{
  student student_node;
  struct Node *next;

};

/* Given a reference (pointer to pointer) to the head of a list
   and an int,  inserts a new node on the front of the list. */
void push_after(struct Node** head_ref, student new_data);
//void pop(struct Node** head_ref, int new_data);
void printList(struct Node *node);
int deleteNode(struct Node** head_ref, long num_estudante);
void bubbleSort(struct Node *start);
void bubbleSort_saldo(struct Node *start);
void swap(struct Node *a, struct Node *b);
int recharge(struct Node *head, long student, double val);
int payment(struct Node *head, long student, double val);
//void transaction(student *dest, student *pag, double valor);
void bubbleSort_saldo(struct Node *start);
int printList_saldo(struct Node *node, double valor);
int print_info(struct Node *temp, long num);
int print_info_saldo(struct Node *temp, double saldo);
int refreshBD(struct Node *node);
int change_class(struct Node *head, long student, char class[MAXCHAR]);
int check_num(struct Node *head, long student);

/* Functions to manage database */
int writeToFileScreen (student this_student);
int read_from_file(struct Node** head_ref);

