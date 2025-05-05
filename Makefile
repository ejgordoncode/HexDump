###########################################################
# E.J. Gordon
###########################################################

EXEC = xed
CC = g++
CFLAGS = -Wall -Wextra -g -std=c++17 -I/Library/Developer/CommandLineTools/usr/include/c++/v1
SRCS = xed.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target: build executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean command to remove compiled files
clean:
	rm -f *.o core $(EXEC)

#######################[ EOF: Makefile ]###################
