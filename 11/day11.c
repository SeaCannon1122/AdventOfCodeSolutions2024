#include <stdio.h>
#include <stdlib.h>

struct step_entry {
    unsigned long long number;
    unsigned long long stones_count[76];
};

struct step_entry* entries;
int entries_count = 0;

unsigned long long get_stone_count(unsigned long long number, int steps) {
    if(steps == 0) return 1;

    for(int entries_index = 0; entries_index < entries_count; entries_index++) if(entries[entries_index].number == number) {
        if(entries[entries_index].stones_count[steps] != 0) return entries[entries_index].stones_count[steps];
        else break;
    }

    unsigned long long stone_count; 

    if(number == 0) stone_count = get_stone_count(1, steps - 1);
    else {

        int digits = 1;
        for(unsigned long long number_ = number;(number_ = number_ / 10) > 0; digits++);
        
        if(digits % 2 == 0) {
            unsigned long long devisor = 1;
            for(int i = 0; i < digits / 2; i++) devisor *= 10;
            stone_count = get_stone_count(number / devisor, steps - 1) + get_stone_count(number % devisor, steps - 1);
        }

        else stone_count = get_stone_count(number * 2024, steps - 1);
    }

    int entries_index = 0;
    for(; entries_index < entries_count; entries_index++) if(entries[entries_index].number == number) break;

    if (entries_index == entries_count) {
        entries[entries_index].number = number;
        entries_count++;
    }
    entries[entries_index].stones_count[steps] = stone_count;
    return stone_count;
}

int main() {

    entries = calloc(sizeof(struct step_entry) * 4000, 1);

    unsigned long long numbers[] = {6563348, 67, 395, 0, 6, 4425, 89567, 739318};

    unsigned long long stones_length1 = 0;
    unsigned long long stones_length2 = 0;

    for(int i = 0; i < sizeof(numbers) / sizeof(unsigned long long); i++){
        stones_length1 += get_stone_count(numbers[i], 25);
        stones_length2 += get_stone_count(numbers[i], 75);
    }

    printf("part1 %lld\n", stones_length1);
    printf("part2 %lld\n", stones_length2);

    return 0;
}