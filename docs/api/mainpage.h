/** \file
 * The main documentation page for doxygen.
 */

/** \mainpage Physical Units and Constants


<h3>Introduction</h3>
This purpose of this package is to easy and consistent access to an extensive
set of physical units, constants, unit systems, and conversion of physical
quantities between various arbitrary unit systems.  While this package began
with the crude support of the \subpage physical_cpp "C++/C" languages only,
it now includes a sophisticated interface for the \ref physical_cpp "C++"
and \subpage physical_python "Python" languages that allows for parsing of
complex mathematical expressions with strict runtime dimensional analysis.  Also
included are new rudimentary interfaces for the
\subpage physical_other "Octave/Matlab" language as well as for
\ref physical_other "Gnuplot".

There are several examples for the \ref physical_cpp "C++" interface.  These
examples demonstrate the rudimentary, but \ref data-only/testDataOnly.cpp
"performance sensitive native storage" interface, simple usage of
\ref output/testOutput.cpp "runtime::physical classes and formatted printing",
\ref calc/parser/testParser.cpp "simple parsing possible" with the
runtime interfaces, the \ref registry/testregistry.cpp "registry" used to add
symbols (variables, constants, and functions) to the mathematical/physical
expression parser, and a \ref calc/interactive/testInteractive.cpp
"full-featured interactive units calculator" program.

<p>
This manual constitutes the technical reference or application programming
interface (API) documentation for the Physical Units and Constants package.  The
doxygen code documentation system is used to automatically generate this manual
in HTML and \f$\textnormal{\LaTeX}\f$ formats based on information extracted
from the actual source code files.  Details of the different namespace-separated
interfaces for the physical library can be found by following the appropriate
links to documentation for included functions, classs, and data-members.


<h3>Additional Material</h3>
  For reference, please also see the following sections:
  - \subpage physical-wishlist
  - \subpage physical_license
  - \subpage physical_readme
  - \subpage physical_install
  - \subpage physical_changelog
  - \subpage physical_authors
  .
*/



//-----------------------------------------------------------
/** \page physical_cpp physical::C++
  The access to these items comes in two primary forms:
    - performance sensitive access where the values are all converted to 64 bit
      floating point numbers at compile time.  This access is defined by the
      physical:: namespace.  This set of interfaces does not perform any type of
      dimensional analysis.
    - runtime::physical:: namespace
      A full fledged scalar calulator system for parsing complex math string
      expressions is included.  Although the unit-system conversion mechanisms
      will compile for this interface (since the code is really the same
      regardless of whether you use the physical:: interfaces or the
      runtime::physical:: interfaces), using these for the runtime::physical::
      interfaces makes little sense.  This is because the
      runtime::physical::Quantity class actually stores all values as SI units
      under the hood.  This is done to enable consistent and easy dimensional
      analysis.

      My own typical work flow is to use the runtime::physical::calc::Driver to
      parse mathematical expressions as given by the user, check the input for
      correct dimensions, then extract the SI-based coefficient and use the value
      with the phyiscal:: interfaces from then on.
    .
*/



