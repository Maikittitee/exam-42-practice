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


void	print_json(struct json data)
{
	
}

void	print_pair(struct pair data)
{
	// key
	printf("key: %s\n", data.key);

	// json value
	if (data.type == STRING){
		printf("str: %s\n", data.string )
	}
}