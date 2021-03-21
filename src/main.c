#include "../include/reverse.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (1 == argc) {
    print_file_contents_in_reverse(stdin);
  } else {
    for (int i = 1; i < argc; ++i) {
      FILE* fp = fopen(argv[i], "r");
      if (NULL == fp) {
        fprintf(stderr, "Could not open specified file path: %s", argv[i]);
        perror(" Reason");
        exit(1);
      }

      print_file_contents_in_reverse(fp);

      fclose(fp);
    }
  }

  return 0;
}
