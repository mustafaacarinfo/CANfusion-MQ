# toolchains/raspi.cmake

# 1) Tanım: Bu bir cross‐build, hedef ARM/Pi
set(CMAKE_SYSTEM_NAME       Linux)
set(CMAKE_SYSTEM_PROCESSOR  arm)

# 2) Kompilerler (tam yol verin)
set(CMAKE_C_COMPILER        /usr/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER      /usr/bin/arm-linux-gnueabihf-g++)

# 3) Sysroot (Pi rootfs)
set(CMAKE_SYSROOT           /opt/rpi-sysroot)

# after set(CMAKE_SYSROOT …)
set(CMAKE_EXE_LINKER_FLAGS  
    "--sysroot=${CMAKE_SYSROOT} -L${CMAKE_SYSROOT}/usr/lib ${CMAKE_EXE_LINKER_FLAGS}"
)

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# 4) Derleme bayrakları → mutlaka --sysroot
set(CMAKE_C_FLAGS           "--sysroot=${CMAKE_SYSROOT} ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS         "--sysroot=${CMAKE_SYSROOT} ${CMAKE_CXX_FLAGS}")

# 5) Link bayrakları → mutlaka --sysroot + doğru kütüphane dizini
set(CMAKE_EXE_LINKER_FLAGS  "--sysroot=${CMAKE_SYSROOT} -L${CMAKE_SYSROOT}/usr/lib ${CMAKE_EXE_LINKER_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "--sysroot=${CMAKE_SYSROOT} -L${CMAKE_SYSROOT}/usr/lib ${CMAKE_SHARED_LINKER_FLAGS}")

link_directories(${CMAKE_SYSROOT}/usr/lib
                 ${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf)

set(CMAKE_EXE_LINKER_FLAGS  "--sysroot=${CMAKE_SYSROOT}")
set(CMAKE_SHARED_LINKER_FLAGS "--sysroot=${CMAKE_SYSROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

# 6) Bulma modları → kesinlikle yalnız sysroot
set(CMAKE_FIND_ROOT_PATH    ${CMAKE_SYSROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

