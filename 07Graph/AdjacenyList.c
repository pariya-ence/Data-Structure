#include <stdio.h>
#include <stdlib.h>
#define V 6
struct Node {
    int vertex;
    struct Node* next;
};
struct Node* graph[V] = {NULL};
// เพิ่มเส้นเชื่อม
void addEdge(int u, int v) {
    struct Node* newNode;
    // u -> v
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = graph[u];
    graph[u] = newNode;
    printf("Added edge: %c -> %c\n", 'A' + u, 'A' + v);
    // v -> u (กราฟไม่มีทิศทาง)
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = u;
    newNode->next = graph[v];
    graph[v] = newNode;
    printf("Added edge: %c -> %c\n", 'A' + v, 'A' + u);
}
// แสดง Adjacency List
void printGraph() {
    struct Node* current;
    for (int i = 0; i < V; i++) {
        printf("%c -> ", 'A' + i);
        current = graph[i];
        while (current != NULL) {
            printf("%c ", 'A' + current->vertex);
            current = current->next;
        }
        printf("\n");
    }
}
int main() {
    addEdge(0, 1);  // A - B
    addEdge(1, 2);  // B - C
    addEdge(1, 4);  // B - E
    addEdge(2, 3);  // C - D
    addEdge(2, 4);  // C - E
    addEdge(3, 4);  // D - E
    addEdge(4, 5);  // E - F
    printGraph();
    return 0;
}
