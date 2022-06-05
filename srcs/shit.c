#include "../includes/executor.h"

char **parse_map()
{
	char **map;
	int fd=open("map.cub", O_RDONLY);
	map = malloc(sizeof(char*) * 100);
	for(int i=0; i<100; i++){
		get_next_line(fd, &map[i]);
		//printf("%s",map[i]);
	}
	
	return map;
}