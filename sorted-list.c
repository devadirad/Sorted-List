#include "sorted-list.h"
#include <stdio.h>
#include <stdlib.h>

node* NodeCreate(void* obj, node* next){
    node* newNode = (node*)malloc(sizeof(node));	//malloc space for node
    newNode->obj = obj;
    newNode->next = next;
    newNode->refs = 1;							//initiate values, return node
    return newNode;
}

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){
    
    SortedListPtr list = (SortedListPtr)malloc(sizeof(struct SortedList));
    
    
    
    if(list != NULL){  //check if malloc worked
        list->destF=df;
        list->compF=cf;
        list->head = NULL;	//if so, create list with given parameters
        //printf("list created!!\n");
        return list;
    }else{
        return NULL;
    }
    
    
}


SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
    
    SortedListIteratorPtr iterator = (SortedListIteratorPtr)malloc(sizeof(struct SortedListIterator));  //malloc space for iterator
    
    
    
    if (iterator != NULL){						//malloc check
        iterator->curr = list->head;				//set current node to head of list and return, as long as list exists
        if (iterator->curr!=NULL){
            list->head->refs++;             //increment reference number
        }
        //printf("iterator created!!\n");
        return iterator;
    }else{
        return NULL;							//fail case
    }
    
}


void *SLNextItem(SortedListIteratorPtr iter){
    
    
    node* tempPTR = iter->curr->next;		//create a temp pointer to the next node
    
    if(iter->curr->refs ==1){			//check if current node has been removed from list but not destroyed
        free(iter->curr);
    }else{
        iter->curr->refs--;             //deducts 1 from reference counter of the next node if next != NULL and refs == 1.
    }
    
    iter->curr = tempPTR;				//Set current node to next node
    
    
    if(iter->curr!=NULL){					//If temp == NULL you are at the end of the list and return NULL
        iter->curr->refs++;
        return iter->curr->obj;			//Else you return the void* object
        printf("here is the next item!!!\n");
    }else{
        
        return NULL;
    }
    
}

int SLInsert(SortedListPtr list, void *newObj){
    double compareVal;
    void* currObj;
    
    SortedListIteratorPtr iterPtr = SLCreateIterator(list);
    if (iterPtr == NULL){
        return 0;
    }
    node* prev = iterPtr->curr;
    
    if (iterPtr->curr == NULL || (*list->compF)(newObj, iterPtr->curr->obj) > 0){		//empty list/first object bigger
        list->head = NodeCreate(newObj,iterPtr->curr);		// head insert
        SLDestroyIterator(iterPtr);
        return 1;
    }
    currObj=SLNextItem(iterPtr);
    
    while(iterPtr->curr != NULL){
        
        compareVal = (*list->compF)(newObj, currObj); //compare curr/new objs
        
        if(compareVal >= 0){									//add here
            break;
        }else if(compareVal == 0){							//duplicate, ignore
            SLDestroyIterator(iterPtr);
            printf("duplicate item!!!\n");
            return 1;
        }else{										//increment pointers
            prev = iterPtr->curr;
            currObj=SLNextItem(iterPtr);
        }
    }
    prev->next = NodeCreate(newObj,iterPtr->curr);		//insert node
    if (prev->next==NULL) {
        printf("Malloc fail!\n");
        return 0;
    }
    SLDestroyIterator(iterPtr);
    return 1;
}


int SLRemove(SortedListPtr list, void *newObj)
{
    int removeVal;
    void* currObj;
    SortedListIteratorPtr remPtr = SLCreateIterator(list);
    if (remPtr == NULL){
        printf("Failed to create iterator!\n");
        return 0;
    }
    
    node *prev = remPtr->curr;
    removeVal=(*list->compF)(newObj, list->head->obj);
    if(removeVal == 0){
        list->head = list->head->next;
        if (remPtr->curr->refs==2){				//remove head
            free(remPtr->curr);
        }
        SLDestroyIterator(remPtr);
        return 1;
    }
    currObj=SLNextItem(remPtr);
    while(remPtr->curr != NULL){                    //go until eof
        
        removeVal = (*list->compF)(newObj, currObj);
        
        if(removeVal==0){                                   //match found
            prev->next = remPtr->curr->next;
            if(remPtr->curr->refs == 2){
                free(remPtr->curr);          //destroy node if not used by other iterators
            }
            SLDestroyIterator(remPtr);
            return 1;
        }else{
            prev = remPtr->curr;
            currObj=SLNextItem(remPtr);
        }
    }
    SLDestroyIterator(remPtr);
    printf("Object not found\n");                //not found
    return 0;
}

void SLDestroy(SortedListPtr list)
{
    free(list);
}

void SLDestroyIterator(SortedListIteratorPtr iter){
    if (iter->curr!=NULL){                                 //checks if curr node in list
        if(iter->curr->refs <= 1){
            free(iter->curr);                       //else decrements refs if pointing to node
        }else {
            iter->curr->refs--;
        }
    }
    free(iter);
}
