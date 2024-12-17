#include "../load_file.c"
#include <string.h>

int check_move(char* large_map, int rows, int columns, int x, int y, char dir) {

    if(dir == '<' ) {
        if (large_map[(x - 1) + y * columns] == '#') return 0;
        else if (large_map[(x - 1) + y * columns] == '.') return 1;
        return check_move(large_map, rows, columns, x - 2, y, '<');
    }
    if(dir == '>' ) {
        if (large_map[(x + 1) + y * columns] == '#') return 0;
        else if (large_map[(x + 1) + y * columns] == '.') return 1;
        else return check_move(large_map, rows, columns, x + 2, y, '>');
    }

    if(dir == '^' ) {
        if (large_map[x + (y - 1) * columns] == '#') return 0;
        else if (large_map[x + (y - 1) * columns] == '.') return 1;
        else {
            if(large_map[x + (y - 1) * columns] == '[') {
                return (check_move(large_map, rows, columns, x + 1, y - 1, '^') & check_move(large_map, rows, columns, x, y - 1, '^'));
            }
            if(large_map[x + (y - 1) * columns] == ']') {
                return (check_move(large_map, rows, columns, x - 1, y - 1, '^') & check_move(large_map, rows, columns, x, y - 1, '^'));
            }
        }
    }

    if(dir == 'v' ) {
        if (large_map[x + (y + 1) * columns] == '#') return 0;
        else if (large_map[x + (y + 1) * columns] == '.') return 1;
        else {
            if(large_map[x + (y + 1) * columns] == '[') {
                return (check_move(large_map, rows, columns, x + 1, y + 1, 'v') & check_move(large_map, rows, columns, x, y + 1, 'v'));
            }
            if(large_map[x + (y + 1) * columns] == ']') {
                return (check_move(large_map, rows, columns, x - 1, y + 1, 'v') & check_move(large_map, rows, columns, x, y + 1, 'v'));
            }
        }
    }

}

void move(char* large_map, int rows, int columns, int x, int y, char dir) {
    
    if(dir == '<' ) {
        if (large_map[(x - 1) + y * columns] == ']') {
            move(large_map, rows, columns, x-2, y, '<');
            large_map[(x - 1) + y * columns] = '.';
            large_map[(x - 2) + y * columns] = ']';
            large_map[(x - 3) + y * columns] = '[';
        }
    }
    if(dir == '>' ) {
        if (large_map[(x + 1) + y * columns] == '[') {
            move(large_map, rows, columns, x+2, y, '>');
            large_map[(x + 1) + y * columns] = '.';
            large_map[(x + 2) + y * columns] = '[';
            large_map[(x + 3) + y * columns] = ']';
        }
    }

    if(dir == '^' ) {
        if(large_map[x + (y - 1) * columns] == '[') {
            move(large_map, rows, columns, x    , y - 1, '^');
            move(large_map, rows, columns, x + 1, y - 1, '^');

            large_map[ x      + (y - 1) * columns] = '.';
            large_map[(x + 1) + (y - 1) * columns] = '.';
            large_map[ x      + (y - 2) * columns] = '[';
            large_map[(x + 1) + (y - 2) * columns] = ']';
        }
        else if(large_map[x + (y - 1) * columns] == ']') {
            move(large_map, rows, columns, x    , y - 1, '^');
            move(large_map, rows, columns, x - 1, y - 1, '^');

            large_map[ x      + (y - 1) * columns] = '.';
            large_map[(x - 1) + (y - 1) * columns] = '.';
            large_map[ x      + (y - 2) * columns] = ']';
            large_map[(x - 1) + (y - 2) * columns] = '[';
        }
    }

    if(dir == 'v' ) {
        if(large_map[x + (y + 1) * columns] == '[') {
            move(large_map, rows, columns, x    , y + 1, 'v');
            move(large_map, rows, columns, x + 1, y + 1, 'v');

            large_map[ x      + (y + 1) * columns] = '.';
            large_map[(x + 1) + (y + 1) * columns] = '.';
            large_map[ x      + (y + 2) * columns] = '[';
            large_map[(x + 1) + (y + 2) * columns] = ']';
        }
        else if(large_map[x + (y + 1) * columns] == ']') {
            move(large_map, rows, columns, x    , y + 1, 'v');
            move(large_map, rows, columns, x - 1, y + 1, 'v');

            large_map[ x      + (y + 1) * columns] = '.';
            large_map[(x - 1) + (y + 1) * columns] = '.';
            large_map[ x      + (y + 2) * columns] = ']';
            large_map[(x - 1) + (y + 2) * columns] = '[';
        }
    }
}

