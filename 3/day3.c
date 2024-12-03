#include "../load_file.c"

char begin[] = "mul(";
char middle[] = ",";
char end[] = ")";

char d[] = "do()";
char dn[] = "don't()";

enum parse_stage {
    BEGIN,
    NUM1,
    MIDDLE,
    NUM2,
    END,
    DO,
    DONT 
};

int main() {

    int size;
    char* data = load_file("input.txt", &size);

    int sum_part1 = 0;
    int sum_part2 = 0;

    int do_active = 1;

    int num1 = 0;
    int num2 = 0;

    int state = BEGIN;
    int state_index = 0;

    int do_index = 0;

    for(int i = 0; i < size; i++) {
        
        if(do_active) {
            if(do_index == sizeof(dn) - 1 - 1) { 
                if(data[i] == dn[do_index]) do_active = 0;
                do_index = 0;
            }
            else if(data[i] == dn[do_index]) do_index++;
            else do_index = 0;
        }
        else {
            if(do_index == sizeof(d) - 1 - 1) { 
                if(data[i] == d[do_index]) do_active = 1;
                do_index = 0;
            }
            else if(data[i] == d[do_index]) do_index++;
            else do_index = 0;
        }

        if(state == BEGIN) {
            if(state_index >= sizeof(begin) - 1) { state = NUM1; state_index = 0;}
            else if(data[i] == begin[state_index]) state_index++;
            else state_index = 0;
        }

        if(state == NUM1) {
            if (data[i] >= '0' && data[i] <= '9') { num1 = num1 * 10 + data[i] - '0'; state_index++;}
            else if (state_index) { state = MIDDLE; state_index = 0;}
            else { state = BEGIN; state_index = 0;}
        }

        if(state == MIDDLE) {
            if(state_index >= sizeof(middle) - 1) { state = NUM2; state_index = 0;}
            else if(data[i] == middle[state_index]) state_index++;
            else { state = BEGIN; state_index = 0; num1 = 0;}
        }

        if(state == NUM2) {
            if (data[i] >= '0' && data[i] <= '9') { num2 = num2 * 10 + data[i] - '0'; state_index++;}
            else if (state_index) { state = END; state_index = 0;}
            else { state = BEGIN; state_index = 0; num1 = 0;}
        }

        if(state == END) {
            if(state_index == sizeof(end) - 1 - 1) { 
                if(data[i] == end[state_index]) {
                    sum_part1 += num1 * num2;
                    if(do_active) sum_part2 += num1 * num2;
                }
                state = BEGIN; state_index = 0; num1 = 0; num2 = 0;
            }
            else if(data[i] == end[state_index]) state_index++;
            else { state = BEGIN; state_index = 0; num1 = 0; num2 = 0;}
        }
        

    }

    printf("part 1: %d\n", sum_part1);
    printf("part 2: %d\n", sum_part2);

    return 0;
}