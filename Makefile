
CFLAGS := -std=c99
librpnconv_C_SRCS := src/infix2rpn.c src/rpn2infix.c src/vector_char.c src/vector_reftype.c src/infix_rpn_common.c
librpnconv_C_OBJS := ${librpnconv_C_SRCS:.c=.o}

.PHONY: all clean

all: rpnconv

librpnconv: $(librpnconv_C_OBJS)
	ar rcs librpnconv.a $(librpnconv_C_OBJS)

rpnconv: librpnconv src/main.c
	gcc -std=c99 -o rpn_conv src/main.c librpnconv.a -lcheck -lm -lpthread -lrt

clean:
	@- $(RM) $(librpnconv_C_OBJS)
	@- $(RM) librpnconv.a
	@- $(RM) rpn_conv
