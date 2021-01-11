aux_source_directory(./src ImageSheeter_SRC)

set(ImageSheeter_Name ImageSheeter.out)

add_executable(${ImageSheeter_Name} main.cpp ${ImageSheeter_SRC})
target_include_directories(${ImageSheeter_Name} PRIVATE ./include)

# some tests
add_executable(ReadImgSheeter_Work.out tests/ReadImgSheeter.cpp ${ImageSheeter_SRC})
target_include_directories(ReadImgSheeter_Work.out PRIVATE ./include)
