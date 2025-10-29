#include <pattern.h>

int char2nybble(char c)
{
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return 0xA + (c - 'a');
  if (c >= 'A' && c <= 'F') return 0xA + (c - 'A');
  return 0xFF;
}

int find_all_patterns(char *buf, size_t size, char *signature)
{
  size_t cur = 0;
  size_t siglen = strlen(signature);
  int count = 0;
  char byte;
  
  while (cur < size) {
    int found = 1;
    int posoff = 0;
    for (size_t i = 0; i < siglen; i+=2) {
      byte = buf[cur+posoff];
      
      char HI_c = signature[i];
      if (HI_c != 'x' && HI_c != 'X') {
        int HI = char2nybble(HI_c);
        if (((byte >> 4) & 0xF) != HI) {
          found = 0;
          break;
        }
      }
      
      char LO_c = signature[i+1];
      if (LO_c != 'x' && LO_c != 'X') {
        int LO = char2nybble(LO_c);
        if ((byte & 0xF) != LO) {
          found = 0;
          break;
        }
      }
      posoff++;
    }
    if (found) {
      printf("Found signature at offset 0x%08X\n", cur);
      count++;
    }
    cur++;
  }
  return count;
}