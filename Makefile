.PHONY: build
build:
	- emcc src/process_image.c -o src/process_image.js \
		-s WASM=1 \
		-s EXPORTED_FUNCTIONS='["_processImage", "_malloc", "_free"]' \
		-s EXPORTED_RUNTIME_METHODS='["HEAPU8"]' \
		-s ALLOW_MEMORY_GROWTH=1 \
		-O3


.PHONY: run
run:
	- python3 -m http.server 9000