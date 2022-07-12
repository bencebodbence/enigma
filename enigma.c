#include <stdio.h>
#include <stdlib.h>

typedef struct Betu {
    char betu;
    struct Betu *next;
    struct Betu *pair;
} Betu;

typedef struct {
    int allas;
    Betu *pre_head;
    Betu *post_head;
} Tarcsa;

Betu *search_betu(char betu, Tarcsa *tarcsa, int rev);
void update_osszes(Tarcsa *tarcsa1, Tarcsa *tarcsa2, Tarcsa *tarcsa3);
void update_tarcsa(Tarcsa *tarcsa);
void kezdo_allas_tarcsa(Tarcsa *tarcsa, int kezdo_allas);
Tarcsa *init_tarcsa(char alphabet[27], char order[27], int kezdo_allas);
char get_kod(char betu, Tarcsa *tarcsa1, Tarcsa *tarcsa2, Tarcsa *tarcsa3, Tarcsa *reflektor);

Betu *search_betu(char betu, Tarcsa *tarcsa, int rev) {
    Betu *current = (Betu*)malloc(sizeof(Betu));

    if (rev==0) {
        current = tarcsa->pre_head;
    }
    else {
        current = tarcsa->post_head;
    }
    while (current->betu!=betu) {
        current = current->next;
    }
    return current;
}

void update_osszes(Tarcsa *tarcsa1, Tarcsa *tarcsa2, Tarcsa *tarcsa3) {
    update_tarcsa(tarcsa1);
    if (tarcsa1->allas == 0) {
        update_tarcsa(tarcsa2);
        if (tarcsa2->allas == 0) {
            update_tarcsa(tarcsa3);
        }
    }
}

void update_tarcsa(Tarcsa *tarcsa) {
    Betu *current, *temp_pair_1, *temp_pair_2;

    current = tarcsa->pre_head;

    temp_pair_1 = current->next->pair->next;
    current->next->pair = current->pair->next;
    current->pair->next->pair = current->next; // reverse pairing
    current = current->next;

    while (current->betu!='a') {
        temp_pair_2 = current->next->pair->next;
        current->next->pair = temp_pair_1;
        temp_pair_1->pair = current->next; // reverse pairing
        temp_pair_1 = temp_pair_2;
        current = current->next;
    }

    tarcsa->allas = ((tarcsa->allas)+1)%27;
}

void kezdo_allas_tarcsa(Tarcsa *tarcsa, int kezdo_allas) {
    for (int i=0; i<kezdo_allas; i++) {
        update_tarcsa(tarcsa);
    }
}

Tarcsa *init_tarcsa(char alphabet[27], char order[27], int kezdo_allas) {
    Betu *pre_head = (Betu*)malloc(sizeof(Betu));
    Betu *post_head = (Betu*)malloc(sizeof(Betu));

    Tarcsa *tarcsa = (Tarcsa*)malloc(sizeof(Tarcsa));
    tarcsa->allas = 0;
    tarcsa->pre_head = pre_head;
    tarcsa->post_head = post_head;

    Betu *current = pre_head;
    Betu *current_pair = post_head;

    for (int i=0; i<27; i++) {
        current->betu = alphabet[i];
        current_pair->betu = alphabet[i];
        if (i!=27-1) {
            current->next = (Betu*)malloc(sizeof(Betu));
            current_pair->next = (Betu*)malloc(sizeof(Betu));
        }
        else {
            current->next = pre_head;
            current_pair->next = post_head;
        }
        current = current->next;
        current_pair = current_pair->next;
    }
    for (int i=0; i<27; i++) {
        current_pair = search_betu(order[i], tarcsa, 1);
        current->pair = current_pair;
        current_pair->pair = current;
        current = current->next;
        current_pair = current_pair->next;
    }
    kezdo_allas_tarcsa(tarcsa, kezdo_allas);
    return tarcsa;
}

char get_kod(char betu, Tarcsa *tarcsa1, Tarcsa *tarcsa2, Tarcsa *tarcsa3, Tarcsa *reflektor) {
    Betu *current;
    current = search_betu(betu, tarcsa1, 0);
    current = current->pair;
    current = search_betu(current->betu, tarcsa2, 0);
    current = current->pair;
    current = search_betu(current->betu, tarcsa3, 0);
    current = current->pair;
    current = search_betu(current->betu, reflektor, 0);
    current = current->pair;
    current = search_betu(current->betu, tarcsa3, 1);
    current = current->pair;
    current = search_betu(current->betu, tarcsa2, 1);
    current = current->pair;
    current = search_betu(current->betu, tarcsa1, 1);
    current = current->pair;
    update_osszes(tarcsa1, tarcsa2, tarcsa3);
    return current->betu;
}

int main() {
    char alphabet[] =        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
    char tarcsa1_order[] =   {'h', 'k', 'c', 'y', 'o', 'r', 'u', 'l', 'b', 'w', 'i', 'd', 'a', 'e', 'v', 'p', 'x', 'm', 'g', 'f', 'z', 's', ' ', 't', 'n', 'j', 'q'};
    char tarcsa2_order[] =   {'n', 'p', 'f', 'c', 'u', 'v', 'k', 'h', 'y', ' ', 'm', 'i', 'a', 'q', 't', 'z', 'd', 'w', 'b', 'r', 'o', 'x', 'l', 'j', 's', 'e', 'g'};
    char tarcsa3_order[] =   {'a', 'q', 'k', 'n', 'w', 't', 'h', 'g', 'c', 'u', 'o', 'x', 'l', 'i', 'y', ' ', 'm', 's', 'd', 'v', 'b', 'p', 'r', 'z', 'f', 'e', 'j'};
    char reflektor_order[] = {'f', 's', 'd', 'c', 'z', 'a', 'p', 'x', 'k', 'o', 'i', 'w', ' ', 'u', 'j', 'g', 't', 'v', 'b', 'q', 'n', 'r', 'l', 'h', 'y', 'e', 'm'};

    Tarcsa *tarcsa1 = init_tarcsa(alphabet, tarcsa1_order, 0);
    Tarcsa *tarcsa2 = init_tarcsa(alphabet, tarcsa2_order, 0);
    Tarcsa *tarcsa3 = init_tarcsa(alphabet, tarcsa3_order, 0);
    Tarcsa *reflektor = init_tarcsa(alphabet, reflektor_order, 0);

    char kod_in, kod_out;
    FILE *f1, *f2;
    f1 = fopen("in.txt", "r");
    f2 = fopen("out.txt", "w");
    if (f1 == NULL || f2 == NULL) {
        return 1;
    }

    while (fscanf(f1, "%c", &kod_in)==1) {
        kod_out = get_kod(kod_in, tarcsa1, tarcsa2, tarcsa3, reflektor);
        fprintf(f2, "%c", kod_out);
    }
    fclose(f1);
    fclose(f2);

    return 0;
}
