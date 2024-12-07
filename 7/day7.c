#include "../load_file.c"
#include "string.h"

#define MAX_EQUATION_LENGTH 20

struct equation {
    long long result;
    long long values[MAX_EQUATION_LENGTH];
    long long length;
};

long long ipow(long long base, long long exp) {
    long long pow = 1;
    for(long long i = 0; i < exp; i++) pow*=base;
    return pow;
}

int main() {

    int size = 0;
    char* data = load_file("input.txt", &size);

    long long lines = 0;
    for(long long i = 0; i < size; i++) if(data[i] == '\n') lines++;

    struct equation* equations = calloc(sizeof(struct equation) * lines, 1);

    long long current_number = 0;
    long long equation_index = 0;

    for(long long i = 0; i < size; i++) {

        if(data[i] >= '0' && data[i] <= '9') {
            current_number = current_number * 10 + data[i] - '0';
        }
        else if(data[i] == ':') {
            equations[equation_index].result = current_number;
            current_number = 0;
            i++;
        }
        else {
            equations[equation_index].values[equations[equation_index].length] = current_number;
            current_number = 0;
            equations[equation_index].length++;
            if(data[i] == '\n') equation_index++;
        }
    }

    long long result_sum = 0;
    int OPERATIONS_COUNT = 2; 

    for(long long i = 0; i < lines; i++) {

        char operations[MAX_EQUATION_LENGTH];
        memset(operations, 0, MAX_EQUATION_LENGTH - 1);

        long long combination_count = ipow(OPERATIONS_COUNT, equations[i].length - 1);
        for (long long j = 0; j < combination_count; j++) {

            long long current_result = equations[i].values[0];

            int overflow = 0;

            for(long long k = 0; k < equations[i].length - 1; k++) {
                if(k == 0) operations[0]++;
                if(operations[k] == OPERATIONS_COUNT) {
                    operations[k] = 0;
                    operations[k+1]++;
                }

                int temp = current_result;

                if(operations[k] == 0) {
                    current_result += equations[i].values[k + 1];
                }
                else if(operations[k] == 1) {
                    current_result *= equations[i].values[k + 1];
                }

                if(current_result < temp) {
                    overflow = 1;
                    break;
                }

            }

            if(overflow) {
                continue;
            }

            if(current_result == equations[i].result) {
                result_sum += current_result;
                break;
            }
        }
    }

    printf("part1: %lld\n", result_sum);


    result_sum = 0;
    OPERATIONS_COUNT = 3; 

    for(long long i = 0; i < lines; i++) {

        char operations[MAX_EQUATION_LENGTH];
        memset(operations, 0, MAX_EQUATION_LENGTH - 1);

        long long combination_count = ipow(OPERATIONS_COUNT, equations[i].length - 1);
        for (long long j = 0; j < combination_count; j++) {

            long long current_result = equations[i].values[0];

            int overflow = 0;

            for(long long k = 0; k < equations[i].length - 1; k++) {
                if(k == 0) operations[0]++;
                if(operations[k] == OPERATIONS_COUNT) {
                    operations[k] = 0;
                    operations[k+1]++;
                }

                int temp = current_result;

                if(operations[k] == 0) {
                    current_result += equations[i].values[k + 1];
                }
                else if(operations[k] == 1) {
                    current_result *= equations[i].values[k + 1];
                }
                else if(operations[k] == 2) {
                    
                    int multiplier = 1;
                    for(; equations[i].values[k + 1] / multiplier > 0; multiplier*=10);

                    current_result = current_result*multiplier + equations[i].values[k + 1];

                }


                if(current_result < temp) {
                    overflow = 1;
                    break;
                }

            }

            if(overflow) {
                continue;
            }

            if(current_result == equations[i].result) {
                result_sum += current_result;
                break;
            }
        }
    }

    printf("part2: %lld\n", result_sum);

    return 0;
}