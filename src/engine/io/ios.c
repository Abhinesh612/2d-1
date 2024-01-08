#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "ios.h"
#include "../util.h"
#include "../types.h"

char* io_file_read(const char* path) {
	FILE* fp = fopen(path, "r");
	if (!fp)
		ERROR_EXIT("ERROR:FAILED TO READ FILE: %s : %s\n", path, strerror(errno));

	fseek(fp, 0, SEEK_END);
	i64 size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* source = calloc(size + 1, sizeof(char));
	assert(source != NULL && "ERROR::FAILED TO ALLOCATED");

	fread(source, sizeof(char), size, fp);
	source[size] = '\0';

	return source;
}
