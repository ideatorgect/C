#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int maxDepth = 0;
int searchFlag = 0;
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
    Node->FileCount = 0;
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


void searchDir(struct FileOrDir*head,char *Location,FILE*fp){
    
    if(strcmp(head->name,Location)== 0){
        printf("\nDirectory :%s ",head->Location);
        fprintf(fp,"\nDirectory :%s ",head->Location);
        return;
    }
    if(head->FileLink != NULL ){
       searchDir(head->FileLink,Location,fp);
    }
    if (head->DirLink != NULL)
    {
        searchDir(head->DirLink,Location,fp);
    }
}


void insertFile(FILE*fp,struct FileOrDir**Filehead, char *name,char *Location,int size, int permission[], char* date){
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
    searchDir(Dirhead,Node->Location,fp);
    if(*Filehead == NULL){
        *Filehead = Node;
    }
    else{
        while(temp->DirLink != NULL){
            temp = temp->DirLink;
        }
        temp->DirLink = Node;
    }
    
}

void recFileInsert(FILE*fp,struct FileOrDir*head,char *name,char *Location,int size, int permission[], char* date){
    
    if(strcmp(head->name,Location)== 0 && head->type == 0){
        head->FileCount+=1;
        insertFile(fp,&head->FileLink,name,Location,size,permission,date);
        searchFlag =1;
        return;
    }
    if(head->FileLink != NULL ){
       recFileInsert(fp,head->FileLink,name,Location,size,permission,date);
    }
    if (head->DirLink != NULL)
    {
        recFileInsert(fp,head->DirLink,name,Location,size,permission,date);
    }
}

void searchifExist(FILE*fp,struct FileOrDir*head,char *name,char *Location){
    
    if(strcmp(head->name,name)== 0){
        if (strcmp(head->Location,Location)== 0)
        {
            printf("Cannot insert file/folder. A file/folder with this name already exists\n");
            fprintf(fp,"\nCannot insert file/folder. A file/folder with this name already exists\n");
            searchFlag =1;
        }
        
        
    }
    if(head->FileLink != NULL ){
       searchifExist(fp,head->FileLink,name,Location);
    }
    if (head->DirLink != NULL)
    {
        searchifExist(fp,head->DirLink,name,Location);
    }
}

void insertFileToDir(FILE*fp,char *name,char *Location,int size, int permission[], char* date){
    // check whether the directory exist else create the new directory
    struct FileOrDir* tempD = Dirhead;
    struct FileOrDir* tempF = Dirhead;
    struct FileOrDir* prev = NULL;
    if (Dirhead != NULL)
    {
        searchifExist(fp,Dirhead,name,Location);
    }
    
    
    if (searchFlag ==1)
    {
        searchFlag = 0;
        return;
    }
    
    if (tempD == NULL)
    {
        int arr[] = {1,1,1};
        
        insertDirectory(&Dirhead,Location,"root",1000,arr,date);
        insertFile(fp,&Dirhead->FileLink,name,Location,size,permission,date);
        Dirhead->FileCount +=1;
        return;
    }
    
    recFileInsert(fp,tempD,name,Location,size,permission,date);   
    
    if (searchFlag ==0)
    {
        searchifExist(fp,Dirhead,Location,"root");
        if (searchFlag ==1)
        {
            searchFlag = 0;
            return;
        }
        int arr[] = {1,1,1};
        insertDirectory(&Dirhead,Location,"root",1000,arr,date);
        while(tempF!=NULL){
            prev = tempF;
            tempF = tempF->DirLink;
        }
        insertFile(fp,&prev->FileLink,name,Location,size,permission,date);
        prev->FileCount += 1;

    }else
    {
        searchFlag=0;
    }

    
}

void recInsert(struct FileOrDir*head,char *name,char *Location,int size, int permission[], char* date){
    
    if(strcmp(head->name,Location)== 0 && head->type==0){
        head->FileCount+=1;
        insertDirectory(&head->FileLink,name,Location,size,permission,date);
        searchFlag =1;
        return;
    }
    if(head->FileLink != NULL ){
       recInsert(head->FileLink,name,Location,size,permission,date);
    }
    if (head->DirLink != NULL)
    {
        recInsert(head->DirLink,name,Location,size,permission,date);
    }
}

