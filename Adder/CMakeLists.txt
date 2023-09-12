# This will build adder as a library
add_library(adder adder.cpp)

# This will add installation functionallity to this lib
install(TARGETS adder DESTINATION lib)
install(FILES adder.h DESTINATION include)