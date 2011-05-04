# Physical constants library
# Copyright 2004-2008 Spencer Olson

cmake_minimum_required( VERSION 2.6 )


project( physical )

include( CTest )

################################################################################
# Obtain the physical version
################################################################################
set( VERSION )

find_program( GIT_EXECUTABLE NAMES git )
if( GIT_EXECUTABLE )
  exec_program(
    ${GIT_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR} ARGS describe
    OUTPUT_VARIABLE VERSION
    RETURN_VALUE GIT_RETVAL )
  if( NOT ${GIT_RETVAL} EQUAL 0 )
    # Something went wrong, fall back on other methods.
    # We still didn't find a version, so it's really unknown.
    set( VERSION "physical-unknownversion" )
  endif()
endif()

message( STATUS "physical VERSION: ${VERSION}" )

# Allow the developer to select what native type to use for
# runtime::physical::quantity<TYPE>
set( RUNTIME_PHYSICAL_QUANTITY "std::complex<double>"  CACHE STRING
    "Storage class for runtime::physical::Quantity"
)
mark_as_advanced( RUNTIME_PHYSICAL_QUANTITY )

MESSAGE(STATUS "Creating RUNTIME_PHYSICAL_QUANTITY include file")
FILE(WRITE
    ${CMAKE_CURRENT_BINARY_DIR}/cxx/physical/rpq.hpp
    "#ifndef CMAKE_AUTO_RUNTIME_PHYSICAL_QUANTITY_INCLUDE\n"
    "#define CMAKE_AUTO_RUNTIME_PHYSICAL_QUANTITY_INCLUDE\n"
    "#define RUNTIME_PHYSICAL_QUANTITY ${RUNTIME_PHYSICAL_QUANTITY}\n"
    "#endif // CMAKE_AUTO_RUNTIME_PHYSICAL_QUANTITY_INCLUDE\n"
)

# include the current directory for framework style includes
LIST(APPEND ${PROJECT_NAME}_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/cxx
    ${CMAKE_CURRENT_BINARY_DIR}/cxx
)

LIST(APPEND ${PROJECT_NAME}_DEFINITIONS
    -DPHYSICAL_VERSION=${VERSION}
    -DRUNTIME_PHYSICAL_QUANTITY_INCLUDE=physical/rpq.hpp
)

find_package( Boost COMPONENTS regex )

if( Boost_FOUND )
    # boost::math is header only, so we have to search for it
    add_definitions( ${Boost_DEFINITIONS} )

    set( Boost_MATH_DIR "Boost_MATH_DIR-NOTFOUND" CACHE FILEPATH "" FORCE )
    mark_as_advanced( Boost_MATH_DIR )
    find_file( Boost_MATH_DIR
        boost/math
        HINTS ${Boost_INCLUDE_DIRS}
        NO_DEFAULT_PATH
    )

    if( NOT Boost_MATH_DIR )
      LIST(APPEND ${PROJECT_NAME}_DEFINITIONS -DBOOST_MATH_NOT_FOUND )
    else()
      include_directories( ${Boost_INCLUDE_DIRS} )
    endif()
endif()


# /physical//physical configuration
set( ${PROJECT_NAME}_HEADERS
    cxx/physical/constant/conversion.h
    cxx/physical/constant/detail/derived-dimensions.h
    cxx/physical/constant/si.h
    cxx/physical/detail/ConvertCoeff.h
    cxx/physical/detail/print_coeff.h
    cxx/physical/dimension/convert.h
    cxx/physical/dimension/define.h
    cxx/physical/dimension/systems.h
    cxx/physical/element.h
    cxx/physical/except.h
    cxx/physical/math.h
    cxx/physical/physical.h
    cxx/physical/quantity.h
    cxx/physical/registry.h
    cxx/physical/runtime.h
    cxx/physical/system.h
)

set( ${PROJECT_NAME}_SOURCES
    cxx/physical/runtime.cpp
    cxx/physical/system.cpp
)

# runtime.cpp doesn't need optimization and often increases build times
# significantly for optimization builds.
if( MSVC )
  set_source_files_properties( cxx/physical/runtime.cpp COMPILE_FLAGS /Od )
