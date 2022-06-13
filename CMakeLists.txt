cmake_minimum_required(VERSION 3.8)
project(slam_tracepoint_provider)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(PkgConfig REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ament_cmake REQUIRED)

add_library(${PROJECT_NAME} SHARED src/tracepoint.cpp)

if(TRACETOOLS_LTTNG_ENABLED)
  pkg_check_modules(lttng REQUIRED IMPORTED_TARGET lttng-ust>=2.13.0)
  target_compile_definitions(${PROJECT_NAME} PUBLIC LTTNG_ENABLED)
else()
  message(WARNING "LTTnG is disabled")
endif()

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include> ${lttng_INCLUDE_DIRS}
  PRIVATE src/)

target_link_libraries(${PROJECT_NAME} PUBLIC ${lttng_LIBRARIES} rclcpp::rclcpp)

ament_export_targets(${PROJECT_NAME}Targets HAS_LIBRARY_TARGET)
ament_export_dependencies(rclcpp)

install(DIRECTORY include/ DESTINATION include)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
  INCLUDES
  DESTINATION include)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights comment the
  # line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo) comment the line
  # when this package is in a git repo and when a copyright and license is added
  # to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
