#include <variables.h>

#include <string.h>
#include <stdlib.h>

struct node {
  struct node *next;
  char *name;
  double value;
};

static struct node *env = NULL;

void add_variable(char *name, double value){
  struct node *new = malloc(sizeof(struct node));
  new->next = env;
  new->name = name;
  new->value = value;
  env = new;
}

void del_variable(char *name){
  struct node *it = env, *prev = NULL, *next = NULL;
  while(it != NULL){
    if(!strcmp(name, it->name)){
      next = it->next;
      if(it->next && prev)
	prev->next = next;
      else if(prev)
	prev->next = NULL;
      else if(next)
	env = next;
      else
	env = NULL;
      free(it->name);
      free(it);
      it = next;
    }
    else{
      prev = it;
      it = it->next;
    }
  }
}

bool is_defined_variable(char *name){
  struct node *it = env;
  while(it != NULL){
    if(!strcmp(it->name, name))
      return true;
    it = it->next;
  }
  return false;
}

double get_variable(char *name){
  struct node *it = env;
  while(it != NULL){
    if(!strcmp(it->name, name))
      return it->value;
    it = it->next;
  }
  return 0;  
}
