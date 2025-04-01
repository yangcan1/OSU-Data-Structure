#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "queue.h"
#include "stack.h"

#define MAX_STR_LEN 256

/*
 * This function prompts the user for input and stores a maximum of `n`
 * characters of the string they enter into `dest`.  Any trailing line ending
 * characters are removed from the input string.  Returns 1 if a string was
 * successfully read from the user or 0 otherwise.
 */
int get_user_str(char* dest, int n) {
  printf("\nEnter a string, and we'll check whether it's a palindrome:\n");
  if (fgets(dest, MAX_STR_LEN, stdin) != NULL) {
    /*
     * If a string was successfully read from the user, remove any trailing
     * line ending characters.  Here's some documentation on strcspn() to help
     * understand how this works:
     *
     * https://en.cppreference.com/w/c/string/byte/strcspn
     */
    dest[strcspn(dest, "\r\n")] = '\0';
    return 1;
  } else {
    return 0;
  }
}

int main(int argc, char const *argv[]) {
  char* in = malloc(MAX_STR_LEN * sizeof(char));
  if (!in) {
    fprintf(stderr, "Memory allocation failed.\n");
    return 1;
  }

  while (get_user_str(in, MAX_STR_LEN)) {
    int is_palindrome = 1;

    struct stack* stack = stack_create();
    struct queue* queue = queue_create();

    for (int i = 0; i < strlen(in); i++) {
      if (isalpha((unsigned char)in[i])) {
        char* q_ptr = malloc(sizeof(char));
        char* s_ptr = malloc(sizeof(char));
        *q_ptr = tolower((unsigned char)in[i]);
        *s_ptr = tolower((unsigned char)in[i]);
        stack_push(stack, s_ptr);
        queue_enqueue(queue, q_ptr);
      }
    }

    while (!queue_isempty(queue)) {
      char* s_char = stack_pop(stack);
      char* q_char = queue_dequeue(queue);

      if (*q_char != *s_char) {
        is_palindrome = 0;
      }

      free(s_char);
      free(q_char);
    }

    if (is_palindrome) {
      printf("The string is a palindrome.\n");
    } else {
      printf("The string is not a palindrome.\n");
    }

    stack_free(stack);
    queue_free(queue);
    free(in);

    return 0;

  }

}