add_executable(multiply_demo main.cpp)
target_link_libraries(multiply_demo PUBLIC
            "-Wl,--no-as-needed -rdynamic" dl "${TORCH_LIBRARIES}" multipy
        )