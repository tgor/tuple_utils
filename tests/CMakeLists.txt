cmake_minimum_required(VERSION 2.8)

macro(add_unit_test name)
  add_executable(test_${name} test_${name}.cpp ${ARGN})
  target_link_libraries(test_${name} cppunit)
  add_test(${name} ${EXECUTABLE_OUTPUT_PATH}/test_${name})
endmacro()

enable_testing()
add_unit_test(make_custom_tuple)
add_unit_test(fold_tuples)
add_unit_test(merge_tuples)
add_unit_test(print_tuple)
