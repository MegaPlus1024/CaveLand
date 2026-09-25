cmake_minimum_required(VERSION 3.22)
project(Caveland LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2 COMPONENTS system window graphics network audio REQUIRED)

add_executable(Caveland
    main.cpp
    Animation.cpp
    Bat.cpp
    Button.cpp
    Collider.cpp
    Entity.cpp
    Finish.cpp
    FinishMenu.cpp
    GI.cpp
    Game.cpp
    Geometry.cpp
    Hopper.cpp
    Level.cpp
    Overworld.cpp
    PauseMenu.cpp
    Platform.cpp
    Player.cpp
    Projectile.cpp
    Slash.cpp
    StartMenu.cpp
    Transition.cpp
    Turtle.cpp
    text.cpp
)

target_link_libraries(Caveland PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)
