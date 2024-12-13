#include "../load_file.c"
#include <string.h>

char current_crop;
int perimeter;
int area;

struct fence {
    int x_0;
    int y_0;
    int x_1;
    int y_1;
};

unsigned char* data;
struct fence* fence_list;
int fence_list_length;

int columns = 0;
int rows = 0;

void combind_fences() {

    for(int j = 0; j < fence_list_length; j++) {

        for (int k = j+1; k < fence_list_length; k++) {

            struct fence new_fence;

            if(fence_list[j].x_0 == fence_list[j].x_1 && fence_list[j].x_1 == fence_list[k].x_0 && fence_list[k].x_0 == fence_list[k].x_1) {
                new_fence.x_0 = fence_list[j].x_0;
                new_fence.x_1 = fence_list[j].x_0;

                int common_y;

                if(fence_list[j].y_0 == fence_list[k].y_0) {
                    common_y = fence_list[j].y_0;
                    new_fence.y_0 = fence_list[j].y_1;
                    new_fence.y_1 = fence_list[k].y_1;
                }

                else if(fence_list[j].y_1 == fence_list[k].y_1) {
                    common_y = fence_list[j].y_1;
                    new_fence.y_0 = fence_list[j].y_0;
                    new_fence.y_1 = fence_list[k].y_0;
                }

                else if(fence_list[j].y_1 == fence_list[k].y_0) {
                    common_y = fence_list[j].y_1;
                    new_fence.y_0 = fence_list[j].y_0;
                    new_fence.y_1 = fence_list[k].y_1;
                }

                else if(fence_list[j].y_0 == fence_list[k].y_1) {
                    common_y = fence_list[j].y_0;
                    new_fence.y_0 = fence_list[j].y_1;
                    new_fence.y_1 = fence_list[k].y_0;
                }

                else continue;

                for(int i = 0; i < fence_list_length; i++) {
                    if(i != j && i != k && 
                    fence_list[i].y_0 == common_y && fence_list[i].y_1 == common_y && 
                    (fence_list[i].x_0 == new_fence.x_0 || fence_list[i].x_1 == new_fence.x_0)
                    ) common_y = -1;
                }

                if(common_y == -1) continue;
            }

            else if(fence_list[j].y_0 == fence_list[j].y_1 && fence_list[j].y_1 == fence_list[k].y_0 && fence_list[k].y_0 == fence_list[k].y_1) {
                new_fence.y_0 = fence_list[j].y_0;
                new_fence.y_1 = fence_list[j].y_0;

                int common_x;

                if(fence_list[j].x_0 == fence_list[k].x_0) {
                    common_x = fence_list[j].x_0;
                    new_fence.x_0 = fence_list[j].x_1;
                    new_fence.x_1 = fence_list[k].x_1;
                }

                else if(fence_list[j].x_1 == fence_list[k].x_1) {
                    common_x = fence_list[j].x_1;
                    new_fence.x_0 = fence_list[j].x_0;
                    new_fence.x_1 = fence_list[k].x_0;
                }

                else if(fence_list[j].x_1 == fence_list[k].x_0) {
                    common_x = fence_list[j].x_1;
                    new_fence.x_0 = fence_list[j].x_0;
                    new_fence.x_1 = fence_list[k].x_1;
                }

                else if(fence_list[j].x_0 == fence_list[k].x_1) {
                    common_x = fence_list[j].x_0;
                    new_fence.x_0 = fence_list[j].x_1;
                    new_fence.x_1 = fence_list[k].x_0;
                }

                else continue;

                for(int i = 0; i < fence_list_length; i++) {
                    if(i != j && i != k && 
                    fence_list[i].x_0 == common_x && fence_list[i].x_1 == common_x && 
                    (fence_list[i].y_0 == new_fence.y_0 || fence_list[i].y_1 == new_fence.y_0)
                    ) common_x = -1;
                }

                if(common_x == -1) continue;
            }

            else continue;

            fence_list[j] = new_fence;
            memmove(&fence_list[k], &fence_list[k+1], sizeof(struct fence) * (fence_list_length - k - 1));

            fence_list_length--;
            j = -1;
            break; 

        }

    }

}

void discover_field(int i) {
    data[i + i/ columns] = current_crop + 128;
    area++;

    for(int j = 0; j < 4; j++) {
        int x = i % columns;
        int y = i / columns;
        int next_x = i % columns;
        int next_y = i / columns;


        if(j == 0) next_x++;
        else if(j == 1) next_x--;
        else if(j == 2) next_y++;
        else if(j == 3) next_y--;

        if(next_x >= 0 && next_x < columns && next_y >= 0 && next_y < rows) {
            if(data[next_x + (columns + 1) * next_y] != current_crop + 128) {
                if(data[next_x + (columns + 1) * next_y] != current_crop) { 
                    perimeter++; 
                    fence_list[fence_list_length] = (struct fence) {
                        (x + next_x + 1) / 2,
                        (y + next_y + 1) / 2,
                        (x + next_x + 2) / 2,
                        (y + next_y + 2) / 2
                    };
                    fence_list_length++;
                }
                else discover_field(next_x + columns * next_y);
            } 
        }
        else { 
            perimeter++; 
            fence_list[fence_list_length] = (struct fence) {
                (x + next_x + 1) / 2,
                (y + next_y + 1) / 2,
                (x + next_x + 2) / 2,
                (y + next_y + 2) / 2
            };
            fence_list_length++;
        }
    }

}

int main() {

    int size = 0;
    data = load_file("input.txt", &size);

    for(int i = 0; data[i] != '\n'; i++) columns++;
    rows = size / (columns + 1);
    fence_list = malloc(sizeof(struct fence) * (rows * (columns + 1) + columns * (rows + 1)));

    long long price1 = 0;
    long long price2 = 0;

    for(int i = 0; i < rows * columns; i++) {
        if(data[i + i/ columns] > 127) continue;
        area = 0;
        perimeter = 0;
        fence_list_length = 0;

        current_crop = data[i + i/ columns];
        discover_field(i);

        combind_fences();

        price1 += area * perimeter;
        price2 += area * fence_list_length;
    }

    printf("part1 %d\n", price1);
    printf("part2 %d\n", price2);

    return 0;
}