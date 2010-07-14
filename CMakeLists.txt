# Physical constants library
# Copyright 2004-2008 Spencer Olson

cmake_minimum_required( VERSION 2.6 )


project( physical )

set( VERSION physical-0.1.3-8-g6080bf7 )

# Allow the developer to select what native type to use for
# runtime::physical::quantity<TYPE>
set( RUNTIME_PHYSICAL_QUANTITY "std::complex<double>"  CACHE STRING
     "Storage class for runtime::physical::Quantity"
)


include( CTest )


add_definitions(
    -DPHYSICAL_VERSION=\"${VERSION}\"
    -DRUNTIME_PHYSICAL_QUANTITY=${RUNTIME_PHYSICAL_QUANTITY}
)


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


find_package( BISON )

set( MIN_BISON_VERSION 2.4 )
if( BISON_VERSION VERSION_EQUAL ${MIN_BISON_VERSION} OR
    BISON_VERSION VERSION_GREATER ${MIN_BISON_VERSION} )
    BISON_TARGET(
        CalcParser
        cxx/physical/calc/detail/Parser.yy
        ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp
    )

    set( PhysicalUsesBISON 1 )
    set( ParserHPP )
    set( ParserCPP ${BISON_CalcParser_OUTPUTS} )

    include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
else()
    set( ParserHPP       cxx/physical/calc/detail/pregen-parser/location.hh
                         cxx/physical/calc/detail/pregen-parser/Parser.hpp
                         cxx/physical/calc/detail/pregen-parser/position.hh
                         cxx/physical/calc/detail/pregen-parser/stack.hh )
    set( ParserCPP       cxx/physical/calc/detail/pregen-parser/Parser.cpp )
    include_directories( cxx/physical/calc/detail/pregen-parser )
endif()


find_package( FLEX )

set( MIN_FLEX_VERSION 2.5.35 )
if( FLEX_VERSION VERSION_EQUAL ${MIN_FLEX_VERSION} OR
    FLEX_VERSION VERSION_GREATER ${MIN_FLEX_VERSION} )
    FLEX_TARGET(
        CalcScanner
        cxx/physical/calc/detail/Scanner.ll
        ${CMAKE_CURRENT_BINARY_DIR}/Scanner.cpp
    )

    set( ScannerHPP )
    set( ScannerCPP ${FLEX_CalcScanner_OUTPUTS} )

    include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

    set( PhysicalUsesFLEX 1 )
    if( PhysicalUsesBISON )
        add_flex_bison_dependency( CalcScanner CalcParser )
    endif()
else()
    set( ScannerHPP      cxx/physical/calc/detail/pregen-scanner/FlexLexer.h )
    set( ScannerCPP      cxx/physical/calc/detail/pregen-scanner/Scanner.cpp )
    include_directories( cxx/physical/calc/detail/pregen-scanner )
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


find_package( Boost COMPONENTS regex )

if( Boost_REGEX_FOUND )
    add_library( ${PROJECT_NAME}_calc
        ${${PROJECT_NAME}_calc_HEADERS}
        ${${PROJECT_NAME}_calc_SOURCES}
    )
    
    target_link_libraries( ${PROJECT_NAME}_calc
        ${PROJECT_NAME}
        ${Boost_REGEX_LIBRARY}
    )
endif()



# include the current directory for framework style includes
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/cxx )


# utility macro to add a unit test to be shared by all subdirectories.
macro( physical_unit_test test_name )
    set(BOOST_USE_STATIC_LIBS_TMP ${Boost_USE_STATIC_LIBS})
    set(Boost_USE_STATIC_LIBS ON)
    find_package( Boost REQUIRED COMPONENTS unit_test_framework )
    set(BOOST_USE_STATIC_LIBS ${Boost_USE_STATIC_LIBS_TMP})
    include_directories( ${Boost_INCLUDE_DIRS} )
    add_executable( physical.${test_name}.test ${ARGN} )
    target_link_libraries( physical.${test_name}.test
        ${PROJECT_NAME}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
    add_test( physical.${test_name} physical.${test_name}.test )
endmacro()

macro( physical_calc_unit_test test_name )
    if( Boost_regex_FOUND )
        set(BOOST_USE_STATIC_LIBS_TMP ${Boost_USE_STATIC_LIBS})
        set(Boost_USE_STATIC_LIBS ON)
        find_package( Boost REQUIRED COMPONENTS unit_test_framework )
        set(BOOST_USE_STATIC_LIBS ${Boost_USE_STATIC_LIBS_TMP})
        include_directories( ${Boost_INCLUDE_DIRS} )
        add_executable( physical_calc.${test_name}.test ${ARGN} )
        target_link_libraries( physical_calc.${test_name}.test
            ${PROJECT_NAME}_calc
            ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
        add_test( physical_calc.${test_name} physical_calc.${test_name}.test )
    endif()
endmacro()

# add source directory to get the unit tests recursively
add_subdirectory( cxx )

