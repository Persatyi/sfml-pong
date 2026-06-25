# cmake_minimum_required(VERSION major.minor[.patch[.tweak]])
# Команда cmake_minimum_required() встановлює мінімальну версію CMake, 
# яка необхідна для збірки проєкту. Вона повинна бути найпершим викликом 
# у вашому головному файлі
cmake_minimum_required(VERSION 3.28)

# project(projectName   [VERSION major[.minor[.patch[.tweak]]]]   [LANGUAGES languageName ...] ) 
# project() — встановлює назву проекту і додаткову інформацію.
# projectName — назва проекту, обов'язкова.
# VERSION — версія у форматі major.minor.patch.tweak. CMake зберігає кожну частину в окремих змінних: PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR і т.д.
# LANGUAGES — мови програмування які використовуються. Наприклад CXX для C++, C для C. Якщо не вказати — CMake сам визначить.
# Приклад: project(Pong VERSION 1.0 LANGUAGES CXX)
project(Pong VERSION 1.0 LANGUAGES CXX)

# set(variableName value) — встановлює значення змінної.
# CMAKE_RUNTIME_OUTPUT_DIRECTORY — вбудована змінна CMake яка вказує куди класти скомпільований .exe. 
# ${CMAKE_BINARY_DIR} — теж вбудована змінна, це папка build. (абсолютний шлях на верхній рівень папки build, йде з коробки CMake)
# в даному випадку я оголошую цю змінну для лінкера, коли він бачить змінну CMAKE_RUNTIME_OUTPUT_DIRECTORY він покладе наш .exe за встановленою адресою тобіш build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# include() в CMake — це як #include в C. Підключає додатковий код.
# В CMake є вбудовані модулі — готові набори функцій. FetchContent
# це один з них. Без include(FetchContent) команди FetchContent_Declare
# і FetchContent_MakeAvailable просто не існують — CMake їх не знає.

# SFML — ім'я залежності, сам придумуєш
# GIT_REPOSITORY — звідки завантажити
# GIT_TAG — яку версію (тег, гілка або хеш коміту)
# GIT_SHALLOW ON — завантажити тільки один коміт без всієї історії, швидше
# EXCLUDE_FROM_ALL — не включати цілі SFML в загальну збірку
# SYSTEM — вказує що це зовнішня бібліотека, пригнічує попередження компілятора
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# add_executable(targetName source1 [source2 ...])
# add_executable() — створює виконуваний файл з вихідного коду.
# targetName — назва цілі (target), тобто ім'я майбутнього .exe файлу.
# source1, source2... — файли з кодом які треба скомпілювати. Перший обов'язковий, решта необов'язкові.
# Приклад: add_executable(pongApp src/main.cpp src/game.cpp)

# Більш повна версія: add_executable(targetName [WIN32] [MACOSX_BUNDLE] [EXCLUDE_FROM_ALL] source1 [source2 ...])
# WIN32 - Для Windows-застосунків без консолі.
# MACOSX_BUNDLE - Створює macOS Application Bundle (.app) Потрібно майже виключно для macOS GUI-програм.
# EXCLUDE_FROM_ALL - Не включати цю ціль у стандартну збірку. 
# Наприклад: add_executable(TestApp EXCLUDE_FROM_ALL test.c) тепер cmake --build . не збере TestApp
# Але можна явно: cmake --build . --target TestApp Корисно для тестів, прикладів, утиліт.
add_executable(main src/main.cpp)

# target_compile_features(<target> <PRIVATE|PUBLIC|INTERFACE> <feature> ...)
# main — назва цілі (твій .exe)
# PRIVATE — ця вимога тільки для цього таргету, не передається далі
# cxx_std_17 — використовувати стандарт C++17
# Тобто команда каже компілятору — збирай цей проект з підтримкою C++17.
target_compile_features(main PRIVATE cxx_std_17)

# target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> <library> ...)
# main — твій .exe
# PRIVATE — те саме що й попереднє
# SFML::Graphics — підключаємо графічний модуль SFML до нашого проекту
# Без цього рядка компілятор не знайде функції SFML навіть якщо #include написаний.
target_link_libraries(main PRIVATE SFML::Graphics)

# копіюємо папку assets в спомпільований проект
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})