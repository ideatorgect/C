#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

int **max,**allocated,*avaiable,**need,*safeSatte,process=0,resourse;  //global variables
char *in;
int pIndex,rIndex,i,temp;
void printNeed(){
    printf("\nNEED:\n\t");
    for(i=65;i< 65 + resourse;i++)
        printf("%c\t",i);
    printf("\n");
    for(pIndex=0 ; pIndex<process ; pIndex++){
        printf("P%d\t",pIndex);
        for(rIndex=0 ; rIndex< resourse ; rIndex++)
            printf("%d\t",need[pIndex][rIndex]);
        printf("\n");
    }
}
void read(){
    FILE *fin;
    int i;
    if ((fin = fopen("i.txt", "r")) == NULL) {
        printf("Error! opening file input.txt");
        exit(1);
    }
    fscanf(fin,"%d",&resourse);
    in = (char*)malloc(sizeof(6*resourse));
    printf("\nContents of the file input.txt Interpreted\n");
    printf("No of resourses:%d\n",resourse);
    printf("AVAIABLE:\n");
    for(i=65;i< 65 + resourse;i++)
        printf("%c\t",i);
    fscanf(fin," %[^\n]\n",in );
    printf("\n%s\n",in);
    printf("%-15s%s","Process","MAX");
    for(i=0;i<resourse;i++)
        printf("\t");
    printf("ALLOCATED\n%-15s"," ");
    for(i=65;i< 65 + resourse;i++)
        printf("%c\t",i);
    //printf("\t");
    for(i=65;i< 65 + resourse;i++)
        printf("%c\t",i);
    i=0;
    while (!feof(fin)) {
        fscanf(fin," %[^\n]\n",in );
        printf("\nP%-14d%s",i,in);
        i++;
    }
    process = i;
    fclose(fin);
    free(in);
}//function to read data from file and print to console
void scan(){
    FILE *fin;
    //allocation of memory
    max = (int **)malloc(process * sizeof(int *)); 
    for (i=0; i<process; i++) 
         max[i] = (int *)malloc(resourse * sizeof(int));
    allocated = (int **)malloc(process * sizeof(int *)); 
    for (i=0; i<process; i++) 
         allocated[i] = (int *)malloc(resourse * sizeof(int));
    avaiable =(int*)malloc(resourse * sizeof(int));
    //opening file
    if ((fin = fopen("i.txt", "r")) == NULL) {
        printf("Error! opening file input.txt");
        exit(1);
    }
    fscanf(fin,"%d",&resourse); 
    //storing values to memory
    for(rIndex=0 ; rIndex< resourse ; rIndex++){
        if(rIndex == (resourse - 1)){
            fscanf(fin,"%d%[^\n]\n", &temp );
            avaiable[rIndex] =temp;
        }
        else{
            fscanf(fin,"%d%[^\t]\t", &temp );
            avaiable[rIndex] =temp;
        }
    }
    for(pIndex=0 ; pIndex<process ; pIndex++){
        for(rIndex=0 ; rIndex< 2*resourse ; rIndex++){
            if(rIndex<resourse){
                fscanf(fin,"%d%[^\t]\t", &temp );
                max[pIndex][rIndex] =temp;
            }
            else{
                if(rIndex == (2*resourse - 1)){
                    fscanf(fin,"%d%[^\n]\n", &temp );
                    allocated[pIndex][rIndex-resourse] =temp;
                }
                else{
                    fscanf(fin,"%d%[^\t]\t", &temp );
                    allocated[pIndex][rIndex-resourse] =temp;
                }
            }
        }
    }
}//function to read data from file and store in memory 
void calcNeed(){
    //NEED = MAX - Allocated
    for(pIndex=0 ; pIndex<process ; pIndex++)
        for(rIndex=0 ; rIndex< resourse ; rIndex++)
            need[pIndex][rIndex] = max[pIndex][rIndex] - allocated[pIndex][rIndex];
}
int findSafeState(){
    int *final =(int *) malloc(process*sizeof(int));
    int *work =(int *) malloc(resourse*sizeof(int));
    for(rIndex=0 ; rIndex< resourse ; rIndex++)
        work[rIndex] = avaiable[rIndex];
    for(i=0;i<process;i++)
        final[i] = 0;
    int finalCounter =0,p =-1;
    do{
        for(pIndex=0;pIndex<process;pIndex++){
     //     printf("\nprocess:%d",pIndex);
     //     printf("\nfinal:%d",final[pIndex]);
            if(final[pIndex] == 0){
                p = pIndex;  
                for(rIndex=0;rIndex<resourse;rIndex++)
                    if(need[pIndex][rIndex]  > work[rIndex])  
                        break; 
    //         printf("\nrIndex:%d",rIndex);
                if(rIndex == resourse){
                    for(rIndex=0 ; rIndex< resourse ; rIndex++)
                        work[rIndex] += allocated[pIndex][rIndex];
                    safeSatte[finalCounter] =pIndex;
                    final[pIndex] =1;
                    finalCounter++;
                    p = -1;
                }
            }
        }
   // printf("FINAL COUNTER:%d",finalCounter);
    }while(finalCounter!=process && p == -1);
    
    free(work);
    free(final);



    if (finalCounter == process)
        return 1;
    else
        return 0;
    




}
void readReq(){
    FILE *fin;
    int p;
    if ((fin = fopen("requests.txt", "r")) == NULL) {
        printf("Error! opening file input.txt");
        exit(1);
    }
    int *req =(int*)malloc(resourse * sizeof(int));
    while(!feof(fin)){
        fscanf(fin,"%d%[^\t]\t", &p );
        for(rIndex=0 ; rIndex< resourse ; rIndex++){
            if(rIndex == (resourse - 1)){
                fscanf(fin,"%d%[^\n]\n", &temp );
                req[rIndex] =temp;
            }
            else{
                fscanf(fin,"%d%[^\t]\t", &temp );
                req[rIndex] =temp;
            }
        }
        printf("\nREQUEST:\n\t");
        for(i=65;i< 65 + resourse;i++)
            printf("%c\t",i);
        printf("\nP%d\t",p);
        for(rIndex=0 ; rIndex< resourse ; rIndex++)
            printf("%d\t",req[rIndex]);
        printf("\n"); //prints the request that was read from file into stdout:
        for(rIndex=0 ; rIndex< resourse ; rIndex++){
            if(req[rIndex] + allocated[p][rIndex] > max[p][rIndex]){
                printf("Request denied since request + allocated exceeds max!!\n");
                break;
            }
        }
        if(rIndex == resourse){
            for(rIndex=0 ; rIndex< resourse ; rIndex++){
                allocated[p][rIndex] += req[rIndex];
                avaiable[rIndex] -= req[rIndex];
            }
            calcNeed();
            printNeed();
            if(findSafeState()){
                printf("\nSAFE SEQUENCE : ");
                for(pIndex = 0;pIndex<process-1;pIndex++)
                    printf("P%d >",safeSatte[pIndex]);
                printf("P%d\n",safeSatte[pIndex]);
            }
            else
            printf("Request denied since no SAFE SEQUENCE exixts when request is granted\n");
            for(rIndex=0 ; rIndex< resourse ; rIndex++){
                allocated[p][rIndex] -= req[rIndex];
                avaiable[rIndex] += req[rIndex];
            }
        }
        else
            break;

    }

}
void main(){
    printf("\nBANKERS ALGORITHM\n");
    read();
    scan();
    need = (int **)malloc(process * sizeof(int *)); 
    for (i=0; i<process; i++) 
         need[i] = (int *)malloc(resourse * sizeof(int));
    calcNeed();
    printNeed();
    safeSatte =(int *) malloc(process*sizeof(int));
    if(findSafeState()){
        printf("\nSAFE SEQUENCE : ");
        for(pIndex = 0;pIndex<process-1;pIndex++)
            printf("P%d >",safeSatte[pIndex]);
        printf("P%d\n",safeSatte[pIndex]);
    }
    else{
        printf("\nNO SAFE SEQUENCE EXISTS SYSYTEM IN DEADLOCK!!\n ");
        exit(1);
    }
    //read request and to check if the request can be granted or not
    printf("\nReading additional requests from process:\n");
    readReq();
    free(need);
    free(safeSatte);
    free(max);
    free(allocated);
    free(avaiable);
    
}
//end of main
