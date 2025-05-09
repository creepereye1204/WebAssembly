#include <emscripten/emscripten.h>
#include <stdint.h> 
#include <stdlib.h> 
#include <math.h>  
#ifdef __cplusplus
extern "C" {
#endif

uint8_t clamp_pixel(float pixel_value) {
    return (uint8_t)fmax(0.0f, fmin(255.0f, pixel_value));
}

void boxBlur(uint8_t* inputData, uint8_t* outputData, int width, int height, int radius) {
    int channels = 4;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float sumR = 0;
            float sumG = 0;
            float sumB = 0;
            int pixelCount = 0;

            for (int ky = -radius; ky <= radius; ++ky) {
                for (int kx = -radius; kx <= radius; ++kx) {
                    int sx = x + kx;
                    int sy = y + ky;

                    if (sx >= 0 && sx < width && sy >= 0 && sy < height) {
                        int inputIndex = (sy * width + sx) * channels;
                        sumR += inputData[inputIndex];
                        sumG += inputData[inputIndex + 1];
                        sumB += inputData[inputIndex + 2];
                        pixelCount++;
                    }
                }
            }

            int outputIndex = (y * width + x) * channels;
            if (pixelCount > 0) {
    
                outputData[outputIndex] = (uint8_t)(sumR / pixelCount);
                outputData[outputIndex + 1] = (uint8_t)(sumG / pixelCount);
                outputData[outputIndex + 2] = (uint8_t)(sumB / pixelCount);
            } else {
                
                 outputData[outputIndex] = 0;
                 outputData[outputIndex + 1] = 0;
                 outputData[outputIndex + 2] = 0;
            }
            
        }
    }
}

// amount: 선명화 강도 (일반적으로 1.0 ~ 5.0 사이 값)
EMSCRIPTEN_KEEPALIVE
void processImage(uint8_t* inputData, uint8_t* outputData, int width, int height, int blurRadius, float amount) {
    int channels = 4;
    int numPixels = width * height;
    int numBytes = numPixels * channels;
    uint8_t* blurredData = (uint8_t*)malloc(numBytes);

    if (blurredData == NULL)return;
    
    boxBlur(inputData, blurredData, width, height, blurRadius);

    for (int i = 0; i < numPixels; ++i) {
        int index = i * channels; 

        float originalR = (float)inputData[index];
        float originalG = (float)inputData[index + 1];
        float originalB = (float)inputData[index + 2];

 
        float blurredR = (float)blurredData[index];
        float blurredG = (float)blurredData[index + 1];
        float blurredB = (float)blurredData[index + 2];

    

        float sharpenedR_float = originalR + (originalR - blurredR) * amount;
        float sharpenedG_float = originalG + (originalG - blurredG) * amount;
        float sharpenedB_float = originalB + (originalB - blurredB) * amount;


        outputData[index] = clamp_pixel(sharpenedR_float);         
        outputData[index + 1] = clamp_pixel(sharpenedG_float);    
        outputData[index + 2] = clamp_pixel(sharpenedB_float);     
        outputData[index + 3] = inputData[index + 3];
    }

    free(blurredData);
}


#ifdef __cplusplus
}
#endif
