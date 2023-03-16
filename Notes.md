# Things I learned


## Header file and cpp file implementation
    > Good practice for coding in C++ is to create .h files containing
    declarations, and then corresponding .cpp files defining those definitions.
    This speeds up the compiling process as this would only compile the needed parts
    of a certain program rather than the entire program. For some reason, picking up
    different parts of a gun, assembling the gun and then using it is faster in
    C++ than simply picking up the gun and using it because the gun "might carry
    unnecessary modifications".

    > If a header "whatevs.h" declares a function "whatevs", "whatevs.cpp" defines 
    that function by borrowing it from the "whatevs.h", and a file "dummy.cpp"
    includes "whatevs.h" and uses the function "whatevs", then run the following
    line in the command line to ensure that you don't get that "function reference
    is undefined" crap:

    ```
    g++ dummy.cpp whatevs.cpp
    ```
    But this won't be necessary with proper cmaking


## \#pragma once directive
    > "#pragma once" is a preprocessor directive which instructs the compiler 
    to include a certain file only once per compilation. This speeds up compilation 
    time and avoids getting compilation errors due to multiple inclusions of the
    same header file. Alternative to "#pragma once":

    ```
    #ifndef FILE_H
    #define FILE_H

    ... Contents of file.h

    #endif /* !FILE_H */
    ```

    Source: https://en.wikipedia.org/wiki/Pragma_once


## Template classes need their methods declared as "inline"


## Forward declarations
    > Use forward declarations of methods/classes (declare them first and define 
    them later) in order to properly implement them as "friend"
    > Steps to properly define a friend template function:
        1. Declare the template class that the future-friend function would take as input/give as output
        2. Declare the template function inside the class with prefix "friend"
        3. During this declaration, state the custom datatype arguments of the method inside <>
        4. Define the friend template function properly after the class.
        > The whole thing will look as follows:
        ```
        // template class initialization so that it could be used by future-friend template method:
        template<typename T, size_t size> class Menace;

        // future-friend template method initialization:
        template<typename T, size_t size>
        Menace<T, size> enrage(Menace<T, size>& dennis);

        // Specifying template method as friend inside class definition:
        template<typename T, size_t size>
        class Menace {
            int chaos = 69;
        public:
            Menace() {}

            friend Menace enrage<T, size>(Menace<T, size>& dennis);
        };

        // friend template method definition:
        template<typename T, size_t size>
        Menace<T, size> enrage(Menace<T, size>& dennis) {
            ...
        };
        ```


## GoogleTest stuff
    > "googletest" (gtest.h) testing framework is used in this project. Things to
    remember when writing tests:
        > Try to make tests as independent and repeatable as possible because
        debugging tests depending on other tests would make you wanna shoot yourself
        
        > Organize your tests well
        
        > Make tests as portable and reusable as possible because different OSs
        might use different compilers
        
        > Write tests such that they provide as much info as possible. Also write
        them such that they don't stop when they hit an error, and instead execute
        till the very last test so that you can look at multiple errors at once.
        This could help when a selected few errors are the cause of multiple many
        errors


## CMake stuff for unit testing
[Read this](https://cmake.org/cmake/help/latest/manual/cmake.1.html)
    ```
    # If you aren't already in the folder with CMakeLists.txt:
    cd <path_to_CMakeListsdottxt>

    # -S flag is followed by source path and -B is followed by build path.
    # This command generates a project build-system:
    cmake -S . -B build

    # This will build the binaries into the build folder:
    cmake --build build
    cd build && ctest
    ```
DELETE PREVIOUS CONTENTS OF THE BUILD FOLDER TO CLEAR PREVIOUS CACHE IF YOU ARE 
BUILDING WITH A NEW CMAKELISTS.TXT
 


## Ctest stuff
In case the test fails and you wanna see what went wrong,
    ```
    ctest -R alkimia-alkinvoice
    ```
will make only the failing test run, and
    ```
    ctest -R alkimia-alkinvoice -VV
    ```
will make only the failing test run as well as display its output.
[Source](https://stackoverflow.com/questions/6931143/how-to-find-where-the-error-is-while-running-ctest)

    
## 21/10/2022
    > Reference: https://www.youtube.com/watch?v=6dqFqh3UbPY

    > Googletest has dependency "googletest (= 1.10.0-2)"
    (Check with "sudo apt show libgtest-dev")

    > Overcome this with "sudo apt install libgtest-dev googletest"

## Geogebra is a good tool for visualization purposes
https://www.geogebra.org/

## Doubly Connected Edge List (DCEL)
[This a popular data structure for working with polygons](https://en.wikipedia.org/wiki/Doubly_connected_edge_list)