# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Espressif/frameworks/esp-idf-v4.4.3/components/bootloader/subproject"
  "C:/UART_2/build/bootloader"
  "C:/UART_2/build/bootloader-prefix"
  "C:/UART_2/build/bootloader-prefix/tmp"
  "C:/UART_2/build/bootloader-prefix/src/bootloader-stamp"
  "C:/UART_2/build/bootloader-prefix/src"
  "C:/UART_2/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/UART_2/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
