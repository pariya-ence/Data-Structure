#include <stdio.h>
#define V 6
int main() {
    char vertex[V] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int graph[V][V] = {
        {0, 1, 0, 0, 0, 0},  // A
        {1, 0, 1, 0, 1, 0},  // B
        {0, 1, 0, 1, 1, 0},  // C
        {0, 0, 1, 0, 1, 0},  // D
        {0, 1, 1, 1, 0, 1},  // E
        {0, 0, 0, 0, 1, 0}   // F
    };
    // แสดง Adjacency Matrix
    printf("  ");
    for (int i = 0; i < V; i++)
        printf("%c ", vertex[i]);
    printf("\n");
    for (int i = 0; i < V; i++) {
        printf("%c ", vertex[i]);
        for (int j = 0; j < V; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    return 0;
}
