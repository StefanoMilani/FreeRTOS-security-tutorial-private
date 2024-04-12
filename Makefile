CC                    := gcc
BIN                   := iot-crypto-tutorial

BUILD_DIR             := ./build
BUILD_DIR_ABS         := $(abspath $(BUILD_DIR))

FREERTOS_DIR          := FreeRTOS/FreeRTOS

FREERTOS_PLUS_DIR     := FreeRTOS/FreeRTOS-Plus

KERNEL_DIR            := ${FREERTOS_DIR}/Source

WOLFSSL_DIR           := ${FREERTOS_PLUS_DIR}/ThirdParty/wolfSSL

# TUTORIAL DIRS
COMMON_UTILITIES_DIR  := common
HASHING_DIR           := 01-hashing_tutorial
AES_DIR               := 02-aes_tutorial
ECC_DIR               := 03-ecc_tutorial

# BASE INCLUDE DIRS
INCLUDE_DIRS          := -I.
INCLUDE_DIRS          += -I./Trace_Recorder_Configuration
INCLUDE_DIRS          += -I${KERNEL_DIR}/include
INCLUDE_DIRS          += -I${KERNEL_DIR}/portable/ThirdParty/GCC/Posix
INCLUDE_DIRS          += -I${KERNEL_DIR}/portable/ThirdParty/GCC/Posix/utils

# WOLFSSL INCLUDE DIRS
INCLUDE_DIRS          += -I${WOLFSSL_DIR}

# TUTORIAL INCLUDE DIRS 
INCLUDE_DIRS          += -I${COMMON_UTILITIES_DIR}
INCLUDE_DIRS          += -I${HASHING_DIR}
INCLUDE_DIRS          += -I${AES_DIR}
INCLUDE_DIRS          += -I${ECC_DIR}

# BASE SOURCE FILES
SOURCE_FILES          := main.c
SOURCE_FILES          += ${FREERTOS_DIR}/Source/tasks.c
SOURCE_FILES          += ${FREERTOS_DIR}/Source/queue.c
SOURCE_FILES          += ${FREERTOS_DIR}/Source/list.c
# Memory manager (use malloc() / free() )
SOURCE_FILES          += ${KERNEL_DIR}/portable/MemMang/heap_3.c

# TUTORIAL SOURCE FILES
SOURCE_FILES          += ${COMMON_UTILITIES_DIR}/common_utils.c
SOURCE_FILES          += ${HASHING_DIR}/hashing_tutorial.c
SOURCE_FILES          += ${AES_DIR}/aes_tutorial.c
SOURCE_FILES          += ${ECC_DIR}/ecc_tutorial.c

# posix port
SOURCE_FILES          += ${KERNEL_DIR}/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
SOURCE_FILES          += ${KERNEL_DIR}/portable/ThirdParty/GCC/Posix/port.c

# WOLFSSL SOURCE FILES
SOURCE_FILES          += ${wildcard ${WOLFSSL_DIR}/wolfcrypt/src/sha*.c}
SOURCE_FILES          += ${WOLFSSL_DIR}/wolfcrypt/src/memory.c
SOURCE_FILES          += ${WOLFSSL_DIR}/wolfcrypt/src/random.c
SOURCE_FILES          += ${WOLFSSL_DIR}/wolfcrypt/src/aes.c
SOURCE_FILES          += ${WOLFSSL_DIR}/wolfcrypt/src/fe_low_mem.c
SOURCE_FILES          += ${WOLFSSL_DIR}/wolfcrypt/src/curve25519.c


# COMPILER FLAGS
CFLAGS                :=    -ggdb3
LDFLAGS               :=    -ggdb3 -pthread
CPPFLAGS              :=    $(INCLUDE_DIRS) -DBUILD_DIR=\"$(BUILD_DIR_ABS)\"
CPPFLAGS              +=    -D_WINDOWS_
CPPFLAGS              +=    -DWC_NO_HARDEN
CPPFLAGS              +=    -DHAVE_CONFIG_H

OBJ_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

DEP_FILE = $(OBJ_FILES:%.o=%.d)

${BIN} : $(BUILD_DIR)/$(BIN)

${BUILD_DIR}/${BIN} : ${OBJ_FILES}
	-mkdir -p ${@D}
	$(CC) $^ ${LDFLAGS} -o $@

-include ${DEP_FILE}

${BUILD_DIR}/%.o : %.c Makefile
	-mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -c $< -o $@

.PHONY: clean

clean:
	-rm -rf $(BUILD_DIR)

run:
	${BUILD_DIR}/${BIN}


GPROF_OPTIONS := --directory-path=$(INCLUDE_DIRS)
