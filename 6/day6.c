#include "../load_file.c"
#include "string.h"

enum heading {
    UP = 1,
    DOWN = 2,
    LEFT = 4,
    RIGHT = 8,
    SPINNING = 16
};

int main() {

    int size = 0;
    char* data = load_file("input.txt", &size);

    int columns = 0;

    for(int i = 0; data[i] != '\n'; i++) columns++;
    for(int i = 0; i < size; i++) if(data[i] == '.') data[i] = 0;
    int rows = size / (columns + 1);

    int guard_x;
    int guard_y;
    int guard_heading;

    for(int i = 0; ; i++) {
        if(data[i] == '<' || data[i] == '>' || data[i] == '^' || data[i] == 'v') {

            if(data[i] == '<') guard_heading = LEFT;
            if(data[i] == '>') guard_heading = RIGHT;
            if(data[i] == '^') guard_heading = UP;
            if(data[i] == 'v') guard_heading = DOWN;
            data[i] = 0;

            guard_x = i % (columns + 1);
            guard_y = i / (columns + 1);

            break;
        }
    }

    int guard_start_x = guard_x;
    int guard_start_y = guard_y;
    int guard_start_heading = guard_heading;

    char* map_copy = malloc(size);
    memcpy(map_copy, data, size);

    map_copy[guard_x + guard_y * (columns + 1)] = 'm';

    while(1) {

        int next_x;
        int next_y;

        while(1) {
            if (guard_heading == LEFT) {next_x = guard_x - 1; next_y = guard_y;}
            else if (guard_heading == RIGHT) {next_x = guard_x + 1; next_y = guard_y;}
            else if (guard_heading == UP) {next_x = guard_x; next_y = guard_y - 1;}
            else if (guard_heading == DOWN) {next_x = guard_x; next_y = guard_y + 1;}

            if (map_copy[next_x + next_y*(columns + 1)] == '#') {
                if (guard_heading == LEFT) guard_heading = UP;
                else if (guard_heading == RIGHT) guard_heading = DOWN;
                else if (guard_heading == UP) guard_heading = RIGHT;
                else if (guard_heading == DOWN) guard_heading = LEFT;
            }
            else break;
        }

        if(next_x < 0 || next_x >= columns || next_y < 0 || next_y >= rows) break;
        guard_x = next_x;
        guard_y = next_y;

        map_copy[guard_x + guard_y * (columns + 1)] = 'm';

    }

    int steps = 0;
    for(int i = 0; i < size; i++) if(map_copy[i] == 'm') steps++;

    free(map_copy);

    printf("part1: %d\n", steps);

    int obsticle_count = 0;

    for(int i = 0; i < columns; i++) {
        for(int j = 0; j < rows; j++) {
            if (data[i + j * (columns + 1)] == '#' || (i == guard_start_x && j == guard_start_y)) continue;
            
            map_copy = malloc(size);
            memcpy(map_copy, data, size);

            map_copy[i + j * (columns + 1)] = '#';

            guard_x = guard_start_x;
            guard_y = guard_start_y;
            guard_heading = guard_start_heading;

            while(1) {

                int next_x;
                int next_y;

                char field_status;

                if (guard_heading == LEFT) {field_status = LEFT;}
                else if (guard_heading == RIGHT) {field_status = RIGHT;}
                else if (guard_heading == UP) {field_status = UP;}
                else if (guard_heading == DOWN) {field_status = DOWN;}

                while(1) {
                    if (guard_heading == LEFT) {next_x = guard_x - 1; next_y = guard_y; }
                    else if (guard_heading == RIGHT) {next_x = guard_x + 1; next_y = guard_y; }
                    else if (guard_heading == UP) {next_x = guard_x; next_y = guard_y - 1; }
                    else if (guard_heading == DOWN) {next_x = guard_x; next_y = guard_y + 1; }

                    if(next_x < 0 || next_x >= columns || next_y < 0 || next_y >= rows) break;

                    if (map_copy[next_x + next_y*(columns + 1)] == '#') {
                        if (guard_heading == LEFT) guard_heading = UP;
                        else if (guard_heading == RIGHT) guard_heading = DOWN;
                        else if (guard_heading == UP) guard_heading = RIGHT;
                        else if (guard_heading == DOWN) guard_heading = LEFT;
                        field_status = SPINNING;
                    }
                    else break;
                }

                if(next_x < 0 || next_x >= columns || next_y < 0 || next_y >= rows) break;
                if(field_status & map_copy[guard_x + guard_y * (columns + 1)]) { obsticle_count++; break;}

                map_copy[guard_x + guard_y * (columns + 1)] |= field_status;
                guard_x = next_x;
                guard_y = next_y;
                

            }
            free(map_copy);
            
        }
    }

    printf("part2: %d\n", obsticle_count);

    return 0;

}