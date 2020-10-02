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
    int permission[3];
    struct FileOrDir* DirLink;
    struct FileOrDir* FileLink;

};


struct FileOrDir* Filehead = NULL;
struct FileOrDir* Dirhead = NULL;

void insertDirectory(struct FileOrDir**Dirhead ,char *name,char *Location,int size, int permission[], char* date ){
    int i;
    struct FileOrDir* Node = (struct FileOrDir*)malloc(sizeof(struct FileOrDir));
    struct FileOrDir* temp = *Dirhead;
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
    for (i = 0;i<3; i++)
    {
        Node->permission[i] = permission[i];
    }
    Node->type =0;
    Node->FileCount = 1;
    Node->FileLink = NULL;
    Node->DirLink = NULL;

    if(*Dirhead == NULL){
        *Dirhead = Node;
    }
    else{
        while(temp->DirLink != NULL){
            temp = temp->DirLink;
        }
        temp->DirLink = Node;
    }
    

    // printf("%s",Node->createdOn);
}






void insertFile(struct FileOrDir**Filehead, char *name,char *Location,int size, int permission[], char* date,FILE*fp){
    int i;
    struct FileOrDir* Node = (struct FileOrDir*)malloc(sizeof(struct FileOrDir));
    struct FileOrDir* temp = *Filehead;

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
    for (i = 0;i<3; i++)
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
    
    if(*Filehead == NULL){
        *Filehead = Node;
    }
    else{
        while(temp->FileLink != NULL){
            temp = temp->FileLink;
        }
        temp->FileLink = Node;
    }
    
}


void insertFileToDir(FILE*fp,char *name,char *Location,int size, int permission[], char* date){
    // check whether the directory exist else create the new directory
    struct FileOrDir* tempD = Dirhead;
    struct FileOrDir* prev = NULL;
    
    struct FileOrDir* temp = Dirhead;
    struct FileOrDir* tempF = NULL;
    
    while (temp != NULL)
    {
        if (strcmp(Location,temp->name)==0)
        {
            tempF = temp->FileLink;
            while (tempF != NULL)
            {
                if (strcmp(tempF->name,name)==0)
                {
                    printf("Cannot insert file. A file with this name already exists");
                    fprintf(fp,"Cannot insert file. A file with this name already exists");
                    return;
                }
                
                tempF = tempF->FileLink;
            }
        }
        
        
        
        temp = temp->DirLink;
    }

    int flag = 0;
    if (tempD == NULL)
    {
        int arr[] = {1,1,1,1,1,1,1,1,1};
        
        insertDirectory(&Dirhead,Location,"root",1000,arr,date);
        insertFile(&Dirhead->FileLink,name,Location,size,permission,date,fp);

        return;
    }
    
    
    
    while (tempD!=NULL)
    {
        if(strcmp(tempD->name,Location)== 0){
            tempD->FileCount+=1;
            insertFile(&tempD->FileLink,name,Location,size,permission,date,fp);
            flag = 1;
            break;
        }
        prev = tempD;
        tempD = tempD->DirLink;
    }
    if (flag ==0)
    {
        // printf("flag\n");
        int arr[] = {1,1,1,1,1,1,1,1,1};
        insertDirectory(&Dirhead,Location,"root",1000,arr,date);
        insertFile(&prev->DirLink->FileLink,name,Location,size,permission,date,fp);

    }

    
}


void searchFile(FILE*fp,char* name){
    struct FileOrDir* temp = Dirhead;
    struct FileOrDir* tempF = NULL;
    int flag = 0,count=0;
    while (temp != NULL)
    {
        tempF = temp->FileLink;
        while (tempF != NULL)
        {
            if (strcmp(tempF->name,name)==0)
            {
                count++;
                printf("\nMATCH %d - ",count);
                fprintf(fp,"\nMATCH %d - ",count);
                printf("\n  File :%s",tempF->name);
                fprintf(fp,"\n  File :%s",tempF->name);
                printf("\n  Directory :%s",tempF->Location);
                fprintf(fp,"\n  Directory :%s",tempF->Location);
                printf("\n  Date created :%s",tempF->createdOn);
                fprintf(fp,"\n  Date created :%s",tempF->createdOn);
                printf("\n  permissions :");
                fprintf(fp,"\n  permissions :");
                printf("%c %c %c",tempF->permission[0]?'R':'-',tempF->permission[1]?'W':'-',tempF->permission[2]?'X':'-');
                fprintf(fp,"%c %c %c",tempF->permission[0]?'R':'-',tempF->permission[1]?'W':'-',tempF->permission[2]?'X':'-');
                flag = 1;
                // return tempF;
            }
            
            tempF = tempF->FileLink;
        }
        
        temp = temp->DirLink;
    }
    if (flag == 0)
    {
        printf("\nNo File Exists\n");
        fprintf(fp,"\nNo File Exists\n");
    }
    
    
    
}

void Display(){
    
    struct FileOrDir* current = NULL;
    struct FileOrDir* Filecurrent = NULL;
    current = Dirhead;
    while (current != NULL)
    {
        
        printf("\n%s(%d) :\n",current->name,current->FileCount);
        Filecurrent = current->FileLink;
        while (Filecurrent != NULL){
            

            printf("%s ",Filecurrent->name);
            Filecurrent = Filecurrent->FileLink;
        }

        current = current->DirLink;
    }
    
}

void DeleteFile(FILE*fp,char* Fname, char* Dname){
    struct FileOrDir* Dtemp = Dirhead;
    struct FileOrDir* temp = NULL;
    struct FileOrDir* prev;
    int flag =0;

    while (Dtemp != NULL)
    {
        if (strcmp(Dtemp->name, Dname)==0)
        {
            flag =1;
            Dtemp->FileCount-=1;
            temp = Dtemp->FileLink;
             if (temp != NULL && strcmp(temp->name, Fname)==0 ) 
            {   
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

                Dtemp->FileLink = temp->FileLink;   // Changed head 
                free(temp);               // free old head 
                return; 
            }
            
            while (temp != NULL && strcmp(temp->name, Fname)!=0) 
            { 
                prev = temp; 
                temp = temp->FileLink; 
            } 
            // If key was not present in linked list 
            if (temp == NULL){
                printf("\nFile not found\n");
                fprintf(fp,"\nFile not found\n");
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
    
            printf("\nFile Deleted\n");
            free(temp); 
            break;
        }
        if (flag == 0)
        {
            printf("\nDirectory not found\n");
        }
        
        
        Dtemp = Dtemp->DirLink;
    }
    

   
}

void main(){
    

    int choice;
    int cont;
    char name[32],Dname[32],Location[32],createdon[32];
    int Filecount,type,size,permission[]= {1,1,1} ;

    FILE * fp,* fpo;

    fp = fopen ("input2.txt", "w+");
    fpo = fopen ("output2.txt", "w+");

    do
    {
        printf("\n--Two Level--\n");
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
            insertFileToDir(fpo,name,Location,size,permission,createdon);
            break;
        case 2:
            printf("\n------DELETE FILE------");
            fprintf(fp,"\n------DELETE FILE------");
            printf("\nEnter the file name : ");
            fprintf(fp,"\nEnter the file name : ");
            scanf("%s",name);
            fprintf(fp,"%s",name);

            printf("Enter the folder name : ");
            fprintf(fp,"\nEnter the folder name : ");
            scanf("%s",Dname);
            fprintf(fp,"%s",Dname);
            DeleteFile(fpo,name,Dname);
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