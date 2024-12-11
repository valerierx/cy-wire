all: c

c:
	make -C src/ cy-wire

mrproper:
	make -C src/ mrproper
