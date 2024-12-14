#include "../load_file.c"
#include <string.h>

#define num(x) for(; (data[data_i] < '0' || data[data_i] > '9') && data[data_i] != '-'; data_i++); long long x=0;\
{int sign = 1; if(data[data_i] == '-') {sign = -1; data_i++;};\
for(; data[data_i] >= '0' && data[data_i] <= '9'; data_i++) x = x * 10 + data[data_i] - '0'; x *= sign;}

#define WIDTH 101
#define HEIGHT 103

struct robot {
    int p_x;
    int p_y;
    int v_x;
    int v_y;
};

int main() { 

    int size = 0;
    char* data = load_file("input.txt", &size);

    int lines = 0;
    for (int i = 0; i < size; i++) if(data[i] == '\n') lines++;

    struct robot* robots = malloc(sizeof(struct robot) * lines);

    int robot_count_q1 = 0, robot_count_q2 = 0, robot_count_q3 = 0, robot_count_q4 = 0;

    int data_i = 0;
    for(int i = 0; i < lines; i++) {
        num(p_x) num(p_y) num(v_x) num(v_y)
        
        robots[i] = (struct robot) {p_x, p_y, v_x, v_y};

        int p_x_final = ((p_x + 100 * v_x) % WIDTH + WIDTH) % WIDTH;
        int p_y_final = ((p_y + 100 * v_y) % HEIGHT + HEIGHT) % HEIGHT;

        if(p_x_final > WIDTH / 2 && p_y_final < HEIGHT / 2) robot_count_q1++;
        else if(p_x_final < WIDTH / 2 && p_y_final < HEIGHT / 2) robot_count_q2++;
        else if(p_x_final < WIDTH / 2 && p_y_final > HEIGHT / 2) robot_count_q3++;
        else if(p_x_final > WIDTH / 2 && p_y_final > HEIGHT / 2) robot_count_q4++;
    }

    int safety_factor = robot_count_q1 * robot_count_q2 * robot_count_q3 * robot_count_q4;

    printf("part1 %d\n", safety_factor);

    int avg_x, avg_y;

    for(int i = 0; i < 10000; i++) {
        avg_x = 0;
        avg_y = 0;

        for(int j = 0; j < lines; j++) { 
            avg_x += ((robots[j].p_x + i * robots[j].v_x) % WIDTH + WIDTH) % WIDTH;
            avg_y += (((robots[j].p_y + i * robots[j].v_y) % HEIGHT + HEIGHT) % HEIGHT);
        }

        avg_x /= lines;
        avg_y /= lines;

        if((avg_x < 45 || avg_x > 55) && ( avg_y < 48 || avg_y > 52)) {
            char file_name[] = "sec++++.txt";
            file_name[3] = i / 1000 + '0';
            file_name[4] = (i / 100) % 10 + '0';
            file_name[5] = (i / 10) % 10 + '0';
            file_name[6] = i % 10 + '0';

            char* layout = malloc((WIDTH + 1) * HEIGHT);

            memset(layout, ' ', (WIDTH + 1) * HEIGHT);
            for(int j = 1; j <= HEIGHT; j++) layout[j * (WIDTH + 1) - 1] = '\n';

            for(int j = 0; j < lines; j++) { 
                int x = ((robots[j].p_x + i * robots[j].v_x) % WIDTH + WIDTH) % WIDTH;
                int y = (((robots[j].p_y + i * robots[j].v_y) % HEIGHT + HEIGHT) % HEIGHT);

                layout[x + y * (WIDTH + 1) ] = '#';
            }

            FILE* file = fopen(file_name, "w");
            fwrite(layout, 1, (WIDTH + 1) * HEIGHT, file);
            fclose(file);

            free(layout);

        }
        
    }

    printf("part2 %d\n", 7037);
    return 0;
}