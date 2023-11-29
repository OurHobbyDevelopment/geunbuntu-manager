#include <stdio.h>
#include <stdlib.h>

// Direct 관련 시스템 콜 헤더 모음
#include <dirent.h>

// Unix에서 쓰이는 표준 심볼들과 상수, 함수들 포함
#include <unistd.h>

int main(int argc, char* argv[])
{
    // cwd(current working directory)에 1024 byte 동적 할당
    char* cwd = (char *)malloc(sizeof(char) * 1024);

    // DIR과 dirent 구조체 포인터를 만들고 우선 NULL 대입
    DIR* dir = NULL;
    struct dirent* entry = NULL;

    // 추가 인자 없이 실행된 경우
    if(argc==1)
    {
        
        // getcwd() 함수는 현재 작업 디렉터리의 경로명을 문자열로 얻음
        // 이 값을 cwd 버퍼에 저장
        getcwd(cwd, 1024);

        // opendir() 함수는 디렉터리 스트림을 열어서 DIR* 포인터를 반환함
        // 이 값을 dir에 저장해서 사용
        if((dir = opendir(cwd)) == NULL)
        {
            printf("current directory open error\n");
            exit(1);
        }
    }
    else
    {
        // main 함수에 추가 인자가 전달된 경우 argv[1] 문자열로 디렉터리 스트림을 열어 디렉터리 포인터 변수에 담아줌
        if((dir=opendir(argv[1]))==NULL)
        {
            printf("directory open error\n");
            exit(1);
        }
    }

    // readdir() 함수는 디렉터리 포인터를 통해서 디렉터리 정보를 하니씩 차례대로 읽음
    // 디렉터리 스트림의 끝에 도달하거나 에러가 발생하면 NULL을 리턴
    // 정상적으로 읽은 경우 struct dirent 구조체 포인터를 반환하는 데 이 값을 entry에 저장하고
    // 파일명이 저장된 구조체 멤버인 char 배열 d_name을 문자열로 출력
    while((entry = readdir(dir))!=NULL)
    {
        printf("%s\n", entry->d_name);
    }
    printf("\n");

    // 동적 할당 해제 및 디렉터리 스트림 닫기
    free(cwd);

    closedir(dir);

    return 0;
}