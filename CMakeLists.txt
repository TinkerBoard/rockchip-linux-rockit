project (rockit)
cmake_minimum_required(VERSION 3.8)

include(sdk/RockitConfig.cmake)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(ROCKIT_FILE_CONFIGS ${ROCKIT_FILE_CONFIGS}/arch64) 
endif()

option(USE_STASTERIA  "enable stasteria" OFF)
if (${USE_STASTERIA})
    set(AI_CAMERA_CONF ${ROCKIT_FILE_CONFIGS}/aicamera_stasteria.json)
else()
    set(AI_CAMERA_CONF ${ROCKIT_FILE_CONFIGS}/aicamera_uvc.json)
endif()

install(FILES ${AI_CAMERA_CONF} DESTINATION ../../oem/usr/share/aiserver/  RENAME  "aicamera.json")
install(FILES ${ROCKIT_FILE_CONFIGS}/aisingle.json DESTINATION ../../oem/usr/share/aiserver/)
install(FILES ${ROCKIT_FILE_LIBS} DESTINATION "lib")
install(DIRECTORY ${ROCKIT_FILE_HEADERS}/ DESTINATION "include/rockit")

# install(FILES ${ROCKIT_FILE_CONFIGS} DESTINATION "lib")
