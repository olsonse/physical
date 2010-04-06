physical_unit_test( quantity   quantity.cpp )
physical_unit_test( conversion conversion.cpp )
physical_unit_test( include-guards-0 include-guards-0.cpp )
physical_unit_test( include-guards-1 include-guards-1.cpp )

# need some help in implementing this...
# try_compile ( RESULT_VAR bindir
#   no-compile-conversion0.cpp
#   INCLUDE_DIRECTORIES
#   LINK_LIBRARIES physical-runtime
# )
