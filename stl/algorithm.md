# <algorithm>

> C++ 표준 템플릿 라이브러리(STL)에서 다양한 컨테이너의 원소들을 대상으로 **검색, 정렬, 변형, 개수 세기** 등의 범용적인 연산을 수행하는 함수 모음입니다.

---

## 1. 개요 (Overview)

`<algorithm>`의 함수들은 대부분 특정 컨테이너에 종속되지 않고 **반복자(Iterator)** 를 통해 동작합니다. 덕분에 `vector`, `deque`, `string`, 일반 C 배열 등 반복자를 지원하는 모든 연속/순차 컨테이너에 동일한 함수를 적용할 수 있습니다.

- **헤더 파일**: `#include <algorithm>` (수치 연산은 `numeric.md` 참고)
- **네임스페이스**: `std`
- **핵심 원칙**: 대부분의 알고리즘은 시작은 포함하고 끝은 포함하지 않는 **반개구간 `[first, last)`** 범위를 다룹니다.

### 주요 특징
| 특징 | 설명 |
| :--- | :--- |
| **컨테이너 독립성** | 컨테이너 내부 구조를 알 필요 없이 이터레이터 쌍 `[begin, end)`만으로 동작 |
| **함수 객체 / 람다 지원** | 조건자(Predicate)나 비교 함수(Comparator)를 커스텀하여 동작 커스터마이징 가능 |
| **고도로 최적화된 성능** | 컴파일러 최적화 및 인라인 확장, Introsort(퀵+힙+삽입 정렬 결합) 등 사용 |

---

## 2. 시간 복잡도 요약 (Time Complexity Cheat Sheet)

| 분류 (Category) | 함수 (Function) | 시간 복잡도 (Time Complexity) | 전제 조건 (Precondition) |
| :--- | :--- | :---: | :--- |
| **정렬** | `sort()`, `stable_sort()` | **$O(N \log N)$** | Random Access Iterator (`vector`, `deque`, 배열) |
| **선형 탐색** | `find()`, `find_if()`, `count()` | **$O(N)$** | 없음 |
| **이진 탐색** | `lower_bound()`, `upper_bound()`, `binary_search()` | **$O(\log N)$** | **데이터가 정렬되어 있어야 함** |
| **최대 / 최소** | `min_element()`, `max_element()` | **$O(N)$** | 없음 |
| **중복 정리** | `unique()` | **$O(N)$** | **데이터가 정렬되어 있어야 유효** |
| **순열 생성** | `next_permutation()`, `prev_permutation()` | **$O(N)$** | 순차 호출 시 전체 $O(N! \cdot N)$ |
| **원소 뒤집기** | `reverse()` | **$O(N)$** | Bidirectional Iterator 이상 |

---

## 3. 정렬 및 순서 조작 (Sorting & Permutation)

### (1) 정렬 (sort)
기본적으로 **오름차순**으로 정렬되며, 사용자 정의 비교자(Comparator)나 람다식을 통해 정렬 기준을 바꿀 수 있습니다.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

