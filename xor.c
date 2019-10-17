#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  int inp1;
  int inp2;
  char buf1[16384];
  char buf2[16384];
  size_t count1 = 1;
  size_t count2 = 1;
  size_t min_count;
  size_t i;

  if (argc < 3) {
    fprintf(stderr, "Usage: %s filename1 filename2\n", argv[0]);
    exit(1);
  }

  inp1 = open(argv[1], O_RDONLY);
  inp2 = open(argv[2], O_RDONLY);

  if (inp1 < 0 || inp2 < 0) {
    fprintf(stderr, "%s: Can't read %s or %s\n", argv[0], argv[1], argv[2]);
    exit(1);
  }

  for(;;) {
    count1 = read(inp1, buf1, sizeof(buf1));
    count2 = read(inp2, buf2, sizeof(buf2));
    min_count = count1 < count2 ? count1 : count2;
    if (min_count <= 0)
      break;
    for(i = 0; i < min_count; ++i) {
      buf1[i] ^= buf2[i];
    }
    fwrite(buf1, sizeof(char), i, stdout);
  }

  close(inp1);
  close(inp2);

  return 0;
}
