#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct FileOrDir
{
    char name[32];
    int FileCount;
    char Location[32];
    int type;// 1 for File and 0 for directory
    int size;
    char createdOn[32];
    int permission[9];
    struct FileOrDir* DirLink;
    struct FileOrDir* FileLink;

};


struct FileOrDir* Filehead = NULL;
// struct FileOrDir* Dirhead = NULL;
struct FileOrDir* current = NULL;


void insertFile(FILE *fp,char *name,char *Location,int size, int permission[], char* date){
    int i;
    
    if (strcmp(Location,"root")!=0)
    {
        printf("Cannot create a new directory in Single level hierarchy");
        fprintf(fp,"Cannot create a new directory in Single level hierarchy");
        return;
    }
    
    struct FileOrDir* Node = (struct FileOrDir*)malloc(sizeof(struct FileOrDir));
    struct FileOrDir* temp = Filehead;
    struct FileOrDir* temp2 = Filehead;

    while (temp2 != NULL)
    {
        if(strcmp(name,temp2->name)==0){
            printf("File name already exists \n");
            fprintf(fp,"\nFile name already exists \n");
            return;
        }
        temp2 = temp2->FileLink;
    }
    

    for ( i = 0; *(name+i)!='\0'; i++)
    {
        Node->name[i] = *(name+i);
    }
    for ( i = 0; *(Location+i)!='\0'; i++){
        Node->Location[i] = *(Location+i);
    }
    for ( i = 0; *(date+i)!='\0'; i++)
    {
        Node->createdOn[i] = *(date+i);
    }
    Node->size = size;
    for (i = 0;i<9; i++)
    {
        Node->permission[i] = permission[i];
    }
    Node->type =1;
    Node->FileCount = 1;
    Node->FileLink = NULL;
    Node->DirLink = NULL;
    printf("\nFile created");
    fprintf(fp,"\nFile created");
    printf("\n  File :%s",Node->name);
    fprintf(fp,"\n  File :%s",Node->name);
    printf("\n  Directory :%s",Node->Location);
    fprintf(fp,"\n  Directory :%s",Node->Location);
    printf("\n  Date created :%s",Node->createdOn);
    fprintf(fp,"\n  Date created :%s",Node->createdOn);
    printf("\n  permissions :");
    fprintf(fp,"\n  permissions :");
    printf("%c %c %c",Node->permission[0]?'R':'-',Node->permission[1]?'W':'-',Node->permission[2]?'X':'-');
    fprintf(fp,"%c %c %c",Node->permission[0]?'R':'-',Node->permission[1]?'W':'-',Node->permission[2]?'X':'-');
    
    if(Filehead == NULL){
        Filehead = Node;
    }
    else{
        while(temp->FileLink != NULL){
            temp = temp->FileLink;
        }
        temp->FileLink = Node;
    }
    

    // printf("%s",Node->createdOn);
}

void searchFile(FILE*fp,char* name){
    struct FileOrDir* temp = Filehead;
    int flag = 0;
    
    
    while(temp != NULL){
        if (strcmp(temp->name, name)==0)
        {
            printf("File found\n");
            fprintf(fp,"File found");
            printf("\n  File :%s",temp->name);
            fprintf(fp,"\n  File :%s",temp->name);
            printf("\n  Directory :%s",temp->Location);
            fprintf(fp,"\n  Directory :%s",temp->Location);
            printf("\n  Date created :%s",temp->createdOn);
            fprintf(fp,"\n  Date created :%s",temp->createdOn);
            printf("\n  permissions :");
            fprintf(fp,"\n  permissions :");
            printf("%c %c %c",temp->permission[0]?'R':'-',temp->permission[1]?'W':'-',temp->permission[2]?'X':'-');
            fprintf(fp,"%c %c %c",temp->permission[0]?'R':'-',temp->permission[1]?'W':'-',temp->permission[2]?'X':'-');
                
            flag =1;
        }
        
        temp = temp->FileLink;
    }
    if (flag == 0)
    {
        printf("\nFile not found\n");
    }
    
    

}

void Display(){
    current = Filehead;
    if(current == NULL){
        printf("\nNothing exists to view\n");
        return;
    }
    while (current->FileLink != NULL)
    {
        printf("%s ",current->name);
        current = current->FileLink;
    }
    printf("%s \n",current->name);
}

