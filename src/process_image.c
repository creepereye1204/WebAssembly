#include <emscripten.h>
#include <stdint.h> // For uint8_t

// JavaScript에서 이 함수를 호출할 수 있도록 내보냅니다.
EMSCRIPTEN_KEEPALIVE
void processImage(uint8_t* pixel_data, int width, int height) {
    // 이미지는 RGBA 형식 (4 바이트/픽셀: R, G, B, A)이라고 가정합니다.
    // 흑백 변환: (R + G + B) / 3 값을 R, G, B 채널에 적용합니다.
    for (int i = 0; i < width * height; ++i) {
        int offset = i * 4; // 각 픽셀의 시작 오프셋

        uint8_t r = pixel_data[offset];
        uint8_t g = pixel_data[offset + 1];
        uint8_t b = pixel_data[offset + 2];

        // 간단한 평균 방식의 흑백 변환
        uint8_t grayscale_value = (r + g + b) / 3;

        pixel_data[offset] = grayscale_value;     // R 채널
        pixel_data[offset + 1] = grayscale_value; // G 채널
        pixel_data[offset + 2] = grayscale_value; // B 채널
        // Alpha 채널 (pixel_data[offset + 3])은 그대로 유지합니다.
    }
}

// WASM 모듈 로드 시 호출될 수 있는 초기화 함수 (선택 사항)
EMSCRIPTEN_KEEPALIVE
int initialize() {
    // 필요한 초기화 작업 수행 (이 예시에서는 필요 없음)
    EM_ASM({
        console.log("WASM module initialized!");
    });
    return 0;
}