int main() {
    vector<int> v = {4, 2, 5, 1, 3};

    // 1. 기본 오름차순: O(N log N)
    sort(v.begin(), v.end()); // {1, 2, 3, 4, 5}

    // 2. 내림차순 정렬 (greater<T>() 활용)
    sort(v.begin(), v.end(), greater<int>()); // {5, 4, 3, 2, 1}

    // 3. 구조체 커스텀 정렬 (람다식 활용)
    vector<Point> pts = {{1, 2}, {3, 1}, {1, 1}};
    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x; // x 기준 오름차순
        return a.y < b.y;                 // x 같으면 y 기준 오름차순
    });

    return 0;
}
```

> 💡 **`sort` vs `stable_sort`**
> - `sort`: 빠르지만 동일한 값의 원래 순서가 보장되지 않습니다 (불안정 정렬).
> - `stable_sort`: 동일한 값의 상대적 순서를 유지해야 할 때 사용합니다 (안정 정렬, $O(N \log N)$ 또는 메모리 부족 시 $O(N \log^2 N)$).

---

### (2) 순열 (next_permutation / prev_permutation)

#### 1. 정확한 동작 원리 (단일 호출 기준)
`next_permutation`은 함수 한 번 호출로 모든 경우의 수를 한 번에 만들어주는 것이 아닙니다.
- **단 1회 호출 시**: 현재 컨테이너에 배치된 원소들을 **"사전순(Lexicographical order)으로 바로 다음으로 큰 순서"** 로 **제자리(In-place)** 에서 직접 재배열합니다.
- **반환값 (`bool`)**:
  - 현재보다 더 큰 다음 순열이 존재하여 변경에 성공한 경우 $\to$ **`true` 반환**
  - 이미 가장 큰 순열(완전 내림차순, 예: `{3, 2, 1}`)이어서 다음 순열이 없는 경우 $\to$ 가장 작은 순열(오름차순 `{1, 2, 3}`)로 되돌려놓고 **`false` 반환**

---

#### 2. 모든 경우의 수($N!$)를 탐색하는 방법
한 번 호출할 때마다 사전순 다음 단계로 1단계씩 전진하므로, **반드시 `do-while` 반복문**과 결합해야 전체 $N!$개의 배치를 누락 없이 하나씩 탐색할 수 있습니다.

> **🔥 IMPORTANT: 왜 반드시 사전에 `sort()`를 해야 하는가?**
>
> - `next_permutation`은 항상 "현재 상태보다 사전순으로 뒤에 오는 것"만 차례대로 만들어냅니다.
> - 만약 `{2, 1, 3}`처럼 정렬되지 않은 상태에서 시작하면, 이미 사전순으로 지나간 `{1, 2, 3}`, `{1, 3, 2}`는 **영영 탐색하지 못하고 건너뛰게 됩니다.**
> - 따라서 전체 모든 순열을 탐색하려면 **가장 첫 번째 순열인 '완전 오름차순' 상태**에서 시작해야 합니다.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v = {3, 1, 2};

    // 1단계: 반드시 오름차순으로 정렬하여 "가장 첫 번째 순열"로 만듦 -> {1, 2, 3}
    sort(v.begin(), v.end());

    // 2단계: do-while 문으로 매 반복마다 다음 순열로 1단계씩 변환하며 순회
    // * while 대신 do-while을 쓰는 이유: 첫 번째 형태 {1, 2, 3}도 처리하기 위함
    do {
        for (int x : v) cout << x << " ";
        cout << "\n";
    } while (next_permutation(v.begin(), v.end()));

    /*
      [출력 순서]
      1) 1 2 3  (최초 상태)
      2) 1 3 2  (다음 큰 순열)
      3) 2 1 3
      4) 2 3 1
      5) 3 1 2
      6) 3 2 1  (마지막 순열 -> 다음 호출 시 false 반환 후 {1, 2, 3} 복구, 루프 종료)
    */

    return 0;
}
```

---

#### 3. 실전 테크닉: 조합(Combination, $_n\mathrm{C}_r$) 구하기
`next_permutation`은 원소에 중복이 있어도 중복 순열을 자동으로 건너뛰고 사전순으로 동작합니다. 이를 이용해 **$N$개 중 $R$개를 뽑는 조합**을 쉽게 구현할 수 있습니다.

```cpp
// 5개 중 3개를 뽑는 조합 (5C3 = 10가지)
vector<int> items = {10, 20, 30, 40, 50};
// 0을 2개, 1을 3개 배치 (1인 위치의 원소를 선택)
vector<int> mask = {0, 0, 1, 1, 1}; // ⚠️ 반드시 오름차순 정렬 상태로 시작!

do {
    for (int i = 0; i < 5; ++i) {
        if (mask[i] == 1) {
            cout << items[i] << " ";
        }
    }
    cout << "\n";
} while (next_permutation(mask.begin(), mask.end()));

/*
  [출력 결과 - 총 10가지 조합]
  30 40 50  (mask: 0 0 1 1 1)
  20 40 50  (mask: 0 1 0 1 1)
  20 30 50  (mask: 0 1 1 0 1)
  20 30 40  (mask: 0 1 1 1 0)
  10 40 50  (mask: 1 0 0 1 1)
  10 30 50  (mask: 1 0 1 0 1)
  10 30 40  (mask: 1 0 1 1 0)
  10 20 50  (mask: 1 1 0 0 1)
  10 20 40  (mask: 1 1 0 1 0)
  10 20 30  (mask: 1 1 1 0 0)
*/
```

