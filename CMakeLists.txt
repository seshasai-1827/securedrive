cmake_minimum_required(VERSION 3.14)
project(journal)

include(FetchContent)

FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v6.1.9
)

FetchContent_MakeAvailable(ftxui)

add_executable(journal ui_test.cpp)

target_link_libraries(journal
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  PRIVATE ssl
  PRIVATE crypto
)