#include <pwd.h>
#include <stddef.h>
#include <string.h>
#include <shadow.h>
#include <grp.h>
#include <sys/utsname.h>
#include <sys/time.h>
struct passwd *getpwnam(const char *name)
{
  struct passwd *ptr;
  setpwent();
  while ((ptr = getpwent()) != NULL)
  {
    if (strcmp(name, ptr->pw_name) == 0)
      break;
  }
  endpwent();
  return (ptr);
}