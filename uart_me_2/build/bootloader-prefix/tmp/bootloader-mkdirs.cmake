# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "F:/software/esp2/Espressif/frameworks/esp-idf-v5.2.1/components/bootloader/subproject"
  "F:/software/esp2/Espressif/frameworks/esp-idf-v5.2.1/examples/uart_me_2/build/bootloader"
  "F:/software/esp2/Espressif/frameworks/esp-idf-v5.2.1/examples/uart_me_2/build/bootloader-prefix"
  "F:/software/esp2/Espressif/frameworks/esp-idf-v5.2.1/examples/uart_me_2/build/bootloader-prefix/tmp"
  "F:/software/esp2/Espressif/frameworks/esp-idf-v5.2.1/examples/uart_me_2/build/bootloader-prefix/src/bootloader-stamp"
  "F:/software/esp2/Espressif/frameworks/esp-idf-v5.2.1/examples/uart_me_2/build/bootloader-prefix/src"
  "F:/software/esp2/Espressif/frameworks/esp-idf-v5.2.1/examples/uart_me_2/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "F:/software/esp2/Espressif/frameworks/esp-idf-v5.2.1/examples/uart_me_2/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "F:/software/esp2/Espressif/frameworks/esp-idf-v5.2.1/examples/uart_me_2/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
