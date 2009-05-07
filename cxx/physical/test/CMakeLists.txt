hpmi_unit_test( quantity                    LIBS physical-runtime )
hpmi_unit_test( conversion                  LIBS physical-runtime )

# need some help in implementing this...
# try_compile ( RESULT_VAR bindir
#   no-compile-conversion0.cpp
#   INCLUDE_DIRECTORIES
#   LINK_LIBRARIES physical-runtime
# )
