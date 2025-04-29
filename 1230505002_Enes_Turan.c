#include <stdio.h>
#include <stdlib.h>

#define SONSUZ 1000000000

int minimum(int a, int b) {
    return (a < b) ? a : b;
}

int minimum_toplam_sure(int **islem_suresi, int **gecis_maliyeti, int is_sayisi, int makine_sayisi) {
    int **dp = (int **)malloc(is_sayisi * sizeof(int *));
    for (int i = 0; i < is_sayisi; i++) {
        dp[i] = (int *)malloc(makine_sayisi * sizeof(int));
        for (int j = 0; j < makine_sayisi; j++) {
            dp[i][j] = SONSUZ;
        }
    }

    for (int j = 0; j < makine_sayisi; j++) {
        dp[0][j] = islem_suresi[0][j];
    }

    for (int i = 1; i < is_sayisi; i++) {
        for (int j = 0; j < makine_sayisi; j++) {
            for (int k = 0; k < makine_sayisi; k++) {
                int maliyet = dp[i-1][k] + gecis_maliyeti[k][j] + islem_suresi[i][j];
                dp[i][j] = minimum(dp[i][j], maliyet);
            }
        }
    }

    int sonuc = SONSUZ;
    for (int j = 0; j < makine_sayisi; j++) {
        sonuc = minimum(sonuc, dp[is_sayisi-1][j]);
    }

    
    for (int i = 0; i < is_sayisi; i++) {
        free(dp[i]);
    }
    free(dp);

    return sonuc;
}

int main() {
    
    int is_sayisi = 3;
    int makine_sayisi = 2;

    
    int islem_suresi_dizi[3][2] = {
        {4, 6},
        {5, 3},
        {7, 8}
    };


    int gecis_maliyeti_dizi[2][2] = {
        {0, 2},
        {2, 0}
    };

    
    int **islem_suresi = (int **)malloc(is_sayisi * sizeof(int *));
    int **gecis_maliyeti = (int **)malloc(makine_sayisi * sizeof(int *));
    for (int i = 0; i < is_sayisi; i++) {
        islem_suresi[i] = (int *)malloc(makine_sayisi * sizeof(int));
        for (int j = 0; j < makine_sayisi; j++) {
            islem_suresi[i][j] = islem_suresi_dizi[i][j];
        }
    }
    for (int i = 0; i < makine_sayisi; i++) {
        gecis_maliyeti[i] = (int *)malloc(makine_sayisi * sizeof(int));
        for (int j = 0; j < makine_sayisi; j++) {
            gecis_maliyeti[i][j] = gecis_maliyeti_dizi[i][j];
        }
    }

    
    int minimum_sure = minimum_toplam_sure(islem_suresi, gecis_maliyeti, is_sayisi, makine_sayisi);

    printf("Minimum toplam is tamamlama suresi: %d\n", minimum_sure);

   
    for (int i = 0; i < is_sayisi; i++) {
        free(islem_suresi[i]);
    }
    for (int i = 0; i < makine_sayisi; i++) {
        free(gecis_maliyeti[i]);
    }
    free(islem_suresi);
    free(gecis_maliyeti);

    return 0;
}
