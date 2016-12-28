#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ENTER 13
#define ESC 27
#define DEL 83
#define DELETE 8
struct n/*Saving elements page by page*/
{
    char x;
    struct n *next;
    struct n *prev;
    int number;
    int pager;
};
typedef struct n node;

struct secondN/*Copied elements*/
{
    char x;
    struct secondN *next;
    struct secondN *prev;
};
typedef struct secondN sNode;
node *r=NULL;
node *iter = NULL;
node *last = NULL;
node *element1 = NULL;
node *element2 = NULL;

sNode *root = NULL;
sNode *lastC=NULL;

int wordNumber = 1;
int lineNumber;
int iteratorsLineNumber=1;
int pageNumber = 1;
int delCounter = 0;
char* fileName="New File";

void mainMenu();
void editMode();
void writeOnScreen();
void help();
void loadFile();
void saveFile();

int main()
{
    system("COLOR F0");
    mainMenu();
    return 0;
}

void editMode()
{
    if(r == NULL) printf("WRITE HERE");
    else writeOnScreen();

    int ch;
    int i;
    int keycode;

    while(1)
    {
emptyList:
        ch=getch();
        keycode=0;
        if((ch==0 || ch == 0xe0 )&& r!=NULL)
        {
            keycode=1;
            ch=getch();
        }
        switch(ch)
        {
            if(keycode == 0)
            {
            default:
addChar:
                if(delCounter!=0)
                    goto copyPaste;
                for(i=' '; i<'}'; i++)
                {
                    if(i == ch)
                    {
lineBreak:
                        if(r == NULL)//If our list is empty...
                        {

                            r=(node*)malloc(sizeof(node));
                            r->x= i;
                            r->next = NULL;
                            r->prev = (node*)malloc(sizeof(node));
                            r->prev->next = r;
                            iter = r;
                            last = r;
                            system("cls");
                            writeOnScreen();
                        }
                        else if(iter == last)
                        {
                            node* temp =(node*)malloc(sizeof(node));
                            temp -> x = i;
                            temp -> prev = last;
                            last -> next = temp;
                            temp ->next = NULL;
                            last = temp;
                            iter = last;
                            system("cls");
                            writeOnScreen();
                        }
                        else if(iter == r)
                        {
                            node* temp =(node*)malloc(sizeof(node));
                            temp -> x = i;
                            temp -> prev = r;
                            temp ->next = r->next;
                            r -> next = temp;
                            iter = temp;
                            system("cls");
                            writeOnScreen();
                        }
                        else if(iter->prev != NULL && iter -> next != NULL)
                        {
                            node* temp =(node*)malloc(sizeof(node));
                            temp -> x = i;
                            temp -> prev = iter;
                            temp->next = iter->next;
                            iter->next->prev = temp;
                            iter -> next = temp;
                            iter=temp;
                            system("cls");
                            writeOnScreen();
                        }
                        if(r->prev == iter)
                        {
                            node* temp =(node*)malloc(sizeof(node));
                            temp -> x = i;
                            temp -> next = r;
                            r -> prev = temp;
                            temp ->prev = (node*)malloc(sizeof(node));
                            temp -> prev ->next = temp;
                            r=temp;
                            iter=r;
                            system("cls");
                            writeOnScreen();
                        }
                    }
                }
                break;
            }
            else
            {
            case DELETE:
            {
                if(r!=NULL && r->prev != iter)
                {
                    if(iter == last && iter != r)
                    {
                        node* temp= iter;
                        last = temp->prev;
                        temp->prev->next = NULL;
                        iter = last;
                        free(temp);
                        system("cls");
                        writeOnScreen();
                    }
                    else if(iter == r && iter->next != NULL)
                    {
                        node *temp =r->next;
                        temp->prev = r->prev;
                        r->prev->next = temp;
                        free(r);
                        r=temp;
                        iter=r->prev;
                        system("cls");
                        writeOnScreen();
                    }
                    else if(iter == r && iter->next ==NULL)
                    {
                        r=NULL;
                        iter=r;
                        system("cls");
                        goto emptyList;
                    }
                    else
                    {
                        node* temp= iter;
                        temp->prev->next=temp->next;
                        temp->next->prev=temp->prev;
                        iter = temp->prev;
                        free(temp);
                        system("cls");
                        writeOnScreen();
                    }
                }
            }
            break;
            case UP_ARROW:
                if(keycode==1 && iteratorsLineNumber != 1)
                {
                    while(iter->x != '\n')
                        iter=iter->prev;
                    iter = iter->prev;
                    system("cls");
                    writeOnScreen();
                }
                else if(keycode ==0)
                {
                    goto addChar;
                }
                break;
            case DOWN_ARROW:
                if(keycode==1 && iteratorsLineNumber != lineNumber)
                {
                    while(iter->x != '\n')
                        iter=iter->next;
                    iter = iter->next;
                    system("cls");
                    writeOnScreen();
                }
                else if(keycode ==0)
                {
                    goto addChar;
                }
                break;
            case LEFT_ARROW:
                if(keycode==1)
                {
                    if(iter->next != r)
                    {
                        iter = iter -> prev;
                        system("cls");
                        writeOnScreen();
                    }

                }
                else
                {
                    goto addChar;
                }
                break;
            case RIGHT_ARROW:
                if(keycode==1)
                {
                    if(iter -> next != NULL)
                    {
                        iter = iter -> next;
                        system("cls");
                        writeOnScreen();
                    }
                }
                else if(r!= NULL)
                {
                    goto addChar;
                }
                break;
            case ENTER:
                i='\n';
                goto lineBreak;
                break;
            case ESC:
                if(delCounter > 0)
                {
                    delCounter = 0;
                    system("cls");
                    writeOnScreen();
                    break;
                }
                system("cls");
                goto leftSwitch;
                break;
            case DEL:
                if(keycode == 1)
                {
                    switch(delCounter)
                    {
                    case 0:
                        element1=iter;
                        delCounter++;
                        system("cls");
                        writeOnScreen();
                        break;
                    case 1:
                        element2 = iter;
                        delCounter++;
                        system("cls");
                        writeOnScreen();
                        break;
                    }
                }
                else
                    goto addChar;

                break;
            }
        }
copyPaste:
        if(delCounter == 2 && (ch == 'c' || ch == 'C'))
        {
            if(root!= NULL)
            {
                sNode *y=root;
                while(y->next != NULL)
                {
                    sNode* temp = y;
                    y=y->next;
                    free(temp);
                }
            }
            root= (sNode*)malloc(sizeof(sNode));
            if(element1->number > element2->number)
            {
                element2=element2->next;
                node  *z = element2;
                sNode *y=root;

                while(z != element1)
                {
                    y->next = (sNode*)malloc(sizeof(sNode));
                    y->x = z->x;
                    y=y->next;
                    z =z->next;
                }
                y->x = element1->x;
                y->next= NULL;
                lastC=y;
            }
            else if(element1->number < element2->number)
            {
                element1=element1->next;
                node  *z = element1;
                sNode *y=root;

                while(z != element2)
                {
                    y->next = (sNode*)malloc(sizeof(sNode));
                    y->x = z->x;
                    y=y->next;
                    z =z->next;
                }
                y->x = element2->x;
                y->next= NULL;
                lastC=y;
            }
            delCounter=0;

        }

        if(delCounter == 2 && (ch == 'x' || ch == 'X'))
        {
            if(root!= NULL)
            {
                sNode *y=root;
                while(y->next != NULL)
                {
                    sNode* temp = y;
                    y=y->next;
                    free(temp);
                }
            }
            root= (sNode*)malloc(sizeof(sNode));
            if(element1->number > element2->number)
            {
                element2=element2->next;
                node  *z = element2;
                sNode *y=root;

                while(z != element1)
                {
                    y->next = (sNode*)malloc(sizeof(sNode));
                    y->x = z->x;
                    y=y->next;
                    z =z->next;
                }
                y->x = element1->x;
                y->next= NULL;
                lastC=y;
                if(element2 !=r && element1->next != NULL)
                {
                    element2->prev->next = element1->next;
                    element1->next->prev = element2->prev;
                }
                else if(element2 ==r && element1->next == NULL)/*If user cuts whole text*/
                {
                    iter=r;
                    while(iter->next != NULL)
                    {
                        node* temp = iter;
                        iter=iter->next;
                        free(temp);
                    }
                    r=NULL;
                    last=NULL;
                    system("cls");
                    delCounter=0;
                    editMode();/*List is empty.*/
                }
                else if(element2  == r && element1->next != NULL)
                {
                    element2->next = element1->next;
                    element1->next->prev = element2;
                    r=r->next;
                    iter=r;
                }
                else if(element2 != r && element1->next == NULL)
                {

                    element2->prev->next = element1->next;
                    last=element2->prev;
                }
                system("cls");
                delCounter=0;
                iter=last;
                writeOnScreen();
            }


            else if(element1->number < element2->number)
            {
                element1=element1->next;
                node  *z = element1;
                sNode *y=root;

                while(z != element2)
                {
                    y->next = (sNode*)malloc(sizeof(sNode));
                    y->x = z->x;
                    y=y->next;
                    z =z->next;
                }
                y->x = element2->x;
                y->next= NULL;
                lastC=y;


                if(element1 !=r && element2->next != NULL)
                {
                    element1->prev->next = element2->next;
                    element2->next->prev = element1->prev;
                    iter=element2->next;
                }
                else if(element1 ==r && element2->next == NULL)/*If user cuts whole text*/
                {
                    iter=r;
                    while(iter->next != NULL)
                    {
                        node* temp = iter;
                        iter=iter->next;
                        free(temp);
                    }
                    r=NULL;
                    last=NULL;
                    system("cls");
                    delCounter=0;
                    editMode();/*List is empty.*/
                }
                else if(element1  == r && element2->next != NULL)
                {
                    element1->next = element2->next;
                    element2->next->prev = element1;
                    r=r->next;
                    iter=r;
                }
                else if(element1 != r && element2->next == NULL)
                {

                    element1->prev->next = element2->next;
                    last=element1->prev;
                    iter=last;
                }
                system("cls");
                delCounter=0;
                writeOnScreen();
            }
            delCounter=0;
        }

        if(delCounter == 1 && (ch == 'v' || ch == 'V') )
        {

            if(iter == last)
            {
                sNode *y= root;
                while(y != NULL)
                {
                    iter->next =(node*)malloc(sizeof(node));
                    iter->next->x = y->x;
                    iter->next->prev=iter;
                    y=y->next;
                    iter=iter->next;
                }
                iter->next = NULL;
                last=iter;
                system("cls");
                delCounter=0;
                writeOnScreen();
            }

            else if(iter == r->prev)//CHECK IT OUT
            {
                sNode *y=root;

                node* temp =(node*)malloc(sizeof(node));
                temp -> x = y->x;
                temp -> next = r;
                r -> prev = temp;
                temp ->prev = (node*)malloc(sizeof(node));
                temp -> prev ->next = temp;
                r=temp;
                iter=r;
                y=root->next;
                while( y!= NULL)
                {

                    temp =(node*)malloc(sizeof(node));
                    temp -> x = y->x;
                    temp -> prev = iter;
                    temp->next = iter->next;
                    iter->next->prev = temp;
                    iter -> next = temp;
                    iter=temp;
                    y=y->next;
                }

                delCounter=0;
                system("cls");
                writeOnScreen();

            }
            else
            {
                sNode *y=root;
                while(y != NULL)
                {
                    node* temp =(node*)malloc(sizeof(node));
                    temp -> x = y->x;
                    temp -> prev = iter;
                    temp->next = iter->next;
                    iter->next->prev = temp;
                    iter -> next = temp;
                    iter=temp;
                    y=y->next;
                }
                system("cls");
                delCounter=0;
                writeOnScreen();
            }
        }

    }
leftSwitch:

    mainMenu();
}

