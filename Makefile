help:
	echo "do make test to test"

test:
	gcc -g test.c alok.c -o test
	chmod +x test
	./test

