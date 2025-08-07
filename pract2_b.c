#include <stdio.h>
#include <math.h>
#include <float.h>

#define MAX 100

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

void update(int near[], double cost[][MAX], int used[], int new_node, int n) {
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            if (near[i] == -1 || cost[i][new_node] < cost[i][near[i]]) {
                near[i] = new_node;
            }
        }
    }
}

int main() {
    int n = 6;

    const char* cities[6] = {
        "Delhi", "Mumbai", "Kolkata", "Chennai", "Bengaluru", "Hyderabad"
    };

    double coordinates[6][2] = {
        {28, 77},
        {19, 72},
        {22, 88},
        {13, 80},
        {12, 77},
        {17, 78}
    };

    double cost[MAX][MAX];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                cost[i][j] = DBL_MAX;
            else
                cost[i][j] = dist(coordinates[i][0], coordinates[i][1], coordinates[j][0], coordinates[j][1]);
        }
    }

    int near[n], used[n];
    for (int i = 0; i < n; i++) {
        near[i] = -1;
        used[i] = 0;
    }

    double min = DBL_MAX;
    int u = -1, v = -1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (cost[i][j] < min) {
                min = cost[i][j];
                u = i;
                v = j;
            }
        }
    }

    int edge[n - 1][2];
    double total = 0.0;

    edge[0][0] = u;
    edge[0][1] = v;
    total += cost[u][v];
    used[u] = used[v] = 1;

    update(near, cost, used, u, n);
    update(near, cost, used, v, n);

    for (int cnt = 1; cnt < n - 1; cnt++) {
        double d = DBL_MAX;
        int k = -1;
        for (int i = 0; i < n; i++) {
            if (!used[i] && near[i] != -1 && cost[i][near[i]] < d) {
                d = cost[i][near[i]];
                k = i;
            }
        }
        if (k == -1) break;
        edge[cnt][0] = k;
        edge[cnt][1] = near[k];
        total += cost[k][near[k]];
        used[k] = 1;
        update(near, cost, used, k, n);
    }

    printf("\nMinimum Spanning Tree:\n");
    printf("Edge\t\tDistance\n");
    for (int i = 0; i < n - 1; i++) {
        printf("%s - %s\t%.2lf\n", cities[edge[i][0]], cities[edge[i][1]], cost[edge[i][0]][edge[i][1]]);
    }

    printf("Total: %.2lf\n", total);

    return 0;
}
