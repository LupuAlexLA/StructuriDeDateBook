#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define DIM 100
#define LINE_BUFFER 128

typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct DDLL Stack;
typedef struct DDLL Queue;
typedef struct DDLL Deck;

static bool switcher = true;

struct Masina {
	char* nume;
	int cai;
};

struct Nod {
	struct Masina* masina;
	struct Nod* next;
	struct Nod* prev;
};

struct DDLL {
	struct Nod* head;
	struct Nod* tail;
};

Masina* creareMasina(const char* nume, int cai) {
	Masina* masina = NULL;
	masina = (Masina*)malloc(sizeof(Masina));
	masina->nume = (char*)malloc(strlen(nume) + 1);
	strcpy(masina->nume, nume);
	masina->cai = cai;
	return masina;
}

Nod* creareNod(Masina* masina) {
	Nod* nod = NULL;
	nod = (Nod*)malloc(sizeof(Nod));
	nod->next = NULL;
	nod->prev = NULL;
	nod->masina = masina;
	return nod;
}

void afisareMasina(Masina* masina) {
	printf("InfoUtil: Nume masina: %s, cai: %d\n", masina->nume, masina->cai);
}

void dezalocareMasina(Masina* masina) {
	free(masina->nume);
	free(masina);
}

// operatia 1.1
void push(Stack* stack, Masina* masina) {
	Nod* nod = creareNod(masina);
	if (stack->head == NULL && stack->tail == NULL) {
		stack->head = stack->tail = nod;
	}
	else {
		nod->next = stack->head;
		stack->head->prev = nod;
	}
	stack->head = nod;
}

// operatia 1.2
Masina* pop(Stack* stack) {
	Masina* result = NULL;
	if (stack->head != NULL) {
		result = stack->head->masina;
		Nod* tmp = stack->head;
		stack->head = stack->head->next;
		if (stack->head != NULL) {
			stack->head->prev = NULL;
		}
		else {
			stack->tail = NULL;
		}
		free(tmp);
	}
	return result;
}

// operatia 2.1
void put(Queue* queue, Masina* masina) {
	Nod* nod = creareNod(masina);
	if (queue->head == NULL && queue->tail == NULL) {
		queue->head = queue->tail = nod;
	}
	else {
		nod->prev = queue->tail;
		queue->tail->next = nod;
	}
	queue->tail = nod;
}

// operatia 2.2
Masina* get(Queue* queue) {
	Masina* result = NULL;
	if (queue->head != NULL) {
		result = queue->head->masina;
		Nod* tmp = queue->head;
		queue->head = queue->head->next;
		if (queue->head != NULL) {
			queue->head->prev = NULL;
		}
		else {
			queue->tail = NULL;
		}
		free(tmp);
	}
	return result;
}

// operatia 3.1
void enqueue(Deck* deck, Masina* masina) {
	Nod* nod = creareNod(masina);
	if (deck->head == NULL && deck->tail == NULL) {
		deck->head = deck->tail = nod;
	}
	else {
		if (switcher) {
			nod->next = deck->head;
			deck->head->prev = nod;
			deck->head = nod;
		} 
		else {
			nod->prev = deck->tail;
			deck->tail->next = nod;
			deck->tail = nod;
		}
	}
	switcher = !switcher;
}

// operatia 3.2
Masina* dequeue(Deck* deck) {
	Masina* result = NULL;
	if (deck->head != NULL) {
		if (switcher) {
			result = deck->head->masina;
			Nod* tmp = deck->head;
			deck->head = deck->head->next;
			if (deck->head != NULL) {
				deck->head->prev = NULL;
			}
			else {
				deck->tail = NULL;
			}
			free(tmp);
		}
		else {
			result = deck->tail->masina;
			Nod* tmp = deck->tail;
			deck->tail = deck->tail->prev;
			if (deck->tail != NULL) {
				deck->tail->next = NULL;
			}
			else {
				deck->head = NULL;
			}
			free(tmp);
		}
	}
	switcher = !switcher;
	return result;
}

// operatia 4
Masina* peek(struct DDLL* capat) {
	return capat->head->masina;
}

// operatia 5
void afisareStiva(Stack* stack) {
	if (stack->head != NULL && stack->tail != NULL) {
		Masina* masina = pop(stack);
		afisareMasina(masina);
		afisareStiva(stack);
		push(stack, masina);
	}
}

void main() {
	FILE* f = fopen("Masini.txt", "r");
	Stack stack = { .head = NULL, .tail = NULL };
	Queue queue = { .head = NULL, .tail = NULL };
	Deck deck = { .head = NULL, .tail = NULL };
	Masina* m1 = NULL, * m2 = NULL, * m3 = NULL;
	char* token, sep_list[] = ",\n", file_line_buf[LINE_BUFFER], * nume = NULL;
	int cai;

	if (f) {
		while (fgets(file_line_buf, sizeof(file_line_buf), f)) { 
			// citire nume
			token = strtok(file_line_buf, sep_list); 
			nume = (char*)malloc((strlen(token) + 1) * sizeof(char)); 
			strcpy(nume, token); 
			// citire salariu
			token = strtok(NULL, sep_list); 
			cai = atoi(token);
			// creare informatie utila
			m1 = creareMasina(nume, cai);
			m2 = creareMasina(nume, cai);
			m3 = creareMasina(nume, cai);
			// operatia 1.1 
			push(&stack, m1);
			// operatia 2.1
			put(&queue, m2);
			// operatia 3.1
			enqueue(&deck, m3);
		}
		fclose(f);
	}

	// operatia 4
	Masina* masina = NULL;

	printf("\nOperatia 4\nAcces element disponibil in STACK:\n");
	masina = peek(&stack);
	afisareMasina(masina);
	
	printf("\nOperatia 4\nAcces element disponibil in QUEUE:\n");
	masina = peek(&queue);
	afisareMasina(masina);

	printf("\nOperatia 4\nAcces element disponibil in DECK:\n");
	masina = peek(&deck);
	afisareMasina(masina);

	// operatia 5
	printf("\nOperatia 5\nAfisarea elementelor din STACK:\n");
	afisareStiva(&stack);

	printf("\nExtragerea tuturor elementelor din STACK:\n");
	while (stack.head) {
		// operatia 1.2
		Masina* masina = pop(&stack);
		afisareMasina(masina);
		dezalocareMasina(masina);
	}

	printf("\nExtragerea tuturor elementelor din QUEUE:\n");
	while (queue.head) {
		// operatia 2.2
		Masina* masina = get(&queue);
		afisareMasina(masina);
		dezalocareMasina(masina);
	}

	printf("\nExtragerea tuturor elementelor din DECK:\n");
	while (deck.head) {
		// operatia 3.2
		Masina* masina = dequeue(&deck);
		afisareMasina(masina);
		dezalocareMasina(masina);
	}
}
