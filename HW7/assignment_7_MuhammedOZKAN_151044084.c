/*************************************************************************************/
/*                               GEBZE TECHNICAL UNIVERSITY                          */
/*                                  COMPUTER ENGINEERING                             */
/*                                     Muhammed OZKAN                                */
/*                                        151044084                                  */
/*                                muhammedozkan@gtu.edu.tr                           */
/*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT 0;
#define AND 1;
#define OR 2;
#define NOT 3;
#define FLIPFLOP 4;

typedef struct
{
    int value;
} input_t;

typedef struct
{
    int a;
    int b;
    int out;
} and_t;

typedef struct
{
    int a;
    int b;
    int out;
} or_t;

typedef struct
{
    int a;
    int out;
} not_t;

typedef struct
{
    int a;
    int former_out;
    int out;
    int execount;
    int execountsave;
} flipflop_t;

typedef union {
    input_t input;
    and_t and;
    or_t or ;
    not_t not;
    flipflop_t flipflop;
} gate_t;

typedef struct node_s
{
    char id[64];
    int type;
    char aorb;
    gate_t gate;
    struct node_s *next_node;
} node_t;

int input_count = 0;
int node_count = 0;

node_t *input;
node_t *node;
node_t *out;

void setup(void);                                                  /*circuit dosyasini okuyarak logic devrenin baglantilari ve default degerlerinin verildigi yer*/
void out_detected(void);                                           /*devrenin cikis ucunun bulundugu fonksiyon*/
void print_list(node_t *head_p);                                   /*debug icin yazilmis printf fonk (programda kullanilmiyor)*/
int search_id(char *_data);                                        /*cikis kapisini bulurken dosyada arama yapan fonk*/
void save_out(char *_data);                                        /*cikis kapisinin kayit edilmesi*/
void execute_node(node_t *head_p, int _value, char _gate);         /*inputlarin tek tek linkedlist seklinde recursive sekilde isletildigi fonk*/
void print_result(void);                                           /*devrenin sonucunun ekrana basildigi fonk*/
void load_value(void);                                             /*inputlara input dosyasindan degerlerin yuklendigi fonk*/
int count_flipflop_execute(node_t *head_p, char *_id, int _count); /*inputlari calisma isleminde flipfloplardan kac kere gecildigi sayan fonksiyon*/
void save_count_flipflop(void);                                    /*flipflop kapisindaki formerout un ne zaman hesaplanmasi gerektigini bulmada kullanilan fonksiyon*/

void main(void)
{
    setup();

    save_count_flipflop();

    out_detected();
    load_value();

    free(input);
    free(node);
}

void save_count_flipflop(void)
{
    int count;
    for (int i = 0; i < node_count; i++)
    {
        if (node[i].type == 4)
        {
            count = 0;
            for (int k = 0; k < input_count; k++)
            {
                count = count_flipflop_execute(input + k, node[i].id, count);
            }
            node[i].gate.flipflop.execount = count;
            node[i].gate.flipflop.execountsave = count;
        }
    }
}

void print_result(void)
{

    if (out->type == 1)
    {
        /*printf("and %d %d \n", (out->gate.and.a),(out->gate.and.b));*/
        printf("%d\n", (out->gate.and.out));
    }
    if (out->type == 2)
    {
        /*printf("or %d %d \n", (out->gate.or.a),(out->gate.or.b));*/
        printf("%d\n", (out->gate.or.out));
    }
    if (out->type == 3)
    {
        printf("%d\n", (out->gate.not.out));
    }
    if (out->type == 4)
    {
        printf("%d\n", (out->gate.flipflop.out));
    }
}

void load_value(void)
{
    FILE *readfile;
    readfile = fopen("input.txt", "r");

    int status = 1, lock = 0;
    int data;

    while (1)
    {
        for (int i = 0; i < input_count; i++)
        {
            status = fscanf(readfile, "%d", &data);
            if (status == EOF)
            {
                lock = 1;
                break;
            }
            else
            {
                /*printf("%d ",data);*/
                /* print_list(input + i);*/
                execute_node(input + i, data, ' ');
            }
        }
        if (lock == 1)
            break;

        print_result();
    }
    fclose(readfile);
}

int search_id(char *_data)
{
    int count = 0;

    FILE *readfile;
    readfile = fopen("circuit.txt", "r");

    int status;
    char data[64];

    while (1)
    {
        status = fscanf(readfile, "%s", &data);

        if (status == EOF)
        {
            break;
        }
        else
        {
            if (strcmp(data, _data) == 0)
                count++;
        }
    }
    fclose(readfile);
    /*printf("%d %s\n",count,_data);*/
    return count;
}

