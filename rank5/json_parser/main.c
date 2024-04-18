#include <stdlib.h>
#include <stdio.h>

struct json
{
    enum
    {
        STRING,
        INTEGER,
        MAP,
    } type;

    union
    {
        struct
        {
            struct pair *data;
            size_t size;
        } map;
        char *string;
        int integer;
    };
};

struct pair
{
    char *key;
    struct json value;
};

void	nchar(char a, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		printf("%c", a);
		i++;
	}
}

void	print_pair(struct pair data, int indent);
void	print_map(struct pair *data, int size, int indent);

void	print_json(struct json data, int indent)
{
	nchar('\t', indent);
	if (data.type == STRING)
		printf("<>%s\n", data.string);
	if (data.type == INTEGER)
		printf("#%d\n", data.integer);
	if (data.type == MAP)
	{
		printf("\n");
		// print_pair(*data.map.data, indent + 1);
		print_map(data.map.data, data.map.size ,indent + 1);
	}

}

void	print_map(struct pair *data, int size, int indent)
{
	int	i;

	i = 0;
	while (i < size)
	{
		print_pair(data[i], indent);
		i++;
	}

}

void	print_pair(struct pair data, int indent)
{
	nchar('\t', indent);
	// key
	printf("%s:", data.key);

	// json value
	print_json(data.value, indent);
}

int is_digit(char a)
{
	return (a >= '0' && a <= '9');
}

int	count_string(char *arg)
{
	 int i = 0;
	 while (*arg == ' ' || *arg == '\"')
		arg++;
	 while (*arg && *arg != '\"')
	 {
		i++;
		arg++;
	 }
	 return (i);
}

int count_int(char *arg)
{
	int i = 0;
	while (*arg == ' ')
		arg++;
	while (*arg != ' ')
	{
		i++;
		arg++;
	}
	return (i);

}

int count_pair(char *arg)
{
	int i;

	i = 0;
	while (*arg)
	{
		if (*arg == ':')
			i++;
		arg++;
	}
	return (i);
}

int count_map(char *arg)
{
	int i = 0;
	while (*arg && *arg != '}')
	{
		arg++;
		i++;
	}
	return (i);
	
}

char *get_string(char *arg, int len)
{
	char *key;
	int i = 0;


	key = malloc(sizeof(char) * (len + 1));
	while (*arg && i < len)
	{
		if (*arg != '\"')
			key[i++] = *arg;
		arg++;
	}	
	key[i] = 0;
	return (key);	
}

int	get_int(char *arg)
{
	int res = 0;

	while (*arg && *arg != ' ' && *arg != ',' && *arg != '}')
	{
		res *= 10;
		if (is_digit(*arg))
		{
			res += (*arg - '0');
		}
		else
			break;
		arg++;
	}
	return (res);
}



struct pair *create_pair(char *arg, int *size)
{
	char *key;
	int		step;
	int		is_key = 1;
	int		str_len;
	int		bracket_cnt = 0;
	int		pair_index = 0;
	struct pair *p;
	int		pair_len;

	pair_len = count_pair(arg);
	p = malloc(sizeof(struct pair) * pair_len);
	*size = pair_len; 
	
	// value must be int, str, map
	while (*arg && (*arg != '}' || bracket_cnt))
	{
		step = 1;
		// key must be string
		printf("iter>%d %s\n", pair_index,arg);
		if (is_key)
		{
			str_len = count_string(arg);
			p[pair_index].key = get_string(arg, str_len);
			arg += (str_len + 2);
			key = 0;
		}
		if (*arg == ':')
		{
			is_key = 0;
		}
		// filler value to its type
		if (*arg == '\"')
		{
			p[pair_index].value.type = STRING;
			str_len = count_string(arg);
			p[pair_index].value.string = get_string(arg, str_len);
			is_key = 1;
			arg += (str_len + 2);
		}
		// printf("now>%s\n", arg);
		if (*arg == '{')
		{
			printf("helloj>%s\n", arg);
			arg++;
			bracket_cnt ++;
			p[pair_index].value.type = MAP;
			p[pair_index].value.map.data = create_pair(arg, size);
			p[pair_index].value.map.size = *size;
			arg += count_map(arg);
			is_key = 1;
		}
		if (*arg == '}')
			break;
		
		if (is_digit(*arg))
		{
			p[pair_index].value.type = INTEGER;
			p[pair_index].value.integer = get_int(arg);
			is_key = 1;
			arg += count_int(arg) + 1;
		}
		if (*arg == ',')
		{
			pair_index++;
		}
		arg += step;

			

	}
	// printf("end>%s\n", p[0].key);

	return (p);

}


struct pair *argo(char *arg)
{
	int i;

	return (create_pair(arg + 1, &i));
}


int	main(void)
{
	struct pair *p = argo("{\"key0\":\"value0\",\"key1\":{\"hello\":\"world\"}}");

	// print_pair(*p, 0);
	printf("%s\n", p[0].key);
	printf("%s\n", p[0].value.string);
	printf("%s\n", p[1].key);
	printf("%s\n", p[1].value.map.data->key);
	printf("%s\n", p[1].value.map.data->value.string);


}