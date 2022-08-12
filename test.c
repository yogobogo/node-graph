#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    //structure of the node
    int num_of_links;                   //contains the number of structure connected to the node
    struct element *links;              //contains hashmapk to all the nodes linked to the node
    char *content;                      //contains the text of the node  
    char *title;                        //contains the title of the node
    int position;
};

struct element
{
    char *name_of_element;
    struct node *element_of_element;
    
};

void setup_node(struct node *target);
void link_node_to_another(struct node *base,char target[],int choice);
void write_on_node(struct node *target, char phrase[],int choice);
struct node *(create_node)(char tit[]);
void delete_node(struct node *target);
void change(struct node **p, struct node *escape);

#define MAX_HASH_SIZE 64
#define MAX_TITLE     24


struct element *hashmap[MAX_HASH_SIZE] = {0}; // WTF?
int hash_size = 0;

int main(int argc, char** argv)
{
    /*
    printf("██████╗░░█████╗░██████╗░███╗░░██╗░█████╗░██████╗░\n");
    printf("██╔══██╗██╔══██╗██╔══██╗████╗░██║██╔══██╗██╔══██╗\n");
    printf("██████╦╝██║░░██║██████╦╝██╔██╗██║██║░░██║██║░░██║\n");
    printf("██╔══██╗██║░░██║██╔══██╗██║╚████║██║░░██║██║░░██║\n");
    printf("██████╦╝╚█████╔╝██████╦╝██║░╚███║╚█████╔╝██████╔╝\n");
    printf("╚═════╝░░╚════╝░╚═════╝░╚═╝░░╚══╝░╚════╝░╚═════╝░\n");
    printf("\n\n\n");
    */
    
    int input_choice = 0; // FIXED
    char input_title[MAX_TITLE+1] = {0}; // FIXED
    //char *input_content = NULL; // FIXED
    struct node *viewer = (struct node*) calloc(1,sizeof(struct node));
    
    
    setup_node(viewer);
    
    while(1)
    {
        printf("\nCURRENT NODE:\n\n%.30s\n",viewer->title);
        printf("\ncontent:\n\n%s\n\n\n",viewer->content);
        
        while(1)
        {
           
            printf("choose from the following options\n\n");
            printf("[1] create node\n");
            printf("[2] destroy node\n");
            printf("[3] link node\n");
            printf("[4] global list\n");
            printf("[5] local list\n");
            printf("[6] go to linked node\n");
            scanf("%d", &input_choice);
            if (input_choice > 6 || input_choice < 1)
            {
                printf("invalid input...\n\n");
            }
            else
            {
                switch(input_choice)
                {
                    case 1:
                        
                        while(1)
                        {
                            printf("title of the new node[max 20 characters and no spaces]:\n\n");
                            scanf("%24s", input_title);
                            if(strlen(input_title)>20) // FIXED
                            {
                                printf("error\n");
                                
                            }
                            else
                            {
                                printf("\ndebug:continue\n");
                                break;
                            }
                        }
                        
                        viewer = create_node(input_title);
                        break;
                    case 2:
                        if(hashmap[(viewer->position)-1]!= NULL)
                        {
                            printf("\ndebug:-1\n");
                            
                            printf("\ndebug:escape pointer      %.25s\n",hashmap[((viewer->position)-1)]->element_of_element->title);
                            delete_node(viewer);
                            change(&viewer,(hashmap[(viewer->position)-1]->element_of_element));
                        }
                        else if(hashmap[(viewer->position)+1]!= NULL)
                        {
                            printf("debug:+1");
                            printf("\ndebug:escape pointer      %.25s\n",hashmap[((viewer->position)+1)]->element_of_element->title);
                            delete_node(viewer);
                            change(&viewer,(hashmap[(viewer->position)+1]->element_of_element));
                        }
                        else
                        {
                            printf("you cannot delete this");
                            break;
                        }
                        
                    case 3:break;
                    case 4:
                        for(int i= 1; i <= hash_size;i++)
                        {
                            printf("%.5d---%.24s\n",i,hashmap[i]->element_of_element->title);
                            printf("     ---%.24x\n",hashmap[i]->element_of_element);
                        }
                        break;
                    case 5:
                        for(int i= 0; i < viewer->num_of_links;i++)
                        {
                            printf("---%.24s\n",((viewer -> links)+i)->name_of_element);
                        }
                        break;
                    case 6:
                        break;
                        
                }
                break; 
            }
        }

    }
    return 0;
}


void setup_node(struct node *target)
{
    ++hash_size;
    printf("\ndebug:before setup_node\n");
    //function to setup the node
    target -> content = (char *) calloc(1,sizeof(char)*6);
    strcpy(target->content, "empty");
    
    target -> title = (char *) calloc(1,sizeof(char)*6);
    strcpy(target->title, "empty");
    
    target -> num_of_links = 0;

    //add the node to the hashmap and increase the global node counter
    hashmap[hash_size] = (struct element*) calloc(1,sizeof(struct element));
    
    //hashmap[hash_size] -> element_of_element = (struct node*) calloc(1,sizeof(struct node));
    
    hashmap[hash_size] -> element_of_element = target;
    hashmap[hash_size] -> name_of_element    = (char*) calloc(1,sizeof(char)*6);
    
    strcpy(hashmap[hash_size] -> name_of_element,target->title);
    
    
    
    //stores the position of the node in the hashmap
    
    target -> position = hash_size;
    
    assert(hash_size < MAX_HASH_SIZE);
}

