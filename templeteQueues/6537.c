#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 */
typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;
/*
 *
 */
typedef struct Node
{
    Process data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
     Node *front, *rear;
} Queue;
/*
 *
 */
Queue* init()
{
    Queue *q = malloc(sizeof(Queue));
    q->front=q->rear=NULL;
    return q;
}
/*
 *
 */
int isEmpty(Queue *q)
{
    if (q->front==NULL)
        return 1;
    return 0;
}
/*
 *
 */

Process dequeue(Queue *q)
{
    Process x;
    if (q->front) {
    Node *temp = q->front;
    x = temp->data;
    q->front=q->front->next;
    free(temp);
    if (q->front == NULL)
        q->rear=NULL;
    return x;
    }
    return x;
}
/*
 *
 */
Node *newNode(Process x){
    Node *f = malloc(sizeof(Queue));
    f->data=x;
    f->next=NULL;
    return f;
}



void enqueue(Queue *q, Process val)
{
    Node *n = newNode(val);
    if (q->front==NULL) {
        q->front=q->rear= n;
    }
    else
    {
        q->rear->next=n;
        q->rear=n;
    }
}
/*
 *
 */
void destroy(Queue *q)
{
    while (!isEmpty(q)) {
        dequeue(q);
    }
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    Queue *f = init();
    Process array[100]={};
    int counter = 0;
    int i,j;
    int collectedTime;
    FILE *fp;
//    char fares [100]=
    fp=fopen(filename,"r");
    char trash[10];
    fscanf(fp, "%s %s %s %s %d",trash,trash,trash,trash,&collectedTime);
    printf("%d",collectedTime);
        while (!feof(fp))
        {
            array[counter].name=malloc(4);
            fscanf(fp, "%s ",array[counter].name);
            fscanf(fp, "%d ",&(array[counter].starting_time));
            fscanf(fp, "%d ",&(array[counter].remaining_time));
//            printf("%s %d %d \n",array[counter].name,array[counter].starting_time,array[counter].remaining_time);
            counter++;
        }
    for (i=0 ; i<collectedTime ; i++)
    {
        for (j=0 ; j<counter ;  j++)
        {
            if(array[j].starting_time == i)
            {
                enqueue(f,array[j]);
            }
        }
        
        if(!isEmpty(f))
        {
            Process fares;
            fares=dequeue(f);
            printf("%s (%d-->%d)",fares.name,i,i+1);
            (fares.remaining_time)--;
            if(fares.remaining_time!=0)
                enqueue(f,fares);
            if(fares.remaining_time==0)
                printf(" %s aborts",fares.name);
            printf("\n");
        }
        else
            printf("Idle (%d--%d)\n",i,i+1);
    }
        
}
    

/*
 *
 */
int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }
    
    return 0;
}
