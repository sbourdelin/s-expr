#ifndef __SEXPR_PARSER_H__
#define __SEXPR_PARSER_H__

#include <stdio.h>

enum SNodeType {
  LIST,
  STRING,
  SYMBOL,
  INTEGER,
  FLOAT
};

struct SNode {
  struct SNode *next;
  enum SNodeType type;
  union {
    struct SNode *list;
    char *value;
  };
};

struct SNode *snode_parse(FILE *fp);
void snode_free(struct SNode *node);

#endif /* __SEXPR_PARSER_H__ */