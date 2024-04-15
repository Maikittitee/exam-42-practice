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

void	print_json(struct json data, int indent)
{
	nchar('\t', indent);
	if (data.type == STRING)
		printf("\"%s\"", data.string);
	if (data.type == INTEGER)
		printf("#%d", data.integer);
	if (data.type == MAP)
	{
		print_pair(*data.map.data, indent + 1);
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

	p2.key = "inside";
	p2.value.type = STRING;
	p2.value.string = "yed mae";

	p.key = "hello";
	p.value.type = MAP;
	p.value.map.data = &p2;


	print_pair(p, 0);
}