void out_detected(void)
{
    FILE *readfile;
    readfile = fopen("circuit.txt", "r");

    char data[64];
    fscanf(readfile, "%s", &data);
    /*printf("%s\n", data);*/

    for (int k = 0; k < input_count; k++)
    {
        fscanf(readfile, "%s", &data);
    }

    for (int i = 0; i < node_count; i++)
    {
        fscanf(readfile, "%s", &data);

        if (strcmp(data, "AND") == 0)
        {
            fscanf(readfile, "%s", &data);
            if (search_id(data) == 1)
                save_out(data);
            fscanf(readfile, "%s", &data);
            if (search_id(data) == 1)
                save_out(data);
            fscanf(readfile, "%s", &data);
            if (search_id(data) == 1)
                save_out(data);
        }
        else if (strcmp(data, "OR") == 0)
        {
            fscanf(readfile, "%s", &data);
            if (search_id(data) == 1)
                save_out(data);
            fscanf(readfile, "%s", &data);
            if (search_id(data) == 1)
                save_out(data);
            fscanf(readfile, "%s", &data);
            if (search_id(data) == 1)
                save_out(data);
        }
        else if (strcmp(data, "NOT") == 0)
        {
            fscanf(readfile, "%s", &data);
            if (search_id(data) == 1)
                save_out(data);
            fscanf(readfile, "%s", &data);
            if (search_id(data) == 1)
                save_out(data);
        }
        else if (strcmp(data, "FLIPFLOP") == 0)
        {
            fscanf(readfile, "%s", &data);
            if (search_id(data) == 1)
                save_out(data);

            fscanf(readfile, "%s", &data);
            if (search_id(data) == 1)
                save_out(data);
        }
    }
}

void save_out(char *_data)
{
    for (int i = 0; i < node_count; i++)
    {
        if (strcmp(node[i].id, _data) == 0)
        {
            out = &node[i];
            /*printf("  %s",out->id);*/
        }
    }
}

int count_flipflop_execute(node_t *head_p, char *_id, int _count)
{
    if (head_p == NULL)
    {
        return _count;
    }
    else
    {

        if (strcmp(head_p->id, _id) == 0)
            _count++;

        count_flipflop_execute(head_p->next_node, _id, _count);
    }
}

void print_list(node_t *head_p)
{
    if (head_p == NULL)
    {
        printf("\n");
    }
    else
    {
        printf("%s %d ", head_p->id, head_p->type);

        /*printf(" %c", head_p->aorb);*/

        /* if (head_p->type == 0)
            printf(" %d\n", head_p->gate.input.value);
        if (head_p->type == 1)
            printf(" %d\n", head_p->gate.and.out);
        if (head_p->type == 2)
            printf(" %d\n", head_p->gate.or.out);
        if (head_p->type == 3)
            printf(" %d\n", head_p->gate.not.out);
        if (head_p->type == 4)
            printf(" %d\n", head_p->gate.flipflop.out);*/

        print_list(head_p->next_node);
    }
}

void execute_node(node_t *head_p, int _value, char _gate)
{
    int value;

    if (head_p == NULL)
    {
    }
    else
    {
        if (head_p->type == 0)
        {

            head_p->gate.input.value = _value;
            value = head_p->gate.input.value;
        }
        else if (head_p->type == 1)
        {
            if (_gate == 'a')
            {
                head_p->gate.and.a = _value;
            }
            else if (_gate == 'b')
            {
                head_p->gate.and.b = _value;
            }

            head_p->gate.and.out = (int)(head_p->gate.and.a && head_p->gate.and.b);

            value = head_p->gate.and.out;
        }
        else if (head_p->type == 2)
        {
            if (_gate == 'a')
            {
                head_p->gate.or.a = _value;
            }
            else if (_gate == 'b')
            {
                head_p->gate.or.b = _value;
            }

            head_p->gate.or.out = (int)(head_p->gate.or.a || head_p->gate.or.b);

            value = head_p->gate.or.out;
        }
        else if (head_p->type == 3)
        {
            head_p->gate.not.a = _value;

            if (head_p->gate.not.a == 0)
                head_p->gate.not.out = 1;
            else
                head_p->gate.not.out = 0;

            value = head_p->gate.not.out;
        }
        else if (head_p->type == 4)
        {
            head_p->gate.flipflop.a = _value;
            head_p->gate.flipflop.execount--;

            if (head_p->gate.flipflop.a == head_p->gate.flipflop.former_out)
            {
                head_p->gate.flipflop.out = 0;
            }
            else
            {
                head_p->gate.flipflop.out = 1;
            }
            if (head_p->gate.flipflop.execount == 0)
            {

                head_p->gate.flipflop.former_out = head_p->gate.flipflop.out;
                head_p->gate.flipflop.execount = head_p->gate.flipflop.execountsave;
            }
            value = head_p->gate.flipflop.out;

            /*printf("flip%s %d %d ",head_p->id,_value,value);*/
        }
        /*printf("%d ",value);
        printf("%s %c\n",head_p->id,head_p->aorb);*/
        execute_node(head_p->next_node, value, head_p->aorb);
    }
}

