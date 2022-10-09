#ifndef _FLOATX_H_
#define _FLOATX_H_

#define FLOATX_VERSION "2022j07-1508"

/*** TODO

*/
/*** DOCU
	modified code from https://www.boost.org/doc/libs/1_64_0/boost/math/cstdfloat/cstdfloat_types.hpp
	- defines portable fixed-width float types, if available:
		- float16_t
		- float32_t
		- float64_t
		- float96_t
		- float128_t
	- check these to see if they're available in the current hardware:
		- FLOATX_HAS_FLOAT16_NATIVE_TYPE
		- FLOATX_HAS_FLOAT32_NATIVE_TYPE
		- FLOATX_HAS_FLOAT64_NATIVE_TYPE
		- FLOATX_HAS_FLOAT96_NATIVE_TYPE
		- FLOATX_HAS_FLOAT128_NATIVE_TYPE
*/

/*** INCLUDES */
	#include <float.h>
/* INCLUDES end. */

#ifdef __cplusplus
	extern "C" {
#endif

/*** DEFINES */
/* DEFINES end. */

/*** TYPEDEFS */
	#define FLOATX_MAXIMUM_AVAILABLE_WIDTH  0

	#define FLOATX_HAS_FLOAT16_NATIVE_TYPE  0
	#define FLOATX_HAS_FLOAT32_NATIVE_TYPE  0
	#define FLOATX_HAS_FLOAT64_NATIVE_TYPE  0
	#define FLOATX_HAS_FLOAT96_NATIVE_TYPE  0
	#define FLOATX_HAS_FLOAT128_NATIVE_TYPE 0

	/* Ensure that the compiler has a radix-2 floating-point representation. */
	#if ( !defined(FLT_RADIX) || ((defined(FLT_RADIX) && (FLT_RADIX != 2))) )
		#error (FLOATX): The compiler does not support any radix-2 floating-point types required for FLOATX.
	#endif

	/* Check if built-in float is equivalent to float16_t, float32_t, float64_t, float96_t, or float128_t. */
	#if( defined(FLT_MANT_DIG) && defined(FLT_MAX_EXP) )
		#if  ( (FLT_MANT_DIG == 11) && (FLT_MAX_EXP == 16) && (FLOATX_HAS_FLOAT16_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT16_NATIVE_TYPE float
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 16
			#undef  FLOATX_HAS_FLOAT16_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT16_NATIVE_TYPE  1
			#define FLOATX_FLOAT_16_MIN  FLT_MIN
			#define FLOATX_FLOAT_16_MAX  FLT_MAX
		#elif( (FLT_MANT_DIG == 24) && (FLT_MAX_EXP == 128) && (FLOATX_HAS_FLOAT32_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT32_NATIVE_TYPE float
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 32
			#undef  FLOATX_HAS_FLOAT32_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT32_NATIVE_TYPE  1
			#define FLOATX_FLOAT_32_MIN  FLT_MIN
			#define FLOATX_FLOAT_32_MAX  FLT_MAX
		#elif( (FLT_MANT_DIG == 53) && (FLT_MAX_EXP == 1024) && (FLOATX_HAS_FLOAT64_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT64_NATIVE_TYPE float
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 64
			#undef  FLOATX_HAS_FLOAT64_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT64_NATIVE_TYPE  1
			#define FLOATX_FLOAT_64_MIN  FLT_MIN
			#define FLOATX_FLOAT_64_MAX  FLT_MAX
		#elif( (FLT_MANT_DIG == 64) && (FLT_MAX_EXP == 16384) && (FLOATX_HAS_FLOAT96_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT96_NATIVE_TYPE float
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 96
			#undef  FLOATX_HAS_FLOAT96_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT96_NATIVE_TYPE  1
			#define FLOATX_FLOAT_96_MIN  FLT_MIN
			#define FLOATX_FLOAT_96_MAX  FLT_MAX
		#elif( (FLT_MANT_DIG == 113) && (FLT_MAX_EXP == 16384) && (FLOATX_HAS_FLOAT128_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT128_NATIVE_TYPE float
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 128
			#undef  FLOATX_HAS_FLOAT128_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT128_NATIVE_TYPE  1
			#define FLOATX_FLOAT_128_MIN  FLT_MIN
			#define FLOATX_FLOAT_128_MAX  FLT_MAX
		#endif
	#endif

	/* Check if built-in double is equivalent to float16_t, float32_t, float64_t, float96_t, or float128_t. */
	#if(defined(DBL_MANT_DIG) && defined(DBL_MAX_EXP))
		#if( (DBL_MANT_DIG == 11) && (DBL_MAX_EXP == 16) && (FLOATX_HAS_FLOAT16_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT16_NATIVE_TYPE double
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 16
			#undef  FLOATX_HAS_FLOAT16_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT16_NATIVE_TYPE  1
			#define FLOATX_FLOAT_16_MIN  DBL_MIN
			#define FLOATX_FLOAT_16_MAX  DBL_MAX
		#elif( (DBL_MANT_DIG == 24) && (DBL_MAX_EXP == 128) && (FLOATX_HAS_FLOAT32_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT32_NATIVE_TYPE double
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 32
			#undef  FLOATX_HAS_FLOAT32_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT32_NATIVE_TYPE  1
			#define FLOATX_FLOAT_32_MIN  DBL_MIN
			#define FLOATX_FLOAT_32_MAX  DBL_MAX
		#elif( (DBL_MANT_DIG == 53) && (DBL_MAX_EXP == 1024) && (FLOATX_HAS_FLOAT64_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT64_NATIVE_TYPE double
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 64
			#undef  FLOATX_HAS_FLOAT64_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT64_NATIVE_TYPE  1
			#define FLOATX_FLOAT_64_MIN  DBL_MIN
			#define FLOATX_FLOAT_64_MAX  DBL_MAX
		#elif( (DBL_MANT_DIG == 64) && (DBL_MAX_EXP == 16384) && (FLOATX_HAS_FLOAT96_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT96_NATIVE_TYPE double
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 96
			#undef  FLOATX_HAS_FLOAT96_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT96_NATIVE_TYPE  1
			#define FLOATX_FLOAT_96_MIN  DBL_MIN
			#define FLOATX_FLOAT_96_MAX  DBL_MAX
		#elif( (DBL_MANT_DIG == 113) && (DBL_MAX_EXP == 16384) && (FLOATX_HAS_FLOAT128_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT128_NATIVE_TYPE double
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 128
			#undef  FLOATX_HAS_FLOAT128_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT128_NATIVE_TYPE  1
			#define FLOATX_FLOAT_128_MIN  DBL_MIN
			#define FLOATX_FLOAT_128_MAX  DBL_MAX
		#endif
	#endif

	/* Check if built-in long double is equivalent to float16_t, float32_t, float64_t, float96_t, or float128_t. */
	#if(defined(LDBL_MANT_DIG) && defined(LDBL_MAX_EXP))
		#if( (LDBL_MANT_DIG == 11) && (LDBL_MAX_EXP == 16) && (FLOATX_HAS_FLOAT16_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT16_NATIVE_TYPE long double
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 16
			#undef  FLOATX_HAS_FLOAT16_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT16_NATIVE_TYPE  1
			#define FLOATX_FLOAT_16_MIN  LDBL_MIN
			#define FLOATX_FLOAT_16_MAX  LDBL_MAX
		#elif( (LDBL_MANT_DIG == 24) && (LDBL_MAX_EXP == 128) && (FLOATX_HAS_FLOAT32_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT32_NATIVE_TYPE long double
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 32
			#undef  FLOATX_HAS_FLOAT32_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT32_NATIVE_TYPE  1
			#define FLOATX_FLOAT_32_MIN  LDBL_MIN
			#define FLOATX_FLOAT_32_MAX  LDBL_MAX
		#elif( (LDBL_MANT_DIG == 53) && (LDBL_MAX_EXP == 1024) && (FLOATX_HAS_FLOAT64_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT64_NATIVE_TYPE long double
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 64
			#undef  FLOATX_HAS_FLOAT64_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT64_NATIVE_TYPE  1
			#define FLOATX_FLOAT_64_MIN  LDBL_MIN
			#define FLOATX_FLOAT_64_MAX  LDBL_MAX
		#elif( (LDBL_MANT_DIG == 64) && (LDBL_MAX_EXP == 16384) && (FLOATX_HAS_FLOAT96_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT96_NATIVE_TYPE long double
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 96
			#undef  FLOATX_HAS_FLOAT96_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT96_NATIVE_TYPE  1
			#define FLOATX_FLOAT_96_MIN  LDBL_MIN
			#define FLOATX_FLOAT_96_MAX  LDBL_MAX
		#elif( (LDBL_MANT_DIG == 113) && (LDBL_MAX_EXP == 16384) && (FLOATX_HAS_FLOAT128_NATIVE_TYPE == 0) )
			#define FLOATX_FLOAT128_NATIVE_TYPE long double
			#undef  FLOATX_MAXIMUM_AVAILABLE_WIDTH
			#define FLOATX_MAXIMUM_AVAILABLE_WIDTH 128
			#undef  FLOATX_HAS_FLOAT128_NATIVE_TYPE
			#define FLOATX_HAS_FLOAT128_NATIVE_TYPE  1
			#define FLOATX_FLOAT_128_MIN  LDBL_MIN
			#define FLOATX_FLOAT_128_MAX  LDBL_MAX
		#endif
	#endif

	/* Make sure that the compiler has any floating-point type(s) whatsoever. */
	#if (   (FLOATX_HAS_FLOAT16_NATIVE_TYPE  == 0)  \
		&& (FLOATX_HAS_FLOAT32_NATIVE_TYPE  == 0)  \
		&& (FLOATX_HAS_FLOAT64_NATIVE_TYPE  == 0)  \
		&& (FLOATX_HAS_FLOAT96_NATIVE_TYPE  == 0)  \
		&& (FLOATX_HAS_FLOAT128_NATIVE_TYPE == 0))
		#error (FLOATX): The compiler does not support any of the floating-point types required for FLOATX.
	#endif

	#if(FLOATX_HAS_FLOAT16_NATIVE_TYPE == 1)
		typedef FLOATX_FLOAT16_NATIVE_TYPE float16_t;
		typedef float16_t float_fast16_t;
		typedef float16_t float_least16_t;
			#undef FLOATX_FLOAT_16_MIN
			#undef FLOATX_FLOAT_16_MAX
	#endif

	#if(FLOATX_HAS_FLOAT32_NATIVE_TYPE == 1)
		typedef FLOATX_FLOAT32_NATIVE_TYPE float32_t;
		typedef float32_t float_fast32_t;
		typedef float32_t float_least32_t;
			#undef FLOATX_FLOAT_32_MIN
			#undef FLOATX_FLOAT_32_MAX
	#endif

	#if(FLOATX_HAS_FLOAT64_NATIVE_TYPE == 1)
		typedef FLOATX_FLOAT64_NATIVE_TYPE float64_t;
		typedef float64_t float_fast64_t;
		typedef float64_t float_least64_t;
			#undef FLOATX_FLOAT_64_MIN
			#undef FLOATX_FLOAT_64_MAX
	#endif

	#if(FLOATX_HAS_FLOAT96_NATIVE_TYPE == 1)
		typedef FLOATX_FLOAT96_NATIVE_TYPE float96_t;
		typedef float96_t float_fast96_t;
		typedef float96_t float_least96_t;
			#undef FLOATX_FLOAT_96_MIN
			#undef FLOATX_FLOAT_96_MAX
	#endif

	#if(FLOATX_HAS_FLOAT128_NATIVE_TYPE == 1)
		typedef FLOATX_FLOAT128_NATIVE_TYPE float128_t;
		typedef float128_t float_fast128_t;
		typedef float128_t float_least128_t;
			#undef FLOATX_FLOAT_128_MIN
			#undef FLOATX_FLOAT_128_MAX
	#endif
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
	}
#endif
#endif /* _FLOATX_H_ */