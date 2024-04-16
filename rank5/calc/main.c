#include <stdio.h>
#include <stdlib.h>



typedef struct s_stack{
	int *items;
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

void	add(t_stack *stack, int new)
{
	stack->items[stack->sp] = new;
	stack->sp += 1;
}

int	pop(t_stack *stack)
{
	int ret;

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

int	prec(char c)
{
	if (c == '+')
		return (1);
	if (c == '*')
		return (2);
	return (3);
}

int	is_op(char a)
{
	return (a == '+' || a == '*');
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

void	print_stack_int(t_stack *stack)
{
	size_t i;

	i = 0;
	while (i < stack->sp)
	{
		if (is_op(stack->items[i]))
			printf("%c ",stack->items[i]);
		else
			printf("%d ", stack->items[i]);
		i++;
	}
	printf("\n");
}


int	is_paren(char a)
{
	return (a == '(' || a == ')');
}

int	is_digit(char a)
{
	return (a >= '0' && a <= '9');
}

t_stack *infix_postfix_conv(char *infix)
{
	t_stack *postfix;
	size_t i;
	t_stack *stack;

	postfix = init_stack(1000);
	stack = init_stack(1000);
	i = 0;
	while (infix[i])
	{
		if (is_digit(infix[i]))
			add(postfix, infix[i]);
		else if (is_paren(infix[i]))
		{
			if (infix[i] == ')')
			{
				while (stack->sp != 0 && peak(stack) != '(')
				{
					char c = pop(stack);
					add(postfix, c);
				}
				if (peak(stack) == '(')
					pop(stack);
			}
			else
				add(stack, infix[i]);
		}
		else if (is_op(infix[i]))
		{
			if (prec(infix[i]) <= prec(peak(stack)))
			{
				while (stack->sp != 0 && peak(stack) != '(' && prec(infix[i]) <= prec(peak(stack)))
				{
					char c = pop(stack);
					if (!is_paren(c))
						add(postfix, c);
				}
			}
			add(stack, infix[i]);
		}
		i++;

	}
	while (stack->sp != 0)
	{
		add(postfix, pop(stack));
	}
	return (postfix);
	
}

int	evaluate_postfix(t_stack *postfix)
{
	t_stack *stack;
	size_t	i;

	stack = init_stack(1000);
	i = 0;
	while (i < postfix->sp)
	{
		if (is_op(postfix->items[i])){
			int	val1 = (int)(pop(stack));
			int	val2 = (int)(pop(stack));
			if (postfix->items[i] == '+')
				add(stack, val2 + val1);
			if (postfix->items[i] == '*')
				add(stack, val2 * val1);
			// print_stack_int(stack);
		}
		else
			add(stack, postfix->items[i]);
		i++;
	}
	return (pop(stack));
	
}

int	check_parenthesis(char *str)
{
	size_t i;
	t_stack *st;

	i = 0;
	st = init_stack(1000);
	while (str[i])
	{
		if (is_paren(str[i]))
		{
			if (str[i] == '(')
				add(st, str[i]);
			else if (str[i] == ')')
			{
				if (st->sp == 0)
					return (0);
				pop(st);
			}
		}
		i++;
	}
	return (st->sp == 0);

}

void	map_int(t_stack *stack)
{
	size_t i;

	i = 0;
	while (i < stack->sp)
	{
		if (is_digit(stack->items[i]))
			stack->items[i] = stack->items[i] - '0';
		i++;
	}
}

int	main(int ac, char **av)
{
	t_stack *postfix;


	if (ac != 2)
	{
		dprintf(2,"program take 1 argument\n");
		return (1);
	}
	if (!check_parenthesis(av[1]))
	{
		dprintf(2, "parenthesis failed\n");
		return (1);
	}

	postfix = infix_postfix_conv(av[1]);
	printf("postfix: ");
	print_stack(postfix);
	map_int(postfix);

	printf("calc: %d\n", evaluate_postfix(postfix));
}

