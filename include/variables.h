#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#if (defined __STDC_VERSION__)			\
  && (__STDC_VERSION__ >= 199901)
#include <stdbool.h>
#else
typedef int bool;
#define true 1
#define false 0
#endif

void add_variable(char *name, double value);

void del_variable(char *name);

bool is_defined_variable(char *name);

/* Before getting the content of a variable, you
 * should check if this variable is defined. If not,
 * the function will return 0.
 */
double get_variable(char *name);

#endif /* _VARIABLES_H_ */
