// Double Ended Queue (Deque) Implementation
// Supports both Static (fixed-size) and Dynamic (auto-resizing) circular arrays

#include <stdio.h>
#include <stdlib.h>

#define MAX 4
typedef struct {
	int arr[MAX]; // Static buffer
	int *dynArr;  // Dynamic buffer pointer
	int front, rear, size;
} Deque;

// --- Static Deque Functions ---
// Uses circular array logic within a fixed MAX size

void insertFrontS(Deque *q, int v) {
	// Check if queue is full (next rear would hit front)
	if ((q->rear + 1) % MAX == q->front) {
		printf("Full\n");
		return;
	}
	if (q->front == -1) // First element insertion
		q->front = q->rear = 0;
	else
		// Circular decrement: wrap around to the end if at index 0
		q->front = (q->front - 1 + MAX) % MAX;
	q->arr[q->front] = v;
}

void insertRearS(Deque *q, int v) {
	if ((q->rear + 1) % MAX == q->front) {
		printf("Full\n");
		return;
	}
	if (q->front == -1)
		q->front = q->rear = 0;
	else
		// Circular increment
		q->rear = (q->rear + 1) % MAX;
	q->arr[q->rear] = v;
}

void deleteFrontS(Deque *q) {
	if (q->front == -1) {
		printf("Empty\n");
		return;
	}
	printf("Deleted: %d\n", q->arr[q->front]);
	if (q->front == q->rear) // Reset queue if it becomes empty
		q->front = q->rear = -1;
	else
		q->front = (q->front + 1) % MAX;
}

void deleteRearS(Deque *q) {
	if (q->front == -1) {
		printf("Empty\n");
		return;
	}
	printf("Deleted: %d\n", q->arr[q->rear]);
	if (q->front == q->rear)
		q->front = q->rear = -1;
	else
		// Circular decrement
		q->rear = (q->rear - 1 + MAX) % MAX;
}

void displayS(Deque *q) {
	if (q->front == -1) {
		printf("Empty\n");
		return;
	}
	int i = q->front;
	while (1) {
		printf("%d ", q->arr[i]);
		if (i == q->rear)
			break;
		i = (i + 1) % MAX;
	}
	printf("\n");
}

// --- Dynamic Deque Functions ---
// Handles memory reallocation when the buffer is full

void resizeD(Deque *q) {
	int oldSize = q->size;
	q->size *= 2;
	int *n = malloc(q->size * sizeof(int));

	// Copy elements from old buffer to new buffer in linear order
	for (int i = 0; i < oldSize; i++)
		n[i] = q->dynArr[(q->front + i) % oldSize];

	free(q->dynArr);
	q->dynArr = n;
	q->front = 0;
	q->rear = oldSize - 1; // Rear is now at the end of the old data count
	printf("Resized to %d\n", q->size);
}

void insertFrontD(Deque *q, int v) {
	if ((q->rear + 1) % q->size == q->front)
		resizeD(q);
	if (q->front == -1)
		q->front = q->rear = 0;
	else
		q->front = (q->front - 1 + q->size) % q->size;
	q->dynArr[q->front] = v;
}

void insertRearD(Deque *q, int v) {
	if ((q->rear + 1) % q->size == q->front)
		resizeD(q);
	if (q->front == -1)
		q->front = q->rear = 0;
	else
		q->rear = (q->rear + 1) % q->size;
	q->dynArr[q->rear] = v;
}

void deleteFrontD(Deque *q) {
	if (q->front == -1) {
		printf("Empty\n");
		return;
	}
	printf("Deleted: %d\n", q->dynArr[q->front]);
	if (q->front == q->rear)
		q->front = q->rear = -1;
	else
		q->front = (q->front + 1) % q->size;
}

void deleteRearD(Deque *q) {
	if (q->front == -1) {
		printf("Empty\n");
		return;
	}
	printf("Deleted: %d\n", q->dynArr[q->rear]);
	if (q->front == q->rear)
		q->front = q->rear = -1;
	else
		q->rear = (q->rear - 1 + q->size) % q->size;
}

void displayD(Deque *q) {
	if (q->front == -1) {
		printf("Empty\n");
		return;
	}
	int i = q->front;
	while (1) {
		printf("%d ", q->dynArr[i]);
		if (i == q->rear)
			break;
		i = (i + 1) % q->size;
	}
	printf("\n");
}

int main() {
	// Initialize struct with default values
	Deque dq = {.front = -1, .rear = -1, .dynArr = NULL};
	int mode, op, v, run = 1;

	printf("1.Static Queue\n2.Dynamic Queue\nChoice: ");
	scanf("%d", &mode);

	if (mode == 2) {
		printf("Initial Size: ");
		scanf("%d", &dq.size);
		dq.dynArr = malloc(dq.size * sizeof(int));
	}

	while (run) {
		printf("\n1.Insert Front\n2.Insert Rear\n3.Delete Front\n4.Delete Rear "
		       "\n5.Display\n6.Exit\nChoice: ");
		scanf("%d", &op);

		switch (op) {
		case 1:
			printf("Value: ");
			scanf("%d", &v);
			mode == 1 ? insertFrontS(&dq, v) : insertFrontD(&dq, v);
			break;
		case 2:
			printf("Value: ");
			scanf("%d", &v);
			mode == 1 ? insertRearS(&dq, v) : insertRearD(&dq, v);
			break;
		case 3:
			mode == 1 ? deleteFrontS(&dq) : deleteFrontD(&dq);
			break;
		case 4:
			mode == 1 ? deleteRearS(&dq) : deleteRearD(&dq);
			break;
		case 5:
			mode == 1 ? displayS(&dq) : displayD(&dq);
			break;
		case 6:
			printf("Exiting...");
			run = 0;
			break;
		default:
			printf("Invalid Choice. Try Again\n");
		}
	}

	// Clean up heap memory if dynamic mode was used
	if (dq.dynArr)
		free(dq.dynArr);
	return 0;
}
