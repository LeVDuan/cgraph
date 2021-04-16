#include "cgraph_error.h"

#include <assert.h>

static cgraph_error_handler_t *cgraph_i_error_handler = 0;

static const char *cgraph_error_strings[] = {
    [CGRAPH_SUCCESS] = "No error",
    [CGRAPH_FAILURE] = "Failed"
};

const char* cgraph_strerror(const cgraph_error_t cgraph_errno) {
  static_assert(sizeof(cgraph_error_strings) / sizeof(char *) == CGRAPH_ERROR_NO_COUNT,
    "Inconsistent error messages");
  int sz = sizeof(cgraph_error_strings) / sizeof(char *);
  if (cgraph_errno < 0 || cgraph_errno >= sz) {
    return "Invalid error code; no error string available.";
  }
  return cgraph_error_strings[cgraph_errno];
}

void cgraph_error_handler_ignore(
      const char *reason,
      const char *file,
      int line,
      cgraph_error_t errno) {
}

int cgraph_error(const char *reason,
                 const char *file,
                 int line,
                 cgraph_error_t errno) {
    if (cgraph_i_error_handler) {
        cgraph_i_error_handler(reason, file, line, errno);
    }
  return 0;
}

cgraph_error_handler_t * cgraph_set_error_handler(
          cgraph_error_handler_t * new_handler) {
    cgraph_error_handler_t * previous_handler = cgraph_i_error_handler;
    cgraph_i_error_handler = new_handler;
  return previous_handler;
}