void DirToDir(FILE*fp,char *name,char *Location,int size, int permission[], char* date){
    // check whether the directory exist else create the new directory
    struct FileOrDir* tempD = Dirhead;
    struct FileOrDir* tempF = Dirhead;
    struct FileOrDir* prev = NULL;
    if (Dirhead != NULL)
    {
        searchifExist(fp,Dirhead,name,"root");
    }
    if (searchFlag ==1)
    {
        searchFlag = 0;
        return;
    }
    int flag = 0;
    if (tempD == NULL)
    {
        int arr[] = {1,1,1};
        
        insertDirectory(&Dirhead,Location,"root",1000,arr,date);
        insertDirectory(&Dirhead->FileLink,name,Location,size,permission,date);
        Dirhead->FileCount +=1;

        return;
    }
    
    
    recInsert(tempD,name,Location,size,permission,date);


    if (searchFlag ==0)
    {
        // printf("flag\n");
        int arr[] = {1,1,1};
        insertDirectory(&Dirhead,Location,"root",1000,arr,date);
        while(tempF!=NULL){
            prev = tempF;
            tempF = tempF->DirLink;
        }
        insertDirectory(&prev->FileLink,name,Location,size,permission,date);
        prev->FileCount += 1;

    }else
    {
        searchFlag=0;
    }
    

      
}

void searchFile(FILE*fp,struct FileOrDir*head,char* TargetName){
    
    if(strcmp(head->name,TargetName)== 0 && head->type==1){
        printf("\nFile Found");
        fprintf(fp,"\nFile Found");
        printf("\nLocation: %s ",head->Location);
        fprintf(fp,"\nLocation: %s ",head->Location);
        printf("\nName: %s ",head->name);
        fprintf(fp,"\nName: %s ",head->name);
        printf("\nSize: %dkb ",head->size);
        fprintf(fp,"\nSize: %dkb ",head->size);
        printf("\nDate: %s",head->createdOn);
        fprintf(fp,"\nDate: %s",head->createdOn);
        printf("\nPermissions:");    
        fprintf(fp,"\nPermissions:");    
        printf("%c %c %c",head->permission[0]?'R':'-',head->permission[1]?'W':'-',head->permission[2]?'X':'-');
        fprintf(fp,"%c %c %c",head->permission[0]?'R':'-',head->permission[1]?'W':'-',head->permission[2]?'X':'-');
        searchDir(Dirhead,head->Location,fp);
        searchFlag =1;
    }
    if(head->FileLink != NULL ){
       searchFile(fp,head->FileLink,TargetName);
       
    }
    if (head->DirLink != NULL)
    {
        searchFile(fp,head->DirLink,TargetName);
    }
}

void traverse(struct FileOrDir*head){  
    printf("%s(%d) ",head->name,head->FileCount);
    
    if(head->FileLink != NULL ){
       traverse(head->FileLink);
       
    }
    if (head->DirLink != NULL)
    {
        traverse(head->DirLink);
    }  
    
}

void DeletefromDir(FILE*fp,struct FileOrDir*head,char *name, char* Fname){
    if (strcmp(head->name, name)==0){
        searchFlag = 1;
        struct FileOrDir* temp = NULL;
        struct FileOrDir* prev = NULL;
        head->FileCount-=1;
        temp = head->FileLink;
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
            searchDir(Dirhead,temp->Location,fp);
            head->FileLink = temp->DirLink;   // Changed head 
            free(temp);               // free old head 
            printf("\nFile Deleted\n");
            return; 
        }
        
        while (temp != NULL && strcmp(temp->name, Fname)!=0) 
        { 
            prev = temp; 
            temp = temp->DirLink; 
        } 
        // If key was not present in linked list 
        if (temp == NULL){
            printf("\nNode not found\n");
            return; 
        }  
    
        // // Unlink the node from linked list 
        prev->DirLink = temp->DirLink; 
        printf("\nFile Deleted\n");
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
        return;
    }
    
    if(head->FileLink != NULL ){
       DeletefromDir(fp,head->FileLink,name,Fname);
       
    }
    if (head->DirLink != NULL)
    {
        DeletefromDir(fp,head->DirLink,name,Fname);
    }  
}

void delFileSearch(FILE*fp,struct FileOrDir*head,char* Fname){
    if (strcmp(head->name, Fname)==0){
        
        DeletefromDir(fp,Dirhead,head->Location,Fname);
    }
    
    if(head->FileLink != NULL ){
       delFileSearch(fp,head->FileLink,Fname);
       
    }
    if (head->DirLink != NULL)
    {
        delFileSearch(fp,head->DirLink,Fname);
    }  
}
        
