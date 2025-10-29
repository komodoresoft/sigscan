#include <file.h>

size_t get_file_size(char *filename, FILE *file)
{
  size_t len = 0;
  
  if (!filename) {
    fseek(file, 0, SEEK_END);
    len = ftell(file);
    fseek(file, 0, SEEK_SET);
    return len;
  }
  // TODO: Get File Size with `filename`
  return len;
}

char *read_file(char *filename, size_t *size)
{
  char *buf = NULL;
  
  FILE *f = fopen(filename, "rb");
  if (!f) {
    printf("error: failed to open \"%s\". (%s)\n", filename, strerror(errno));
    return NULL;
  }
  *size = get_file_size(NULL, f);
  buf = malloc(*size);
  if (!buf) {
    printf("error: failed to load file content.\n");
    return NULL;
  }
  fread(buf, 1, *size, f);
  return buf;
}