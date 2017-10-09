#include <stdio.h>
#include <stdlib.h>
///written by Henry Mattoon,
///based of Dijkstra pseudocode on wikipedia
int dijkstraDist(int cost[8][8], int start ,int end, int nUI);

int main()
{
    int nUI=8; ///number of inputs change depending on how many different nodes there are.
    int input;
    int start, end;
    int line;


    //printf("please enter the number of nodes within matrix file: ");
    //scanf("%d", &nUI);
    printf("number of nodes is %d, now enter the starting node (0=A, 1=B, etc): ",nUI);
    scanf("%d", &start);
    printf("starting node is %c, now enter the ending node (0=A, 1=B, etc): ",start+65);
    scanf("%d", &end);
    printf("ending node is %c\n",end+65);

    int cost[nUI][nUI];

    FILE *file;
    file=fopen("shortest_path_matrix.txt","r");

    fscanf(file, "%d", &input);
    int j= 0;
    while(!feof(file)) {
        int i =0;
        for (i=0;i<nUI;i++){
                ///printf ("%d ", input);//for testing purposes only
                cost[i][j]=input;///send contents of file to 2d array
                fscanf (file, "%d", &input);
        }
        ///printf("\n");
        j++;
    }
    fclose(file);
    //at this point the cost has been filled
    int distance = dijkstraDist(cost, start, end, nUI);
    printf("\n\nthe distance between the two is: %d", distance);
    printf("\n\n");

}




int dijkstraDist(int cost[8][8], int start ,int end, int nUI){
        int current[nUI], prevNode[nUI], path[nUI];
        int min, nextNode, distHolder,i;
        int distance[nUI];

        for(i=0; i<nUI; i++){ ///initiate the arrays
            prevNode[i]=-10;    ///prevNode is set to a non existant node, this will be the path eventually
            current[i]=0;       ///current node is set to zero everywhere except for the starting node which is set to 1
            distance[i]=1000;   ///distance is set to the max value everywhere except at start because distance from start to start is nothing (0)

        }
        distance[start]=0;
        current[start]=1;
        while(current[end]==0){ ///loop will keep running until it has been signaled that the end has been reached.
            min =1000;          ///set min to maximum value (not infinity but close enough)
            nextNode=0;         ///
            for(i=0;i<nUI;i++){ /// going through all the different neighbors of the current node which at first is the start node.
                distHolder=distance[start]+cost[start][i]; ///updating distance holder
                if(distHolder<distance[i]&&current[i]==0){
                    distance[i]=distHolder;///saving distance
                    prevNode[i]=start;///saving path
                }
                if(min>distance[i]&&current[i]==0){
                    min=distance[i];
                    nextNode=i;
                }
            }
            start=nextNode;
            current[start]=1;

        }
        int k=0;
        printf("goal: ");
        i=end;

        while(i!=-10){///testing
            printf(" %c ",i+65); ///converting prevNode to char using its ascii code
            //printf("\n");

            i=prevNode[i];
        }
        printf(" :beginning.");

        return distance[end];


    }
