/** \file
 * A registry for physical::quantity types that have been initialized
 * properly.
 *
 * Copyright 2008 Spencer E. Olson
 *
 * */

#include <physical/registry.h>

/** Just a useful set of tools to help with the registry problem. */
namespace monkeywrench {
  std::vector<std::string> namespace_stack = std::vector<std::string>();
}

