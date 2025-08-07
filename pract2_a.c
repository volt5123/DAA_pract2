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
    int n, m;
    printf("Enter the size of array(n): ");
    scanf("%d", &n);
    printf("Enter the size of array(m): ");
    scanf("%d", &m);

    double a[n][m];

    for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        printf("Enter value at [%d][%d]: ", i, j);
        scanf("%lf", &a[i][j]);
    }
}
    printf("The array is:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%0.1lf",a[i][j]);
            printf("\t");
            }
        printf("\n");
    }

    printf("\nInput Points:\n");
    for (int i = 0; i < n; i++) {
        if (m >= 2)
            printf("Point %d: (%.1lf, %.1lf)\n", i, a[i][0], a[i][1]);
        else
            printf("Point %d: (%.1lf)\n", i, a[i][0]);
    }

    double cost[MAX][MAX];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                cost[i][j] = DBL_MAX;
            else
                cost[i][j] = dist(a[i][0], a[i][1], a[j][0], a[j][1]);
        }
    }

    int near[n], used[n];
    for (int i = 0; i < n; i++) {
        near[i] = -1;
        used[i] = 0;
    }

    double min = DBL_MAX;
    int a1 = -1, b1 = -1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (cost[i][j] < min) {
                min = cost[i][j];
                a1 = i;
                b1 = j;
            }
        }
    }

    int edge[n - 1][2];
    double total = 0.0;

    edge[0][0] = a1;
    edge[0][1] = b1;
    total += cost[a1][b1];
    used[a1] = used[b1] = 1;

    update(near, cost, used, a1, n);
    update(near, cost, used, b1, n);

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

    printf("\nMST Edges:\n");
    for (int i = 0; i < n - 1; i++) {
        printf("%d - %d: %.2lf\n", edge[i][0], edge[i][1], cost[edge[i][0]][edge[i][1]]);
    }

    printf("Total: %.2lf\n", total);

    return 0;
}