void DeleteFile(FILE*fp,char* name){
    struct FileOrDir* temp = Filehead;
    struct FileOrDir* prev;
    
    
    if (temp != NULL && strcmp(temp->name, name)==0 ) 
    { 
        Filehead = temp->FileLink;   // Changed head 
        printf("\nFile deleted");
        fprintf(fp,"\nFile deleted");
        printf("\n  File :%s",temp->name);
        fprintf(fp,"\n  File :%s",temp->name);
        printf("\n  Directory :%s",temp->Location);
        fprintf(fp,"\n  Directory :%s",temp->Location);
        printf("\n  Date created :%s",temp->createdOn);
        fprintf(fp,"\n  Date created :%s",temp->createdOn);
        printf("\n  permissions :");
        fprintf(fp,"\n  permissions :");
        printf("%c %c %c",temp->permission[0]?'R':'-',temp->permission[1]?'W':'-',temp->permission[2]?'X':'-');
        fprintf(fp,"%c %c %c",temp->permission[0]?'R':'-',temp->permission[1]?'W':'-',temp->permission[2]?'X':'-');

        free(temp);               // free old head 
        return; 
    }
    
    while (temp != NULL && strcmp(temp->name, name)!=0) 
    { 
        prev = temp; 
        temp = temp->FileLink; 
    } 
    // If key was not present in linked list 
    if (temp == NULL){
       printf("Node not found");
       return; 
    }  
  
    // // Unlink the node from linked list 
    prev->FileLink = temp->FileLink; 
    printf("\nFile deleted");
    fprintf(fp,"\nFile deleted");
    printf("\n  File :%s",temp->name);
    fprintf(fp,"\n  File :%s",temp->name);
    printf("\n  Directory :%s",temp->Location);
    fprintf(fp,"\n  Directory :%s",temp->Location);
    printf("\n  Date created :%s",temp->createdOn);
    fprintf(fp,"\n  Date created :%s",temp->createdOn);
    printf("\n  permissions :");
    fprintf(fp,"\n  permissions :");
    printf("%c %c %c",temp->permission[0]?'R':'-',temp->permission[1]?'W':'-',temp->permission[2]?'X':'-');
    fprintf(fp,"%c %c %c",temp->permission[0]?'R':'-',temp->permission[1]?'W':'-',temp->permission[2]?'X':'-');

    free(temp); 
    
}

void main(){
    
    int choice;
    int cont;
    char name[32],Location[32],createdon[32];
    int Filecount,type,size,permission[]= {1,1,1,1,1,1,1,1,1} ;
    FILE * fp,* fpo;

    fp = fopen ("input.txt", "w+");
    fpo = fopen ("output.txt", "w+");

    do
    {
        printf("\n--Single level--\n");
        fprintf(fp,"\n--Single level--\n");
        printf("1.Create File\n");
        fprintf(fp,"1.Create File\n");
        printf("2.Delete File\n");
        fprintf(fp,"2.Delete File\n");
        printf("3.Search File\n");
        fprintf(fp,"3.Search File\n");
        printf("4.Display\n");
        fprintf(fp,"4.Display\n");
        printf("Enter choice:");
        fprintf(fp,"Enter choice:");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("\n------INSERT FILE------");
            fprintf(fp,"\n------INSERT FILE------");
            printf("\nEnter the file name : ");
            fprintf(fp,"\nEnter the file name : ");
            scanf("%s",name);
            fprintf(fp,"%s",name);

            printf("Enter the Location(only root can exist) : ");
            fprintf(fp,"\nEnter the Location(only root can exist) : ");
            scanf("%s",Location);
            fprintf(fp,"%s",Location);

            printf("Enter the date of creation : ");
            fprintf(fp,"\nEnter the date of creation : ");
            scanf("%s",createdon);
            fprintf(fp,"%s",createdon);

            printf("Enter the size : ");
            fprintf(fp,"\nEnter the size : ");
            scanf("%d",&size);
            fprintf(fp,"%d",size);

            printf("\nDEFAULT values filed in rest of the fields\n");
            fprintf(fp,"\nDEFAULT values filed in rest of the fields\n");
            insertFile(fpo,name,Location,size,permission,createdon);
            break;
        case 2:
            printf("\n------DELETE FILE------");
            fprintf(fp,"\n------DELETE FILE------");
            printf("\nEnter the file name : ");
            fprintf(fp,"\nEnter the file name : ");
            scanf("%s",name);
            fprintf(fp,"%s",name);
            DeleteFile(fpo,name);
            break;
        case 3:
            printf("\n------SEARCH FILE------");
            fprintf(fp,"\n------SEARCH FILE------");
            printf("\nEnter the file name : ");
            fprintf(fp,"\nEnter the file name : ");
            scanf("%s",name);
            fprintf(fp,"%s",name);
            searchFile(fpo,name);
            break;
        case 4:
            Display();

        default:
            break;
        }

        printf("\nDo yu want to continue (Press 1 for yes 0 for no) : ");
        scanf("%d",&cont);
    } while (cont == 1 );
    
    
fclose(fp);
fclose(fpo);

}