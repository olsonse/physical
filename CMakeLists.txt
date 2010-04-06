# Physical constants library
# Copyright 2004-2008 Spencer Olson

cmake_minimum_required( VERSION 2.6 )


project( physical )

include( CTest )


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
    cxx/physical/registry.cpp
    cxx/physical/runtime.cpp
    cxx/physical/system.cpp
)

add_library( ${PROJECT_NAME} 
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries( ${PROJECT_NAME} ${LIBXML2_LIBRARIES} )




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

    # FIXME: use flex/bison if proper versions can be found
    cxx/physical/calc/detail/pregen-parser/location.hh
    cxx/physical/calc/detail/pregen-parser/Parser.hpp
    cxx/physical/calc/detail/pregen-parser/position.hh
    cxx/physical/calc/detail/pregen-parser/stack.hh
    cxx/physical/calc/detail/pregen-scanner/FlexLexer.h
)

set( ${PROJECT_NAME}_calc_SOURCES
    cxx/physical/calc/Driver.cpp

    # FIXME: use flex/bison if proper versions can be found
    #cxx/physical/calc/detail/Parser.yy
    #cxx/physical/calc/detail/Scanner.ll
    cxx/physical/calc/detail/pregen-parser/Parser.cpp
    cxx/physical/calc/detail/pregen-scanner/Scanner.cpp
)


find_package( Boost COMPONENTS regex )

if( Boost_regex_FOUND )
    add_library( ${PROJECT_NAME}_calc
        ${${PROJECT_NAME}_calc_HEADERS}
        ${${PROJECT_NAME}_calc_SOURCES}
    )
    
    target_link_libraries( ${PROJECT_NAME}_calc
        ${PROJECT_NAME}
        ${Boost_regex_LIBRARY}
    )
endif()



# include the current directory for framework style includes
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/cxx )


# utility macro to add a unit test to be shared by all subdirectories.
macro( physical_unit_test test_name )
    find_package( Boost REQUIRED COMPONENTS unit_test_framework )
    include_directories( ${Boost_INCLUDE_DIRS} )
    add_executable( physical.${test_name}.test ${ARGN} )
    target_link_libraries( physical.${test_name}.test
        ${PROJECT_NAME}
        ${Boost_LIBRARIES} )
    add_test( physical.${test_name} physical.${test_name}.test )
endmacro()

macro( physical_calc_unit_test test_name )
    if( Boost_regex_FOUND )
        find_package( Boost REQUIRED COMPONENTS unit_test_framework )
        include_directories( ${Boost_INCLUDE_DIRS} )
        add_executable( physical_calc.${test_name}.test ${ARGN} )
        target_link_libraries( physical_calc.${test_name}.test
            ${PROJECT_NAME}_calc
            ${Boost_LIBRARIES} )
        add_test( physical_calc.${test_name} physical_calc.${test_name}.test )
    endif()
endmacro()

# add source directory to get the unit tests recursively
add_subdirectory( cxx )