void setup(void)
{
    FILE *readfile;
    readfile = fopen("circuit.txt", "r");

    int status, lock = 0;
    char data1;
    char data[64];
    status = fscanf(readfile, "%s", &data);
    /*printf("%s\n", data);*/

    while (1)
    {
        status = fscanf(readfile, "%c", &data1);
        /*printf("%c", data1);*/
        if (status == EOF)
        {
            break;
        }
        else
        {
            if (data1 == ' ' && lock == 0)
                input_count++;
            if (data1 == '\n')
            {
                node_count++;
                lock = 1;
            }
        }
    }
    fclose(readfile);

    input = (node_t *)calloc(input_count, sizeof(node_t));
    node = (node_t *)calloc(node_count, sizeof(node_t));

    /* printf("\n%d\n", input_count);
    printf("%d", node_count);*/
    readfile = fopen("circuit.txt", "r");
    status = fscanf(readfile, "%s", &data);
    /*printf("%s\n", data);*/

    for (int k = 0; k < input_count; k++)
    {
        status = fscanf(readfile, "%s", &data);
        strcpy(input[k].id, data);
        input[k].type = INPUT;
        input[k].gate.input.value = 0;
    }

    int x;

    for (int i = 0; i < node_count; i++)
    {
        status = fscanf(readfile, "%s", &data);

        if (strcmp(data, "AND") == 0)
        {
            fscanf(readfile, "%s", &data);
            strcpy(node[i].id, data);
            node[i].type = AND;

            node[i].gate.and.a = 0;
            node[i].gate.and.b = 0;

            fscanf(readfile, "%s", &data);

            for (x = 0; x < input_count; x++)
            {
                if (strcmp(input[x].id, data) == 0)
                {
                    input[x].next_node = &node[i];
                    input[x].aorb = 'a';
                }
            }
            for (x = 0; x < node_count; x++)
            {
                if (strcmp(node[x].id, data) == 0)
                {
                    node[x].next_node = &node[i];
                    node[x].aorb = 'a';
                }
            }

            fscanf(readfile, "%s", &data);

            for (x = 0; x < input_count; x++)
            {
                if (strcmp(input[x].id, data) == 0)
                {
                    input[x].next_node = &node[i];
                    input[x].aorb = 'b';
                }
            }
            for (x = 0; x < node_count; x++)
            {
                if (strcmp(node[x].id, data) == 0)
                {
                    node[x].next_node = &node[i];
                    node[x].aorb = 'b';
                }
            }
        }
        else if (strcmp(data, "OR") == 0)
        {
            fscanf(readfile, "%s", &data);
            strcpy(node[i].id, data);
            node[i].type = OR;

            node[i].gate.or.a = 0;
            node[i].gate.or.b = 0;

            fscanf(readfile, "%s", &data);
            for (x = 0; x < input_count; x++)
            {
                if (strcmp(input[x].id, data) == 0)
                {
                    input[x].next_node = &node[i];
                    input[x].aorb = 'a';
                }
            }
            for (x = 0; x < node_count; x++)
            {
                if (strcmp(node[x].id, data) == 0)
                {
                    node[x].next_node = &node[i];
                    node[x].aorb = 'a';
                }
            }
            fscanf(readfile, "%s", &data);
            for (x = 0; x < input_count; x++)
            {
                if (strcmp(input[x].id, data) == 0)
                {
                    input[x].next_node = &node[i];
                    input[x].aorb = 'b';
                }
            }
            for (x = 0; x < node_count; x++)
            {
                if (strcmp(node[x].id, data) == 0)
                {
                    node[x].next_node = &node[i];
                    node[x].aorb = 'b';
                }
            }
        }
        else if (strcmp(data, "NOT") == 0)
        {
            fscanf(readfile, "%s", &data);
            strcpy(node[i].id, data);
            node[i].type = NOT;

            node[i].gate.not.a = 0;

            fscanf(readfile, "%s", &data);
            for (x = 0; x < input_count; x++)
            {
                if (strcmp(input[x].id, data) == 0)
                {
                    input[x].next_node = &node[i];
                    input[x].aorb = 'a';
                }
            }
            for (x = 0; x < node_count; x++)
            {
                if (strcmp(node[x].id, data) == 0)
                {
                    node[x].next_node = &node[i];
                    node[x].aorb = 'a';
                }
            }
        }
        else if (strcmp(data, "FLIPFLOP") == 0)
        {
            fscanf(readfile, "%s", &data);
            strcpy(node[i].id, data);
            node[i].type = FLIPFLOP;

            node[i].gate.flipflop.a = 0;
            node[i].gate.flipflop.former_out = 0;
            node[i].gate.flipflop.execount = 0;
            node[i].gate.flipflop.execountsave = 0;

            fscanf(readfile, "%s", &data);
            for (x = 0; x < input_count; x++)
            {
                if (strcmp(input[x].id, data) == 0)
                {
                    input[x].next_node = &node[i];
                    input[x].aorb = 'a';
                }
            }
            for (x = 0; x < node_count; x++)
            {
                if (strcmp(node[x].id, data) == 0)
                {
                    node[x].next_node = &node[i];
                    node[x].aorb = 'a';
                }
            }
        }
    }
    fclose(readfile);
}