---

#### 4. `next_permutation` vs 백트래킹(DFS) — 가지치기(Pruning)의 차이

> **📝 NOTE: 조기 종료(`break`) vs 가지치기(`pruning`)**
>
> - **조기 종료 (`break`)**: 원하는 정답을 찾아 전체 탐색을 종료 (둘 다 가능)
> - **가지치기 (Pruning)**: 가망 없는 하위 경우의 수 수십만 개를 **생성조차 하지 않고 통째로 스킵** (백트래킹만 가능)

- **`next_permutation`의 한계**:
  이미 완성된 $N$자리 수열을 하나씩 받아오므로, 루프 내에서 `continue`를 하더라도 **해당 접두사로 시작하는 수만~수십만 개의 수열을 CPU가 일일이 다 생성하면서 `continue`를 수십만 번 반복**합니다.
- **선택 기준**:
  - **`next_permutation`**: $N \le 10$이고 조건 분기 없이 **모든 경우를 전부 확인**해야 할 때 ($O(1)$ 추가 메모리, 구현 간단)
  - **백트래킹(재귀/스택)**: 탐색 도중 조건에 맞지 않는 **하위 분기를 잘라내야 할 때** (연산량 대폭 절감, 필수 최적화)

---

## 4. 탐색 (Searching)

### (1) 선형 탐색 (`find`, `count`)

```cpp
vector<int> v = {10, 20, 30, 20, 50};

// 값 탐색: 원소를 가리키는 반복자(vector<int>::iterator) 반환, 없으면 v.end() 반환
vector<int>::iterator it = find(v.begin(), v.end(), 30);
// auto it = find(v.begin(), v.end(), 30); // 동일
if (it != v.end()) {
    cout << "값: " << *it << "\n";     // 역참조(*)로 실제 값 접근 -> 30
    int idx = it - v.begin();           // 인덱스 계산 -> 2
}

// 조건부 탐색 (find_if)
auto it2 = find_if(v.begin(), v.end(), [](int n) { return n > 25; });

// 특정 값의 개수 세기
int cnt = count(v.begin(), v.end(), 20); // 2
```

---

### (2) 이진 탐색 (`lower_bound`, `upper_bound`, `binary_search`)

> **🚨 WARNING: 이진 탐색 계열 함수들은 반드시 정렬된 범위에 대해서만 사용해야 $O(\log N)$이 보장됩니다.**  
>
> 정렬되지 않은 상태에서 호출 시 잘못된 결과가 나옵니다.

#### 반환값 명세
| 함수 | 반환 타입 | 반환값의 의미 | 찾는 조건이 없을 때 |
| :--- | :--- | :--- | :--- |
| `binary_search()` | `bool` | 원소의 존재 여부 (`true` / `false`) | `false` |
| `lower_bound()` | `vector<T>::iterator` | `key` **이상($\ge$)** 인 첫 번째 원소의 **반복자** | `v.end()` 반환 |
| `upper_bound()` | `vector<T>::iterator` | `key` **초과($>$)** 인 첫 번째 원소의 **반복자** | `v.end()` 반환 |

