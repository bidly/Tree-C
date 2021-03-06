#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

int size = 0;

struct node {
    int data;
    int key;
    int parent;
    struct node *next;
    struct node *prev;
};
struct node *head = NULL;

void printList() { /*list printer function. */
    struct node *ptr = head;
    printf("\n[ ");

    //start from the beginning

    while (ptr != NULL) {
        printf("(%d) ", ptr->data);
        ptr = ptr->next;
    }



    printf(" ]");
}

void insertFirst(int data, int key, int parent) { /*this function adds the numbers to the beggining of the linked list*/
    //create a link
    struct node *link = (struct node *) malloc(sizeof(struct node));

    link->data = data;


    //point it to old first node
    link->next = head;

    //point first to new first node
    head = link;
    size++;
}


struct node *delete(int key) { /*this func deletes a node with given key*/

    //start from the first link
    struct node *current = head;
    struct node *previous = NULL;

    //if list is empty
    if (head == NULL) {
        return NULL;
    }

    //navigate through list
    while (current->key == key ) {

        //if it is last node
        if (current->next == NULL) {
            return NULL;
        } else {
            //store reference to current link
            previous = current;
            //move to next link
            current = current->next;
        }
    }

    //found a match, update the link
    if (current == head) {
        //change first to point to next link
        head = head->next;
    } else {
        //bypass the current link
        previous->next = current->next;
    }


    return current;
}


void reverse(struct node **head_ref) { /*since my structure is first in last out, this func reverses the list.*/
    struct node *prev = NULL;
    struct node *current = *head_ref;
    struct node *next;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head_ref = prev;
}


int main() {






    FILE *fp, *fpSize;
    char *line = NULL, *line2 = NULL;
    size_t len = 0;
    ssize_t read;


    fpSize = fopen("Input1.txt", "r");
    fp = fopen("Input1.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int flag = 0;
    int flag2 = 0;
    int turn = 0; /*implements where is the line. Like this time we should pick the number from 5th element of array. rank*/
    int sizeOfFirst = 0;
    int treeSize = 0;


    while ((read = getline(&line, &len, fpSize)) != -1) {
        if(strlen(line) != 1)
            sizeOfFirst++;
    }
    fclose(fpSize);

    treeSize = sizeOfFirst;

    int nodes[sizeOfFirst][2];
    int i = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        if(strlen(line) != 1)
        {
            char *token;
            int j = 0;
            token = strtok(line, " ");
            while (token != NULL) {
                nodes[i][j]= atoi(token);
                token = strtok(NULL, " ");
                j++;
            }
            i++;
        }
    }



    int counter = 1;
    int secondColumnCounter = 0;
    int j = 1, temp = 1;

    insertFirst(nodes[0][0], counter, -1); /*inserting the root. It has parent -1 so i can easily check the root*/

    for(i = 1; i<=nodes[0][1]; i++) /*inserting first leafs.*/
    {
        insertFirst(nodes[i][0], i, nodes[0][0]);
        counter++;
    }

    turn = turn + i;
    secondColumnCounter = secondColumnCounter + 1;
    treeSize = treeSize - i;

    while(treeSize >= 0 && flag2 != 2) /*check if all the nodes are placed or not*/
    {




        if(nodes[secondColumnCounter][1] < nodes[secondColumnCounter-1][1])
        {
            for(i = 0; i<nodes[secondColumnCounter][1]; i++) /*inserting other leaves.*/
            {

                insertFirst(nodes[counter][0], counter, nodes[0][0]); /*PARENTTA HATA VAR DÜZELT SONRADAN*/
                flag = 1;
                counter++;
            }
        }
        else if(nodes[secondColumnCounter][1] == nodes[secondColumnCounter-1][1])
        {
            for(i = 0; i<nodes[secondColumnCounter][1]; i++) /*inserting other leaves.*/
            {
                insertFirst(nodes[counter][0], counter, nodes[counter-nodes[secondColumnCounter][1]][0]); /*PARENTTA HATA VAR DÜZELT SONRADAN*/
                counter++;
            }
        }
        else if(nodes[secondColumnCounter][1] > nodes[secondColumnCounter-1][1])
        {
            int mod = nodes[secondColumnCounter][1] / nodes[secondColumnCounter-1][1] + 1;

            for(i = 1; i<mod+1; i++)
            {
                while (j<=nodes[secondColumnCounter][1])
                {
                    printf("%d,", turn + j -1-1);

                    insertFirst(nodes[turn + j - 1][0], counter, nodes[0][0]); /*PARENTTA HATA VAR DÜZELT SONRADAN*/
                    j = j + mod;
                    counter++;
                }
                temp = temp +1;
                j = temp;

            }
        }


        treeSize = treeSize - nodes[secondColumnCounter][1]; /*update how many nodes left*/

        secondColumnCounter++;




        if(treeSize<=nodes[secondColumnCounter][1])
        {
            nodes[secondColumnCounter][1] = treeSize;
            flag2++;
        }
        turn = turn + nodes[secondColumnCounter][1];    /*update the rank*/


        temp = 1;
        j = 1;
    }



    reverse(&head);
    printList();
}