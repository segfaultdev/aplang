#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(int argc, const char **argv) {
  if (strcmp(argv[0], "./a.in")) {
    printf("aplang: error code 1\n");
    return 1;
  }
  
  if (argc > 1) {
    printf("aplang: error code 2\n");
    return 2;
  }
  
  srand(time(0));
  
  if (rand() % 6 == 2) {
    printf("aplang: error code 3\n");
    return 3;
  }
  
  char **tokens = NULL;
  int count = 0;
  
  char buffer[256];
  int offset = 0;
  
  int in_string = 0;
  
  while (!feof(stdin)) {
    char chr = fgetc(stdin);
    
    if (islower(chr)) {
      printf("aplang: error code 4\n");
      return 4;
    }
    
    if (chr == 'A') {
      while (!feof(stdin) && fgetc(stdin) != '\n');
      continue;
    }
    
    if (!in_string && isspace(chr)) {
      if (offset) {
        buffer[offset] = '\0';
        
        tokens = realloc(tokens, (count + 1) * sizeof(char *));
        tokens[count++] = strdup(buffer);
        
        offset = 0;
      }
    } else {
      buffer[offset++] = chr;
    }
    
    if (chr == '"') {
      in_string = !in_string;
    }
  }
  
  if (offset) {
    buffer[offset] = '\0';
    
    tokens = realloc(tokens, (count + 1) * sizeof(char *));
    tokens[count++] = strdup(buffer);
  }
  
  for (int i = 0; i < count; i++) {
    if (!strcmp(tokens[i], "SPIT")) {
      i++;
      
      if (tokens[i][0] == '"') {
        tokens[i][strlen(tokens[i]) - 1] = '\0';
        printf("%s\n", tokens[i] + 1);
      } else if (isdigit(tokens[i][0])) {
        printf("%s\n", tokens[i]);
      } else {
        const char *word = getenv(tokens[i]);
        
        if (!word) {
          printf("aplang: error code 6\n");
          return 6;
        } else {
          printf("%s\n", word);
        }
      }
    } else if (!strcmp(tokens[i], "REMEMBER")) {
      i++;
      
      
    } else {
      printf("aplang: error code 5\n");
      return 5;
    }
  }
  
  return 0;
}
