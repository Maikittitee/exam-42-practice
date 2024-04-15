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
		printf("\"%s\"\n", data.string);
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

int	main(void)
{
	struct pair p;

	struct pair p2;
	struct pair p3;

	p2.key = "subkey1";
	p2.value.type = STRING;
	p2.value.string = "subvalue1";
	
	p3.key = "subkey2";
	p3.value.type = INTEGER;
	p3.value.integer = 65;

	p.key = "hello";
	p.value.type = MAP;
	p.value.map.size = 2;
	p.value.map.data = malloc(sizeof(struct pair) * 2);
	p.value.map.data[0] = p2;
	p.value.map.data[1] = p3;


	print_pair(p, 0);
}