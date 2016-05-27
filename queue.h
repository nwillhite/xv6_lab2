#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct node {
    int value;
    struct node *next;
}node;

struct queue{
    int size;
    struct node * head;
    struct node * tail;
};

// queue library
void init_q(struct queue *);
void add_q(struct queue *, int);
int empty_q(struct queue *);
int pop_q(struct queue *);

#endif // __QUEUE_H__
