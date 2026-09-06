#include <stdio.h>

#include <libdragon.h>


int main(void){

    console_init();
    int ret = dfs_init(DFS_DEFAULT_LOCATION);
    assert(ret == DFS_ESUCCESS);

    char c;
    int fp = dfs_open("/stuff.txt");

    while (1){
        while (!dfs_eof(fp)){
            dfs_read(&c, 1, 1, fp);
            printf("%d\t%c\n", dfs_tell(fp), c);
        }
        break;
    }

    dfs_close(fp);
}