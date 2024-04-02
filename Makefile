CC                    := gcc
BIN                   := iot-crypto-tutorial

BUILD_DIR             := ./build
BUILD_DIR_ABS         := $(abspath $(BUILD_DIR))

FREERTOS_DIR      := FreeRTOS/FreeRTOS

FREERTOS_PLUS_DIR := FreeRTOS/FreeRTOS-Plus

KERNEL_DIR            := ${FREERTOS_DIR}/Source

WOLFSSL_DIR           := ${FREERTOS_PLUS_DIR}/ThirdParty/wolfSSL

# TUTORIAL DIRS
COMMON_UTILITIES_DIR  := ./common
HASHING_DIR           := ./01-hashing

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

# BASE SOURCE FILES
SOURCE_FILES          := $(wildcard *.c)
SOURCE_FILES          += $(wildcard ${FREERTOS_DIR}/Source/*.c)
# Memory manager (use malloc() / free() )
SOURCE_FILES          += ${KERNEL_DIR}/portable/MemMang/heap_3.c

# TUTORIAL SOURCE FILES
SOURCE_FILES          += ${COMMON_UTILITIES_DIR}/common_utils.c
SOURCE_FILES          += ${HASHING_DIR}/hashing.c

# posix port
SOURCE_FILES          += ${KERNEL_DIR}/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
SOURCE_FILES          += ${KERNEL_DIR}/portable/ThirdParty/GCC/Posix/port.c

# WOLFSSL SOURCE FILES
SOURCE_FILES          += ${wildcard ${WOLFSSL_DIR}/wolfcrypt/src/sha*.c}


# COMPILER FLAGS
CFLAGS                :=    -ggdb3
LDFLAGS               :=    -ggdb3 -pthread
CPPFLAGS              :=    $(INCLUDE_DIRS) -DBUILD_DIR=\"$(BUILD_DIR_ABS)\"
CPPFLAGS              +=    -D_WINDOWS_

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
