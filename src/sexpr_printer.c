/**
 * sexpr_parser.c - the S-Expression printer.
 */

#include <stdio.h>

#include "sexpr_parser.h"
#include "sexpr_option.h"

int depth;

/**
 * Helper function to print the output on an expression
 *
 * @param type the type of the expression
 * @param value the value of the expression
 * @param depth the level of depth in the list
 */
void print_expr(char *type, char *value, int depth)
{

#if PRINT_DEPTH
  int i;

  /* represent the level of depth */
  for (i = 0; i < depth; i++) {
    printf(" ");
  }
#else
  (void)depth;
#endif

  printf("%s: %s\n", type, value);

}

/**
 * Print recursively the s-expression tree in a nested fashion way
 * 
 * @param node the head of the s-expression tree
 */
void print_list(struct SNode *node)
{

  while (node) {

    switch (node->type)
    {
    case LIST:
      /* verify the recursive level to avoid stack overflow */
      depth++;
      if (depth > MAX_DEPTH) {
        fprintf(stderr, "max recursive level reached, stop here to avoid stack overflow\n");
        return;
      }

      /* call recursively into child node */
      print_expr("List", "", depth);
      print_list(node->list);
      break;
    
    case STRING:
      print_expr("String", node->value, depth);
      break;

    case INTEGER:
      print_expr("Integer", node->value, depth);
      break;

    case FLOAT:
      print_expr("Float", node->value, depth);
      break;

    default:
      fprintf(stderr, "unknown node type\n");
      break;
    }

    /* jump to the next node */
    node = node->next;
  }

}