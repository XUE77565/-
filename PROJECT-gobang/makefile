CC = gcc

# 编译选项
CFLAGS = -Wall -g

# 目标文件
TARGET = main

# 源文件
SRCS = main.c checkban.c variable.c wincheck.c shape.c score.c minimax.c checksimple.c

# 目标文件
OBJS = $(SRCS:.c=.o)

# 默认目标
all: $(TARGET) clean_objs

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 编译源文件生成目标文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的中间文件
clean_objs:
	rm -f $(OBJS)

# 清理生成的所有文件
clean:
	rm -f $(OBJS) $(TARGET)

# 伪目标
.PHONY: all clean clean_objs