# C++ Problem Solves (cpp_solves)

C++26 기반 알고리즘 및 문제 풀이(PS) 독립 워크스페이스입니다.

## 특징
- C++26 표준 지원
- `<bits/stdc++.h>` 헤더 기본 탑재 (`include/`)
- VSCode <kbd>Cmd</kbd> + <kbd>Shift</kbd> + <kbd>B</kbd> (Ninja 빌드) 및 <kbd>F5</kbd> (LLDB 디버그) 원클릭 연동
- Cross-platform 호환 (macOS, Linux, Windows)

## 빌드 및 실행
```bash
# Debug 빌드
cmake -B build/debug -DCMAKE_BUILD_TYPE=Debug -G Ninja
ninja -C build/debug
./build/debug/example

# Release 빌드
cmake -B build/release -DCMAKE_BUILD_TYPE=Release -G Ninja
ninja -C build/release
./build/release/example
```
