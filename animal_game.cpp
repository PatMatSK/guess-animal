#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Tnode
{
    char * question;
    char * res_true;
    char * res_false;
    struct Tnode * next_true;
    struct Tnode * next_false;
}TNODE;

typedef struct tree
{
    TNODE * start;
}TREE;

void del_it( TNODE * tipec )
{
    if ( tipec->next_true )
        del_it(tipec->next_true);
    if ( tipec->next_false )
        del_it(tipec->next_false);
    if ( tipec->res_true )
        free(tipec->res_true);
    if ( tipec->res_false )
        free(tipec->res_false);
    free(tipec->question);
    free(tipec);
    tipec = NULL;
}

int intro()
{
    char x;
    printf("Isto uhadnem na aké zviera myslíš.\nZahráme si?(a/n):\n");
    if (scanf ("%c",&x) != 1 )
        return 0;
    if ( x == 'n')
        return 0;
    printf("Mysli na hociaké zviera.\n\n");
    return 1;
}

TREE setup()
{
    TREE data;
    TNODE * nepal = (TNODE*) malloc (sizeof(TNODE));
    nepal->next_false = NULL;
    nepal->next_true = NULL;
    nepal->question = strdup("lieta");
    nepal->res_false = strdup ("pes");
    nepal->res_true = strdup("vtak");
    data.start = nepal;
    return data;
}

int onemore()
{
    char x;
    printf("Dáme ešte jednu(a/n)?\n");
    if (scanf(" %c", &x) != 1)
        return 0;
    if ( x == 'a')
    {
        printf("\nLetsgooooo\n\n");
        return 1;
    }
    printf("okey suchar\n");
    return 0;
}

TNODE * createone()
{
    TNODE * nepal = (TNODE*)malloc(sizeof(TNODE));
    nepal->next_false = NULL;
    nepal->next_true = NULL;
    nepal->question = NULL;
    nepal->res_false = NULL;
    nepal->res_true = NULL;
    return nepal;
}

char * difference ( TNODE ** tibet , char * novacik, TNODE ** zelenac , int statement )
{
    char * medziclanok;
    if (statement) {
        printf("Akú otazku by si sa opýtal, aby si rozlíšil %s a %s?\n", novacik, (*tibet)->res_true);
        medziclanok = strdup((*tibet)->res_true);
        free((*tibet)->res_true);
        (*tibet)->res_true = NULL;
        (*tibet)->next_true = *zelenac;
    } else {
        printf("Akú otázku by si sa opýtal, aby si rozlíšil %s a %s?\n", novacik, (*tibet)->res_false);
        medziclanok = strdup((*tibet)->res_false);
        free((*tibet)->res_false);
        (*tibet)->res_false = NULL;
        (*tibet)->next_false = *zelenac;
    }
    return medziclanok;
}

char getquestion( TNODE ** zelenac,char * novacik )
{
    char x;
    char ques[30];
    fgets(ques,30,stdin);
    ques[strlen(ques)-1] = '\0';
    (*zelenac)->question = strdup(ques);
    printf("%s %s(a/n)?\n", novacik, ques );
    scanf(" %c", &x);
    return x;
}

void addhim( char * novacik, TNODE ** tibet , int statement )
{
    TNODE * zelenac = createone();
    char * medziclanok = difference(tibet,novacik,&zelenac,statement);
    char x = getquestion(&zelenac, novacik);

    if ( x == 'a')
    {
        zelenac->res_true = strdup(novacik);
        zelenac->res_false = medziclanok;
    }
    else
    {
        zelenac->res_false = strdup(novacik);
        zelenac->res_true = medziclanok;
    }
}


int findend( TNODE ** tibet , char * zviera  , int statement)
{
    char x;
    printf("Je to %s?\n",zviera );
    if ( scanf(" %c",&x) != 1 )
        return 0;
    if ( x == 'a' )
    {
        printf("Ja som ale macher, to si nečakal čo?\n");
        return onemore();
    }
    else
    {
        char y;//sluzi na newline
        char animal[20];
        printf("Čožeeee? Tak to si ma dostal, čo to bolo?\n");
        scanf(" %19s", animal);
        printf("Chceš moju databázu obohatit o tvoje zviera?(a/n)\n");
        scanf(" %c%c",&x,&y);
        if ( x == 'a' )
            addhim(animal, tibet, statement);
        return onemore();
    }
}

int riesimneriesim( TNODE ** tibet, int statement )
{
    if ( statement )
    {
        if ((*tibet)->res_true == NULL )
            return 2;
        else
            return findend(tibet, (*tibet)->res_true, 1);
    }
    else
    {
        if ((*tibet)->res_false == NULL )
            return 3;
        else
            return findend(tibet, (*tibet)->res_false, 0);
    }
}

int ask ( TNODE ** tibet )
{
    char x;
    printf("%s?(a/n)\n",(*tibet)->question);
    if ( scanf(" %c",&x) != 1 )
        return 0;
    if ( x =='a')
        return riesimneriesim(tibet,1);
    else
        return riesimneriesim(tibet,0);
}


int main ( void )
{
    int game = intro();
    TREE data = setup();
    TNODE ** tibet = &(data.start);
    while( game )
    {
        int statement = ask(tibet);
        switch ( statement )
        {
            case 1: tibet = &(data.start); break;
            case 2: tibet = &(*tibet)->next_true; break;
            case 3: tibet = &(*tibet)->next_false; break;
            default: game = 0; break;
        }
    }
    del_it(data.start);

    return 0;
}
