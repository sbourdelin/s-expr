/**
 * sexpr_parser.c - the S-Expression parser.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sexpr_parser.h"

#define BUFFER_MAX 512


/**
 * Helper function to check if the string passed can be convert to a float
 * 
 * @param str the string to check
 * 
 * @return true if the string can be convert to a float, false otherwise
 */
int is_float(char *str)
{
  char *ptr = NULL;
  strtod(str, &ptr);
  return !*ptr;
}

/**
 * Helper function to check if the string passed can be convert to an integer
 * 
 * @param str the string to check
 * 
 * @return true if the string can be convert to an integer, false otherwise
 */
int is_integer(char *str)
{
  char *ptr = NULL;
  strtol(str, &ptr, 10);
  return !*ptr;
}

/**
 * Helper function to check if the char passed is an s-expression delimiter term
 * 
 * @param c the character to check
 * 
 * @return true if the character is a valid s-expression delimiter, false otherwise
 */
int is_lst_term(int c)
{
  return c == EOF || isspace(c) || c == '(' || c == ')';
}

/**
 * Retrieve an s-expression value from a file
 * 
 * @param fp a pointer to the file to read the value from
 * @param c the starting character to read the value from in the file stream
 *
 * @return a pointer to the read value
 */
char *read_value(FILE *fp, int *c)
{
  int len = 0;
  char buffer[BUFFER_MAX + 1];

  /* retrieve the value until reaching a delimiter */
  while (!is_lst_term(*c = fgetc(fp)) && len < BUFFER_MAX) {
    buffer[len] = *c;
    len++;
  }
  buffer[len] = '\0';
  
  char *str = malloc((len + 1) * sizeof(char));

  return strcpy(str, buffer);
}

/**
 * Built the s-expression tree from a file
 * 
 * @param fp the file stream
 * 
 * @return the head of the tree
 */
struct SNode *snode_parse(FILE *fp)
{
  struct SNode *tail, *head = NULL;
  int c;

  /* build the s-expression tree */
  while ((c = fgetc(fp)) != EOF) {

    struct SNode *node = NULL;

    if (c == ')') {
      /* on an end list delimiter we end the recursion */
      break;
    }

    else if (c == '(') {
      /* on a new list delimiter we begin the list recursion */
      node = malloc(sizeof(struct SNode));
      node->type = LIST;
      node->list = snode_parse(fp);
    }

    else if (!isspace(c)) {  
      /* put the last character back in the file stream */
      ungetc(c, fp);
      
      node = malloc(sizeof(struct SNode));
      if (node == NULL) {
        fprintf(stderr, "Error: cannot allocate a new node\n");
        return NULL;
      }

      node->value = read_value(fp, &c);

      /* put the terminator back in the file stream */
      ungetc(c, fp);

      /* determine the type of the value and store it in the node */
      if (is_integer(node->value)) {
        node->type = INTEGER;
      } else if (is_float(node->value)) {
        node->type = FLOAT;
      } else {
        node->type = STRING;
      }
    }

    /* update the tree if a new node has been added */
    if (node != NULL) {

      node->next = NULL;
      
      /* if the head hasn't been defined,
       * it means this node is our head.
       * otherwise we had the node to the tail */
      if (head == NULL) {
        head = tail = node;
      } else {
        tail = tail->next = node;
      }
    }

  }

  return head;
}

/**
 * Recursively free the memory allocated by a node
 * 
 * @param node the node to start the deallocation
 */ 
void snode_free(struct SNode *node)
{
  
  while (node != NULL) {
    struct SNode *tmp = node;

    if (node->type == LIST) {
      snode_free(node->list);
    } else {
      /* free the current value */
      free(node->value);
      node->value = NULL;
    }

    node = node->next;

    /* free the current node */
    free(tmp);
    tmp = NULL;
  }

}
