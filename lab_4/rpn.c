#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum Bracket{
    Bracket_open,
    Bracket_close,
};

enum Operation{
    OP_plus,
    OP_minus,
    OP_multi,
    OP_div,
};

enum Lexem_type{
    NUMBER,
    OPERATION,
    BRACKET,
    Last,
    First,
};

struct Lexem{
    enum Lexem_type type;
    struct v{
        int num_value;
        enum Operation op;
        enum Bracket br;
    } value;
};

struct Lexem_list{
    struct Lexem lex;
    struct Lexem_list *next;
};

void push(struct Lexem_list **stack, struct Lexem lex){
    struct Lexem_list *newLexem = (struct Lexem_list*)malloc(sizeof(struct Lexem_list));
    newLexem->lex = lex;
    newLexem->next = *stack;
    *stack = newLexem;
}

struct Lexem pop(struct Lexem_list **stack){
    struct Lexem lex = (*stack)->lex;
    struct Lexem_list *p = *stack;
    *stack = (*stack)->next;
    free(p);
    return lex;
}

struct Lexem_list* getLexemList(){
    struct Lexem_list* list = (struct Lexem_list*)malloc(sizeof(struct Lexem_list));
    struct Lexem lex;
    lex.type = Last;
    list->lex = lex;
    push(&list,lex);
    char tec = ' ';
    int num = -1;
    while(tec != '!'){
        scanf("%c", &tec);
        if(isdigit(tec)){
            if(num == -1) num = 0;
            num *= 10;
            num += tec - '0';
        } else{
            if(num != -1){
                lex.type = NUMBER;
                lex.value.num_value = num;
                push(&list,lex);
                num = -1;
            }
            if(tec == '+'){
                lex.type = OPERATION;
                lex.value.op = OP_plus;
                push(&list,lex);
            }else
            if(tec == '-'){
                lex.type = OPERATION;
                lex.value.op = OP_minus;
                push(&list,lex);
            }else
            if(tec == '*'){
                lex.type = OPERATION;
                lex.value.op = OP_multi;
                push(&list,lex);
            }else
            if(tec == '/'){
                lex.type = OPERATION;
                lex.value.op = OP_div;
                push(&list,lex);
            }else
            if(tec == '('){
                lex.type = BRACKET;
                lex.value.br = Bracket_open;
                push(&list,lex);
            }else
            if(tec == ')'){
                lex.type = BRACKET;
                lex.value.br = Bracket_close;
                push(&list,lex);
            }
        }
    }
    lex.type = First;
    push(&list,lex);
    return list;
}

void printlist(struct Lexem_list * list){
    struct Lexem_list * pointer = list;
    // pointer = pointer->next;
    printf("\n");
    while(pointer->lex.type != Last){
        //printf("%d", pointer->lex.type);
        if(pointer->lex.type == NUMBER) printf(" %d ", pointer->lex.value.num_value);
        if(pointer->lex.type == OPERATION) printf("%d", pointer->lex.value.op);
        pointer = pointer->next;
    }
}

int g1(struct Lexem_list* stack, struct Lexem l){
    push(&stack,l);
    return 1;
}
int g2(struct Lexem_list* stack,struct Lexem_list* rpn){
    struct Lexem l = pop(&stack);
    push(&rpn,l);
    printf("g");
    return 2;
}
int g3(struct Lexem_list* stack){
    pop(&stack);
    return 3;
}

struct Lexem_list * getRPN(struct Lexem_list* input){
    struct Lexem_list *stack = (struct Lexem_list*)malloc(sizeof(struct Lexem_list));
    struct Lexem_list *rpn = (struct Lexem_list*)malloc(sizeof(struct Lexem_list));
    stack->lex.type = Last;
    rpn->lex.type = Last;
    struct Lexem l, last_steck;
    last_steck.type = Last;
    l.type = First;
    int status;
    while(l.type != Last){
        l = pop(&input);
        if(l.type == NUMBER){
                push(&rpn,l);
                continue;
        }
        status = -1;
        while(!(status ==1 || status == 4 || status == 3)){
            if(l.type == OPERATION && (l.value.op == OP_plus || l.value.op == OP_minus)){
                if(last_steck.type == Last){
                    printf("t1");
                    push(&stack,l);
                    status = 1;
                    printf("-%d-", last_steck.type);
                    last_steck = stack->lex;
                    printf("-%d-", last_steck.type);
                }else
                if(last_steck.type == OPERATION){
                    printf("k1");
                    status = 2;
                    push(&rpn,pop(&stack));
                    last_steck = stack->lex;
                }else
                if(last_steck.type == BRACKET){
                    printf("t2");
                    push(&stack,l);
                    status = 1;
                    last_steck = stack->lex;
                }
            }else
            if(l.type == OPERATION && (l.value.op == OP_multi || l.value.op == OP_div)){
                if(last_steck.type == Last || last_steck.type == BRACKET || (last_steck.type == OPERATION && (last_steck.value.op == OP_plus || last_steck.value.op == OP_minus))){
                    printf("t3");
                    push(&stack,l);
                    status = 1;
                    last_steck = stack->lex;
                }else
                if(last_steck.type == OPERATION && (last_steck.value.op == OP_multi || last_steck.value.op == OP_div)){
                    printf("k2");
                    status = 2;
                    push(&rpn,pop(&stack));
                    last_steck = stack->lex;
                }
            }else
            if(l.type == BRACKET && l.value.br == Bracket_open){
                printf("t4");
                push(&stack,l);
                    status = 1;
                last_steck = stack->lex;
            }else
            if(l.type == BRACKET && l.value.br == Bracket_close){
                if(last_steck.type == OPERATION){
                    printf("k3");
                    status = 2;
                    push(&rpn,pop(&stack));
                    last_steck = stack->lex;
                }
                if(last_steck.type == BRACKET){
                    printf("j1");
                    status = 3;
                    pop(&stack);
                    last_steck = stack->lex;
                }
            }else
            if(l.type == Last || last_steck.type == First){
                printf("kek");
                if(last_steck.type == OPERATION){
                    printf("k4");
                    status = 2;
                    push(&rpn,pop(&stack));
                    last_steck = stack->lex;
                }
                if(last_steck.type == Last){
                    status = 4;
                }
            }
            printf("lol");
        }
        if (status == 4)
        {
            break;
        }
    }
return rpn;
}

int main(){
    struct Lexem_list *input = getLexemList();
    struct Lexem_list *rpn = getRPN(input); 
    printlist(rpn);
    
    return 0;
}