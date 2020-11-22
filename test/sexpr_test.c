/**
 * sexpr_test.c - the S-Expression unit-test.
 * 
 * This unit test is only designed to work with the default exemple.sexp dataset
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../src/sexpr_parser.h"
#include "../src/sexpr_printer.h"

void run_tests(struct SNode *node)
{
  struct SNode *current = NULL, 
               *list_1 = NULL,
               *list_2 = NULL,
               *list_3 = NULL;

  printf("Running test...\n");

  assert(node != NULL);
  assert(node->type == LIST);
  current = node->list;
  
  assert(current->type == LIST);
  current = current->list;
  
  assert(current->type == STRING);
  assert(!strcmp(current->value, "Capture"));
  current = current->next;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "image-01.raw"));
  current = current->next;

  assert(current->type == LIST);
  list_1 = current;
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "id"));
  current = current->next;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "6zlQW000LK"));

  current = list_1;
  current = current->next;

  assert(current->type == LIST);
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "name"));
  current = current->next;
  
  assert(current->type == STRING);
  assert(!strcmp(current->value, "1KDVQwb"));
  
  current = list_1;
  current = current->next;
  current = current->next;
 
  assert(current->type == LIST);
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "timestamp"));
  current = current->next;
  
  assert(current->type == STRING);
  assert(!strcmp(current->value, "2019-10-23T11:50:04-04:00"));

  current = list_1;
  current = current->next;
  current = current->next;
  current = current->next;

  assert(current->type == LIST);
  list_2 = current;
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "capture_settings"));
  current = current->next;

  assert(current->type == LIST);
  current = current->list;

  assert(current->type == LIST);
  list_3 = current;
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "mode"));
  current = current->next;
  
  assert(current->type == STRING);
  assert(!strcmp(current->value, "idle"));

  current = list_3;
  current = current->next;

  assert(current->type == LIST);
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "frequency"));
  current = current->next;
  
  assert(current->type == INTEGER);
  assert(!strcmp(current->value, "2400"));

  current = list_3;
  current = current->next;
  current = current->next;

  assert(current->type == LIST);
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "fps"));
  current = current->next;
  
  assert(current->type == INTEGER);
  assert(!strcmp(current->value, "33"));

  current = list_3;
  current = current->next;
  current = current->next;
  current = current->next;

  assert(current->type == LIST);
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "exposure"));
  current = current->next;
  
  assert(current->type == INTEGER);
  assert(!strcmp(current->value, "9750"));

  current = list_3;
  current = current->next;
  current = current->next;
  current = current->next;
  current = current->next;

  assert(current->type == LIST);
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "gain_r"));
  current = current->next;
  
  assert(current->type == INTEGER);
  assert(!strcmp(current->value, "250"));

  current = list_3;
  current = current->next;
  current = current->next;
  current = current->next;
  current = current->next;
  current = current->next;

  assert(current->type == LIST);
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "gain_g"));
  current = current->next;
  
  assert(current->type == FLOAT);
  assert(!strcmp(current->value, "50.2"));

  current = list_3;
  current = current->next;
  current = current->next;
  current = current->next;
  current = current->next;
  current = current->next;
  current = current->next;
  
  assert(current->type == LIST);
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "gain_b"));
  current = current->next;
  
  assert(current->type == FLOAT);
  assert(!strcmp(current->value, "5876.123"));

  current = list_2;
  current = current->next;

  assert(current->type == LIST);
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "coordinates"));
  current = current->next;

  assert(current->type == LIST);
  current = current->list;

  assert(current->type == LIST);
  list_3 = current;
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "latitude"));
  current = current->next;
  
  assert(current->type == FLOAT);
  assert(!strcmp(current->value, "45.5169557"));

  current = list_3;
  current = current->next;

  assert(current->type == LIST);
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "longitude"));
  current = current->next;
  
  assert(current->type == FLOAT);
  assert(!strcmp(current->value, "-73.580725"));

  current = list_3;
  current = current->next;
  current = current->next;

  assert(current->type == LIST);
  current = current->list;

  assert(current->type == STRING);
  assert(!strcmp(current->value, "altitude"));
  current = current->next;
  
  assert(current->type == INTEGER);
  assert(!strcmp(current->value, "-6300000"));

  printf("Test passed!\n");
}