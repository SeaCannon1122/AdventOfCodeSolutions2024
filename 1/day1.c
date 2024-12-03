#include "../load_file.c"

int compare_ints(int* a, int* b) {
    return (*a > *b) - (*a < *b);
}

int main() {

    //parsing data

    int size;
    char* data = load_file("input.txt", &size);

    int lines = 0;
    for(int i = 0; i < size; i++) if(data[i] == '\n') lines++;

    int* list0 = malloc(lines * sizeof(int));
    int* list1 = malloc(lines * sizeof(int));

    int number_index = 0;
    int mode = 0;
    int reading = 0;
    int current_number = 0;

    for(int i = 0; i < size; i++) {

        if(data[i] >= '0' && data[i] <= '9') {
            current_number = current_number * 10 + data[i] - '0';
            reading = 1;
        }
        else {
            if(reading == 1) {
                if(mode == 0) {
                    list0[number_index] = current_number;
                }
                else {
                    list1[number_index] = current_number;
                    number_index++; 
                }

                current_number = 0;
                mode = ~mode;
            }
            reading = 0;
        }

    }

    qsort(list0, lines, sizeof(int), compare_ints);
    qsort(list1, lines, sizeof(int), compare_ints);

    int diff_sum = 0;
    for(int i = 0; i < lines; i++) {
        int diff = list0[i] - list1[i];
        if(diff < 0) diff = -diff;

        diff_sum += diff;
    }

    printf("part 1: %d\n", diff_sum);


    char* counts = calloc(1, 100000);

    for (int i = 0; i < lines; i++) counts[list1[i]]++;

    int similarity = 0;

    for (int i = 0; i < lines; i++) similarity += list0[i] * counts[list0[i]];

    printf("part 2: %d\n", similarity);

    return 0;
}