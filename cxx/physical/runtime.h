/** \file
 * A runtime library for a multitude of physical constants and units (mks
 * where applicable) organized into a bunch of namespaces.
 *
 * By runtime, I mean that errors from units mismatch will NOT be caught at
 * compile time like for boost units and other implementations, but rather
 * exceptions will be thrown when such errors are encountered. 
 *
 * One of the main benefits to having runtime error control is that
 * interactive user input may be parsed, translated into Quantity objects, and
 * then automatically tested for units mismatch (this is at least the reason
 * why I wrote this library).
 *
 * Copyright 2008 Spencer E. Olson
 *
 * */

#ifndef physical_runtime_h
# define physical_runtime_h

# include <physical/quantity.h>

/* Declare the extern const definition macros. */
# ifndef RUNTIME_PHYSICAL_QUANTITY_INIT
#  define PHYSICAL_QUANTITY_EXTERN_DECL
# else
#  undef PHYSICAL_QUANTITY_EXTERN_DECL
# endif

/* now finally, load extern declarations for the data. */
# define PHYSICAL_DATA_FOR_RUNTIME
# include <physical/physical.h>
# undef PHYSICAL_DATA_FOR_RUNTIME

/* make sure that this def is no longer */
# undef PHYSICAL_QUANTITY_EXTERN_DECL

#endif // physical_runtime_h