//-----------------------------------------------------------
/** \page physical_python physical::Python
  The Python implementation mimics closely the functionality of the
  runtime::physical \ref physical_cpp "C++" implementation, specifically the
  parsing, dimensional analysis, and formatted output capabilities.
  physical::Python is designed to work well with any mathematical expression.
  It is also designed so as to function well within Numpy arrays and
  operations, albeit dimensions are automatically dropped for some Numpy
  operations.

  <h3>Printing</h3>
  Similar to \ref physical_cpp, physical::Python provides a consistent mechanism
  for converting a physical expression into a string representation.  For
  example, the expression <code>K_B</code> gives the following string
  representation in python:
  \verbatim
    >>> K_B
    <1.38066e-23 kg m^2 / K s^2> (Boltzmann constant)
    >>>
  \endverbatim
  and the expression
  <code>( 8 * K_B * 300 * K / ( pi * physical.element.Ar.mass ) )**(0.5)</code>
  gives the string representation
  \verbatim
    >>> ( 8 * K_B * 300 * K / ( pi * physical.element.Ar.mass ) )**(0.5)
    <398.751 m / s>
    >>>
  \endverbatim
  Unlike \ref physical_cpp, physical::Python does not currently have a method to
  change the output format of the units printing mechanism.

  A significant difference between physical::Python and \ref physical_cpp
  pertains to expressions that result in unitless quantities.  While in
  \ref physical_cpp, the compiled nature of C++ requires that the result be a
  runtime::physical::quantity class, physical::Python can take advantage that
  return types of functions need not be a single type.  Thus, for
  physical::Python expressions that result in unitless quantities, the result is
  automatically converted to a float (a native python type with no associated
  units).  As an example, consider the above print statement for
  <code>K_B</code>.  While the expression just for <code>K_B</code> results in a
  special formatted output, the expression
  <code>K_B * K * s**2 / (kg * m**2)</code> results in a unitless quantity:
  \verbatim
    >>> K_B * K * s**2 / (kg * m**2 )
    1.3806580000000001e-23
    >>>
  \endverbatim

  <h3>PI \f$(\pi)\f$</h3>
  Similar to \ref physical_cpp, there are two versions of the constant
  \f$\pi\f$.  While <code>physical.unit.pi</code> is a physical quantity with
  dimensions of 'radians', <code>physical.constant.pi</code> is a unitless
  quantity.

  <h3>Usage</h3>
  For the python implementation, just make sure that the python directory is
  added to your PYTHONPATH (however you choose do this).  As an example, for
  bash,  you could add the following line to your .bash_profile file:
  \verbatim
    export PYTHONPATH=":/PATH/TO/PHYSICAL-PACKAGE/python:"
  \endverbatim

  Typically, when I am using physical::Python, I issue the commands:
  \verbatim
    import physical;
    from physical.unit import *;
    from physical.constant import *;
  \endverbatim
*/



//-----------------------------------------------------------
/** \page physical_other physical::Other
  - GNUPLOT:<br>
      The gnuplot 'port' is not the most elegant (i.e. the namespaces are just
      tacked onto the names, such as 'arc_centesimal_minute' instead of
      'arc::centesimal::minute' but it has been handy for me.  To use this, just
      execute
      \verbatim
        load '/path/to/physical.gnuplot'
      \endverbatim


  - OCTAVE/MATLAB:<br>
      For the octave/matlab version, you only have to run the 'physical.m' script to
      get all of the units/contants loaded into memory as variables.  The namespaces
      are loaded as structs, except that the physical::unit(s) and
      physical::constant(s) prefixes are removed (perhaps this should not be the
      case, but oh well).  For Octave, this might be best included by first
      ensuring that physical.m can be found in your octave search path.  For
      example:
      \verbatim
        ]$ export OCTAVE_EXEC_PATH=/path/to-physical.m/:${OCTAVE_EXEC_PATH}
        ]$ octave
        octave:1> physical
        octave:2>
      \endverbatim
  .
*/



//-----------------------------------------------------------
/** \page physical-wishlist Todo/Wish List
    @todo Create a small C++ program that generates the content of the units,
    constants, and elements sub-packages from the similar content in the C++
    library.  This would be done at CMake time, and could also be done
    manually.  By populating the content of the Python package from the C++
    content, we only need maintain one set of data instead of several.
    @todo Follow up the auto-generation of Python content with similar programs
    that auto-generate content for the other formats (octave/matlab and
    gnuplot).
*/



//-----------------------------------------------------------
/** \page physical_license Licence
    \verbinclude COPYING
*/



//-----------------------------------------------------------
/** \page physical_readme README
    \verbinclude README
*/



//-----------------------------------------------------------
/** \page physical_install INSTALL
    \verbinclude INSTALL
*/



//-----------------------------------------------------------
/** \page physical_changelog ChangeLog
    \verbinclude ChangeLog
*/



//-----------------------------------------------------------
/** \page physical_authors AUTHORS
    \verbinclude AUTHORS
*/


