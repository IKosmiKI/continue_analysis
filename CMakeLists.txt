cmake_minimum_required(VERSION 3.29)
project(continue_analysis)

set(CMAKE_CXX_STANDARD 14)

add_executable(continue_analysis
    main.cpp
        test.cpp
        main.cpp
        Lexer.h
        Lexer.cpp
        Parser.cpp
        Parser.h
        tokeninfo.h)
