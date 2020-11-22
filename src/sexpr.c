/**
 * sexpr.c - the S-Expression entry point.
 */

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sexpr_option.h"
#include "sexpr_parser.h"
#include "sexpr_printer.h"
#include "../test/sexpr_test.h"


/**
 * Print program usage
 */
void print_usage()
{
  printf("Usage : sexpr [options]\n"
		"Options:\n"
		"\t-h\tprint this help message\n"
		"\t-p\tprint the output of the sexpression dataset in a nested fashion format\n"
		"\t-t\trun test on the dataset, only work with the default dataset (exemple.sexp)\n"
    "\t-d\tspecify the dataset path to use\n");
}

/**
 * Entry point
 */
int main(int argc, char *argv[])
{
  int option;
  int enable_print = 0;
  int enable_test = 0;
  char *dataset = DEFAULT_DATASET;

   while ((option = getopt(argc, argv, "hptd:")) != -1) {
    switch (option) {
      case 'h':
        print_usage();
        return EXIT_SUCCESS;

      case 'p':
        enable_print = 1;
        break;

      case 't':
        enable_test = 1;
        break;

      case 'd':
        dataset = optarg;
        break;

      default:
        print_usage();
        return EXIT_FAILURE;
    }
  }

  /* we want at least print or test the dataset */
  if (!enable_print && !enable_test) {
    fprintf(stderr, "Please use at least the -p or -t options\n");
    print_usage();
    return EXIT_FAILURE;
  }

  /* Open the file stream */
  FILE *fp = fopen(dataset, "r");
  if (fp == NULL) {
    fprintf(stderr, "Can't open the file: %s\n", dataset);
    return EXIT_FAILURE;
  }

  /* Read the file into a tree */
  struct SNode *node = snode_parse(fp);

  /* Close the file */
  fclose(fp);

  /* print the s-expression dataset */
  if (enable_print) {
    print_list(node);
  }

  /* run test on the s-expression dataset */
  if (enable_test) {
    run_tests(node);
  }

  /* Deallocate the tree */
  snode_free(node);

  return EXIT_SUCCESS;
}