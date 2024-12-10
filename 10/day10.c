#include "../load_file.c"
#include "string.h"

int columns = 0;
int rows = 0;

char* data; 
char* trail_ends;

int rating_sum = 0;

void check_path(int pos) {

    if(data[pos + pos / columns] == '9') {trail_ends[pos] = 1; rating_sum++;}
    else {
        if((pos % columns) + 1 < columns) if(data[pos + 1 + (pos + 1) / columns] == data[pos + pos / columns] + 1) check_path(pos + 1);
        if((pos % columns) - 1 >= 0) if(data[pos - 1 + (pos - 1) / columns] == data[pos + pos / columns] + 1) check_path(pos - 1);
        if((pos / columns) + 1 < rows) if(data[pos + (columns + 1) + pos / columns] == data[pos + pos / columns] + 1) check_path(pos + columns);
        if((pos / columns) - 1 >= 0) if(data[pos - (columns + 1) + pos / columns] == data[pos + pos / columns] + 1) check_path(pos - columns);
    }

}


int main() {

    int size = 0;
    data = load_file("input.txt", &size);

    for(int i = 0; data[i] != '\n'; i++) columns++;
    rows = size / (columns + 1);

    trail_ends = malloc(rows * columns);

    int score_sum = 0;

    for(int i = 0; i < rows * columns; i++) if(data[i + i/ columns] == '0') {
        memset(trail_ends, 0, rows * columns);
        check_path(i);
        for(int j = 0; j < rows * columns; j++) if(trail_ends[j]) score_sum++;
    }

    printf("part1 %d\n", score_sum);
    printf("part2 %d\n", rating_sum);

    return 0;
}