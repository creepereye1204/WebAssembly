.PHONY: build
build:
	- emcc src/core.c -o src/core.html

.PHONY: run
run:
	- python3 -m http.server 9000