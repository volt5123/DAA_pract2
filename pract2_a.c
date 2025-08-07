#include <stdio.h>
#include <stdbool.h>

#define MAX 100
#define INF 999999

int main() {
    int n;
    printf("Enter Size of Array: ");
    scanf("%d", &n);

    int dist[MAX][MAX];
    int i, j;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(i == j) {
                dist[i][j] = 0;
            } else {
                printf("\n%d%d index: ", i, j);
                scanf("%d", &dist[i][j]);
            }
        }
    }
    printf("\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%d ",dist[i][j]);
        }
        printf("\n");
    }

    int parent[MAX];
    int key[MAX];
    bool mstSet[MAX];

    for(i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = false;
        parent[i] = -1;
    }

    key[0] = 0;

    for(int count = 0; count < n - 1; count++) {
        int min = INF, u = -1;

        for(i = 0; i < n; i++) {
            if(mstSet[i] == false && key[i] < min) {
                min = key[i];
                u = i;
            }
        }

        mstSet[u] = true;

        for(int v = 0; v < n; v++) {
            if(dist[u][v] && mstSet[v] == false && dist[u][v] < key[v]) {
                parent[v] = u;
                key[v] = dist[u][v];
            }
        }
    }

    int totalDistance = 0;
    printf("\nEdges:\n");
    for(i = 1; i < n; i++) {
        printf("A%d - A%d : %d\n", parent[i] + 1, i + 1, dist[i][parent[i]]);
        totalDistance += dist[i][parent[i]];
    }
    printf("Total minimum distance: %d\n", totalDistance);

    return 0;
}
