#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 1000000

typedef struct Point point;
struct Point {
	int x;
	int y;
};

// pops the last point off the stack, and puts the coords in x and y
// returns 1 on success, 0 on failure
int pop(point stack_arr[STACK_SIZE], int* stack_pointer, int* x, int* y);
// pushes x and y onto the stack
// returns 1 on success, 0 on failure
int push(point stack_arr[STACK_SIZE], int* stack_pointer, int x, int y);

void pop_all(point stack_arr[STACK_SIZE], int* stack_pointer);

#endif