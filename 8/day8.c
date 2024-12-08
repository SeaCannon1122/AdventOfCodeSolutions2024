#include "../load_file.c"
#include "string.h"

int main() {

    int size = 0;
    char* data = load_file("input.txt", &size);

    int columns = 0;

    for(int i = 0; data[i] != '\n'; i++) columns++;
    int rows = size / (columns + 1);

    char* antinodes = calloc(1, columns * rows);

    for(int i = 0; i < rows*columns; i++) {

        if(data[i + (i/columns)] != '.') {

            for(int j = i + 1; j < columns * rows; j++) {

                if(data[i + (i/columns)] == data[j + (j/columns)]) {

                    int dx = (j % columns) - (i % columns);
                    int dy = (j / columns) - (i / columns);

                    for(int k = 0; k < rows*columns; k++) 
                        if(((k % columns) - (i % columns)) * dy == ((k / columns) - (i / columns)) * dx) antinodes[k] |= 1;

                    int x_0 = (i % columns) - dx;
                    int y_0 = (i / columns) - dy;

                    if(x_0 >= 0 && x_0 < columns && y_0 >= 0 && y_0 < rows) antinodes[x_0 + y_0 * columns] = 3;

                    int x_1 = (j % columns) + dx;
                    int y_1 = (j / columns) + dy;

                    if(x_1 >= 0 && x_1 < columns && y_1 >= 0 && y_1 < rows) antinodes[x_1 + y_1 * columns] = 3;
                }

            }

        }

    }

    int part1_antinode_count = 0;
    int part2_antinode_count = 0;

    for(int i = 0; i < rows*columns; i++) {
        if(antinodes[i] == 3) part1_antinode_count++;
        if(antinodes[i]) part2_antinode_count++;
    }

    printf("part1 %d\n", part1_antinode_count);
    printf("part2 %d\n", part2_antinode_count);

    return 0;
}