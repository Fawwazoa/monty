#ifndef MONTY_H
#define MONTY_H
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>


/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;


extern stack_t *head;
typedef void (*op_func) (stack_t ** , unsigned int);


void openf(char *file_name);
int pline(char *buffer, int line_number, int format);
void readf(FILE *);
int len_chars(FILE *);
void find_func(char *, char *, int, int);


stack_t *crnode(int n);
void frnode(void);
void pstack(stack_t **, unsigned int);
void add2stack(stack_t **, unsigned int);
void add2queue(stack_t **, unsigned int);

void cfun(op_func, char *, char *, int, int);
void prtop(stack_t **, unsigned int);
void poptop(stack_t **, unsigned int);
void nop(stack_t **, unsigned int);
void swanodes(stack_t **, unsigned int);


void anodes(stack_t **, unsigned int);
void snodes(stack_t **, unsigned int);
void dnodes(stack_t **, unsigned int);
void mulnodes(stack_t **, unsigned int);
void modnodes(stack_t **, unsigned int);


void prchar(stack_t **, unsigned int);
void prstr(stack_t **, unsigned int);
void rotl(stack_t **, unsigned int);


void merr(int error_code, ...);
void moerr(int error_code, ...);
void strerr(int error_code, ...);
void rotr(stack_t **, unsigned int);

#endif
