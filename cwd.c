/*
 * cwd.c - determine current working directory
 */

#include <unistd.h>
#include <sys/param.h>
#include "cwd.h"

/*
 * cwd - get path of current directory as a string
 * 
 * @return - string containing path to current directory
 */
char *cwd(void) {
#ifdef PATH_MAX
  // linux
  static char path[PATH_MAX];
  return getcwd(path, PATH_MAX);
#else
  // mac
  static char path[MAXPATHLEN];
  return getcwd(path, MAXPATHLEN);
#endif

}
