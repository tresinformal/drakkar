set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND RUN_CLANG_TIDY_BIN_ARGS
    -clang-tidy-binary ${CLANG_TIDY_BIN}
    -header-filter=.*
    -checks=clan*,cert*,misc*,perf*,cppc*,read*,mode*,cppcoreguidelines*,-cert-err58-cpp,-misc-noexcept-move-constructor
	-format-style='{IndentWidth: 4}'
)

add_custom_target(
    tidy
    COMMAND ${RUN_CLANG_TIDY_BIN} ${RUN_CLANG_TIDY_BIN_ARGS}
    COMMENT "running clang tidy"
)