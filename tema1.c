/* THEODHORAQ Mihallari - 313CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {              //listă standard dublu standard    
    char data;
    struct node *next;
    struct node *prev;
} node;

typedef struct TDoubleLinkedList {
    node *head;
    node *tail;
    int len;
} TDoubleLinkedList;

void initializeList(TDoubleLinkedList *list) {   //funcția de inițializare a listei de maximum 
                                                  //100 de caractere cu caractere nule
    int i;
    for (i = 0; i < 100; i++) {
        node *new_node = (node *) malloc(sizeof(node));
        new_node->data = '\0';
        new_node->next = NULL;
        new_node->prev = NULL;

        if (list->head == NULL) {
            list->head = new_node;
            list->tail = new_node;
        } else {
            list->tail->next = new_node;
            new_node->prev = list->tail;
            list->tail = new_node;
        }
        list->len++;
    }
}
void moveRight(int *curr_pos, TDoubleLinkedList *list) {
    (*curr_pos)++;                     //functie pentru positia sa merg la dreapta
    if (*curr_pos >= list->len) {
        *curr_pos = list->len - 1;
    }
    list->len++;
}

void moveLeft(int *curr_pos, TDoubleLinkedList *list) {
    (*curr_pos)--;                    //functie pentru positia sa merg la stanga
    if (*curr_pos < 0) {
        *curr_pos = 0;
    }
    list->len--;
}
void write(char overwrite_char, int curr_pos, TDoubleLinkedList *list) {
    node *curr = list->head;
    int j;
    for (j = 0; j < curr_pos; j++) {   //Funcția inițializează mai întâi un pointer numit „curr”
                                        // la capul listei dublu legate. Apoi parcurge lista până ajunge
                                        // la nodul din poziția „curr_pos” și o suprascrie 
          curr = curr->next;
    }

    if (curr != NULL) {
        curr->data = overwrite_char;
    } else {
        node *new_node = (node *) malloc(sizeof(node));
        new_node->data = overwrite_char;
        new_node->next = NULL;
        new_node->prev = NULL;

        if (curr_pos == 0) {
            new_node->next = curr;
            curr->prev = new_node;
            list->head = new_node;
        } else if (curr_pos == list->len) {
            curr->next = new_node;
            new_node->prev = curr;
            list->tail = new_node;
        } else {
            new_node->prev = curr->prev;
            new_node->next = curr;
            curr->prev->next = new_node;
            curr->prev = new_node;
        }

        list->len++;
    }
}
void show(TDoubleLinkedList *list,int num_of_mr, FILE *out_file){
    node *curr = list->head;
    int k;
    int w = list->len - 100;

    for (k=0;k<num_of_mr;k++) {  //funcție simplă de a afișa lista, printr-o buclă se ajunge la extrema
                                // listei și dacă „\0” se afișează #, de asemenea, se tipărește poziția curentă în interior | |
        if (k == w) {
            if(curr->data=='\0'){
                fprintf(out_file, "|#|");
            } else{
                fprintf(out_file, "|%c|", curr->data);
            }
        }else if(curr->data=='\0'){
            fprintf(out_file, "#");
        } 
        else {
            fprintf(out_file, "%c", curr->data);
        }
        curr = curr->next;
    } 
    fprintf(out_file, "\n");
}

void show_c(TDoubleLinkedList *list,int num_of_com_that_need_ex, FILE *out_file){
    node *curr = list->head;
    int k = 0, q = -1;
    int w = list->len - 100;

    while (k < num_of_com_that_need_ex - q) {  //exact ca funcția de mai sus, dar doar imprimă caracterul curent
        if (k == w) {
            fprintf(out_file, "%c", curr->data);
        }
        curr = curr->next;
        k++;
        q++;
    }
    fprintf(out_file, "\n");
}


int pos(char c, int *curr_pos, TDoubleLinkedList *list) {
    node *curr = list->head;
    int j;              //functia care returneaza posita de characterul c
                        // acest functie este folosit pentru MOVE_RIGHT/LEFT_CHAR
    for (j = 0; j < *curr_pos; j++) {
        curr = curr->next;
    }

    while (curr != NULL) {
        if (curr->data == c) {
            return *curr_pos;
        }
        curr = curr->prev;
        (*curr_pos)--;
    }
    return -1;
    
}
void insert_left(char insert_char, int *curr_pos, TDoubleLinkedList *list) {
        node *curr = list->head;
        int j;
        for (j = 0; j < *curr_pos - 1; j++) {  //parcurgeți lista grupului, găsiți poziția curentă, 
                                                 //creați un nou nod la stânga
            curr = curr->next;
        }
        node *new_node = (node *) malloc(sizeof(node));
        new_node->data = insert_char;
        new_node->next = curr->next;
        new_node->prev = curr;
        curr->next->prev = new_node;
        curr->next = new_node;
}

void insert_right(char insert_char, int *curr_pos, TDoubleLinkedList *list) {
    node *curr = list->head;
    int j;
    for (j = 0; j < *curr_pos; j++) {
        curr = curr->next;
    }

    node *new_node = (node *) malloc(sizeof(node));
    new_node->data = insert_char;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (curr != NULL) {
        new_node->next = curr->next;
        new_node->prev = curr;
        if (curr->next != NULL) {
            curr->next->prev = new_node;
        } else {
            list->tail = new_node;
        }
        curr->next = new_node;
    } else {
        if (list->head == NULL) {
            list->head = new_node;
            list->tail = new_node;
        } else {
            list->tail->next = new_node;
            new_node->prev = list->tail;
            list->tail = new_node;
        }
    }

    (*curr_pos)++;
    list->len++;
}
void freeList(TDoubleLinkedList *list) {
    node *current = list->head;
    node *temp = NULL;

    while (current) {
        temp = current;
        current = current->next;
        free(temp);
    }

    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}
int main() {
    TDoubleLinkedList list;
    initializeList(&list);
    
    int num_command; // numărul de comenzi
    char commands[100][100];
    char ctbe[100][100]; // CommandsToBeExecuted
    int nctbe = 0; // NumberOfCommandsToBeExecuted
    int num_of_com_that_need_ex = 0; // NumberofCommandsThatNeedExecute
    int p = 0, i; // pentru loop for
    int num_of_mr = 1; // numărul de comandă MOVE_RIGHT astfel încât să putem acum extrema listei
    int curr_pos = 0;

    FILE* input_file = fopen("tema1.in", "r");
    if (input_file == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    FILE* output_file = fopen("tema1.out", "w");
    if (output_file == NULL) {
        printf("Error opening output file!\n");
        fclose(input_file);
        return 1;
    }

    fscanf(input_file, "%d", &num_command);

    for (i = 0; i < num_command; i++) {
        fscanf(input_file, " %[^\n]", commands[i]);
    }
//mai întâi scanăm toate comenzile și nu facem nimic,
// am folosit-o pe scanf(" %[^\n]" pentru INSERT_LEFT/RIGHT și WRITE,
// deoarece avem nevoie de ultimul caracter când aceste commenzi au fost scanate
    
    for (i = 0; i < num_command; i++) {
    //apoi parcurgem bucla una câte una și copiem comenzile care trebuie să emită cuvântul EXECUTE
    // într-o altă matrice de șiruri, astfel încât să le putem urmări și
    // să le executăm atunci când comanda EXECUTE este citită
    //folosim strcmp si pentru INERT_LEFT/RIGHT, WRITE etc folosim strncmp
        if (strcmp(commands[i], "MOVE_RIGHT") == 0 ){
            strcpy(ctbe[nctbe], commands[i]); 
            nctbe++;
          num_of_com_that_need_ex ++;
        
        }else if (strcmp(commands[i], "MOVE_LEFT") == 0) {
            strcpy(ctbe[nctbe], commands[i]); 
            nctbe++;
           
        } 
        else if (strncmp(commands[i], "WRITE", 5) == 0) {
            strcpy(ctbe[nctbe], commands[i]);
            nctbe++;
            num_of_com_that_need_ex++;

        }else if (strncmp(commands[i], "MOVE_RIGHT_CHAR", 15) == 0) {
            strcpy(ctbe[nctbe], commands[i]);
            nctbe++;
            num_of_com_that_need_ex++; 

        }else if (strncmp(commands[i], "MOVE_LEFT_CHAR", 14) == 0) {
            strcpy(ctbe[nctbe], commands[i]);
            nctbe++;
           num_of_com_that_need_ex++; 

        }else if (strncmp(commands[i], "INSERT_RIGHT", 12) == 0) {
            strcpy(ctbe[nctbe], commands[i]);
            nctbe++;
            num_of_com_that_need_ex++;
         
        } else if (strncmp(commands[i], "INSERT_LEFT", 11) == 0) {
            strcpy(ctbe[nctbe], commands[i]);
            nctbe++;
            num_of_com_that_need_ex++;
        }
         else if (strcmp(commands[i], "SHOW") == 0) {
     
        show( &list,num_of_mr,output_file);
       
    
        } else if (strcmp(commands[i], "SHOW_CURRENT") == 0) {
         
         show_c(&list,num_of_mr,output_file);
         //show si show_c nu avet nevoi pentru EXECUTE si facem direct
        
        } else if(strcmp(commands[i],"UNDO")==0){
           
            int p;

for ( p= num_command - 1; p >= 0; p--){
        
        if(strcmp(commands[p],"MOVE_LEFT")==0){
   //pentru commanda UNDO si REDO mergem la lista de stringuri de la sfarsit
   //si primu ca est MOVE_RIGHT/LEFT in cazul UNDO facem invers,in REDO facem apoi commanda
    moveRight(&curr_pos, &list);
    
    break;
    
}else if(strcmp(commands[p],"MOVE_RIGHT")==0){
     
    moveLeft(&curr_pos,&list);
    break;
}
    }

}else if(strcmp(commands[i],"REDO")==0){
int p;

for ( p= num_command - 1; p >= 0; p--){
        if(strcmp(commands[p],"MOVE_LEFT")==0){
   
    moveLeft(&curr_pos,&list);
    
}else if(strcmp(commands[p],"MOVE_RIGHT")==0){
     
   moveRight(&curr_pos,&list);
}
    }
}else if (strcmp(commands[i],"EXECUTE")==0){
    //daca citim EXECUTE executeam comenzi din inceput
    if (strcmp(ctbe[p], "MOVE_RIGHT") == 0) {
       moveRight(&curr_pos, &list);
       num_of_mr++;

    } else if (strcmp(ctbe[p], "MOVE_LEFT") == 0) {
       if (list.len-100==0){
   printf("ERROR\n");
   }else{
         moveLeft(&curr_pos, &list);
         }
    } else if (strncmp(ctbe[p], "WRITE", 5) == 0) {
     char overwrite_char = ctbe[p][6];
                    write(overwrite_char, curr_pos, &list);
    
    } else if((strncmp(ctbe[p], "INSERT_RIGHT", 12) == 0)){
                     
                     char overwrite_char = ctbe[p][13];
        //știm că în orice moment caracterul pe care trebuie să-l suprascriem va fi în această poziție
                  insert_right(overwrite_char,&curr_pos,&list)  ;
                  num_of_mr++;

    }else if((strncmp(ctbe[p], "INSERT_LEFT", 11) == 0)){
      if (list.len-100==0){
    printf("ERROR\n");
  }else{
       
       char overwrite_char= ctbe[p][12];
     
        insert_left(overwrite_char,&curr_pos,&list)  ;
     num_of_mr++;
    
     int n;
           for(n=i;n<num_command;n++){
            if (strcmp(commands[n],"MOVE_RIGHT")==0){
                num_of_mr--;
                break;
            }
           }
     }
    }else if (strncmp(ctbe[p], "MOVE_RIGHT_CHAR", 15) == 0){
        char overwrite_char = ctbe[p][16];
        int b=list.len-100; //asta este pozitia curent
        int i,e;//i este pentru loop,e este pozita pe catacterul ca vream sa stim unde e
    pos(overwrite_char,&curr_pos,&list);
    e=curr_pos;

   if (e==-1){
    printf("ERROR\n");
   }else {
   for ( i = 0; i < b-e; i++) {
       moveRight(&curr_pos,&list);  //facem moverigh/left cat de timpuri avem nevoie sa mergem in characterul
    }
    }
    }else if (strncmp(ctbe[p], "MOVE_LEFT_CHAR", 14) == 0){
        char overwrite_char = ctbe[p][15];
         int b=list.len-100;
         int i,e;

    pos(overwrite_char,&curr_pos,&list);
   e=curr_pos;

if (e==-1){
    printf("ERROR\n");
}else { 
   for ( i = 0; i < b-e; i++) {
       
       moveLeft(&curr_pos,&list);
      
    }
    }
        }
       
        p++; 
}
    }
     
     freeList(&list);
   
    fclose(input_file);
    fclose(output_file);
    
    return 0;
}


