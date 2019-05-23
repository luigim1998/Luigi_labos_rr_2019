#include <iostream>
using namespace std;

int main() {
    // P0, P1, P2, P3, P4 are the Process names here 
    
    int processes, resources, i, j, k;
    processes = 5; // Number of processes
    resources = 3; // Number of resources
    int alloc[5][3] = {{0, 1, 0}, // P0    // Allocated resource matrix
                       {2, 0, 0}, // P1
                       {3, 0, 2}, // P2
                       {2, 1, 1}, // P3
                       {0, 0, 2}}; // P4
    
    int max[5][3] = {{7, 5, 3}, // P0    // Matrix with the maximum resources a process can request
                     {3, 2, 2}, // P1
                     {9, 0, 2}, // P2
                     {2, 2, 2}, // P3
                     {4, 3, 3}}; // P4
    
    int avail[3] = {3, 3, 2}; // Available Resources
    
    int finish[processes];
    int ans[processes], ind = 0;
    for (k = 0; k < processes; k++) {// All values are zero until they are finished
        finish[k] = 0;
    }
    int need[processes][resources];// Matrix with resources that are needed to complete
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    int y = 0;
    for (k = 0; k < 5; k++) {
        for (i = 0; i < processes; i++) {
            if (finish[i] == 0) {
                
                int flag = 0;
                for (j = 0; j < resources; j++) {
                    if (need[i][j] > avail[j]) {// Change the value of the flag if there is not enough available resource
                        flag = 1;
                        break;
                    }
                }
                
                if (flag == 0) { // If the flag is zero, it means that it can enter the escalation sequence
                    ans[ind++] = i;
                    for (y = 0; y < resources; y++)
                        avail[y] += alloc[i][y];
                    finish[i] = 1;
                }
            }
        }
    }
    
    cout << "Following is the SAFE Sequence" << endl;
    for (i = 0; i < processes - 1; i++)
        cout << " P" << ans[i] << " ->";
    cout << " P" << ans[processes - 1] << endl;
    
    return (0);
    
    // This code is contributed by Deep Baldha (CandyZack) 
} 