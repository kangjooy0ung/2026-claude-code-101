#include <iostream>

// 두 정수를 입력받아 곱셈 결과를 반환하는 함수입니다.
int multiply(int a, int b) {
    // a와 b를 곱한 값을 계산하여 반환합니다.
    return a * b;
}

int main() {
    int x = 3;
    int y = 4;

    // multiply 함수를 호출하여 곱셈 결과를 구합니다.
    int result = multiply(x, y);

    // 계산된 결과를 화면에 출력합니다.
    std::cout << x << " x " << y << " = " << result << std::endl;

    return 0;
}
