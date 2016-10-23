
rpn_conv: src/*.c
	gcc -std=c99 -o rpn_conv src/*.c -lcheck -lm -lpthread -lrt
