#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>

int ismember(char* dir, char* name);

int main(int argc, char* argv[]){
    //가상 환경 : "dir" 디렉터리에 "test.txt" 파일이 있음
    mkdir("dir", 0755);
    chdir("dir");
    int fd;
    fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    close(fd);

    //현재 디렉터리로 되돌아 온 후 테스트
    chdir("..");
    if(ismember(argv[1], argv[2]) == -1){
        perror("ismember");
        exit(1);
    }
}

int ismember(char* dir, char* name){
    DIR* curdp = opendir(".");
    DIR* subdp = NULL; //하위 디렉터리의 디렉터리 포인터를 저장
    struct dirent* dent;
    
    //현재 디렉터리의 하위 디렉터리로 존재하는지 확인
    while((dent = readdir(curdp)) != NULL){
        if(strcmp(dir, dent->d_name) == 0){
            subdp = opendir("dir");
            break;
        }
    }
    //할당받은 디렉터리 주소가 없다면 종료
    if(subdp == NULL){
        printf("directory \"%s\" is not in cwd\n", dir);
        closedir(curdp);
        return -1;
    }
    //하위 디렉터리에 파일이 존재하는지 확인
    while((dent = readdir(subdp)) != NULL){
        if(strcmp(name, dent->d_name) == 0){
            printf("file \"%s\" is  in cwd/%s\n", name, dir);
            closedir(curdp);
            closedir(subdp);
            return 0;
        }
    }
    printf("file \"%s\" is not in cwd/%s\n", name, dir);
    closedir(curdp);
    closedir(subdp);
    return -1;
}