# <numeric>

> C++ 표준 라이브러리에서 수열과 수학적 데이터를 대상으로 **누적 합, 연속 수 채우기, 최대공약수/최소공배수, 부분합** 등의 수치 연산(Numeric Algorithms)을 제공하는 헤더입니다.

---

## 1. 개요 (Overview)

`<algorithm>`이 데이터의 **정렬, 탐색, 재배열**에 초점을 맞춘다면, `<numeric>`은 수치 데이터를 바탕으로 한 **계산 및 집계(Aggregation)** 에 특화되어 있습니다.

- **헤더 파일**: `#include <numeric>`
- **네임스페이스**: `std`
- **C++ 표준 발전**: C++17부터 `std::gcd`, `std::lcm` 및 병렬 처리를 지원하는 `std::reduce`, `std::inclusive_scan` 등이 추가되어 수학/알고리즘 문제 풀이에 더욱 강력해졌습니다.

### 주요 특징
| 특징 | 설명 |
| :--- | :--- |
| **수치 집계 특화** | 합계(`accumulate`), 연속 수 채우기(`iota`), 내적(`inner_product`) 등 수치 계산 최적화 |
| **자유로운 연산자 확장** | 단순 덧셈뿐만 아니라 곱셈, 람다식을 이용한 커스텀 집계 연산 지원 |
| **수학 유틸리티 내장 (C++17)** | 유클리드 호제법을 직접 구현할 필요 없이 `gcd`/`lcm` 기본 제공 |

---

## 2. 시간 복잡도 요약 (Time Complexity Cheat Sheet)

| 연산 (Operation) | 함수 (Function) | 시간 복잡도 (Time Complexity) | 비고 (Notes) |
| :--- | :--- | :---: | :--- |
| **누적 계산** | `accumulate()` | **$O(N)$** | 원소 개수만큼 순차 순회 |
| **연속 수 채우기** | `iota()` | **$O(N)$** | 범위 내 $1$씩 증가하며 값 대입 |
| **부분합 계산** | `partial_sum()` | **$O(N)$** | Prefix Sum 배열 생성 |
| **인접 원소 차분** | `adjacent_difference()` | **$O(N)$** | $A[i] - A[i-1]$ 차분 배열 생성 |
| **두 벡터 내적** | `inner_product()` | **$O(N)$** | $\sum (A[i] \times B[i])$ |
| **최대공약수 / 최소공배수** | `gcd()`, `lcm()` *(C++17)* | **$O(\log(\min(a, b)))$** | 유클리드 호제법 기반 |

---

## 3. 핵심 수치 함수 (Key Numeric Functions)

### (1) 누적 계산 (`accumulate`)
범위 내의 모든 원소를 차례대로 누적 계산합니다. 기본 연산은 덧셈이지만, 곱셈이나 사용자 정의 람다식을 넘길 수도 있습니다.

```cpp
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};

    // 1. 기본 덧셈 누적합 (15)
    // ⚠️ 세 번째 인자는 '초깃값'입니다.
    int sum = accumulate(v.begin(), v.end(), 0);

    // 2. 누적 곱 계산 (120)
    int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());

    // 3. 커스텀 람다식 활용 (예: 모든 짝수만 합산)
    int even_sum = accumulate(v.begin(), v.end(), 0, [](int acc, int cur) {
        return cur % 2 == 0 ? acc + cur : acc;
    }); // 2 + 4 = 6

    return 0;
}
```

---

### (2) 연속된 숫자 채우기 (`iota`)
초깃값부터 시작하여 $1$씩 증가하는 연속된 수열로 컨테이너를 채웁니다. 코딩 테스트에서 **인덱스 배열(`0 ~ N-1`)** 을 빠르게 생성할 때 매우 자주 사용됩니다.

```cpp
vector<int> v(5);

// 0부터 1씩 증가하며 채우기 -> {0, 1, 2, 3, 4}
iota(v.begin(), v.end(), 0);

// 특정 시작값 지정 -> {10, 11, 12, 13, 14}
iota(v.begin(), v.end(), 10);
```

---

### (3) 최대공약수 / 최소공배수 (`gcd`, `lcm`) *(C++17)*
직접 유클리드 호제법 재귀 함수를 짤 필요 없이 기본 제공됩니다.

```cpp
int a = 12, b = 18;

// 최대공약수 (Greatest Common Divisor): 6
int g = gcd(a, b);

// 최소공배수 (Least Common Multiple): 36
int l = lcm(a, b);
```

---

### (4) 부분합 (`partial_sum`) & 인접 차분 (`adjacent_difference`)
알고리즘 문제에서 **누적합(Prefix Sum)** 배열을 만들어 구간합 쿼리를 $O(1)$에 처리할 때 활용할 수 있습니다.

```cpp
vector<int> v = {1, 2, 3, 4, 5};
vector<int> prefix_sum(v.size());

// 누적 부분합 생성: {1, 3, 6, 10, 15}
partial_sum(v.begin(), v.end(), prefix_sum.begin());

// 인접 원소 간의 차분: {1, 2-1, 3-2, 4-3, 5-4} -> {1, 1, 1, 1, 1}
vector<int> diff(v.size());
adjacent_difference(v.begin(), v.end(), diff.begin());
```

---

## 4. 주의사항 및 모범 사례 (Pitfalls & Best Practices)

### ⚠️ `accumulate` 사용 시 반환 타입 결정과 정수 오버플로우
`std::accumulate`의 반환 타입은 컨테이너의 원소 타입이 아니라, **"넘겨준 초깃값의 타입"** 에 의해 결정됩니다!

```cpp
vector<int> v(100'000, 100'000); // 총합: 100억 (int 범위 약 21억 초과)

// ❌ 치명적 오류: 초깃값 0이 int형이므로 int 연산 수행 -> 오버플로우 발생(쓰레기값 반환)
long long s1 = accumulate(v.begin(), v.end(), 0);

// ⭕ 올바른 방법: 0LL (long long 리터럴)을 전달하여 long long 누적 연산 강제
long long s2 = accumulate(v.begin(), v.end(), 0LL);
```

### ⚠️ `accumulate`에 빈 컨테이너 전달 시
컨테이너가 비어있을 때(`v.empty() == true`), `accumulate`는 에러를 내지 않고 **세 번째 인자로 넘겨준 초깃값**을 그대로 반환합니다.

### 💡 인덱스 벡터 초기화는 `for`문 대신 `iota()` 습관화
좌표 압축이나 정렬용 인덱스 배열을 만들 때 수동 `for` 루프 대신 `iota(idx.begin(), idx.end(), 0)`를 쓰면 코드가 훨씬 깔끔해지고 실수를 줄일 수 있습니다.
