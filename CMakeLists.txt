cmake_minimum_required(VERSION 3.16)

project(librarymanagement LANGUAGES C)

add_executable(librarymanagement main.c
    admin.c
    admin.h
    book.c
    book.h
    borrowedbook.h
    borrowedbook.c
    filehanding.h
    filehanding.c
    main1.h
    main1.c
    returnedbook.h
    returnedbook.c
    sortbyauthor.h
    sortbyauthor.c
    sortbybookname.h
    sortbybookname.c
    staff.h
    staff.c
    student.h
    student.c
)

include(GNUInstallDirs)
install(TARGETS librarymanagement
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