void saveFile()
{
    fileName=malloc(sizeof(char)*16);
    printf("Enter file name: ");
    scanf("%s",fileName);
    FILE* saveFile = fopen(fileName,"w");

    iter=r;
    while(iter != last)
    {
        fputc(iter->x,saveFile);
        iter=iter->next;
    }
    fputc(last->x,saveFile);/*We can't access last value of linked list via while loop*/
    printf("File saved as %s.\n\n",fileName);
    fclose(saveFile);
    mainMenu();
}
void loadFile()
{
    if(r != NULL)/*Clear list*/
    {
        iter=r;
        while(iter != last)
        {
            node* temp = iter;
            iter=iter->next;
            free(temp);
        }
        r=NULL;
        last= NULL;
    }
    fileName=malloc(sizeof(char)*16);
    printf("Enter file name: ");
    scanf("%s",fileName);
    FILE *openFile = fopen (fileName, "r");
    while(!feof(openFile))
    {
        if(r == NULL)/*First process*/
        {
            r=(node*)malloc(sizeof(node));
            r->x = fgetc(openFile);
            r->next = NULL;
            r->prev = (node*)malloc(sizeof(node));
            r->prev->next = r;
            iter = r;
            last = r;
        }
        else
        {
            node* temp =(node*)malloc(sizeof(node));
            temp -> x = fgetc(openFile);
            temp -> prev = last;
            last -> next = temp;
            temp ->next = NULL;
            last = temp;
            iter = last->prev;
        }
    }
    printf("File loaded.\n\n");
    fclose(openFile);
    mainMenu();
}
void writeOnScreen()
{
    wordNumber=1;
    r->pager = 1;
    iteratorsLineNumber=1;
    lineNumber=1;
    int flag=0;
    int prev=-1;
    node *y = r;
    if(r->prev == iter)
        printf("|");

    node *z = r;
    if(iter != r->prev)
        while(z != iter)
        {
            if(z -> x == '\n')
                iteratorsLineNumber++;
            z = z-> next;
        }
    pageNumber = (iteratorsLineNumber/21) +1;
    if(pageNumber != prev)
    {
        flag=1;
    }
    else
        flag=0;
    prev= pageNumber;

    while(y !=  NULL)
    {
        if(y-> x == '\n')
        {
            lineNumber++;
        }

        if(lineNumber % 21 == 0 && flag == 1)
            y->pager = (lineNumber /21) +1;
        else if(y != r)
            y->pager = -1;

        y = y -> next;
    }
    y=r;
    while(y && y->pager != pageNumber)
    {
        y=y->next;
    }
    while(y && y->pager != pageNumber+1  )
    {
        printf("%c",y->x);
        if(y == iter && r->prev != iter)
        {
            printf("|");
        }
        y=y->next;
    }
    y=r;
    while(y)
    {
        y->number = wordNumber;
        wordNumber++;
        y=y->next;
    }
    r->prev->number=0;
    if(delCounter > 0)
    {
        if(delCounter == 1)
            printf("\n\n\n\n\n\n\t\t\t\t\tPres 'V' to paste or choose another element. Press ESC to leave.");
        if(delCounter == 2)
            printf("\n\n\n\n\n\n\t\t\t\t\tPress 'C' to copy or press 'X' to cut. Press ESC to leave.");
        printf("\n\t\t\t\t\t\tPage:%d\n\t\t\t\t\t\tFile:%s",pageNumber,fileName);
    }
    else
    printf("\n\n\n\n\n\n\n\t\t\t\t\t\tPage:%d\n\t\t\t\t\t\tFile:%s",pageNumber,fileName);
}
void mainMenu()
{
    int option=-1;

    while(option<0 || option >4)
    {
        printf("1-Edit/New File \n2-Load File\n3-Save File\n4-Help\n");
        printf("Enter your choice: ");
        scanf("%d",&option);
    }
    switch(option)
    {
    case 1:
        system("cls");
        editMode();
        break;
    case 2:
        loadFile();
        break;
    case 3:
        saveFile();
        break;
    case 4:
        help();
        break;
    }
}
void help()
{
    system("cls");
    printf("+ You can edit your file in edit mode.\n+ You can load exist file in load mode.\n+ You can save file which you created or edited.\n+ Press ESC to leave edit mode.\n+Press delete to do copy/paste/cut ");
    printf("\n\nPress enter to return main menu.");
    int ch;
    while(1)
    {
        ch=getch();
        if(ch == 0 || ch == 0xE0)
        {
            ch=getch();

        }
        if(ch==13)
        {
            system("cls");
            mainMenu();
        }
        else
            continue;
    }
}
