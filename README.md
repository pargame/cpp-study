# C++ Study (`cpp_study`)

C++26 기반 알고리즘 문제 풀이(`solve`) 및 STL 학습(`stl`) 통합 워크스페이스입니다.

## 폴더 구조
* `solve/`: 알고리즘 및 문제 풀이 소스코드
* `stl/`: C++ 표준 템플릿 라이브러리(STL) 학습 노트 및 코드
* `include/`: `<bits/stdc++.h>` 등 공통 헤더

## 빌드 및 실행
```bash
# Debug 빌드
cmake -B build/debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G Ninja
ninja -C build/debug
./build/debug/example

# Release 빌드
cmake -B build/release -DCMAKE_BUILD_TYPE=Release -G Ninja
ninja -C build/release
./build/release/example
```
