# Ce script CMake permet de nettoyer les fichiers générés lors de la construction du projet.
# Utilisation : cmake -P CMakeClean.cmake

file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/CMakeFiles")
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/Testing")
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/doc")
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/html")
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/latex")
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/man")
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/xml")
file(REMOVE "${CMAKE_BINARY_DIR}/CMakeCache.txt")
file(REMOVE "${CMAKE_BINARY_DIR}/CTestTestfile.cmake")
file(REMOVE "${CMAKE_BINARY_DIR}/Makefile")
file(REMOVE "${CMAKE_BINARY_DIR}/cmake_install.cmake")
file(REMOVE "${CMAKE_BINARY_DIR}/install_manifest.txt")
