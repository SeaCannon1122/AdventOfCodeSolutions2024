#include "../load_file.c"
#include "string.h"

int main() {

    int size = 0;
    char* data = load_file("input.txt", &size);

    int disk_size = 0;
    for(int i = 0; i < size; i++) {data[i] -= '0'; disk_size += data[i];}

    int* disk1 = malloc(disk_size * sizeof(int));
    int* disk2 = malloc(disk_size * sizeof(int));

    int disk_i = 0;
    int file_bool = 1;
    for(int i = 0; i < size; i++) {

        int block_end = data[i] + disk_i;
        for(; disk_i < block_end; disk_i++) {
            if(file_bool == 1) disk1[disk_i] = i/2;
            else disk1[disk_i] = -1;
        }
        file_bool *= -1;
    }

    memcpy(disk2, disk1, disk_size * sizeof(int));

    int next_free_i = 0;
    for(int i = disk_size - 1;; i--) {
        while(disk1[next_free_i] != -1) next_free_i++;

        if(i <= next_free_i) break;

        if(disk1[i] != -1) {
            disk1[next_free_i] = disk1[i];
            disk1[i] = -1;
        }
    }

    long long check_sum1 = 0;
    for(int i = 0; i < disk_size - 1; i++) if(disk1[i] != -1) check_sum1 += disk1[i] * i;

    printf("part1 %lld\n", check_sum1);

    int file_block_begin;
    int file_index = -1;

    for(int i = disk_size - 1; i > 0; i--) {
        if(disk2[i] == -1 && file_index == -1) continue;
        else if(file_index == -1) {
            file_index = disk2[i];
            file_block_begin = i;
        }
        else if(disk2[i] != file_index) {

            int empty_block_begin = -1;

            for(int j = 0; j <= i; j++) {
                if(disk2[j] == -1 && empty_block_begin == -1) empty_block_begin = j;
                if(disk2[j] == -1) if(j - empty_block_begin + 1 == file_block_begin - i) {
                    for(int k = 0; k < file_block_begin - i; k++) {
                        disk2[empty_block_begin + k] = disk2[i + 1 + k];
                        disk2[i + 1 + k] = -1;
                    }
                    break;
                }
                if(disk2[j] != -1) empty_block_begin = -1;
            }

            file_block_begin = -1;
            file_index = -1;
            i++;
        } 
    }

    long long check_sum2 = 0;
    for(int i = 0; i < disk_size - 1; i++) if(disk2[i] != -1) check_sum2 += disk2[i] * i;

    printf("part2 %lld\n", check_sum2);

    return 0;
}