else()
  set_source_files_properties( cxx/physical/runtime.cpp COMPILE_FLAGS -O0 )
endif()

add_definitions( ${${PROJECT_NAME}_DEFINITIONS} )
include_directories( ${${PROJECT_NAME}_INCLUDE_DIRS} )
add_library( ${PROJECT_NAME}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES}
)
list(APPEND ${PROJECT_NAME}_COMPONENTS ${PROJECT_NAME})
list(APPEND targets_to_install ${PROJECT_NAME})

find_package( BISON )

set( MIN_BISON_VERSION 2.4 )
if( BISON_VERSION VERSION_EQUAL ${MIN_BISON_VERSION} OR
    BISON_VERSION VERSION_GREATER ${MIN_BISON_VERSION} )

    set( CalcParserDir
      ${CMAKE_CURRENT_BINARY_DIR}/cxx/physical/calc/detail/parser
    )
    FILE(MAKE_DIRECTORY ${CalcParserDir} )

    BISON_TARGET(
        CalcParser
        cxx/physical/calc/detail/Parser.yy
        ${CalcParserDir}/Parser.cpp
    )

    set( PhysicalUsesBISON 1 )
    set( ParserHPP )
    set( ParserCPP ${BISON_CalcParser_OUTPUTS} )

    LIST(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${CalcParserDir} )
else()
    set( ParserHPP       cxx/physical/calc/detail/pregen-parser/location.hh
                         cxx/physical/calc/detail/pregen-parser/Parser.hpp
                         cxx/physical/calc/detail/pregen-parser/position.hh
                         cxx/physical/calc/detail/pregen-parser/stack.hh )
    set( ParserCPP       cxx/physical/calc/detail/pregen-parser/Parser.cpp )

    LIST(APPEND ${PROJECT_NAME}_INCLUDE_DIRS
        cxx/physical/calc/detail/pregen-parser
    )
endif()


find_package( FLEX )

set( MIN_FLEX_VERSION 2.5.35 )
if( FLEX_VERSION VERSION_EQUAL ${MIN_FLEX_VERSION} OR
    FLEX_VERSION VERSION_GREATER ${MIN_FLEX_VERSION} )

    set( CalcScannerDir
      ${CMAKE_CURRENT_BINARY_DIR}/cxx/physical/calc/detail/scanner
    )
    FILE(MAKE_DIRECTORY ${CalcScannerDir} )

    FLEX_TARGET(
        CalcScanner
        cxx/physical/calc/detail/Scanner.ll
        ${CalcScannerDir}/Scanner.cpp
    )

    set( ScannerHPP )
    set( ScannerCPP ${FLEX_CalcScanner_OUTPUTS} )

    set( PhysicalUsesFLEX 1 )
    if( PhysicalUsesBISON )
        add_flex_bison_dependency( CalcScanner CalcParser )
    endif()

    LIST(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${CalcScannerDir} )
else()
    set( ScannerHPP      cxx/physical/calc/detail/pregen-scanner/FlexLexer.h )
    set( ScannerCPP      cxx/physical/calc/detail/pregen-scanner/Scanner.cpp )

    LIST(APPEND ${PROJECT_NAME}_INCLUDE_DIRS
        cxx/physical/calc/detail/pregen-scanner
    )
endif()



# /physical//calc configuration
set( ${PROJECT_NAME}_calc_HEADERS
    cxx/physical/calc/detail/expression/Add.h
    cxx/physical/calc/detail/expression/Assign.h
    cxx/physical/calc/detail/expression/Divide.h
    cxx/physical/calc/detail/expression/Function.h
    cxx/physical/calc/detail/expression/Literal.h
    cxx/physical/calc/detail/expression/Modulo.h
    cxx/physical/calc/detail/expression/Multiply.h
    cxx/physical/calc/detail/expression/Negate.h
    cxx/physical/calc/detail/expression/Node.h
    cxx/physical/calc/detail/expression/Power.h
    cxx/physical/calc/detail/expression/StringFunction.h
    cxx/physical/calc/detail/expression/Subtract.h
    cxx/physical/calc/detail/expression/VariableLookup.h
    cxx/physical/calc/detail/Scanner.h
    cxx/physical/calc/Driver.h
    cxx/physical/calc/except.h
    cxx/physical/calc/math.h
    cxx/physical/calc/symbol.h
    cxx/physical/calc/units.h
    ${ParserHPP}
    ${ScannerHPP}
)

