#include <stdio.h>
#include "sorted-list.h"
#include <string.h>

//Sample comparator and display functions

int CompareInt(void * a, void *b) {		//compare integers
    return (*(int*)a-*(int*)b);
}

double CompareDouble(void * a, void *b) {	//compare doubles
    double one = *(double*)a;
    double two = *(double*)b;
    
    return one-two;
}


void displayIList(SortedListPtr list) //display integer list
{
    node *temp;
    for(temp=list->head;temp!=NULL;temp=temp->next)
    {
        printf("%d,",*(int*)temp->obj);
    }
    printf("\n");
}

void displayDList(SortedListPtr list)	//display double list
{
    node *temp;
    for(temp=list->head;temp!=NULL;temp=temp->next)
    {
        printf("%lf,",*(double*)temp->obj);
    }
    printf("\n");
}

/*void displaySList(SortedListPtr list)		//display string list
 {
 node *temp;
 for(temp=list->head;temp!=NULL;temp=temp->next)
 {
 printf("%s,",(char*)temp->obj);
 }
 printf("\n");
 }*/

void IntTest1() {
    SortedListPtr Ilist =SLCreate((CompareFuncT)CompareInt,(DestructFuncT)SLDestroy); // create list
    int *ip1=malloc(sizeof(int));
    int *ip2=malloc(sizeof(int));
    int *ip3=malloc(sizeof(int));
    int *ip4=malloc(sizeof(int));
    *ip1=5;*ip2=2;*ip3=8;*ip4=4;
    SLInsert(Ilist,ip1);
    SLInsert(Ilist,ip2);
    SLInsert(Ilist,ip3);
    SLInsert(Ilist,ip4);
    printf("test 1\n");
    displayIList(Ilist);
    free(ip1);
    free(ip2);
    free(ip3);
    free(ip4);
    SLDestroy(Ilist);
}

void IntTest2() {
    SortedListPtr Ilist =SLCreate((CompareFuncT)CompareInt,(DestructFuncT)SLDestroy); // create list
    int *ip1=malloc(sizeof(int));
    int *ip2=malloc(sizeof(int));
    int *ip3=malloc(sizeof(int));
    int *ip4=malloc(sizeof(int));
    *ip1=5;*ip2=2;*ip3=8;*ip4=4;
    SLInsert(Ilist,ip1);
    SLInsert(Ilist,ip2);
    SLInsert(Ilist,ip3);
    SLInsert(Ilist,ip4);
    SLRemove(Ilist,ip2);
    printf("test2 \n");
    displayIList(Ilist);
    free(ip1);
    free(ip2);
    free(ip3);
    free(ip4);
    SLDestroy(Ilist);
}

void DoubleTest1() {
    SortedListPtr Dlist =SLCreate((CompareFuncT)CompareDouble,(DestructFuncT)SLDestroy); // create list
    double *ip1=malloc(sizeof(double));
    double *ip2=malloc(sizeof(double));
    double *ip3=malloc(sizeof(double));
    double *ip4=malloc(sizeof(double));
    *ip1=5.2;*ip2=2.5;*ip3=8.33;*ip4=4.01;
    SLInsert(Dlist,ip1);
    SLInsert(Dlist,ip2);
    SLInsert(Dlist,ip3);
    SLInsert(Dlist,ip4);
    printf("\n");
    //SLRemove(Dlist,ip2);
    displayDList(Dlist);
    free(ip1);
    free(ip2);
    free(ip3);
    free(ip4);
    SLDestroy(Dlist);
}
int main()
{
    
    //Testcase 1 - Insertion of integers
    IntTest1();
    
    IntTest2();
    
    DoubleTest1();
    return 0;
}


