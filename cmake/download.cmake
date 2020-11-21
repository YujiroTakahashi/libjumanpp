if (NOT EXISTS ${JPP_SRC_DIR})
    file(DOWNLOAD
        "https://github.com/ku-nlp/jumanpp/releases/download/v2.0.0-rc3/jumanpp-2.0.0-rc3.tar.xz"
        ${CMAKE_SOURCE_DIR}/jumanpp.tgz
        EXPECTED_HASH SHA256=b5ff1e6f712224297454af7771f29ca5642fbe875de35ab850da2d78a67e17dc)

    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_SOURCE_DIR}/jumanpp.tgz
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/jumanpp.tgz
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif ()
