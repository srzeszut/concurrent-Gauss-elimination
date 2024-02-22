#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void A (int k,int i,double **matrix,double **multi_matrix){
        multi_matrix[k][i] = matrix[k][i] / matrix[i][i];
    
    }

void B(int i,int j,int k, double **matrix,double **multi_matrix,double **diff_matrix){
           diff_matrix[k][j] = matrix[i][j] *multi_matrix[k][i] ;
    
}

void C(int j,int k, double **matrix,double **diff_matrix){
            matrix[k][j] -= diff_matrix[k][j];
            
 
}
void scheduler(int n, double **matrix, double **diff_matrix, double **multi_matrix) {

        for (int i = 0; i < n - 1; i++) {

            #pragma omp parallel for
            for (int k = i + 1; k < n; k++) {
                A(k, i, matrix, multi_matrix);
            }

            #pragma omp parallel for collapse(2) 
            for (int j = i; j <= n; j++) {
                for (int k = i + 1; k < n; k++) {
                    B(i, j, k, matrix, multi_matrix, diff_matrix);
                }
            }

            #pragma omp parallel for collapse(2) 
            for (int j = i; j <= n; j++) {
                for (int k = i + 1; k < n; k++) {
                    C(j, k, matrix, diff_matrix);
                }
            }
        }
    }

int main() {

    

    FILE *file;
    int n;
    int i, j;

    file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return 1;
    }

    fscanf(file, "%d", &n);


    double **matrix = (double **)malloc(n * sizeof(double *));
    double **diff_matrix = (double **)malloc(n * sizeof(double *));
    double **multi_matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc((n + 1) * sizeof(double));
        diff_matrix[i] = (double *)malloc((n + 1) * sizeof(double));
        multi_matrix[i] = (double *)malloc((n + 1) * sizeof(double));
    }
    

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
           
        }
    }

    for (i = 0; i < n; i++) {
        fscanf(file, "%lf", &matrix[i][n]);
    }

    fclose(file);
   


    scheduler(n, matrix, diff_matrix, multi_matrix);


// Back substitution
    for(i = n - 1; i >= 0; i--) {
        matrix[i][n] /= matrix[i][i];
        matrix[i][i] = 1;

        for(j = i - 1; j >= 0; j--) {
            matrix[j][n] -= matrix[j][i] * matrix[i][n];
            matrix[j][i] = 0;
        }
    }


    
    file = fopen("res.txt", "w");
    if (file == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return 1;
    }

    fprintf(file, "%d\n", n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fprintf(file, "%.1lf ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    for(i=0;i<n;i++){
        fprintf(file, "%lf ", matrix[i][n]);
    }

    fclose(file);



    for (int i = 0; i < n; i++) {
        free(matrix[i]);
        free(diff_matrix[i]);
        free(multi_matrix[i]);
    }

    free(matrix);
    free(diff_matrix);
    free(multi_matrix);
    



return 0;
}

