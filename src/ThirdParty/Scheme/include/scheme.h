#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#if _MSC_VER
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API extern
#endif // _MSC_VER


EXPORT_API void Scheme_init();
EXPORT_API void Schem_eval(FILE *in);