```cpp
//                 인덱스: 0  1  2  3  4  5  6
vector<int> v = {1, 3, 5, 5, 5, 7, 9};

// 1. binary_search: 단순 존재 여부 확인 (bool)
bool found = binary_search(v.begin(), v.end(), 5); // true

// 2. lower_bound: 5 이상(>=)인 첫 번째 위치
// * 반환 타입: vector<int>::iterator (실무/코테에서는 편의상 auto 사용)
vector<int>::iterator lb = lower_bound(v.begin(), v.end(), 5);
// auto lb = lower_bound(v.begin(), v.end(), 5); // 동일한 의미

if (lb != v.end()) {
    cout << "값: " << *lb << "\n";         // 역참조(*)로 실제 값 접근 -> 5
    cout << "인덱스: " << lb - v.begin() << "\n"; // 시작 위치를 빼서 인덱스 계산 -> 2
}

// 3. upper_bound: 5 초과(>)인 첫 번째 위치
vector<int>::iterator ub = upper_bound(v.begin(), v.end(), 5);
// auto ub = upper_bound(v.begin(), v.end(), 5); // 동일한 의미

if (ub != v.end()) {
    cout << "값: " << *ub << "\n";         // 7
    cout << "인덱스: " << ub - v.begin() << "\n"; // 5
}

// 💡 팁: 정렬된 배열에서 특정 원소의 개수를 O(log N)으로 구하기
// (초과 위치 반복자) - (이상 위치 반복자) = 원소 개수
int count_5 = ub - lb; // 5 - 2 = 3개!
```


---

## 5. 원소 변형 및 조작 (Modifying & Utility)

### (1) 중복 원소 제거 (unique + erase 패턴)

> **🔥 IMPORTANT: 왜 반드시 사전에 `sort()`를 해야 하는가?**
>
> - `std::unique()`는 전체 배열을 뒤져서 같은 값을 찾아내는 것이 아니라, **오직 "서로 바로 맞붙어 있는(인접한) 중복 원소"** 만 검사합니다.
> - 만약 정렬하지 않고 `{1, 2, 1, 2}` 상태에서 `unique()`를 호출하면, **동일한 숫자들이 서로 떨어져 있어서 인접하지 않으므로 아무것도 걸러내지 못합니다.** (`{1, 2, 1, 2}` 그대로 유지)
> - 따라서 같은 값들을 서로 이웃하게 모아주기 위해 **반드시 사전에 `sort()`가 선행**되어야 합니다.

#### `unique()`의 동작 방식과 `erase()`가 필요한 이유
- **컨테이너 크기는 그대로**: `unique()`는 일반 알고리즘 함수이므로 `vector`의 물리적 메모리 크기(`size()`)를 줄일 권한이 없습니다.
- **동작**: 유효한 고유값들만 배열 앞부분으로 덮어써서 채우고, **"유효한 데이터의 새로운 끝 지점"을 가리키는 반복자(`vector<int>::iterator`)** 를 반환합니다.
- **해결 (Erase-Unique 관용구)**: 따라서 반환된 새 끝 지점부터 기존 끝 지점(`v.end()`)까지 남겨진 쓰레기 데이터들을 컨테이너의 멤버 함수 `erase()`로 잘라내야 비로소 중복 제거가 완성됩니다.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // ❌ 정렬하지 않은 경우: 인접한 중복만 없애므로 실패
    vector<int> bad = {2, 1, 2, 1};
    bad.erase(unique(bad.begin(), bad.end()), bad.end());
    // 결과: {2, 1, 2, 1} (중복이 전혀 제거되지 않음!)

    // ⭕ 올바른 방법 (원리 이해용 3단계 풀이)
    vector<int> v = {3, 1, 2, 3, 2, 1};

    // 1단계: 정렬하여 동일한 원소들을 서로 인접하게 모음
    sort(v.begin(), v.end()); 
    // 정렬 후: {1, 1, 2, 2, 3, 3}

    // 2단계: unique 호출 -> {1, 2, 3, ?, ?, ?}로 앞쪽에 유효값 배치
    // * new_end는 3의 다음 위치(인덱스 3)를 가리키는 반복자를 반환함
    auto new_end = unique(v.begin(), v.end());

    // 3단계: 뒷부분 남은 쓰레기 원소들을 완전히 삭제
    v.erase(new_end, v.end()); 
    // 최종 결과: {1, 2, 3} (size: 3)


    // 💡 실전 압축 형태 (코딩 테스트 & 실무에서 가장 많이 쓰는 2줄)
    // unique()의 반환값을 erase()의 시작 인자로 직접 넘겨 2~3단계를 한 줄로 결합!
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    return 0;
}
```

> 💡 **대안: `std::set`을 활용한 자동 중복 제거**  
> 중복을 허용하지 않고 자동 정렬되는 `std::set`을 경유할 수도 있습니다:  
> `set<int> s(v.begin(), v.end()); v.assign(s.begin(), s.end());`  
> 코드는 매우 단순하지만, `set`은 균형 이진 트리 노드를 힙에 동적 할당하므로 `vector + sort + unique`보다 **속도가 2~3배 느리고 메모리를 더 많이 소모**합니다. 대량 데이터 처리나 코딩 테스트에서는 `sort + unique + erase` 조합이 정석입니다.


---

### (2) 최대 / 최소값 (`min_element`, `max_element`, `clamp`)

```cpp
vector<int> v = {4, 1, 9, 2};

