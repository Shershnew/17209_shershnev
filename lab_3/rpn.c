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
    int priority;
    struct v{
        double num_value;
        enum Operation op;
        enum Bracket br;
    } value;
};

struct Lexem_list{
    struct Lexem lex;
    struct Lexem_list *next;
};

struct calc_answer{
    int error;
    double res;
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

struct Lexem_list* reverse(struct Lexem_list * list){
    struct Lexem_list *last = 0;
    while(list != 0){
        struct Lexem_list *p = list->next;
        list->next = last;
        last = list;
        list = p;
    }
    return last;
}

struct Lexem_list* getLexemList(){
    struct Lexem_list* list = (struct Lexem_list*)malloc(sizeof(struct Lexem_list));
    struct Lexem lex;
    lex.type = First;
    list->lex = lex;
    list->next = 0;
    char tec = ' ';
    int i = 0;
    int bracket_count = 0;
    int num_count = 0;
    int op_count = 0;
    int unar_op = 1;
    int dot = 0;
    int count_after_dot = 0;
    double num = -1;
    while(tec != '\n'){
        scanf("%c", &tec);
        if(isdigit(tec) || tec == '.'){
            if(tec == '.'){
                dot = 1;
            } else{
                if(num == -1){
                    num = 0;
                }
                num *= 10;
                num += tec - '0';
                if(dot == 1){
                    count_after_dot++;
                }
            }
        } else{
            if(num != -1){
                for(i = 0; i < count_after_dot; i++){
                    num /=10;
                }
                lex.type = NUMBER;
                lex.value.num_value = num;
                if(num_count < op_count){
                    lex.value.num_value *= unar_op;
                    op_count--;
                }
                push(&list,lex);
                dot = 0;
                count_after_dot = 0;
                num = -1;
                num_count++;
            }
            if(tec == '+'){
                lex.type = OPERATION;
                lex.value.op = OP_plus;
                lex.priority = 3;
                op_count++;
                if(num_count < op_count){
                    unar_op = 1;
                }else{
                    push(&list,lex);
                }
            }else if(tec == '-'){
                lex.type = OPERATION;
                lex.value.op = OP_minus;
                lex.priority = 3;
                op_count++;
                if(num_count < op_count){
                    unar_op = -1;
                } else{
                    push(&list,lex);
                }
            }else if(tec == '*'){
                lex.type = OPERATION;
                lex.value.op = OP_multi;
                lex.priority = 4;
                push(&list,lex);
                op_count++;
            }else if(tec == '/'){
                lex.type = OPERATION;
                lex.value.op = OP_div;
                lex.priority = 4;
                push(&list,lex);
                op_count++;
            }else if(tec == '('){
                bracket_count++;
                lex.type = BRACKET;
                lex.value.br = Bracket_open;
                lex.priority = 2;
                push(&list,lex);
            }else if(tec == ')'){
                bracket_count--;
                lex.type = BRACKET;
                lex.value.br = Bracket_close;
                lex.priority = 2;
                push(&list,lex);
            }
        }
        if(bracket_count < 0){
            free(list);
            return 0;
        }
    }
    if(bracket_count != 0){
        free(list);
        return 0;
    }
    lex.type = Last;
    push(&list,lex);
    list = reverse(list);
    return list;
}

void printlist(struct Lexem_list * list){
    struct Lexem_list * pointer = list;
    while(pointer != 0){
        if(pointer->lex.type == NUMBER){
            printf(" %f ", pointer->lex.value.num_value);
        }
        if(pointer->lex.type == OPERATION && pointer->lex.value.op == OP_plus){
            printf("+");
        }
        if(pointer->lex.type == OPERATION && pointer->lex.value.op == OP_minus){
            printf("-");
        }
        if(pointer->lex.type == OPERATION && pointer->lex.value.op == OP_multi){
            printf("*");
        }
        if(pointer->lex.type == OPERATION && pointer->lex.value.op == OP_div){
            printf("/");
        }
        if(pointer->lex.type == BRACKET && pointer->lex.value.br == Bracket_open){
            printf("(");
        }
        if(pointer->lex.type == BRACKET && pointer->lex.value.br == Bracket_close){
            printf(")");
        }
        if(pointer->lex.type == First){
            printf(" F ");
        }
        if(pointer->lex.type == Last){
            printf(" L ");
        }
        pointer = pointer->next;
    }
}

struct Lexem_list * getRPN(struct Lexem_list* input){
    struct Lexem_list *stack = (struct Lexem_list*)malloc(sizeof(struct Lexem_list));
    struct Lexem_list *rpn = (struct Lexem_list*)malloc(sizeof(struct Lexem_list));
    stack->lex.type = Last;
    rpn->lex.type = First;
    rpn->next = 0;
    struct Lexem l, last_steck, forpop;
    last_steck.type = Last;
    last_steck.priority = 1;
    l.type = First;
    while(l.type != Last){
        l = pop(&input);
        if(l.type == NUMBER){
            push(&rpn,l);
        }
        if(l.type == OPERATION){
            while(last_steck.priority >= l.priority){
                push(&rpn,forpop = pop(&stack));
                last_steck = stack->lex;
            }
            push(&stack,l);
            last_steck = stack->lex;
        }
        if(l.type == BRACKET && l.value.br == Bracket_open){
            push(&stack,l);
            last_steck = stack->lex;
        }
        if(l.type == BRACKET && l.value.br == Bracket_close){
            while(last_steck.type != BRACKET || last_steck.value.br != Bracket_open){
                push(&rpn,pop(&stack));
                last_steck = stack->lex;
            }
            pop(&stack);
            last_steck = stack->lex;
        }
    }
    printf("\n!-----------------------------!\n");
    while(last_steck.type != Last){
        push(&rpn,forpop = pop(&stack));
        last_steck = stack->lex;
    }
    rpn = reverse(rpn);
    free(stack);
    return rpn;
}

struct calc_answer calc(struct Lexem_list * rpn){
    struct calc_answer c_a;
    c_a.error = 0;
    struct Lexem_list * pointer = rpn;
    struct Lexem_list * stack = (struct Lexem_list*)malloc(sizeof(struct Lexem_list));
    struct Lexem l;
    struct Lexem left;
    struct Lexem right;
    stack->next = 0;
    stack->lex.type = Last;
    printf("\n!-----------------------------!\n");
    while(pointer != 0){
        l = pop(&pointer);
        if(l.type == NUMBER){
            push(&stack,l);
        }
        if(l.type == OPERATION){
            if(stack->lex.type != Last){
                right = pop(&stack);
            } else{
                c_a.error = 3;
                free(stack);
                return c_a;
            }
            if(stack->lex.type != Last){
                left = pop(&stack);
            } else{
                c_a.error = 3;
                free(stack);
                return c_a;
            }
            if(right.type != NUMBER || left.type != NUMBER){
                c_a.error = 1;
                free(stack);
                return c_a;
            }
            if(l.value.op == OP_minus){
                right.value.num_value = left.value.num_value - right.value.num_value;
                push(&stack,right);
            }
            if(l.value.op == OP_plus){
                right.value.num_value = left.value.num_value + right.value.num_value;
                push(&stack,right);
            }
            if(l.value.op == OP_multi){
                right.value.num_value = left.value.num_value * right.value.num_value;
                push(&stack,right);
            }
            if(l.value.op == OP_div){
                if(right.value.num_value == 0.0){
                    c_a.error = 2;
                    free(stack);
                    return c_a;
                }
                right.value.num_value = left.value.num_value / right.value.num_value;
                push(&stack,right);
            }
        }
    }
    c_a.res = pop(&stack).value.num_value;
    free(stack);
    return c_a;
}

int main(){
    while(1){
        struct Lexem_list *input = getLexemList();
        if(input == 0){
            printf("incorrect bracket\n");
            return 0;
        }
        struct Lexem_list *rpn = getRPN(input); 
        printlist(rpn);
        struct calc_answer ans = calc(rpn);
        if(ans.error == 0){
            printf("ANSWER : %f\n", ans.res);
        } else{
            switch(ans.error){
                case 1: printf("no operator\n"); break;
                case 2: printf("div on 0\n"); break;
                case 3: printf("cant read operator\n"); break;
            }
            return 0;
        }
    }
    return 0;
}