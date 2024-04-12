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

int	prec(char c)
{
	if (c == '+')
		return (1);
	if (c == '*')
		return (2);
	return (-1);
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

int	ft_strlen(char *str)
{
	size_t i;
	int	cnt;

	i = 0;
	while (str[i])
		cnt ++;
	return (cnt);
}

void reverse(char* str, int len, int i, int temp)
{
    // if current index is less than the remaining length of
    // string
    if (i < len) {
        temp = str[i];
        str[i] = str[len - 1];
        str[len - 1] = temp;
        i++;
        len--;
        reverse(str, len, i, temp);
    }
}

int	is_op(char a)
{
	return (a == '+' || a == '*');
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

	// reverse(infix, ft_strlen(infix), 0, 0);
	postfix = init_stack(1000);
	stack = init_stack(1000);
	i = 0;
	while (infix[i])
	{
		// is operator or perenthesis => to stack
		if (is_op(infix[i]) || is_paren(infix[i]))
		{
			if (!is_paren(infix[i])){
				while (stack->sp != 0 && prec(infix[i]) <= prec(peak(stack)))
					add(postfix, pop(stack));
				add(stack, infix[i]);
			}
			if (is_paren(infix[i])){
				if (infix[i] == '(')
					add(stack, infix[i]);
				else { // )
					while (1){
						char c = pop(stack);
						if (!is_paren(c))
							add(postfix, c);
						if (c == '(')
						{
							pop(stack);
							break;
						}
					}
				}
			}


		}
		// is number => to postfix;
		if (is_digit(infix[i]))
		{
			printf("add %c\n", infix[i]);
			add(postfix, infix[i]);
		}
		// // if find couple => clear stack and move to postfix
		if (in(stack, '(') && in(stack, ')'))
		{
			while (1)
			{
				char c = pop(stack);
				if (!is_paren(c))
					add(postfix, c);
				if (c == '(')
					break;

			}
		}
		i++;
		// // end => clear stack and move to postfix


	}
	while (stack->sp != 0)
	{
		add(postfix, pop(stack));
	}
	// postfix->items[postfix->sp] = 0;
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
		if (is_digit(postfix->items[i]))
			add(stack, postfix->items[i] - '0');
		else
		{
			int	val1 = (int)(pop(stack));
			int	val2 = (int)(pop(stack));
			if (postfix->items[i] == '+')
				add(stack, (char)((val2 + val1)));
			if (postfix->items[i] == '*')
				add(stack, (char)((val2 * val1)));
		}

		i++;
	}
	return (pop(stack));
	
}

void	char_to_int(t_stack *st)
{
	size_t i;

	i = 0;
	while (i < st->sp)
	{
		st->items[i] -= '0';
		i++;
	}
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

	printf("calc: %d\n", evaluate_postfix(postfix));


		
	
}

