#include <stdio.h>
#include <stdlib.h>



typedef struct s_stack{
	char *items;
	size_t	sp;
	int size;
}t_stack;

t_stack *init_stack(int size)
{
	t_stack *st;

	st = malloc(sizeof(t_stack));

	st->size = size;
	st->items = calloc(sizeof(char), size);
	st->sp = 0;
	return (st);
}

void	add(t_stack *stack, char new)
{
	stack->items[stack->sp] = new;
	stack->sp += 1;
}

char	pop(t_stack *stack)
{
	char ret;

	if (stack->sp == 0)
		return (0);

	stack->sp -= 1;
	ret = stack->items[stack->sp];
	return (ret);
}

// peak
char	peak(t_stack *stack)
{
	if (stack->sp == 0)
	{
		return (0);
	}
	return (stack->items[stack->sp - 1]);
}

// in?
int	in(t_stack *stack, char q)
{
	size_t i;

	i = 0;
	while (i < stack->sp)
	{
		if (stack->items[i] == q)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_stack(t_stack *stack)
{
	size_t i;

	i = 0;
	while (i < stack->sp)
	{
		printf("%c ",stack->items[i]);
		i++;
	}
	printf("\n");


}

int	main(int ac, char **av)
{
	// char *postfix;
	t_stack *st;

	st = init_stack(1000);

	add(st, 'A');
	print_stack(st);
	printf("peak: %c\n", peak(st));
	
	add(st, 'b');
	print_stack(st);
	printf("peak: %c\n", peak(st));
	
	add(st, 'c');
	print_stack(st);
	printf("peak: %c\n", peak(st));
	
	add(st, 'd');
	print_stack(st);
	printf("peak: %c\n", peak(st));
	
	add(st, 'e');
	print_stack(st);
	printf("peak: %c\n", peak(st));


	printf("pop %c\n", pop(st));
	print_stack(st);
	printf("peak: %c\n", peak(st));

	printf("pop %c\n", pop(st));
	print_stack(st);
	printf("peak: %c\n", peak(st));
	

	printf("pop %c\n", pop(st));
	print_stack(st);
	printf("peak: %c\n", peak(st));
	
	printf("pop %c\n", pop(st));
	print_stack(st);
	printf("peak: %c\n", peak(st));
	
	printf("pop %c\n", pop(st));
	print_stack(st);
	printf("peak: %c\n", peak(st));
	// if (ac != 2)
	// {
	// 	dprintf(stderr,"program take 1 argument\n");
	// 	return (1);
	// }
	// if (!check_parenthesis(av[1]))
	// {
	// }

	// postfix = infix_postfix_conv(av[1])

		
	
}

