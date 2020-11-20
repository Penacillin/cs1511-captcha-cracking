#include "stack.h"
#include <stdio.h>

// pops the last point off the stack, and puts the coords in x and y
// returns 1 on success, 0 on failure
int pop(point stack_arr[STACK_SIZE], int* stack_pointer, int* x, int* y)
{
	//printf("pop, pointer is %d", *stack_pointer);
	if (*stack_pointer > 0)
	{
		*x = stack_arr[*stack_pointer].x;
		*y = stack_arr[*stack_pointer].y;
		*stack_pointer -= 1;
		return 1;
	}
	else
	{
		//fprintf(stderr, "POP FAILED stack: %d x: %d y: %d\n", *stack_pointer, *x, *y);
		return 0;
	}
}
// pushes x and y onto the stack
// returns 1 on success, 0 on failure
int push(point stack_arr[STACK_SIZE], int* stack_pointer, int x, int y)
{
	if (*stack_pointer < STACK_SIZE - 1)
	{
		*stack_pointer += 1;
		point p = { x, y };
		stack_arr[*stack_pointer].x = p.x;
		stack_arr[*stack_pointer].y = p.y;
		//printf("just pushed. x: %d, y: %d\n", x, y);
		return 1;
	}
	fprintf(stderr, "PUSH FAILED\n");
	return 0;
}

void pop_all(point stack_arr[STACK_SIZE], int* stack_pointer)
{
	int x, y;
	while (pop(stack_arr, stack_pointer, &x, &y));
}