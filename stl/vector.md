# std::vector

> C++ 표준 템플릿 라이브러리(STL)의 대표적인 **시퀀스 컨테이너(Sequence Container)** 로, 크기가 동적으로 조절되는 **동적 배열(Dynamic Array)** 입니다.

---

## 1. 개요 (Overview)

`std::vector`는 메모리상에 원소들을 **연속적(Contiguous)** 으로 배치합니다. 따라서 배열처럼 임의 접근(Random Access)이 매우 빠르며, 배열의 끝에서 원소를 추가/제거하는 작업이 효율적입니다.

- **헤더 파일**: `#include <vector>`
- **네임스페이스**: `std`
- **메모리 구조**: 힙(Heap) 영역에 연속된 메모리 블록을 할당받아 관리합니다.

### 장점 vs 단점
| 장점 (Pros) | 단점 (Cons) |
| :--- | :--- |
| • 인덱스를 통한 $O(1)$ 임의 접근 가능<br>• 메모리가 연속되어 캐시 적중률(Cache Locality) 우수<br>• 끝단 삽입/삭제 속도가 빠름<br>• 크기가 자동으로 동적 확장됨 | • 중간/앞단 삽입/삭제 시 원소 이동으로 $O(N)$ 소요<br>• 메모리 재할당 시 전체 복사/이동 오버헤드 발생<br>• `std::vector<bool>`은 비트 단위 최적화로 일반 참조 불가 |

---

## 2. 시간 복잡도 (Time Complexity)

| 작업 (Operation) | 함수 (Function) | 시간 복잡도 (Time Complexity) | 비고 (Notes) |
| :--- | :--- | :---: | :--- |
| **임의 접근** | `v[i]`, `v.at(i)` | **$O(1)$** | 배열과 동일한 상수 시간 |
| **끝단 삽입** | `v.push_back()`, `v.emplace_back()` | **$O(1)$ (Amortized)** | 재할당 발생 시 일시적 $O(N)$ |
| **끝단 삭제** | `v.pop_back()` | **$O(1)$** | 끝 원소 소멸 |
| **중간 삽입/삭제** | `v.insert()`, `v.erase()` | **$O(N)$** | 이후 원소들의 메모리 시프트 필요 |
| **탐색 (선형)** | `std::find()` | **$O(N)$** | 정렬되지 않은 경우 |
| **탐색 (이진)** | `std::lower_bound()` 등 | **$O(\log N)$** | 정렬된 경우에만 사용 가능 |

---

## 3. 선언 및 초기화 (Declaration & Initialization)

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 1. 빈 벡터 선언
    vector<int> v1;

    // 2. 기본값(0)으로 채워진 크기 5인 벡터 {0, 0, 0, 0, 0}
    vector<int> v2(5);

    // 3. 특정 값(10)으로 채워진 크기 5인 벡터 {10, 10, 10, 10, 10}
    vector<int> v3(5, 10);

    // 4. 초기화 리스트 (C++11)
    vector<int> v4 = {1, 2, 3, 4, 5};

    // 5. 다른 벡터 복사
    vector<int> v5(v4);

    // 6. 2차원 벡터 선언 (행: 3, 열: 4, 초기값: 0) - 코테 빈출!
    vector<vector<int>> matrix(3, vector<int>(4, 0));

    return 0;
}
```

---

## 4. 핵심 멤버 함수 (Key Member Functions)

### (1) 원소 접근 (Element Access)

| 함수 | 설명 |
| :--- | :--- |
| `v[i]` | $i$번째 원소 반환 (범위 검사 없음, 빠름) |
| `v.at(i)` | $i$번째 원소 반환 (범위 검사 수행, 초과 시 `std::out_of_range` 예외 발생) |
| `v.front()` | 첫 번째 원소의 참조 반환 |
| `v.back()` | 마지막 원소의 참조 반환 |
| `v.data()` | 실제 데이터가 저장된 내부 연속 배열의 포인터 반환 |

```cpp
vector<int> v = {10, 20, 30, 40};

cout << v[1] << "\n";       // 20
cout << v.front() << "\n";  // 10
cout << v.back() << "\n";   // 40
```

---

### (2) 크기 및 용량 (Size & Capacity)

> **🔥 IMPORTANT: `size` vs `capacity`**
>
> - **`size`**: 벡터에 현재 실제로 들어있는 원소의 개수
> - **`capacity`**: 메모리 재할당 없이 저장 가능한 최대 원소 개수 (여유 공간)

| 함수 | 설명 |
| :--- | :--- |
| `v.empty()` | 비어있으면 `true`, 아니면 `false` 반환 ($O(1)$) |
| `v.size()` | 현재 원소 개수 반환 |
| `v.capacity()` | 현재 할당된 메모리 용량 반환 |
| `v.reserve(n)` | 최소 $n$개의 원소를 담을 수 있도록 용량(capacity)을 미리 확보 (**재할당 방지 최적화**) |
| `v.resize(n)` | 벡터의 크기(size)를 $n$으로 변경 (늘어나면 기본값 생성, 줄어들면 초과분 제거) |
| `v.shrink_to_fit()`| 용량(capacity)을 현재 크기(size)에 맞게 축소 |

```cpp
vector<int> v;
v.reserve(100); // 100개 공간 미리 확보 -> push_back 시 재할당 오버헤드 0!

