# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "C:\\Users\\rojin\\OneDrive\\Desktop\\projectTest\\vitis_all\\platform\\microblaze_riscv_0\\standalone_microblaze_riscv_0\\bsp\\include\\sleep.h"
  "C:\\Users\\rojin\\OneDrive\\Desktop\\projectTest\\vitis_all\\platform\\microblaze_riscv_0\\standalone_microblaze_riscv_0\\bsp\\include\\xiltimer.h"
  "C:\\Users\\rojin\\OneDrive\\Desktop\\projectTest\\vitis_all\\platform\\microblaze_riscv_0\\standalone_microblaze_riscv_0\\bsp\\include\\xtimer_config.h"
  "C:\\Users\\rojin\\OneDrive\\Desktop\\projectTest\\vitis_all\\platform\\microblaze_riscv_0\\standalone_microblaze_riscv_0\\bsp\\lib\\libxiltimer.a"
  )
endif()
