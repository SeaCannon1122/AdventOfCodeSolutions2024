#include "stdio.h"
#include "stdlib.h"

void* load_file(char* src, int* size) {

	FILE* file = fopen(src, "rb");
	if (file == NULL) return NULL;

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);

	void* buffer = malloc(fileSize);
	if (buffer == NULL) {
		fclose(file);
		return NULL;
	}

	size_t bytesRead = fread(buffer, 1, fileSize, file);

	fclose(file);

    *size = bytesRead;

	return buffer;
}