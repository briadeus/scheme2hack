# CMakeList.txt: CMake-Projekt für "CMakeProject1". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)
project("scheme2hack")



# GTest
enable_testing()
find_package(gtest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (scheme2hack "scanner.cpp" "scanner.h" "scheme2hack.cpp")

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
target_link_libraries(scheme2hack ${GTEST_BOTH_LIBRARIES})