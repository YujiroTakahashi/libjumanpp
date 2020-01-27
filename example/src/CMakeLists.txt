add_executable(jumanpp-example-bin
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cc)

if (execinfo-shared)
    target_link_libraries(jumanpp-shared ${execinfo-shared})
endif ()

target_link_libraries(jumanpp-example-bin
    ${pathie-shared} Threads::Threads
    ${jumanpp-shared})

set_target_properties(jumanpp-example-bin PROPERTIES OUTPUT_NAME example) 
