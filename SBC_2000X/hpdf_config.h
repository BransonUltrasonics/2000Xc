/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/hpdf_config.h_v   1.2   28 Mar 2014 14:33:02   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/hpdf_config.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:02   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     26 Mar 2014 14:22:58 rjamloki     
 * macro declaration of UNDER_CE changed.It was giving warning during compilation
 *
 *    Rev 1.0     05 Mar 2014 16:07:18 rjamloki      
 * Initial Revision.
*/
/* include/hpdf_config.h.in.  Generated from configure.in by autoheader.  */

/* Define to 1 if you have the <dlfcn.h> header file. */
#undef LIBHPDF_HAVE_DLFCN_H

/* Define to 1 if you have the <inttypes.h> header file. */
#undef LIBHPDF_HAVE_INTTYPES_H

/* Define to 1 if you have the `png' library (-lpng). */
#define LIBHPDF_HAVE_LIBPNG 1

/* Define to 1 if you have the `z' library (-lz). */
#define LIBHPDF_HAVE_LIBZ 1

/* Define to 1 if you have the <memory.h> header file. */
#undef LIBHPDF_HAVE_MEMORY_H

/* Define to 1 if you have the <stdint.h> header file. */
#undef LIBHPDF_HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#define LIBHPDF_HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define LIBHPDF_HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define LIBHPDF_HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define LIBHPDF_HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#undef LIBHPDF_HAVE_SYS_TYPES_H

/* Define to 1 if you have the <unistd.h> header file. */
#define LIBHPDF_HAVE_UNISTD_H 1

#ifndef UNDER_CE
#define UNDER_CE 1
#endif
/* define pi */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif  /*  M_PI  */

/* debug build */
#undef LIBHPDF_DEBUG

/* debug trace enabled */
#undef LIBHPDF_DEBUG_TRACE

/* libpng is not available */
#undef LIBHPDF_HAVE_NOPNGLIB

/* zlib is not available */
#undef LIBHPDF_HAVE_NOZLIB

/* Define to the address where bug reports for this package should be sent. */
#undef LIBHPDF_PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#undef LIBHPDF_PACKAGE_NAME

/* Define to the full name and version of this package. */
#define LIBHPDF_PACKAGE_STRING "libhpdf 2.2.0"

/* Define to the one symbol short name of this package. */
#undef LIBHPDF_PACKAGE_TARNAME

/* Define to the version of this package. */
#define LIBHPDF_PACKAGE_VERSION "2.2.0"

/* Define to 1 if you have the ANSI C header files. */
#define LIBHPDF_STDC_HEADERS 1

/* Define to `unsigned int' if <sys/types.h> does not define. */
#undef size_t
