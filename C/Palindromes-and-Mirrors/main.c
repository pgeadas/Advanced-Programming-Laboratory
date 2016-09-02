/*
 ============================================================================
 Name        : main.c (Problem E - Palindromes and Mirrors)
 Author      : Pedro Geadas
 Version     :
 Copyright   : 
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _no {
	char letra;
	struct _no *next;
} No_pilha;

typedef struct _cabeca {
	No_pilha *header;
	No_pilha *tail;
	int size;
} Pilha;

void push(char c, Pilha *pilha);
char pop(Pilha *pilha);
char testMirror(char c);

int main() {
	char *word = NULL, c = NULL, *word2 = NULL, *mirrorS = NULL,
			ch = NULL, x = NULL;
	int i, mirrorPalindromo = 0;
	No_pilha *element = NULL;
	Pilha *stack = NULL;

	/* initialize list */
	element = (No_pilha *) malloc(sizeof(No_pilha));
	stack = (Pilha *) malloc(sizeof(Pilha));

	if (element == NULL || stack == NULL)
		return 1;

	element->letra = c;
	element->next = NULL;
	stack->size = 0;
	stack->header = element;
	stack->tail = element;
	fflush(stdin);

	/*waits for input */
	ch = getchar();
	do {

		if (ch == EOF) {
			return 0;
		}

		word = (char *) malloc(21 * sizeof(char));
		x = 0;

		do {
			*(word + x) = ch;
			ch = getchar();
			x++;
			if (x == 20) {
				fflush(stdin);
				break;
			}
		} while (ch != '\n');

		*(word + x) = '\0';

		mirrorPalindromo = 0;

		mirrorS = (char *) malloc(strlen(word) * sizeof(char) + 1);

		for (i = 0; i < strlen(word); i++) {

			word[i] = toupper(word[i]);
			c = word[i];

			if (c == 'A' || c == 'H' || c == 'I' || c == 'M' || c == 'O'
					|| c == 'T' || c == 'U' || c == 'V' || c == 'W' || c == 'X'
					|| c == 'Y' || c == '1' || c == '8') {
				mirrorPalindromo += 1;/*it can be mirror palindrome*/
			} else {
				mirrorPalindromo -= 1;/*cant be mirror palindrome*/
			}

			*(mirrorS + i) = testMirror(c);
			push(c, stack);
		}

		mirrorPalindromo -= strlen(word);
		mirrorPalindromo += 1;

		word2 = (char *) malloc(((strlen(word)) * sizeof(char)) + 1);

		i = 0;
		while (stack->size != 0) {
			*(word2 + i) = pop(stack);
			i++;
		}
		*(word2 + i) = '\0';

		if (mirrorPalindromo == 1 && strcmp(word, word2) == 0) {
			printf("%s -- is a mirrored palindrome.\n", word);
		} else if (strcmp(word, word2) == 0) {
			printf("%s -- is a regular palindrome.\n", word);
		} else {
			for (i = 0; i < strlen(mirrorS); i++) {
				push(mirrorS[i], stack);
			}
			i = 0;
			while (stack->size != 0) {
				*(word2 + i) = pop(stack);
				i++;
			}

			if (strcmp(word2, mirrorS) == 0) {
				printf("%s -- is a mirrored string.\n", word);
			} else {
				printf("%s -- is not a palindrome.\n", word);
			}
		}

	} while (ch != EOF && (ch = getc(stdin)) != '\n');

	return 0;
}

char testMirror(char c) {
	switch (c) {
	case '3':
		c = 'E';
		break;

	case 'L':
		c = 'J';
		break;

	case '2':
		c = 'S';
		break;

	case '5':
		c = 'Z';
		break;

	default:
		return c;
		break;
	}
	return c;

}

void push(char c, Pilha *pilha) {
	No_pilha *elemento;

	elemento = (No_pilha *) malloc(sizeof(No_pilha));
	if (elemento == NULL)
		return;

	elemento->letra = c;
	elemento->next = NULL;

	if (pilha->size == 0)
	{
		pilha->size = 1;
		pilha->header = elemento;
		pilha->tail = pilha->header;
	} else {
		(pilha->tail)->next = elemento;
		pilha->tail = elemento;
		pilha->size++;
	}
}

char pop(Pilha *pilha) {
	No_pilha *elemento = pilha->header;
	char retorno;

	if (pilha->header == NULL)
		return 0;

	if (pilha->header == pilha->tail)
	{
		retorno = (pilha->header)->letra;
		pilha->size = 0;
		(pilha->header)->next = NULL;
		return retorno;
	} else {
		while (elemento->next != pilha->tail)
			elemento = elemento->next;

		elemento->next = NULL;
		retorno = (pilha->tail)->letra;
		pilha->size--;
		free(pilha->tail);
		pilha->tail = elemento;

	}
	return retorno;
}
