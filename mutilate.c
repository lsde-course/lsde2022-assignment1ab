#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils.h" // Person defined here, and the mmap calls to load files into virtual memory

unsigned long person_num = 0;
Person *person_map;
unsigned int *knows_map;


int main(int argc, char *argv[]) {
  unsigned long file_length;
  FILE *outfile = fopen(makepath(argv[1], (char*) "mutilated", (char*) "bin"), "w+");
  knows_map    = (unsigned int *)   mmapr(makepath(argv[1], (char*) "knows",    (char*) "bin"), &file_length);
  person_map   = (Person *)         mmapr(makepath(argv[1], (char*) "person",   (char*) "bin"), &file_length);
  person_num   = file_length/sizeof(Person);

  for (unsigned int person1 = 0; person1 < person_num; person1++) {
    int mutilate = (person1&15) == 0;
    for (unsigned long knows2 = person_map[person1].knows_first;
         knows2 < person_map[person1].knows_first + person_map[person1].knows_n;
         knows2++)
    {
      unsigned int person2 = mutilate?0:knows_map[knows2];
      mutilate = 0;
      fwrite(&person2, sizeof(person2), 1, outfile);
    }
  }
  fclose(outfile);
  return 0;
}