cout << "size: " << v.size() << "\n";         // 0
cout << "capacity: " << v.capacity() << "\n"; // 100
```

---

### (3) 원소 추가 / 제거 / 수정 (Modifiers)

| 함수 | 설명 | 시간 복잡도 |
| :--- | :--- | :---: |
| `v.push_back(val)` | 끝에 원소 복사/이동 추가 | $O(1)$ amortized |
| `v.emplace_back(args)`| 끝에서 객체를 직접 생성하여 추가 (불필요한 임시 객체 복사/이동 방지) | $O(1)$ amortized |
| `v.pop_back()` | 마지막 원소 제거 | $O(1)$ |
| `v.insert(iter, val)`| `iter` 위치에 원소 삽입 | $O(N)$ |
| `v.erase(iter)` | `iter` 위치의 단일 원소 제거 | $O(N)$ |
| `v.erase(start, end)`| `[start, end)` 범위의 원소들 제거 | $O(N)$ |
| `v.clear()` | 모든 원소 제거 (`size` = 0, `capacity`는 유지됨) | $O(N)$ |

> **💡 TIP:** 단순 기본 자료형(`int`, `double`)에서는 `push_back`과 `emplace_back`의 성능 차이가 거의 없으나, 사용자 정의 구조체/클래스에서는 `emplace_back`이 생성자 인자만 넘겨 인플레이스(In-place) 생성하므로 성능상 유리합니다.

---

## 5. 순회 및 탐색 (Iteration)

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v = {10, 20, 30, 40, 50};

    // 1. 범위 기반 for문 (읽기 전용 권장)
    for (const auto& x : v) {
        cout << x << " ";
    }
    cout << "\n";

    // 2. 범위 기반 for문 (값 수정 시)
    for (auto& x : v) {
        x *= 2;
    }

    // 3. 인덱스 기반 순회
    for (int i = 0; i < static_cast<int>(v.size()); ++i) {
        cout << v[i] << " ";
    }
    cout << "\n";

    // 4. 반복자(Iterator) 기반 순회
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    // 5. 역순 반복자(Reverse Iterator) 순회
    for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << "\n";

    return 0;
}
```

---

## 6. 주요 `<algorithm>` 연계 (요약)

> **📝 NOTE:** 각 알고리즘 및 수치 연산 함수의 상세 옵션과 구현 패턴은 별도의 `algorithm.md` 및 `numeric.md` 문서를 참고하세요.

| 분류 | 함수 및 관용구 (Idiom) | 시간 복잡도 |
| :--- | :--- | :---: |
| **정렬** | `sort(v.begin(), v.end());` | $O(N \log N)$ |
| **중복 제거** | `v.erase(unique(v.begin(), v.end()), v.end());` | $O(N)$ *(정렬 필수)* |
| **원소 뒤집기** | `reverse(v.begin(), v.end());` | $O(N)$ |
| **최대 / 최소** | `*max_element(v.begin(), v.end());` | $O(N)$ |
| **이진 탐색** | `lower_bound(v.begin(), v.end(), val);` | $O(\log N)$ *(정렬 필수)* |
| **누적합** | `accumulate(v.begin(), v.end(), 0);` *(numeric.md 참고)* | $O(N)$ |

---

## 7. 주의사항 및 모범 사례 (Pitfalls & Best Practices)

### ⚠️ 반복자 무효화 (Iterator Invalidation)
`push_back`이나 `insert`로 인해 용량(capacity)이 초과되면, 새로운 더 큰 메모리 공간을 할당받고 기존 원소를 이동시킵니다. 이 과정에서 **기존 반복자, 포인터, 참조가 모두 무효화(dangling)** 됩니다.
```cpp
auto it = v.begin();
v.push_back(100); // 재할당 발생 가능
// *it = 10;     // ❌ 위험: it가 가리키던 주소가 해제되었을 수 있음
```

### ⚠️ `v.size()` 언더플로우 주의
`v.size()`는 부호 없는 정수형(`size_t`)을 반환합니다.
```cpp
// ❌ 위험: v가 비어있을 때 v.size() - 1은 음수가 아니라 매우 큰 양수(언더플로우)가 됨!
for (int i = 0; i <= v.size() - 1; ++i) { ... }

// ⭕ 권장:
for (size_t i = 0; i < v.size(); ++i) { ... }
// 또는
for (int i = 0; i < static_cast<int>(v.size()); ++i) { ... }
```

### ⚠️ `std::vector<bool>`의 특수화
`vector<bool>`은 메모리 절약을 위해 1바이트가 아닌 1비트씩 묶어 관리하는 특수 프록시(Proxy) 객체를 반환합니다.
따라서 `auto& b = v[0];` 같은 일반 참조 바인딩이 컴파일 에러를 일으킵니다. 비트 연산이 필요하다면 `std::bitset` 또는 `std::vector<char>` / `std::vector<uint8_t>` 사용을 고려하세요.

### 💡 대량 데이터 추가 시 `reserve()` 습관화
추가할 원소의 개수를 사전에 알고 있거나 어림할 수 있다면, 반드시 `reserve(N)`을 호출하여 불필요한 동적 재할당(메모리 복사)을 방지하세요.
