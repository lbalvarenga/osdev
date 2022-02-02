# Tools
CC = i686-elf
CFLAGS  = 
LDFLAGS = 

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
KERN_TGT  = ${OBJ_DIR}/${KERN_DIR}/kern.bin
KERN_SRCS = $(shell find ${SRC_DIR}/${KERN_DIR} -type f -name "*.c")
KERN_OBJS = $(patsubst ${SRC_DIR}/${KERN_DIR}/%.c,${OBJ_DIR}/${KERN_DIR}/%.o,${KERN_SRCS})

BOOT_SRCS = $(shell find ${SRC_DIR}/${BOOT_DIR} -type f -name "*.s")
BOOT_OBJS = $(patsubst ${SRC_DIR}/${BOOT_DIR}/%.s,${OBJ_DIR}/${BOOT_DIR}/%.o,${BOOT_SRCS})



# Makefile definitions
.PHONY: all run debug dumpimg dirs clean

all: dirs ${TARGET}

run: all
	${QEMU} -drive format=raw,file=${TARGET}

debug: all
	${QEMU} -drive format=raw,file=${TARGET} -s -S -monitor stdio

dumpimg: all
	hexdump -C ${TARGET}

${TARGET}: ${BOOT_OBJS} # ${KERN_TGT}
	cat $^ > $@

# Bootloader
${OBJ_DIR}/${BOOT_DIR}/%.o: ${SRC_DIR}/${BOOT_DIR}/%.s
	@mkdir -p $(dir $@)
	${AS} -f bin $< -o $@

# Kernel

dirs:
	@mkdir -p ${BUILD_DIR}

clean:
	rm -rf ${BUILD_DIR}