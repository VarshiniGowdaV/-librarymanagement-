cmake_minimum_required(VERSION 3.16)

project(------librarymanagement------ LANGUAGES C)

add_executable(------librarymanagement------ main.c
    student.h
    student.c
    main1.c
    main1.h
    filehanding.h
    filehanding.c
    book.h
    book.c
    staff.h
    staff.c
    borrowedbook.h
    borrowedbook.c
    retunedbook.h
    retunedbook.c
    admin.h
    admin.c)

include(GNUInstallDirs)
install(TARGETS ------librarymanagement------
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