int main() { 

    int size = 0;
    char* data = load_file("input.txt", &size);


    int rows = 0;
    int columns = 0;
    int data_i = 0;
    for(; data[data_i] != '\n'; data_i++) columns++;
    for(; data[data_i-1] != '\n' || data[data_i] != '\n'; data_i++) if(data[data_i] == '\n') rows++;
    data_i++;

    char* map = malloc(rows * columns);

    for(int i = 0; i < rows * columns; i++) map[i] = data[i + i / columns];

    int i = 0;
    for(i = 0; map[i] != '@'; i++);
    int robot_x = i % columns;
    int robot_y = i / columns;
    map[i] = '.';
    
    int intructions_begin = data_i;

    for(; data_i < size; data_i++) if(data[data_i] != '\n') {

        int move_x = 0;
        int move_y = 0;

        if(data[data_i] == '^' ) move_y = -1;
        if(data[data_i] == 'v' ) move_y = 1;
        if(data[data_i] == '<' ) move_x = -1;
        if(data[data_i] == '>' ) move_x = 1;

        

        for(int j = 1;;j++) {
            if(map[(robot_x + j*move_x) + (robot_y + j*move_y) * columns] == '#') break;
            else if(map[(robot_x + j*move_x) + (robot_y + j*move_y) * columns] == 'O') continue;
            else if(map[(robot_x + j*move_x) + (robot_y + j*move_y) * columns] == '.') {

                map[(robot_x + move_x) + (robot_y + move_y) * columns] = '.';
                for (int k = 2; k <= j; k++) {
                    map[(robot_x + k*move_x) + (robot_y + k*move_y) * columns] = 'O';

                }

                robot_x += move_x;
                robot_y += move_y;

                break;
            }
        }

    }

    int gps_sum1 = 0;
    for(i = 0; i < rows * columns; i++) {
        if(map[i] == 'O') gps_sum1 += (i % rows) + 100 * (i / rows); 
    }

    printf("part1 %d\n", gps_sum1);

    char* large_map = malloc(rows * columns * 2);

    for(int i = 0; i < rows * columns; i++) {
        if(data[i + i/columns] == '#') {
            large_map[2 * i] = '#';
            large_map[2 * i + 1] = '#';
        }
        else if(data[i + i/columns] == '.') {
            large_map[2 * i] = '.';
            large_map[2 * i + 1] = '.';
        }
        else if(data[i + i/columns] == 'O') {
            large_map[2 * i] = '[';
            large_map[2 * i + 1] = ']';
        }
        else if(data[i + i/columns] == '@') {
            large_map[2 * i] = '@';
            large_map[2 * i + 1] = '.';

            robot_y = i / columns;
            robot_x = (i % rows) * 2;
        }
    }

    rows *= 2;
    columns *= 2;

    data_i = intructions_begin;

    for(; data_i < size; data_i++) if(data[data_i] != '\n') {

        int can_move = check_move(large_map, rows, columns, robot_x, robot_y, data[data_i]);

        if(can_move) {
            move(large_map, rows, columns, robot_x, robot_y, data[data_i]);
            
            if(data[data_i] == '^' ) robot_y += -1;
            if(data[data_i] == 'v' ) robot_y += 1;
            if(data[data_i] == '<' ) robot_x += -1;
            if(data[data_i] == '>' ) robot_x += 1;
        }        

    }

    int gps_sum2 = 0;
    for(i = 0; i < rows * columns; i++) {
        if(large_map[i] == '[') gps_sum2 += (i % rows) + 100 * (i / rows); 
    }

    printf("part2 %d\n", gps_sum2);

    return 0;
}