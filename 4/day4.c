#include "../load_file.c"

//input has no carrige returns, so +1
//inputtest has carrige returns, so it has to be +2
#define IS(x, y, char) (data[x + (y) * (columns + 1)] == char)

int main() {

    int size;
    char* data = load_file("input.txt", &size);

    int lines = 0;
    int columns = 0;
    for(int i = 0; i < size; i++) if(data[i] == '\n') lines++;
    for(; data[columns] != '\n' && data[columns] != '\r'; columns ++);

    int xmas_count = 0;

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < lines; j++) {

            if(i < columns - 3) {
                if(IS(i, j, 'X') && IS(i + 1, j, 'M') && IS(i + 2, j, 'A') && IS(i + 3, j, 'S')) xmas_count++;
                if(IS(i, j, 'S') && IS(i + 1, j, 'A') && IS(i + 2, j, 'M') && IS(i + 3, j, 'X')) xmas_count++;
            }

            if(j < lines - 3) {
                if(IS(i, j, 'X') && IS(i, j + 1, 'M') && IS(i, j + 2, 'A') && IS(i, j + 3, 'S')) xmas_count++;
                if(IS(i, j, 'S') && IS(i, j + 1, 'A') && IS(i, j + 2, 'M') && IS(i, j + 3, 'X')) xmas_count++;
            }

            if(i < columns - 3 && j < lines - 3) {
                if(IS(i, j, 'X') && IS(i + 1, j + 1, 'M') && IS(i + 2, j + 2, 'A') && IS(i + 3, j + 3, 'S')) xmas_count++;
                if(IS(i, j, 'S') && IS(i + 1, j + 1, 'A') && IS(i + 2, j + 2, 'M') && IS(i + 3, j + 3, 'X')) xmas_count++;

                if(IS(i, j + 3, 'X') && IS(i + 1, j + 2, 'M') && IS(i + 2, j + 1, 'A') && IS(i + 3, j, 'S')) xmas_count++;
                if(IS(i, j + 3, 'S') && IS(i + 1, j + 2, 'A') && IS(i + 2, j + 1, 'M') && IS(i + 3, j, 'X')) xmas_count++;
            }

        }
    }

    printf("part1: %d\n", xmas_count);

    xmas_count = 0;

    for (int i = 0; i < columns - 2; i++) {
        for (int j = 0; j < lines - 2; j++) {

            if(IS(i, j, 'M') && IS(i + 2, j, 'M') && IS(i + 1, j + 1, 'A') && IS(i, j + 2, 'S') && IS(i + 2, j + 2, 'S')) xmas_count++;
            else if(IS(i, j, 'S') && IS(i + 2, j, 'M') && IS(i + 1, j + 1, 'A') && IS(i, j + 2, 'S') && IS(i + 2, j + 2, 'M')) xmas_count++;
            else if(IS(i, j, 'S') && IS(i + 2, j, 'S') && IS(i + 1, j + 1, 'A') && IS(i, j + 2, 'M') && IS(i + 2, j + 2, 'M')) xmas_count++;
            else if(IS(i, j, 'M') && IS(i + 2, j, 'S') && IS(i + 1, j + 1, 'A') && IS(i, j + 2, 'M') && IS(i + 2, j + 2, 'S')) xmas_count++;
            
        }
    }

    printf("part2: %d\n", xmas_count);

    return 0;
}