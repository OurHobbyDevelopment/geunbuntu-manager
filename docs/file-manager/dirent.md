# dirent.h

- `/usr/include/` 위치함
- **디렉터리 스트림** 을 사용하여 파일을 열고 닫는다는 게 특징

## 디렉터리 스트림(Directory stream)이란?

스트림은 입력과 출력이 이루어지는 가상의 연결 통로를 말하며, 그 종류는 입출력 데이터를 무엇으로 쓰이냐에 따라 갈린다. 그 중 디렉터리 스트림이랑 입출력 데이터를 **디렉터리(directory)** 단위로 처리하는 것을 의미한다.

`dirent.h` 파일 내에서는 **디렉터리 조작의 기반 수단**으로 쓰이는 **DIR 구조체** 를 의미하며, 이러한 구조체는 정규 파일 조작을 위한 파일 스트림(`FILE *`)과 상당히 비슷한 방식으로도 쓰인다.

### DIR

위에서 설명하였듯 DIR 구조체를 통해 디렉터리 파일 스트림을 표현하는 데, 이 DIR은 __dirstream의 파생이며, 그 원형은 아래와 같다.

```C
// glibc/sysdeps/unix/dirstream.h

#include <sys/types.h>

struct __dirstream
{
    int fd;                         /*  File descriptor.  */

    __libc_lock_define (, lock)     /*  Mutex lock for this structure.      */

    size_t allocation;              /*  블록에 할당된 공간    */
    size_t size;                    /*  블록의 총 유효 데이터  */
    size_t offset;                  /*  블록에 대한 현재 오프셋  */

    off_t filepos;                  /*  읽을 다음 항목의 위치  */

    /*  Directory block  */
    char data[0] __attribute__ ((aligned (__alignof__ (void*))));
};
```

참고하면 좋을듯.

### (++) 왜 헤더파일만 공개하고 소스코드는 꽁꽁 싸메는가?
출처: https://stackoverflow.com/questions/16893895/what-is-dirstream-where-can-we-find-the-definition

찾다보니 나온 내용인데, 나도 소스코드가 궁금해서 찾아보려 했건만 생각보다 꽁꽁 싸매져있어 코드 내용을 확인하기 어려웠다.

그 이유가 여기 나와있었는데, 소스코드가 공개되어 있으면 사용자 맘대로 풀어져버려서 어지러워지기 때문이라고.

## dirent

dirent 구조체는 다음과 같이 선언된다.

```C
struct dirent
{
    long    d_ino;              // i_node
    off_t   d_off;              // dirent의 offset
    unsigned short d_reclen;    // d_name의 길이
    char d_name [NAME_MAX+1];   // 파일 이름(없다면 NULL로 종료)
}
```

dirent 구조체는 파일, 또는 디렉터리가 가지고 있는 정보 구조체이다. 참고로 DIR과 dirent의 역할을 확연히 다르니 참고하시길!

## Functions

### opendir

원형

```C
#include <sys/types.h>
#include <dirent.h>

DIR* opendir(const char *dirname);
```

opendir() 함수는 매개변수 dirname에 해당하는 디렉터리 스트림을 열고, 그 디렉터리 스트림에 대한 포인터를 반환한다. 

### readdir



## 출처
https://velog.io/@eeunnii/%EC%8A%A4%ED%8A%B8%EB%A6%BC
https://sosal.kr/114
https://sourceware.org/git/?p=glibc.git;a=blob;f=sysdeps/unix/dirstream.h;h=8303f07fab6f6efaa39e51411ef924e712d995e0;hb=fa39685d5c7df2502213418bead44e9543a9b9ec