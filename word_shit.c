/*
 * word_shit.c
 *
 *  Created on: 30/06/2018
 *      Author: ernesto
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define HYPHEN '-'
#define HASHIT '#'
#define APOSTROPHE '\''

#define MAX_TAM_PAL 30
#define MAX_TAM_LIN 80

static inline char es_car_descon(char c) {
	return c == HYPHEN || c == APOSTROPHE;
}
static inline char es_car_valido(char c) {
	char r = 0;

	assert(!isdigit(c));
	if (isalpha(c) || es_car_descon(c)) {
		r = 1;
	}
//	printf("car '%c' es %u\n", c, r);
	return r;
}

static inline int tam_cad(char *s) {
	int r = 0;
	while (s[r] != EOF && s[r] != '\n') {
		r++;
	}
	return r;
}

static inline void proc_linea(char *linea, int *conteos, int *carrie) {
	int carrie_int = *carrie;
	int linea_tam = tam_cad(linea);
	char uc = '\0';
	int i = 0;
	int j = 0;

	*carrie = 0;
	assert(!carrie_int || es_car_valido(linea[0]));

	while (i < linea_tam) {
		int t = 0;
		int inv_cnt = 0;

		while (i < linea_tam && !es_car_valido(linea[i])) {
			i++;
		}

		if (i == linea_tam) {
			break;
		}

		inv_cnt = es_car_descon(linea[i]);
		j = i + 1;
		while (j < linea_tam && es_car_valido(linea[j])) {
			uc = linea[j++];
			if (es_car_descon(uc)) {
				inv_cnt++;
			}
		}
		t = j - i + carrie_int - inv_cnt;
		carrie_int = 0;
		if (uc == HYPHEN) {
			assert(j == linea_tam);
			*carrie = t;
		} else {
			conteos[t]++;
		}
		assert(t > 0);
		if (j < linea_tam) {
			linea[j] = '\0';
		}
//		printf("caca '%s' tam %u car %u inv %u\n", linea + i, t, *carrie, inv_cnt);
		i = j + 1;
	}
}

int main(void) {
	char *linea = (char[MAX_TAM_LIN + 1] ) { '\0' };
	int conteos[MAX_TAM_PAL + 1] = { 0 };
	int carry = 0;

	while (fgets(linea, MAX_TAM_LIN + 1, stdin)) {
//		printf("a mi m gusta '%s':%u\n", linea, tam_cad(linea));
		if (*linea == HASHIT) {
			assert(!carry);
			for (int i = 0; i < MAX_TAM_PAL + 1; i++) {
				assert(i || !conteos[i]);
				if (conteos[i]) {
					printf("%u %u\n", i, conteos[i]);
				}
				conteos[i] = 0;
			}
			printf("\n");
		} else {
			proc_linea(linea, conteos, &carry);
		}
	}
	return EXIT_SUCCESS;
}
