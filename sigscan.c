#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <config.h>
#include <file.h>
#include <pattern.h>

int arguments(int argc, char **argv);
int not_valid_signature(char *signature);
void version(void);
void usage(void);

char *appname = NULL;
char *filename = NULL;
char *signature = NULL;

int main(int argc, char **argv)
{
  size_t siglen = 0;
  appname = argv[0];
  
  if (arguments(argc, argv))
    return 0; // don't continue
  
  // Checks
  if (!filename || !signature)
    return 1;
  
  if (not_valid_signature(signature)) {
    return 1;
  }
  
  size_t buf_size;
  char *buf = read_file(filename, &buf_size);
  if (!buf) {
    return 1;
  }
  int count = find_all_patterns(buf, buf_size, signature);
  printf("\n%d match%s found.\n", count, (count==1) ? "es": "");
  free(buf);
  return 0;
}

int arguments(int argc, char **argv)
{
  if (argc < 2) {
    printf("error: No arguments provided.\n");
    printf("type '-h' to display help message.\n");
    return 1;
  }
  
  int i = 1;
  while (i < argc) {
    if (!strcmp(argv[i], "-h")) {
      usage();
      return 1;
    } else
    if (!strcmp(argv[i], "-v")) {
      version();
      return 1;
    } else {
      filename = argv[i];
      i++;
      if (i >= argc) {
        printf("error: expected hexadecimal signature.\n");
        printf("type '-h' to display help message.\n");
        return 1;
      }
      signature = argv[i];
      return 0;
    }
    i++;
  }
}

int not_valid_signature(char *signature)
{
  if (!signature)
    return 1;

  size_t siglen = strlen(signature);
  if (siglen % 2 != 0) {
    printf("error: signature length needs to be even.\n");
    return 1;
  }

  for (size_t i = 0; i < siglen; i++) {
    char ch = signature[i];
    
    if (!((ch >= '0' && ch <= '9') ||
          (ch >= 'a' && ch <= 'f') ||
          (ch >= 'A' && ch <= 'F') ||
          (ch == 'x' || ch == 'X'))) {
      printf("error: Invalid character %c\n", ch);
      return 1;
    }
  }

  return 0;
}

void version(void)
{
  printf("%s VERSION %s\n", appname, VERSION);
  printf("Copyright (c) Komodore - Marc-Daniel DALEBA. All rights reserved.\n");
  printf("Scan files for binary signatures.\n");
}

void usage(void)
{
  printf("Usage: %s [Options] File Signature\n", appname);
  printf("Options:\n");
  printf("    -v              Show version.\n");
  printf("    -h              Show this message.\n");
  printf("\n");
  printf("Signature:\n");
  printf("  Signatures should contain only hexadecimal\n");
  printf("  characters and optionally special characters\n");
  printf("  listed below:\n");
  printf("     x              Any nybble value (wildcard)\n");
}