set( ${PROJECT_NAME}_calc_SOURCES
    cxx/physical/calc/Driver.cpp
    ${ParserCPP}
    ${ScannerCPP}
)

if( Boost_REGEX_FOUND )
    # configure the physical_calc library
    include_directories( ${Boost_INCLUDE_DIRS} )
    include_directories( ${${PROJECT_NAME}_INCLUDE_DIRS} )
    add_library( ${PROJECT_NAME}_calc
        ${${PROJECT_NAME}_calc_HEADERS}
        ${${PROJECT_NAME}_calc_SOURCES}
    )

    target_link_libraries( ${PROJECT_NAME}_calc
        ${PROJECT_NAME}
        ${Boost_REGEX_LIBRARY}
    )

    list(APPEND ${PROJECT_NAME}_COMPONENTS calc)
    list(APPEND targets_to_install ${PROJECT_NAME}_calc)


    #  ############## BEGIN ############### #
    #  ########## physical_units ########## #
    add_executable( ${PROJECT_NAME}_units
        examples/calc/interactive/testInteractive.cpp
    )

    #  THE FOLLOWING IS BECAUSE WE DON'T YET HAVE A FindReadline.cmake
    #        ##### BEGIN find_package(readline) #####
    find_library(READLINE_LIBRARY NAMES readline)
    if(READLINE_LIBRARY)
        list(APPEND READLINE_LIBRARIES ${READLINE_LIBRARY})

        # #### BEGIN check if we need curses...
        set(OLD_CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES})
        list(APPEND CMAKE_REQUIRED_LIBRARIES ${READLINE_LIBRARY})
        set( READLINE_TEST_CODE
            "
            extern \"C\" char * readline(const char *);
            int main() {
              char * line = readline(\"prompt> \");
              return 0;
            }
            "
        )
        include( CheckCXXSourceCompiles )
        message( STATUS "Check for simple libreadline compile" )
        check_cxx_source_compiles( "${READLINE_TEST_CODE}" R_SIMPLE )
        message( STATUS "Check for simple libreadline compile -- ${R_SIMPLE}" )
        if( NOT R_SIMPLE )
            find_package( Curses QUIET )
            if( CURSES_FOUND )
                list(APPEND CMAKE_REQUIRED_LIBRARIES ${CURSES_LIBRARIES})
                
                message( STATUS "Check for curses-libreadline compile" )
                check_cxx_source_compiles( "${READLINE_TEST_CODE}" R_CURSES )
                message( STATUS "Check for curses-libreadline compile -- ${R_CURSES}" )
                if( R_CURSES )
                    list(APPEND READLINE_LIBRARIES ${CURSES_LIBRARIES})
                else()
                    message(FATAL_ERROR "ARG!")
                endif()
            endif()
        endif()
        set(CMAKE_REQUIRED_LIBRARIES ${OLD_CMAKE_REQUIRED_LIBRARIES})
        # #### END check if we need curses...

        message(STATUS "Found GNU readline: ${READLINE_LIBRARY}")
        #FIXME: test whether history is really supported
        list(APPEND READLINE_DEFINES
            HAVE_LIBREADLINE HAVE_READLINE_HISTORY )

        # find headers
        find_path(READLINE_INCLUDE_DIR readline/readline.h)
        if( READLINE_INCLUDE_DIR )
            list(APPEND READLINE_DEFINES HAVE_READLINE_READLINE_H )
            find_path(HISTORY_INCLUDE_DIR readline/history.h)
            if( HISTORY_INCLUDE_DIR )
                list(APPEND READLINE_DEFINES HAVE_READLINE_HISTORY_H )
            endif()
        else()
            find_path(READLINE_INCLUDE_DIR readline.h)
            if ( READLINE_INCLUDE_DIR )
                list(APPEND READLINE_DEFINES HAVE_READLINE_H )
                find_path(HISTORY_INCLUDE_DIR history.h)
                if( HISTORY_INCLUDE_DIR )
                    list(APPEND READLINE_DEFINES HAVE_HISTORY_H )
                endif()
            endif()
        endif()

        if( READLINE_INCLUDE_DIR )
            include_directories( ${READLINE_INCLUDE_DIR} )
            set_target_properties(
                ${PROJECT_NAME}_units
                PROPERTIES COMPILE_DEFINITIONS "${READLINE_DEFINES}"
            )
        endif()
    else()
        message(FATAL_ERROR "Could not find GNU readline")
        set(READLINE_LIBRARIES)
    endif()
    #        ##### END find_package(readline) #####

    target_link_libraries( ${PROJECT_NAME}_units
        ${PROJECT_NAME}_calc
        ${READLINE_LIBRARIES}
    )
    list(APPEND targets_to_install ${PROJECT_NAME}_units)
    #  ########## physical_units ########## #
    #  ############### END ################ #
endif()


# Stuff to help a simple local find module for this project
MESSAGE(STATUS "Creating physical-config.cmake")
FILE(WRITE
    ${CMAKE_BINARY_DIR}/physical-config.cmake
    "set( ${PROJECT_NAME}_VERSION \n"
    "     ${VERSION}\n"
    ")\n"
    "set( ${PROJECT_NAME}_DEFINITIONS \n"
    "   ${${PROJECT_NAME}_DEFINITIONS}\n"
    ")\n"
    "set( ${PROJECT_NAME}_INCLUDE_DIRS\n"
    "   ${${PROJECT_NAME}_INCLUDE_DIRS}\n"
    ")\n"
    "set( ${PROJECT_NAME}_${PROJECT_NAME}_LIBRARY\n"
    "     ${PROJECT_NAME}\n"
    ")\n"
    "set( ${PROJECT_NAME}_calc_LIBRARY\n"
    "   ${PROJECT_NAME}_calc\n"
    ")\n"
    "set( ${PROJECT_NAME}_COMPONENTS\n"
    "   ${${PROJECT_NAME}_COMPONENTS}\n"
    ")\n"
)

install( TARGETS ${targets_to_install}
    ARCHIVE DESTINATION lib/static
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)



# utility macro to add a unit test to be shared by all subdirectories.
macro( physical_unit_test test_name )
    set(BOOST_USE_STATIC_LIBS_TMP ${Boost_USE_STATIC_LIBS})
    set(Boost_USE_STATIC_LIBS ON)
    find_package( Boost REQUIRED COMPONENTS unit_test_framework )
    set(BOOST_USE_STATIC_LIBS ${Boost_USE_STATIC_LIBS_TMP})
    include_directories( ${Boost_INCLUDE_DIRS} )
    add_definitions( ${Boost_DEFINITIONS} )
    add_executable( physical.${test_name}.test ${ARGN} )
    target_link_libraries( physical.${test_name}.test
        ${PROJECT_NAME}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
    add_test( physical.${test_name} physical.${test_name}.test )
endmacro()

macro( physical_calc_unit_test test_name )
    if( Boost_REGEX_FOUND )
        set(BOOST_USE_STATIC_LIBS_TMP ${Boost_USE_STATIC_LIBS})
        set(Boost_USE_STATIC_LIBS ON)
        find_package( Boost REQUIRED COMPONENTS unit_test_framework )
        set(BOOST_USE_STATIC_LIBS ${Boost_USE_STATIC_LIBS_TMP})
        include_directories( ${Boost_INCLUDE_DIRS} )
        add_definitions( ${Boost_DEFINITIONS} )
        add_executable( physical_calc.${test_name}.test ${ARGN} )
        target_link_libraries( physical_calc.${test_name}.test
            ${PROJECT_NAME}_calc
            ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
            ${Boost_REGEX_LIBRARY} )
        add_test( physical_calc.${test_name} physical_calc.${test_name}.test )
    endif()
endmacro()

# add source directory to get the unit tests recursively
add_subdirectory( cxx )

