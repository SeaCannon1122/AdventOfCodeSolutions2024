#include "../load_file.c"
#define MAX_REPORT_LENGTH 10

struct report {
    int length;
    int values[MAX_REPORT_LENGTH];
};

int main() {

    int size;
    char* data = load_file("input.txt", &size);

    int lines = 0;
    for (int i = 0; i < size; i++) if(data[i] == '\n') lines++;

    struct report* reports = calloc(1, sizeof(struct report) * lines);

    int reading = 0;
    int report_index = 0;
    int current_number = 0;

    for (int i = 0; i < size; i++) {
        if (data[i] >= '0' && data[i] <= '9') {
            current_number = current_number * 10 + data[i] - '0';
            reading = 1;
        }
        else {

            if(reading == 1) {
                reports[report_index].values[reports[report_index].length] = current_number;
                reports[report_index].length++;
                
                current_number = 0;
            }

            if(data[i] == '\n') report_index++;

            reading = 0;
        }
    }

    int save_reports_count = 0;

    for (int i = 0; i < lines; i++) {

        int save = 1;
        int acending = -1;
        
        int last_difference = 0;

        for (int j = 1; j < reports[i].length; j++) {

            int difference = reports[i].values[j] - reports[i].values[j-1];

            if (last_difference * difference < 0) save = 0;
            last_difference = difference;

            if (difference < 0) difference = -difference;

            if (difference < 1 || difference > 3) save = 0;
        }

        if (save) save_reports_count++;
    }

    printf("part 1: %d\n", save_reports_count);

    save_reports_count = 0;

    for (int i = 0; i < lines; i++) {

        for (int k = 0; k < reports[i].length; k++) {

            int save = 1;
        
            int last_difference = 0;

            for (int j = 1; j < reports[i].length && save == 1; j++) {

                if((k == 0 && j == 1) || k == j) continue;

                int difference = reports[i].values[j] - reports[i].values[j-1 - (k + 1== j)];

                if (last_difference * difference < 0) save = 0;
                last_difference = difference;

                if (difference < 0) difference = -difference;

                if (difference < 1 || difference > 3) save = 0;
            }

            if (save) {
                save_reports_count++;
                break;
            }

        }

        
    }

    printf("part 2: %d\n", save_reports_count);

    return 0;

}