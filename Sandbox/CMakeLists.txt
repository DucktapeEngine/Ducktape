cmake_minimum_required (VERSION 3.20)

file (GLOB_RECURSE dtp_source_list "${PROJECT_SOURCE_DIR}/Sandbox/User/Scripts/**/*.cpp" "${PROJECT_SOURCE_DIR}/Sandbox/User/Scripts/*.cpp")
add_library (DucktapeProject SHARED ${dtp_source_list})
set_target_properties (DucktapeProject PROPERTIES PREFIX "")
target_link_libraries(DucktapeProject PRIVATE Ducktape)