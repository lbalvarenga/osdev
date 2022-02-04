# Tools
CC = i686-elf-gcc
CFLAGS  = -ffreestanding -Wall -Wextra -pedantic \
-std=c2x -ffunction-sections -I ${SRC_DIR}/${KERN_DIR}

LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc
LDFILE = linker.ld

AS = nasm
QEMU = qemu-system-i386

# Directories/Files
BUILD_DIR = build
TARGET = ${BUILD_DIR}/boot.flp

BOOT_DIR = boot
KERN_DIR = kern

SRC_DIR = src
OBJ_DIR = ${BUILD_DIR}/obj



# Dependency management
KERN_TGT    = ${OBJ_DIR}/${KERN_DIR}/kern.bin
KERN_C_SRCS = $(shell find ${SRC_DIR}/${KERN_DIR} -type f -name "*.c")
KERN_C_OBJS = $(patsubst ${SRC_DIR}/${KERN_DIR}/%.c,${OBJ_DIR}/${KERN_DIR}/%.o,${KERN_C_SRCS})
KERN_S_SRCS = $(shell find ${SRC_DIR}/${KERN_DIR} -type f -name "*.s")
KERN_S_OBJS = $(patsubst ${SRC_DIR}/${KERN_DIR}/%.s,${OBJ_DIR}/${KERN_DIR}/%.o,${KERN_S_SRCS})

BOOT_SRCS = $(shell find ${SRC_DIR}/${BOOT_DIR} -type f -name "*.s")
BOOT_DEPS = $(shell find ${SRC_DIR}/${BOOT_DIR} -type f -name "*.inc")
BOOT_OBJS = $(patsubst ${SRC_DIR}/${BOOT_DIR}/%.s,${OBJ_DIR}/${BOOT_DIR}/%.o,${BOOT_SRCS})



# Makefile definitions
.PHONY: all run debug dumpimg dirs clean

all: dirs ${TARGET}

run: all
	${QEMU} -drive format=raw,file=${TARGET}

debug: all
	${QEMU} -drive format=raw,file=${TARGET} -s -S -monitor stdio

${TARGET}: ${BOOT_OBJS} ${KERN_TGT}
	cat $^ > $@

# Bootloader ------------------------------------------------------

${OBJ_DIR}/${BOOT_DIR}/%.o: ${SRC_DIR}/${BOOT_DIR}/%.s ${BOOT_DEPS}
	@echo "[AS] $< -> $@"
	@mkdir -p $(dir $@)
	@${AS} -f bin $< -o $@ -I ${SRC_DIR}/${BOOT_DIR}

# Kernel ----------------------------------------------------------

# C source files
${OBJ_DIR}/${KERN_DIR}/%.o: ${SRC_DIR}/${KERN_DIR}/%.c
	@echo "[CC] $< -> $@"
	@mkdir -p $(dir $@)
	@${CC} -c $< -o $@ ${CFLAGS}

# Assembly files
${OBJ_DIR}/${KERN_DIR}/%.o: ${SRC_DIR}/${KERN_DIR}/%.s
	@echo "[AS] $< -> $@"
	@mkdir -p $(dir $@)
	@${AS} -f elf32 $< -o $@

# Linking
${KERN_TGT}: ${KERN_C_OBJS} ${KERN_S_OBJS}
	@echo "[LD] ${OBJ_DIR}/* -> $@"
	@${CC} -T ${LDFILE} -o $@ $^ ${LDFLAGS}

dirs:
	@mkdir -p ${BUILD_DIR}

clean:
	rm -rf ${BUILD_DIR}
