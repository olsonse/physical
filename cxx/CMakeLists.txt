# define the library, its source files, and its dependencies 
hpmi_library( physical
    GLOB physical/*.cpp
         physical/calc/*.cpp
         physical/constant/*.cpp
         physical/constant/detail/*.cpp
         physical/detail/*.cpp
         physical/dimension/*.cpp
    INCLUDE_DIRS .
    STATIC
)

client_requirements( physical
    INCLUDE_DIRS .
)

# add unit tests
add_subdirectory( physical/test )
# add_subdirectory( physical/calc/test )

