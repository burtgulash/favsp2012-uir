#include <stdio.h>
#include <stdint.h>

#define SET_BIT(dst, bit) dst |= (bit)
#define UNSET_BIT(dst, bit) dst &= ~(bit)


int board[16];
unsigned solutions;
static uint32_t size;
static uint32_t left_mask, right_mask, down_mask;


static void print_board()
{
	int i, j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (board[i] == j)
				printf("+");
			else
				printf("-");
		}
		printf("\n");
	}
	printf("\n");
}


static void place(uint32_t row)
{
	uint32_t col;
	uint32_t left, right, down;

	if (row >= size) {
		printf("Solution %d:\n", solutions++);
		print_board();
		return;
	}

	for (col = 0; col < size; col++) {
		left = 1 << (row + col);
		right = 1 << (size - 1 - row + col);
		down = 1 << col;

		if ((left_mask & left) == 0 
            && (right_mask & right) == 0 
            && (down_mask & down) == 0) 
		{
			SET_BIT(left_mask, left);	
			SET_BIT(right_mask, right);
			SET_BIT(down_mask, down);
			board[row] = col;
			
			place(row + 1);

			board[row] = -1;
			UNSET_BIT(left_mask, left);	
			UNSET_BIT(right_mask, right);
			UNSET_BIT(down_mask, down);
		}
	}
}


int main(int argc, char **argv)
{
	solutions = 1;
	left_mask = right_mask = down_mask = 0;

	if (argc == 2) {
		size = strtoul(argv[1], 0, 10);

		if (size <= 16)
			place(0);
	} 

	return 0;
}
