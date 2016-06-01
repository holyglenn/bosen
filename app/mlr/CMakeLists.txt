project(mlr)

add_compile_options(-std=c++11 -Wall)

file(GLOB MLR_SOURCE_FILES src/*.[ch]pp)

add_executable(mlr_main ${MLR_SOURCE_FILES})


#find_package(Gflags REQUIRED)

target_include_directories(
    mlr_main PUBLIC ${bosen_INCLUDE_DIRS})
#target_include_directories(
#    mlr_main PUBLIC ${Gflags_INCLUDE_DIRS})



target_link_libraries(mlr_main petuum_bosen)
#target_link_libraries(mlr_main ${Gflags_LIBRARIES})
