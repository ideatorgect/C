#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////// Indexed File Allocation structure /////////////////////////////////////////////
typedef struct
{
    int p_id;
    int allocated;
    int index;
    char val;
    int index_length;
    int *addr;
} nodeIndexed;

//////////////////////////////////////////////////////// Sequential Allocation structure///////////////////////////////////////////////////
typedef struct
{
    int id;
    char val;
    int allocated;
} nodeSeq;

///////////////////////////////////////////////////// Linked List Allocation structure ////////////////////////////////////////////////////
typedef struct
{
    int p_id;
    char val;
    int index;
    int next_index;
    int allocated;
} nodeLinked;

FILE *fout;

// Linke List File Allocation Function
void linked()
{
    // Initialisation
    nodeLinked *lin, *pointer;
    FILE *mem, *proc;
    int n = 0, ind, next, len, p_id;
    char c[20];
    // Reading input from file
    // file containing info for setting the links between the nodes/spaces/blocks
    if ((mem = fopen("memorylink.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    // Reading the data from the file
    if ((proc = fopen("processlink.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    // Setting the number of blocks
    printf("Enter the no. of blocks: ");
    scanf("%d", &n);
    fprintf(fout, "Enter the no. of blocks:%d ", n);
    fprintf(fout, "%d\n", n);
    printf("\nNode Linkage data:\nCurrent Node\tNext Node\n");
    fprintf(fout, "\nNode Linkage data:\nCurrent Node\tNext Node\n");
    // setting the links between the nodes/spaces/blocks
    while (!feof(mem))
    {
        fscanf(mem, "%d\t%d", &ind, &next);
        printf("%d\t\t%d\n", ind, next);
        fprintf(fout, "%d\t\t%d\n", ind, next);
    }
    rewind(mem);

    // Pringting the contents to the console
    printf("\nProcess File Content\nProcess\t\tLength\t\tContent\n");
    fprintf(fout, "\nProcess File Content\nProcess\t\tLength\t\tContent\n");
    while (!feof(proc))
    {
        fscanf(proc, "%d\t%d\t%s", &p_id, &len, c);
        printf("P%d\t\t%d\t\t%s\n", p_id, len, c);
        fprintf(fout, "P%d\t\t%d\t\t%s\n", p_id, len, c);
    }
    rewind(proc);

    // Initialising the data
    lin = (nodeLinked *)malloc(n * sizeof(nodeLinked));
    for (int i = 0; i < n; i++)
    {
        (lin + i)->index = i + 1;
        (lin + i)->next_index = -1;
        (lin + i)->allocated = -1;
        (lin + i)->p_id = -1;
    }
    int free = 0, links = 0;
    while (!feof(mem))
    {
        fscanf(mem, "%d\t%d", &ind, &next);
        (lin + ind - 1)->next_index = next;
        free++;
    }
    links = free;
    int last = 0, num_process = 0, end = -1;

    printf("\nProcess\t\tStartAddress\tEndAddress\tStatus\n");
    fprintf(fout, "\nProcess\t\tStartAddress\tEndAddress\tStatus\n");
    // Reading the process file and allocating to the memory
    while (!feof(proc))
    {
        fscanf(proc, "%d\t%d\t%s", &p_id, &len, c);
        printf("P%d\t\t%d\t", p_id, last + 1);
        fprintf(fout, "\tP%d\t\t%d\t", p_id, last + 1);
        // Memory availability and checking already allocated
        if (free - len >= 0 && (lin + last)->allocated == -1)
        {
            num_process++;
            // Traversing through the string
            for (int j = 0; j < len; j++)
            {
                // Setting the process id to the block it bellogs to
                (lin + last)->allocated = p_id; // Allocated or not
                (lin + last)->val = c[j];       // Setting the data
                (lin + last)->p_id = p_id;      // Setting the process id associated with it
                end = last;                     // Setting the ending address of the block
                // Updating the last allocated area
                last = (lin + last)->next_index - 1;
                // Free space reduces acquired by data
                free--;
            }
        }
        // If unallocated due to memory insufficency
        if (end == -1)
        {
            printf("\t%s\t\t%s\n", " ", "Not Alloted");
            fprintf(fout, "\t%s\t\t%s\n", " ", "Not Alloted");
        }
        // If alloted
        else
        {
            printf("\t%d\t\t%s\n", end + 1, "Alloted");
            fprintf(fout, "\t%d\t\t%s\n", end + 1, "Alloted");
        }
        end = -1;
    }
    rewind(proc);

    // Printing the output
    printf("\nContents of Process\n");
    fprintf(fout, "\nContents of Process\n");
    while (!feof(proc))
    {
        fscanf(proc, "%d\t%d\t%s", &p_id, &len, c);
        printf("P%d\n", p_id);
        fprintf(fout, "P%d\n", p_id);
        for (int i = 0; i < n; i++)
        {
            if (p_id == (lin + i)->p_id)
            {
                printf("\t%d\t%c\n", i + 1, (lin + i)->val);
                fprintf(fout, "\t%d\t%c\n", i + 1, (lin + i)->val);
            }
        }
    }

    // Closing the files
    fclose(proc);
    fclose(mem);
}

////////////////////////////////////////////////////// Sequential Allocation Function ////////////////////////////////////////////////////
void sequential()
{
    // Initialisation
    nodeSeq *seq;
    int i;
    FILE *fptr;
    int n = 0, ind, len;
    char c[20];
    // input from the file
    if ((fptr = fopen("sequential.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    // Setting the number of blocks
    printf("Enter the no. of blocks: ");

    scanf("%d", &n);
    fprintf(fout, "Enter the no. of blocks: %d", n);
    fprintf(fout, "%d\n", n);
    printf("File Content\nStarting Address\tLength\tContent\n");
    fprintf(fout, "File Content\nStarting Address\tLength\tContent\n");
    // Printing contents of file to console and output file
    while (!feof(fptr))
    {
        fscanf(fptr, "%d\t%d\t%s", &ind, &len, c);
        printf("%d\t\t\t%d\t%s\n", ind, len, c);
        fprintf(fout, "\t\t%d\t\t\t%d\t%s\n", ind, len, c);
    }
    rewind(fptr);
    // Initialising the required structure
    seq = (nodeSeq *)malloc(n * sizeof(nodeSeq));
    for (i = 0; i < n; i++)
    {
        (seq + i)->id = i + 1;
        (seq + i)->allocated = -1;
        (seq + i)->val = ' ';
    }
    int last = 0;
    // Allocating the data according to algorithm
    printf("\nRequest's Status: \n");
    fprintf(fout, "\nRequest's Status: \n");
    while (!feof(fptr))
    {
        fscanf(fptr, "%d\t%d\t%s", &ind, &len, c);
        // Allocating based on algorithm.
        // Memory availability and checking already allocated
        if (last + len < n && (seq + ind - 1)->allocated == -1)
        {
            printf("\t%d\tAllocated\n", ind);
            fprintf(fout, "\t%d\tAllocated\n", ind);
            // Traversing through the string
            for (int j = 0; j < len; j++)
            {
                // Allocating sequentially
                (seq + ind - 1 + j)->allocated = ind - 1; // Allocated or not
                (seq + ind - 1 + j)->val = c[j];          // Setting the data
                // Update last position
                last = ind - 1 + j;
            }
        }
        else
        {
            // Print if cannot be allocated (Memory insufficient or already allocated)
            printf("\t%d\tNot allocated\n", ind);
            fprintf(fout, "\t%d\tNot allocated\n", ind);
        }
    }

    // Printing the ouput
    printf("Status of memory blocks\t\tBlocks\t\tContents\n");
    fprintf(fout, "Status of memory blocks\t\tBlocks\t\tContents\n");
    // Traversing through the block
    for (i = 0; i < n; i++)
    {
        printf("\t%d\t\t\t%s\t%c\n", (seq + i)->id, ((seq + i)->allocated == -1) ? "Free" : "Occupied", (seq + i)->val);
        fprintf(fout, "\t\t%d\t\t\t\t\t%s\t\t%c\n", (seq + i)->id, ((seq + i)->allocated == -1) ? "Free" : "Occupied", (seq + i)->val);
    }
    //  File closing
    fclose(fptr);
}

// Indexed file allocation function
void indexed()
{
    // Initialisation
    nodeIndexed *indNode;
    FILE *proc;
    int n = 0, ind, p_id, len;
    char c[20];
    // Reading from the the input file
    if ((proc = fopen("indexed.txt", "r")) == NULL)
    {
        printf("Error! opening memory link file");
        exit(1);
    }

    // Setting the number of blocks
    printf("Enter the no. of blocks: ");
    scanf("%d", &n);
    fprintf(fout, "Enter the no. of blocks: %d", n);
    fprintf(fout, "%d\n", n);

    printf("Process File Content\nProcess\tLength\tIndex\tContent\n");
    fprintf(fout, "Process File Content\nProcess\tLength\tIndex\tContent\n");
    // Printing the contents to console and file
    while (!feof(proc))
    {
        fscanf(proc, "%d\t%d\t%d\t%s", &p_id, &len, &ind, c);
        printf("P%d\t%d\t%d\t%s\n", p_id, len, ind, c);
        fprintf(fout, "\tP%d\t\t%d\t\t%d\t\t%s\n", p_id, len, ind, c);
    }
    rewind(proc);

    // Initialising the blocks
    indNode = (nodeIndexed *)malloc(n * sizeof(nodeIndexed));
    for (int i = 0; i < n; i++)
    {
        (indNode + i)->addr = NULL;
        (indNode + i)->allocated = -1;
        (indNode + i)->val = ' ';
        (indNode + i)->p_id = -1;
        (indNode + i)->index = -1;
        (indNode + i)->index_length = -1;
    }

    // Reading the files and allocating the data in the memory
    int free = n;
    while (!feof(proc))
    {
        fscanf(proc, "%d\t%d\t%d\t%s", &p_id, &len, &ind, c);
        // Memory availability and checking already allocated
        if (free >= len + 1 && (indNode + ind - 1)->allocated == -1)
        {
            (indNode + ind - 1)->index = ind;      // Setting the index block
            (indNode + ind - 1)->p_id = p_id;      // Setting the process id
            (indNode + ind - 1)->allocated = p_id; // Allocated or not
            // Allocating the space in the index table for keeping the address
            (indNode + ind - 1)->addr = (int *)malloc(len * sizeof(int));
            (indNode + ind - 1)->index_length = len; // Setting the number of blocks taken by the data
            // Reducing the space acquired by the index table
            free--;
            // Traversing through the string
            for (int j = 0; j < len; j++)
            {
                int addr = -1;
                // Searching for holes
                for (int k = 0; k < n; k++)
                {
                    if ((indNode + k)->allocated == -1)
                    {
                        addr = k;
                        // If found break out
                        break;
                    }
                }
                // Setting data to the required hole and updating index
                if (addr != -1 && free >= len)
                {
                    (indNode + ind - 1)->addr[j] = addr; // Updating the address in index table
                    (indNode + addr)->val = c[j];        // Setting data in hole
                    (indNode + addr)->p_id = p_id;       // Setting the process id associated
                    (indNode + addr)->allocated = p_id;  // Allocated or not
                    // Reducingthe sapce acquired by data
                    free--;
                }
            }
        }
    }

    rewind(proc);
    // Printing the output
    printf("\nProcess\t\tIndex\t\tBlocks\t\tStatus\n");
    fprintf(fout, "\nProcess\t\tIndex\t\tBlocks\t\tStatus\n");

    while (!feof(proc))
    {
        fscanf(proc, "%d\t%d\t%d\t%s", &p_id, &len, &ind, c);
        if ((indNode + ind - 1)->index != -1)
        {
            printf("P%d\t\t%d\t\t", (indNode + ind - 1)->p_id, ind);
            fprintf(fout, "P%d\t\t%d\t\t", (indNode + ind - 1)->p_id, ind);
            for (int j = 0; j < (indNode + ind - 1)->index_length; j++)
            {
                printf("%d, ", (indNode + ind - 1)->addr[j] + 1);
                fprintf(fout, "%d, ", (indNode + ind - 1)->addr[j] + 1);
            }
            printf("\t\tAlloted\n");
            fprintf(fout, "\t\tAlloted\n");
        }
        else
        {
            printf("P%d\t\t%d\t\t\t\tNot Alloted\n", p_id, ind);
            fprintf(fout, "P%d\t\t%d\t\t\t\t\t\tNot Alloted\n", p_id, ind);
        }
    }
    printf("\nAllocation\n");
    fprintf(fout, "\nAllocation\n");
    printf("Index\tBlock\tContents\n");
    fprintf(fout, "Index\tBlock\tContents\n");

    for (int i = 0; i < n; i++)
    {
        if ((indNode + i)->index != -1)
        {
            for (int j = 0; j < (indNode + i)->index_length; j++)
            {
                printf("%d\t%d\t%c\n", i + 1, (indNode + i)->addr[j] + 1, (indNode + (indNode + i)->addr[j])->val);
                fprintf(fout, "%d\t\t%d\t\t%c\n", i + 1, (indNode + i)->addr[j] + 1, (indNode + (indNode + i)->addr[j])->val);
            }
        }
    }
    // Closing the file
    fclose(proc);
}

// Main function
int main()
{

    int ch;
    fout = fopen("output.txt", "w");
    if (fout == NULL)
    {
        printf("Error!\n");
        exit(1);
    }

    // Menu for the sellection of various allocation!
    while ('True')
    {
        printf("Menu\n1.SEQUENTIAL\n2.LINKED\n3.INDEXED\n4.EXIT\nenter choice:");

        scanf("%d", &ch);
        fprintf(fout, "Menu\n1.SEQUENTIAL\n2.LINKED\n3.INDEXED\n4.EXIT\nenter choice: %d", ch);
        //switch case for choosing the menu
        switch (ch)
        {
        case 1:
            printf("\nSEQUENTIAL\n");
            fprintf(fout, "\nSEQUENTIAL\n");
            sequential();
            break;
        case 2:
            printf("\nLINKED\n");
            fprintf(fout, "\nLINKED\n");
            linked();
            break;
        case 3:
            printf("\nINDEXED\n");
            fprintf(fout, "\nINDEXED\n");
            indexed();
            break;
        case 4:
            printf("\nEXITING...\n");
            fprintf(fout, "\nEXITING...\n");
            exit(0);
            break;

        default:
            printf("Invalid choice\n");
            fprintf(fout, "Invalid choice\n");
            break;
        }
    }

    fclose(fout);
    return (0);
}
