/** \file
 * Actual location that runtime::physical::* values are instantiated.
 * Currently, a single compilation unit includes this file.
 */

/* first thing is the define the appropriate macros so that the data gets
 * initialized instead of extern declared. */

#define _OPEN_NAMESPACE(i,id)   \
  namespace id { \
    const int init_ ## i = monkeywrench::push_namespace(#id); \
  } namespace id

#define  _CLOSE_NAMESPACE(i)    \
  const int uninit_ ## i =  monkeywrench::pop_namespace();

#define _ALIAS_NAMESPACE(alias,ns) \
  const int I_ ## alias ## _ ## ns = \
    Quantity::registry().import(monkeywrench::get_prefix() + #ns, "*", \
                                monkeywrench::get_prefix() + #alias); \
  namespace alias = ns

/** Imports namespace only in registry. */
#define _IMPORT_NAMESPACE(ns) \
  const int I_ ## using ## _ ## ns = \
    Quantity::registry().import(monkeywrench::get_prefix() + #ns, "*", \
                                monkeywrench::get_namespace() )

/** Imports namespace both in actual namespace and in registry. */
#define _USING_NAMESPACE(ns)  _IMPORT_NAMESPACE(ns); using namespace ns


#define RUNTIME_PHYSICAL_QUANTITY_INIT
/* Now we load all definitions and intializations. */
#include <physical/runtime.h>
#undef RUNTIME_PHYSICAL_QUANTITY_INIT
