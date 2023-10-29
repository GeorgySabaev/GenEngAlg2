# CMakeList.txt: проект CMake для GenAlg; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (GenAlg "testmain.cpp" "SolverGA.cpp" "ReverseMutationOperator.cpp" "KnapsackProblemAssesser.cpp" "CrossoverOperator.cpp" "FlipMutationOperator.cpp" "InsertionOperator.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GenAlg PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
