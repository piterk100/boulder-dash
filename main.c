#include <stdio.h>
#include <stdlib.h>

#define ROCKFORD '@'
#define PUSTE ' '
#define ZIEMIA '+'
#define KAMIEN 'O'
#define DIAMENT '$'
#define WYJSCIE 'X'

#define GORA 'w'
#define LEWO 'a'
#define DOL 's'
#define PRAWO 'd'

struct plansza_info {
    int rockford_x;
    int rockford_y;
    int wszystkie_diamenty;
    int zebrane_diamenty;
    int czy_koniec;
};

struct plansza_info wpisz(char** p, int w) {
    int diamenty = 0, rockford_x = 0, rockford_y = 0, j;
    char x = (char) getchar();
    for (int i = 0; i < w; i++) {
        j = 0;
        while ((x = (char) getchar()) != '\n') {
            p[i][j] = x;
            if (x == DIAMENT)
                diamenty++;
            else if (x == ROCKFORD) {
                rockford_x = i;
                rockford_y = j;
            }
            j++;
        }
    }
    struct plansza_info info = { rockford_x, rockford_y, diamenty , 0 , 0 };
    return info;
}

void wypisz(char** p, int w, int k) {
    printf("%d %d\n", w, k);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < k; j++)
            putchar(p[i][j]);
        printf("\n");
    }
}

void zamien(char** p, int x1, int x2, int y1, int y2) {
    char x = p[x1][y1];
    p[x1][y1] = p[x2][y2];
    p[x2][y2] = x;
}

void stabilizuj(char** p, int w, int k) {
    int x;
    for (int i = w - 3; i > 0; i--) {
        for (int j = 1; j < k - 1; j++) {
            if (p[i][j] == KAMIEN || p[i][j] == DIAMENT) {
                x = i;
                while (p[x + 1][j] == PUSTE)
                    x++;
                if (x != i)
                    zamien(p, i, x, j, j);
            }
        }
    }
}

void aktualizuj(struct plansza_info* info, int x, int y) {
    info->rockford_x = x;
    info->rockford_y = y;
}

void ruch(char** p, struct plansza_info* info, int x, int y) {
    if (info->czy_koniec != 1) {
        switch (p[x][y])
        {
        case PUSTE:
            zamien(p, info->rockford_x, x, info->rockford_y, y);
            aktualizuj(info, x, y);
            break;
        case ZIEMIA:
            p[x][y] = PUSTE;
            zamien(p, info->rockford_x, x, info->rockford_y, y);
            aktualizuj(info, x, y);
            break;
        case KAMIEN:
            if (y > info->rockford_y) {
                if (p[x][y + 1] == PUSTE) {
                    zamien(p, x, x, y, y + 1);
                    zamien(p, info->rockford_x, x, info->rockford_y, y);
                    aktualizuj(info, x, y);
                }
            }
            else if (y < info->rockford_y) {
                if (p[x][y - 1] == PUSTE) {
                    zamien(p, x, x, y, y - 1);
                    zamien(p, info->rockford_x, x, info->rockford_y, y);
                    aktualizuj(info, x, y);
                }
            }
            break;
        case DIAMENT:
            info->zebrane_diamenty++;
            p[x][y] = PUSTE;
            zamien(p, info->rockford_x, x, info->rockford_y, y);
            aktualizuj(info, x, y);
            break;
        case WYJSCIE:
            if (info->zebrane_diamenty == info->wszystkie_diamenty) {
                p[info->rockford_x][info->rockford_y] = PUSTE;
                info->czy_koniec = 1;
            }
            break;
        default:
            break;
        }
    }
}

void gra(char** p, int w, int k, struct plansza_info info) {
    char x = '1';
    stabilizuj(p, w, k);
    wypisz(p, w, k);
    while (x != EOF) {
        x = (char) getchar();
        while (x != '\n' && x != EOF) {
            stabilizuj(p, w, k);
            if (info.rockford_x != 0) {
                switch (x)
                {
                case GORA:
                    ruch(p, &info, info.rockford_x - 1, info.rockford_y);
                    break;
                case LEWO:
                    ruch(p, &info, info.rockford_x, info.rockford_y - 1);
                    break;
                case DOL:
                    ruch(p, &info, info.rockford_x + 1, info.rockford_y);
                    break;
                case PRAWO:
                    ruch(p, &info, info.rockford_x, info.rockford_y + 1);
                    break;
                default:
                    break;
                }
            }
            stabilizuj(p, w, k);
            x = (char) getchar();
        }
        if(x != EOF)
            wypisz(p, w, k);
    }
}

int main() {
    int w, k;
    if(scanf("%d %d", &w, &k))
        w+=0;
    char** p = malloc((long unsigned int) w * sizeof(char*));
    for (int i = 0; i < w; i++)
        p[i] = malloc((long unsigned int) k * sizeof(char));
    gra(p, w, k, wpisz(p, w));
    for (int i = 0; i < w; i++)
        free(p[i]);
    free(p);
    return 0;
}
