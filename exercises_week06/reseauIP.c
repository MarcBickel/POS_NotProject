#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_NEIGHBOURS 5


typedef struct node_struct {
	unsigned char adress[4];
	struct node_struct* voisins;
	size_t nbr_voisins;
} node;

node creation(unsigned char part1, unsigned char part2, unsigned char part3, unsigned char part4) {
	node result;
	result.adress[0] = part1;
	result.adress[1] = part2;
	result.adress[2] = part3;
	result.adress[3] = part4;
	result.voisins = calloc(MAX_NEIGHBOURS + 1, sizeof(node));
	result.nbr_voisins = 0;
	
	return result;
}

int sont_voisins(node node1, node node2) {
	if (node1.nbr_voisins >= MAX_NEIGHBOURS || node2.nbr_voisins >= MAX_NEIGHBOURS) {
		printf("Les nodes ont déjà un nombre de voisins maximal.\n");
		return 1;
	} else {
		node1.voisins[node1.nbr_voisins] = node2;
		node1.nbr_voisins += 1;
		node2.voisins[node2.nbr_voisins] = node1;
		node2.nbr_voisins += 1;
		
		return 0;
	}
}

int voisins_communs(node node1, node node2) {
	int result = 0;
	for (int i = 0; i < node1.nbr_voisins; ++i) {
		for (int j = 0; j < node2.nbr_voisins; ++j) {
			if (node1.voisins[i].adress[0] == node2.voisins[j].adress[0] && node1.voisins[i].adress[1] == node2.voisins[j].adress[1] &&
			node1.voisins[i].adress[2] == node2.voisins[j].adress[2] && node1.voisins[i].adress[3] == node2.voisins[j].adress[3]) {
				result += 1;
			}
		}
	}
	
	return result;
}

void affiche_current(node current) {
	for (int i = 0; i < 4; ++i) {
		printf("%u.", current.adress[i]);
	}
}

void affiche_voisins(node current) {
	for (int i = 0; i < current.nbr_voisins; ++i) {
		affiche_current(current.voisins[i]);
		printf(", ");
	}
}

void affiche(node current) {
	printf("L'adresse du noeud est : ");
	affiche_current(current);
	printf("\n");
	
	printf("Il a actuellement %d voisins : ", current.nbr_voisins);
	affiche_voisins(current);
	
	printf("\n");
}


int main(void) {
	node node1 = creation(192, 168, 1, 1);
	node node2 = creation(192, 168, 1, 2);
	node node3 = creation(192, 168, 10, 1);
	node node4 = creation(192, 168, 10, 2);
	node node5 = creation(192, 168, 1, 3);
	node node6 = creation(192, 168, 20, 1);
	node node7 = creation(192, 168, 29, 2);
	
	sont_voisins(node1, node2);
	sont_voisins(node2, node3);
	sont_voisins(node3, node4);
	sont_voisins(node1, node5);
	sont_voisins(node5, node6);
	sont_voisins(node6, node7);
	sont_voisins(node2, node5);
	sont_voisins(node2, node6);
	sont_voisins(node3, node5);
	sont_voisins(node3, node6);
	
	affiche(node3);
	printf("Nombre de voisins : %d\n", voisins_communs(node1, node6));
	printf("nombre de voisins : %d\n", voisins_communs(node2, node5));
	
	return 0;
}
