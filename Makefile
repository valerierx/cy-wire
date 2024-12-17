all: c

c:
	make -C src/

mrproper:
	make -C src/ mrproper