// 반복자를 반환하므로 역참조(*)하여 값 획득
int min_val = *min_element(v.begin(), v.end()); // 1
int max_val = *max_element(v.begin(), v.end()); // 9

// 인덱스 구하기
int max_idx = max_element(v.begin(), v.end()) - v.begin(); // 2

// clamp(val, low, high) (C++17): 범위를 벗어나지 않도록 값 제한
int clamped = clamp(15, 0, 10); // 10
```

---

### (3) 값 일괄 변경 및 복사 (`fill`, `copy`)

```cpp
vector<int> v(5);

// 1. 특정 값으로 범위 일괄 채우기: {7, 7, 7, 7, 7}
fill(v.begin(), v.end(), 7);

// 2. 시작 위치부터 N개만 채우기: {10, 10, 10, 7, 7}
fill_n(v.begin(), 3, 10);

// 3. 다른 컨테이너로 원소 복사
vector<int> target(5);
copy(v.begin(), v.end(), target.begin());
```

> **📝 NOTE: 수치 연산 함수 (`accumulate`, `iota`, `gcd` 등)**  
>
> 합계 계산이나 수열 생성 같은 수치 특화 알고리즘은 `<numeric>` 헤더에 정의되어 있습니다. 상세 내용은 `numeric.md` 문서를 참고하세요.

---

## 6. 주의사항 및 모범 사례 (Pitfalls & Best Practices)

### ⚠️ 커스텀 비교자 작성 시 Strict Weak Ordering 준수
`sort` 등의 비교 함수를 만들 때 **반드시 `<` (미만)** 연산자 의미를 유지해야 합니다. **`<=` (이하)** 를 사용하면 동등한 두 원소 비교 시 `(a <= b) && (b <= a)`가 둘 다 `true`가 되어 무한 루프나 세그멘테이션 폴트(Segmentation Fault)를 일으킵니다.

```cpp
// ❌ 잘못된 비교자: 값이 같을 때 true를 반환하면 런타임 크래시 발생 가능!
bool cmp(int a, int b) {
    return a <= b;
}

// ⭕ 올바른 비교자: 엄격한 약순서(<) 준수
bool cmp(int a, int b) {
    return a < b;
}
```

### ⚠️ 반개구간 `[first, last)` 특성 인지
`v.end()`는 마지막 원소가 아닌 **"마지막 원소의 다음 위치"** 를 가리킵니다. 따라서 탐색 실패 시 `it == v.end()` 조건을 반드시 확인해야 하며, 역참조(`*v.end()`)는 정의되지 않은 동작(UB)입니다.


### 💡 인덱스 변환은 `iterator - v.begin()`
`find`, `max_element`, `lower_bound` 등은 모두 반복자(Iterator)를 반환합니다. 인덱스 정수가 필요하다면 단순히 시작 반복자를 빼주면 $O(1)$로 구할 수 있습니다.
