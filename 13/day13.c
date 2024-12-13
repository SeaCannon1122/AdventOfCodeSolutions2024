#include "../load_file.c"
#define num(x) for(; d[i] < '0' || d[i] > '9'; i++); long long x=0; for(; d[i] >= '0' && d[i] <= '9'; i++) x = x * 10 + d[i] - '0';

int main() { 
    long long cost1 = 0, cost2 = 0, size = 0; char* d = load_file("input.txt", (int*)&size);

    for(long long i = 0; i < size - 1;) { //theres no machine with parallel equation lines in my dset, so determinant != 0

        num(A_x) num(A_y) num(B_x) num(B_y) num(Price_x) num(Price_y)
        long long det = A_x * B_y - A_y * B_x;
        long long det_B1 = Price_x * B_y - Price_y * B_x, det_A1 = Price_x * A_y - Price_y * A_x;
        long long det_B2 = (Price_x + 10000000000000) * B_y - (Price_y + 10000000000000) * B_x;
        long long det_A2 = (Price_x + 10000000000000) * A_y - (Price_y + 10000000000000) * A_x;

        if(det_B1 / det * det == det_B1 && -det_A1 / det * det == -det_A1) cost1 += 3 * det_B1 / det + -det_A1 / det;
        if(det_B2 / det * det == det_B2 && -det_A2 / det * det == -det_A2) cost2 += 3 * det_B2 / det + -det_A2 / det;
    }
    
    printf("part1 %lld\npart2 %lld\n", cost1, cost2);
}