void DeleteFile(FILE*fp,struct FileOrDir*head,char* Fname, char* Dname){
    if (strcmp(head->name, Dname)==0)
    {
        
        delFileSearch(fp,head->FileLink,Fname);
    }
    if(head->FileLink != NULL ){
       DeleteFile(fp,head->FileLink,Fname, Dname);
    }
    if (head->DirLink != NULL)
    {
        DeleteFile(fp,head->DirLink,Fname, Dname);
    }
       
}

void main(){
    // int arr[] = {1,2,3,4,5,6,7,8,3};
    // DirToDir("Dir1","main",32,arr,"5/2/2014");
    // insertFileToDir("file6","main",32,arr,"5/2/2014");
    // insertFileToDir("file6","main",32,arr,"5/2/2014");
    // DirToDir("Dir2","main",32,arr,"5/2/2014");
    // DirToDir("Dir2.1","Dir2",32,arr,"5/2/2014");
    // DirToDir("Dir3","sec",32,arr,"5/2/2014");
    // DirToDir("Dir4","sec",32,arr,"5/2/2014");
    // DirToDir("Dir5","ter",32,arr,"5/2/2014");
    // traverse(Dirhead);
    // DeleteFile(Dirhead,"file6","main");
    // if (searchFlag == 0)
    // {
    //     printf("\nFile not found\n");
    // }
    // searchFlag = 0;
    // traverse(Dirhead);
    

    // searchFile(Dirhead,"file3");
    // if(searchFlag != 1 ){
    //     printf("\nFile not found\n");
    // }
    // searchFlag = 0;

    // Display();
    // printf("\n");
    // DeleteFile("file2");
    // Display();

    int choice;
    int cont;
    char name[32],Dname[32],Location[32],createdon[32];
    int Filecount,type,size,permission[]= {1,1,1} ;
    FILE * fp,* fpo;

    fp = fopen ("input3.txt", "w+");
    fpo = fopen ("output3.txt", "w+");

    do
    {
        printf("\n--Heirarchy level--\n");
        fprintf(fp,"\n--Single level--\n");
        printf("1.Create File\n");
        fprintf(fp,"1.Create File\n");
        printf("2.Delete File\n");
        fprintf(fp,"2.Delete File\n");
        printf("3.Search File\n");
        fprintf(fp,"3.Search File\n");
        printf("4.Create new directory\n");
        fprintf(fp,"4.Create new directory\n");
        printf("5.Display\n");
        fprintf(fp,"5.Display\n");
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

            printf("Enter the Location(if dir does not exist it will be created in root) : ");
            fprintf(fp,"\nEnter the Location(if dir does not exist it will be created in root) : ");
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
            DeleteFile(fpo,Dirhead,name,Dname);
            if (searchFlag == 0)
            {
                printf("\nFile not found\n");
            }
            searchFlag = 0;
            break;
        case 3:
            printf("\n------SEARCH FILE------");
            fprintf(fp,"\n------SEARCH FILE------");
            printf("\nEnter the file name : ");
            fprintf(fp,"\nEnter the file name : ");
            scanf("%s",name);
            fprintf(fp,"%s",name);
            searchFile(fpo,Dirhead,name);
            if(searchFlag != 1 ){
                printf("\nFile not found\n");
            }
            searchFlag = 0;
            break;
        case 4:
            printf("Enter the folder name : ");
            fprintf(fp,"\nEnter the folder name : ");
            scanf("%s",name);
            fprintf(fp,"%s",name);
            
            printf("Enter the Location (if the directory does not exist it will be created in the root) : ");
            fprintf(fp,"Enter the Location (if the directory does not exist it will be created in the root) : ");
            scanf("%s",Location);
            fprintf(fp,"%s",Location);

            printf("Enter the date of creation : ");
            fprintf(fp,"Enter the date of creation : ");
            scanf("%s",createdon);
            fprintf(fp,"%s",createdon);

            printf("Enter the size : ");
            fprintf(fp,"Enter the size : ");
            scanf("%d",&size);
            fprintf(fp,"%d",size);

            printf("\nDEFAULT values filed in rest of the fields\n");
            DirToDir(fpo,name,Location,size,permission,createdon);
            break;
        case 5:
            traverse(Dirhead);

        default:
            break;
        }

        printf("\nDo yu want to continue (Press 1 for yes 0 for no) : ");
        scanf("%d",&cont);
    } while (cont == 1 );
fclose(fp);
fclose(fpo);
}