# [미완]printf fge
- 글쓴이 : 박용준(Yongjun Park; yoopark(Github), yopark(42Seoul))
- 시작일 : 2021-01-17(일)

## 1. 프로젝트 소개
stdio.h에 포함되어 있는 `printf` 함수 중 부동 소수점 연산과 관련된 `%f, %g, %e` 기능만을 재구현하는 것이 목표입니다. 

42서울 본 과정 서브젝트 중 하나인 **ft_printf**에서 발상을 얻어 시작되었으나, (1)float 자료형을 사용하지 않으며 (2)비트 연산만을 사용하여 부동 소수점 반올림을 구현한다는 점에서 차별점을 두고 있습니다. 

**C언어**를 사용합니다. 

## 2. 사용법
`int printf_fge(const char *format, ... );`

- *2021/01/20(수)* 발생 가능한 모든 에러 상황을 다 잡으려 하였으나, 특히 denormalize 영역을 처리하는게 쉽지 않음을 깨달았습니다. 성능보다는 에러를 최소화하는 것을, 에러를 최소화하는 것보다는 일단 일반적 입력에 대하여 잘 기능하는 프로그램을 만드는 것을 목표로 수정하였습니다. 현재 bigint_operation_utils.c 까지 끝낸 뒤 ~~fb2bigint.c~~ struct2bigint.c 진행 중입니다.

## 3. 필요한 지식
이 프로젝트를 수행할 때 필요한 지식은 다음과 같습니다. 
- 부동 소수점(floating point)의 부호 비트, 지수 필드, 비율 필드
- 부동 소수점에서의 반올림(rounding) 방식
- 비트 연산(필요한 이유는 아래 참조)
- C에서 가변 인자(variable argument) 관련 함수 : va_start, va_arg, va_end
- printf의 width, flag, precision 작동 규칙

이 프로젝트는 *김형신 역, 컴퓨터 시스템 : 제3판, 2016(원저 : Randal E. Bryant, David R. O'Hallaron, Computer Systems - A Programmer's Perspective : 3rd Ed., 2015)* 136쪽에 명시된 **비트수준 부동소수점 코딩 규칙**을 따릅니다. 

> 다음 문제들에서 부동소수점 숫자의 비트수준 표시에 대해 직접 연산하는 부동소수점 함수를 구현하는 코드를 작성하게 된다. 여러분의 코드는 근사가 필요할 때는 짝수근사법을 사용하는 것을 포함해서 IEEE 부동소수점 연산의 관습을 정확히 따라야 한다. 

> 이를 위해 `float_bits`와 `unsinged`의 동일한 자료형을 정의한다. 
> ```
> /* Access bit-level representation floating-point number */
> typedef unsigned float_bits;
> ```

> 여러분의 코드에 `float` 자료형을 사용하는 대신, `float_bits`를 사용해야 한다. `int`와 `unsigned`, 비 부호형 상수, 정수 상수들, 연산들은 사용해도 좋다. Union, ~~struct, 배열~~은 사용해서는 안 된다. 가장 중요한 점은 부동소수점 자료형, 연산, 상수를 사용해서는 안된다는 것이다. 대신, 여러분의 코드는 특정 부동소수점 연산을 구현하는 비트연산을 수행해야 한다. 

## 4. 참고한 내용 출처
