#include<stdio.h> 
const int P = 5;     //No. of processes 
const int R = 3;    // No. of resources
    
// Fuction to find safe state  
void Safe(int process[], int avl[], int max[][R], int allot[][R],int need[][R]) 
{  
    int finish[P] = {0};               // Mark all processes infinish 
    int sSeq[P];                     // to store safe sequence 
  
    int Work[R];                      // Make a copy of available resources 
    for (int i=0;i<R;i++) 
        Work[i] = avl[i]; 
  
   int count = 0;              // While all processes are not finished 
    while (count < P)           // or system is not in safe state
    { 
         
        int f= 0;                      // Find a process which is not finish and whose needs
        for (int p = 0; p < P; p++)          // can be satisfied with current Work[] resources.
        { 
            
            if (finish[p] == 0)             // First check if a process is finished, 
                {                            // if no, go for next condition 
                
                int j; 
                for (j = 0; j < R; j++)         // Check if for all resources of current 
                    if (need[p][j] > Work[j])    // P need is less than Work.
                     break; 
  
                if (j == R)                       // If all needs of p were satisfied.
                { 
                   for (int k = 0 ; k < R ; k++)   // Add the allocated resources of 
                    Work[k] += allot[p][k];        // current P to the available/Work 
                                                   // resources i.e.free the resources 
                    
					sSeq[count++] = p;         // Add this process to safe sequence.
                    finish[p] = 1;               // Mark this p as finished 
                    f = 1; 
                } 
            } 
        } 
  
         
        if (f == 0)            // If we could not find a next process in safe sequence.
        { 
            printf ("System is not in safe state"); 
        } 
    } 
    printf ("....System is in safe state......\n");    // If system is in safe state then print it
    printf("\nSafe state is: "); 
	for (int i=0;i<P;i++) 
        printf ("%d " ,sSeq[i]); 
} 
  

int main() 
{ 
    int process[] = {0, 1, 2, 3, 4}; 
    int avl[] = {3, 3, 2};              // avlable instances of resources
    int max[][R] = {{7, 5, 3},         // Maximum Resourses can be allocated  
                     {3, 2, 2}, 
                     {9, 0, 2}, 
                     {2, 2, 2}, 
                     {4, 3, 3}}; 
    int allot[][R] = {{0, 1, 0},       // Resources allocated to processes
                      {2, 0, 0}, 
                      {3, 0, 2}, 
                      {2, 1, 1}, 
                      {0, 0, 2}}; 
    int need[P][R];                              //to store need of each process
	 
	for (int i=0;i<P;i++)                        // Calculating Need of each Process
      for (int j=0;j<R;j++)                   
          need[i][j] = max[i][j] - allot[i][j]; 
          
    Safe(process, avl, max, allot,need);              //fn to check safe state
    return 0; 
} 

