# Docker 컨테이너 생성
```bash
docker build -t c-wasm-env .
docker run -b c-wasm-env
```



# 컨테이너 접속후
UI로 들가서 emsdk 가설치된 경로 기입
![alt text](imgs/image-1.png)
<br/>
예시
![alt text](imgs/image.png)

# 컴파일 방법
```bash
emcc process_image.c -o process_image.js \
-s WASM=1 \
-s EXPORTED_FUNCTIONS='["_processImage", "_malloc", "_free"]' \
-s EXPORTED_RUNTIME_METHODS='["HEAPU8"]' \
-s ALLOW_MEMORY_GROWTH=1 \
-O3 # 최적화 플래그 추가

```
# 실행해보기
```bash
python3 -m http.server 9000
```

# 참고자료
https://velog.io/@mahwin/WASM-%EC%82%AC%EC%9A%A9%ED%95%98%EA%B8%B0