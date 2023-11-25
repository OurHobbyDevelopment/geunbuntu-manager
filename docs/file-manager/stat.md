# <sys/stat.h>

```C
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int stat(const char *path, struct stat *buf);
```

파일의 크기, 파일의 권한, 파일의 생성일시, 파일의 최정 변경일 등 파일의 상태나 파일의 정보를 얻는 함수이다. **stat(2) 함수는 symbolic link인 파일을 path로 넘기면 그 원본 파일의 정보를 얻는다.** lstat(2) 함수는 symbolic link 파일 자신의 정보를 얻는다. 나머지 기능은 동일하다.

이 함수는 우리가 가장 많이 사용하는 명령어 중 하나인 `ls -al` 명령어로 알 수 있는 내용들을 대부분 있다. `stat(1)` 명령어도 이 `stat(2)`와 비슷한 내용임을 알 수 있다.

## (+) 사용자 명령어와 시스템 콜

여기서 짚고 넘겨야 할 부분은 stat(1),(2)의 부분이다. 1과 2는 무슨 차이점일까? 
- **사용자 수준 명령어 (`stat(1)`, `ls` 등):**
  - 사용자가 콘솔이나 터미널에서 직접 실행하는 명령들
  - 이들은 주로 파일 및 디렉터리의 메타데이터를 사용자 친화적인 형태로 제공함
  - 예를 들어, `ls -l` 명령은 현재 디렉터리의 파일 목록과 각 파일의 상세 정보를 나열한다.
- **시스템 콜(`stat(2)`, `lstat(2)` 등):**
  - 프로그래밍에서 직접 호출되는 함수들로, C 라이브러리에서 제공된다.
  - 이들은 파일 및 디렉터리의 메타데이터를 프로그램 내에서 직접 처리할 수 있도록 한다.
  - **`stat(2)`** 및 **`lstat(2)`** 는 파일 경로를 받아 해당 파일의 메타데이터를 얻는 시스템 콜이다. 참고로 `lstat`는 심볼릭 링크의 경우 링크 자체의 정보를 반환하며, `stat`는 심볼릭 링크가 가리키는 파일의 정보를 반환한다.

사용자 명령어는 주로 사용자 편의를 위해 디자인되었고, 시스템 콜은 프로그램이 더 직접적으로 시스템과 상호작용할 수 있도록 제공해주는 것을 말한다.

## 파라미터

```
path
    - 파일명 또는 파일에 대한 상대경로 or 절대경로
```

```C
buf
    - 파일의 상태 및 정보를 저장할 buf 구조체

struct stat {
    dev_t       st_dev;     /* ID of device containing file */
    ino_t       st_ino;     /* inode number */
    mode_t      st_mode;    /* 파일의 종류 및 접근권한 */
    nlink_t     st_nlink;   /* hardlink 된 횟수 */
    uid_t       st_uid;     /* 파일의 owner */
    gid_t       st_gid;     /* group IO of owner */
    dev_t       st_rdev;    /* device ID (if special file); */ 
    off_t       st_size;    /* 파일의 크기(bytes) */
    blksize_t   st_blksize; /* blocksize for file system I/O */
    blkcnt_t    st_blocks;  /* number of 512B blocks allocated */
    time_t      st_atime;   /* time of last access */
    time_t      st_mtime;   /* time of last modification */
    time_t      st_ctime;   /* time of last status change */
};

이 중에서 주요 내용을 보면, 
st_mode: 파일의 종류와 file에 대한 access 권한 정보(mode_t)
    파일의 종류 체크하는 POSIX macro이다.

S_ISREG(buf.st_mode)    : 일반 파일 여부
S_ISDIR(buf.st_mode)    : 디렉토리 여부
S_ISCHR(buf.st_mode)    : character device 여부
S_ISBLK(buf.st_mode)    : block device 여부
S_ISFIFO(buf.st_mode)   : FIFO(선입선출) 여부
S_ISLNK(buf.st_mode)    : symbolic link 여부
S_ISSOCK(buf.st_mode)   : socket 여부 (주로 AF_UNIX로 socket 생성된 경우) 
```

## Return

```C
0
    - 정상적으로 파일의 정보 조회

1 
    - 오류가 발생하였으며, 상세한 오류 내용은 errno 전역변수에 설정됨.

EACCES          : path를 구성하는 directory 중에서 search 권한(x)이 없어서 접근 불가
EFAULT          : path 변수 자체가 잘못된 구조임.
ELOOP           : 너무 많은 symbolic link로 directory가 loop에 빠짐
ENAMETOOLONG    : path가 너무 길거나 이름이 너무 김
ENOENT          : path가 빈 문자열이거나 path를 구성하는 directory 중에는 없는 directory가 있음.
ENOMEM          : 메모리가 부족함.
ENOTDIR         : path를 구성하는 directory 중에서 directory가 아닌 것이 있음.
EOVERFLOW       : 32bit os에서 컴파일시에 -D_FILE_OFFSET_BITS=64 옵션없이 컴파일하여 파일크기나 inode 번호가 64bit에 맞지 않은 경우
```

---

## Example

```C
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct stat sb;     // <sys/stat.h> 라이브러리에서 구조체 긁어옴

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        return 1;
    }

    if (stat(argv[1], &sb) == -1)
    {
        perror("stat");
        return 1;
    }

    printf("File type:                  ");

    switch (sb.st_mode & S_IFMT)
    {
        case S_IFBLK:   printf("block device\n");           break;
        case S_IFCHR:   printf("character device\n");       break;
        case S_IFDIR:   printf("directory\n");              break;
        case S_IFIFO:   printf("FIFO/pipe\n");              break;
        case S_IFLNK:   printf("symlink\n");                break;
        case S_IFREG:   printf("regular file\n");           break;
        case S_IFSOCK:  printf("socket\n");                 break;
        default:        printf("unknown?\n");               break;
    }

    printf("I-node number:              %ld\n",                 (long) sb.st_ino);
    printf("Mode:                       %lo (octal)\n",         (unsigned long) sb.st_mode);
    printf("Link count:                 %ld\n",                 (long) sb.st_nlink);
    printf("Ownership:                  UID=%ld   GID=%ld\n",   (long) sb.st_uid, (long) sb.st_gid);
    printf("Preferred I/O block size:   %ld bytes\n",           (long) sb.st_blksize);
    printf("File size:                  %lld bytes\n",          (long long) sb.st_size);
    printf("Blocks allocated:           %lld\n",                (long long) sb.st_blocks);
    printf("Last status change:         %s",                    ctime(&sb.st_ctime));
    printf("Last file access:           %s",                    ctime(&sb.st_atime));
    printf("Last file modification:     %s",                    ctime(&sb.st_mtime));

    return 0;
}
```

```
결과:
File type:                  regular file
I-node number:              26348461
Mode:                       100664 (octal)
Link count:                 1
Ownership:                  UID=1000   GID=1000
Preferred I/O block size:   4096 bytes
File size:                  1969 bytes
Blocks allocated:           8
Last status change:         Sat Nov 25 16:27:30 2023
Last file access:           Sat Nov 25 16:27:30 2023
Last file modification:     Sat Nov 25 16:27:30 2023
```

## 출처
- https://www.it-note.kr/173