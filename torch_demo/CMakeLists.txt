add_executable(torch_demo main.cpp)
target_link_libraries(torch_demo "${TORCH_LIBRARIES}")
set_property(TARGET torch_demo PROPERTY CXX_STANDARD 14)
