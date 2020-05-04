TARGET_EXEC ?= TMCAPI_EXAMPLE
BUILD_DIR ?= ./bin
CC = gcc
CXX = g++

# C Fags
CFLAGS			+= -Wall 
CFLAGS			+= -g
LDFLAGS			+= -lbcm2835 
LDFLAGS			+= -lwiringPi

# define the C source files
SRCS				+= main.c
SRCS				+= SPI_TMC.c
# used functions from TMC_API
#SRCS				+= TMC-API/tmc/helpers/Debug.c
#SRCS 			+= TMC-API/tmc/ic/TMC2130/TMC2130.c
#SRCS 			+= TMC-API/tmc/ic/TMC2208/TMC2208.c
#SRCS 			+= TMC-API/tmc/ic/TMC2224/TMC2224.c
#SRCS 			+= TMC-API/tmc/ic/TMC2660/TMC2660.c
#SRCS 			+= TMC-API/tmc/ic/TMC5130/TMC5130.c
SRCS 			+= TMC-API/tmc/ic/TMC5160/TMC5160.c
#SRCS				+= TMC-API/tmc/ic/TMC4330/TMC4330.c
#SRCS				+= TMC-API/tmc/ic/TMC4331/TMC4331.c
#SRCS				+= TMC-API/tmc/ic/TMC4361/TMC4361.c
#SRCS				+= TMC-API/tmc/ic/TMC4361A/TMC4361A.c
#SRCS				+= TMC-API/tmc/ic/TMC4670/TMC4670.c
#SRCS				+= TMC-API/tmc/ic/TMC4671/TMC4671.c
#SRCS				+= TMC-API/tmc/ic/TMC4672/TMC4672.c
#SRCS				+= TMC-API/tmc/ic/TMCC160/TMCC160.c
#SRCS				+= TMC-API/tmc/ic/TMC5041/TMC5041.c
#SRCS				+= TMC-API/tmc/ic/TMC5062/TMC5062.c
#SRCS				+= TMC-API/tmc/ic/TMC5072/TMC5072.c

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p