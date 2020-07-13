project (rockit)
cmake_minimum_required(VERSION 3.8)

include(sdk/RockitConfig.cmake)

install(DIRECTORY ${ROCKIT_FILE_HEADERS}/ DESTINATION "include/rockit")
install(FILES ${ROCKIT_FILE_LIBS} DESTINATION "lib")

# install(FILES ${ROCKIT_FILE_CONFIGS} DESTINATION "lib")
