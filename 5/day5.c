#include "../load_file.c"

#define MANUAL_MAX_PAGES 30

struct rule {
    int before_page;
    int after_page;
};

struct manual {
    int pages[MANUAL_MAX_PAGES];
    int length;
};

int sort_manual(struct manual* manual, struct rule* rules, int rules_count) {

    int correct = 1;

start:
    for(int i = 0; i < manual->length - 1; i++) {

        for(int j = i + 1; j < manual->length; j++) {

            for(int k = 0; k < rules_count; k++) {

                if (manual->pages[i] == rules[k].after_page && manual->pages[j] == rules[k].before_page) {
                    int temp = manual->pages[i];
                    manual->pages[i] = manual->pages[j];
                    manual->pages[j] = temp;
                    
                    correct = 0;

                    goto start;
                }

            }

        }

    }

    return correct;

}

int main() {

    int size = 0;
    char* data = load_file("input.txt", &size);

    int rules_count = 0;
    
    int i = 1;
    for(; data[i] != '\n' || data[i-1] != '\n'; i++) if(data[i] == '\n') rules_count++;

    struct rule* rules = malloc(2 * sizeof(int) * rules_count);

    for(int j = 0; j < rules_count; j++) {
        rules[j].before_page = (data[6 * j] - '0') * 10 + data[6 * j + 1] - '0';
        rules[j].after_page = (data[6 * j + 3] - '0') * 10 + data[6 * j + 4] - '0';
    }

    i++;

    int manuals_count = 0;
    
    for(int j = i; j < size; j++) if(data[j] == '\n') manuals_count++;

    struct manual* manuals = calloc(1, sizeof(struct manual) * manuals_count); 

    for(int manual_index = 0; manual_index < manuals_count; i++) {

        manuals[manual_index].pages[manuals[manual_index].length] = (data[i] - '0') * 10 + data[i + 1] - '0';
        i += 2;

        if(data[i] == ',') manuals[manual_index].length++;
        else {manuals[manual_index].length++; manual_index++; }
    }

    int correct_sum = 0;
    int incorrect_sum = 0;

    for(int j = 0; j < manuals_count; j++) {

        struct manual reordering_manual = manuals[j];

        if(sort_manual(&reordering_manual, rules, rules_count)) correct_sum += manuals[j].pages[manuals[j].length / 2];
        else incorrect_sum += reordering_manual.pages[reordering_manual.length / 2];
    }

    printf("part1: %d\n", correct_sum);
    printf("part2: %d\n", incorrect_sum);

    return 0;

}