void link_node_to_another(struct node *base, char* target, int choice)
{
    
    //function to link a node to others nodes
    struct element *tmp_target    = NULL; // FIXED
    struct element *tmp_base_link = NULL; // FIXED
    struct element *tmp_garbage   = NULL; // FIXED
    char tmp_garbage_name[sizeof(((base -> links + (base -> num_of_links)) -> name_of_element))]; // WTF?!
    int tracker = 0; // FIXED
    
    const size_t target_size = strlen(target)+1;
    
    char* tmp = (char*) calloc(1, target_size); // FIXED
    
    //copies the string in another array
    for(int i = 0; i < target_size; ++i) // FIXED
    {
        tmp[i] = (char) (choice+i); // WHY? this copy int binary into a char??? ITOA() instead?
    }

    for(int i; i <= sizeof((base -> links + (base -> num_of_links)) -> name_of_element);i++)
    {
        tmp_garbage_name[i]=*(((base -> links + (base -> num_of_links)) -> name_of_element)+i);
    }
    
    //find the element with the name
    for(int i = 0; i <= hash_size+1 && i < MAX_HASH_SIZE; ++i) // FIXME buffer overflow ?!
    {
        if (i < hash_size)
        {
        if(hashmap[i]->name_of_element == tmp) // COMPARING POINTERS WTF?! strcmp() ?!
            {
                tmp_target = hashmap[i];
                break;
            }
        }
        else
        {
            printf("\nthere is no such element in the global list\n");
        }
    }
    for(int i = 0; i <= (base -> num_of_links)+1 ; ++i) // FIXMED buffer overflow
    {
        if(i < base -> num_of_links)
        {
        if(tmp_garbage_name == ((base -> links)+i)->name_of_element)
            {
                tmp_garbage = ((base -> links)+i);
                tracker = i;
                break;
            }
        }
        else
        {
            printf("\nthere is no such element in the links list\n");
        }
    }


    switch(choice)
    {
        printf("\ndebug:switch\n");
        case 1:
            ++base -> num_of_links; // FIXED
            base -> links = realloc(base->links,sizeof(struct element)*base->num_of_links);
            tmp_base_link = base -> links + (base -> num_of_links);
            tmp_base_link = tmp_target;
            printf("\ndebug:succesfully linked :)\n");
            break;
        case 2:
            free((base -> links)+tracker); // WTF !?
            ++tracker;
            for(int i = tracker; i<=base -> num_of_links;++i)  // FIXED
            {
                // FIXME why --i and i
                memcpy((base -> links)+(--i),(base -> links)+(i),sizeof(struct element));
                free((base -> links)+i);
            }
            break;
        default:
            printf("\nerror: invalid choice :(\n");
            break;
    }

    free(tmp);
}

void write_on_node(struct node *target, char* phrase, int choice)
{
    //function to write the title or the content (text) of the selected node
    switch(choice)
    {
        case 2:     
            target -> content = (char *) realloc(target -> content, strlen(phrase) + 1); // FIXED
            strcpy(target->content, phrase);
            printf("\ncontent:\n%s \n\n",target -> content);
            break;
        case 1:
            target -> title = (char *) realloc(target -> title, strlen(phrase) + 1); // FIXED
            strcpy(target->title, phrase);
            printf("\ntitle:\n%s \n\n",target -> title); 
            break;
        default:
            printf("\nerror: invalid choice\n");
            break;
    }
   
}

struct node* create_node(char* title)
{
    //create a lil node
    printf("\ndebug:uccesful\n");
    
    struct node *tmp = (struct node *) calloc(1, sizeof(struct node));
    printf("\ndebug:create tmp = succesful\n");
    setup_node(tmp);
    printf("\ndebug:after setup_node\n");
    tmp -> title = (char *) realloc(tmp -> title, strlen(title)+ 1);    //FIXED

    strcpy(tmp -> title , title);
    printf("\ndebug:1\n");
    return tmp;
    printf("\ndebug:2\n");
}

void delete_node(struct node *target)
{
    //obliterate the node from existence and fill the empty space in the hashmap
    int tmp = target -> position;
    printf("\n-------------------------------------------------------\n");
    printf("\nhasmap[tmp-1]:\n");
    printf("\n\tname:%.23s\n",hashmap[tmp-1]->element_of_element->title);
    printf("\n\tpointer:%.16x\n");
    printf("\nhasmap[tmp]:\n");
    printf("\n\tname:%.23s\n",hashmap[tmp]->element_of_element->title);
    printf("\n\tpointer:%.16x\n");
    
    printf("\n-------------------------------------------------------\n");

    free(hashmap[tmp]);
    tmp++;
    for(int i = tmp,b = 0; i<=hash_size;++i) // BUFFER OVERFLOW
    {
        b = i -1;
        hashmap[i] = NULL;
        // Why i-- and i
        memcpy(hashmap[b],hashmap[i],sizeof(struct element));
        hashmap[i] = NULL; 
        free(hashmap[i]);
    }
    hash_size--;
}
void change(struct node **p, struct node *escape)
{
    *p = escape;
}
