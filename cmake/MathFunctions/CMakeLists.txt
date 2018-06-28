


#add_library(MathFunctions mysqrt.cpp)
add_library(MathFunctions STATIC mysqrt.cpp)


install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)
