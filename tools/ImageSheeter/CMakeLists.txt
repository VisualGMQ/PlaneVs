aux_source_directory(./src ImageSheeter_SRC)

set(ImageSheeter_Name ImageSheeter.out)

add_executable(${ImageSheeter_Name} ${ImageSheeter_SRC})
target_include_directories(${ImageSheeter_Name} PRIVATE ./include)
