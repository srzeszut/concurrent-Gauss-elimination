#include <stdio.h>

void printDotRepresentation(int n) {

    printf("digraph DiekertGraph {\n");

    for (int i = 1; i <= n - 1; i++) {
        for (int k = i + 1; k <= n; k++) {
            for (int j = i; j <= n + 1; j++) {
            
                printf("\tA_%d_%d -> B_%d_%d_%d;\n", i, k, i, j, k);
               
                printf("\tB_%d_%d_%d -> C_%d_%d_%d;\n", i, j, k, i, j, k);
            }
        }
    }

    for (int i = 1; i < n - 1; i++) {
        {
            int k_c = i+1;
            for (int k_a = i+1 + 1; k_a <= n; k_a++) {
                printf("\tC_%d_%d_%d -> A_%d_%d;\n", i, i+1, k_c, i+1, k_a);
            }
        };
        for (int k_c = i+1 + 1; k_c <= n; k_c++) {
            int k_a = k_c;
            printf("\tC_%d_%d_%d -> A_%d_%d;\n", i, i+1, k_c, i+1, k_a);
        }
    }


    for (int i = 1; i <= n - 1; i++) {
        for (int k = i + 1; k <= n; k++) {
            for (int j = i; j <= n + 1; j++) {
                if (j != i && i >= 2) {
                    printf("\tC_%d_%d_%d -> B_%d_%d_%d;\n", i - 1, j, i, i, j, k);

                }
            }
        }
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int k = i + 1; k <= n; k++) {
            for (int j = i; j <= n + 1; j++) {
                if (i != j && i >= 2) {
                
                    printf("\tC_%d_%d_%d -> C_%d_%d_%d;\n", i - 1, j, k, i, j, k);
                }
            }
        }
    }

    printf("}\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 1) {
        printf("N must be a positive integer.\n");
        return 1;
    }

    printDotRepresentation(n);

    return 0;
}
