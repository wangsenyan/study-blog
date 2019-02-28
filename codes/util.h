#define GET_ARRAY_LEN(array, len)            \
  {                                          \
    len = (sizeof(array) / sizeof *array[0]) \
  }
void showArray(double *p, int n);
