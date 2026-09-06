#include <stdio.h>

#include <libdragon.h>


int main(void){

    console_init();
    int ret = dfs_init(DFS_DEFAULT_LOCATION);
    assert(ret == DFS_ESUCCESS);

    char sbuf[1024];
    int fp = dfs_open("/stuff.txt");

    while (1){
        while (!dfs_eof(fp)){
            dfs_read(sbuf, 1, -1, fp);
            printf("%i\t%s\n", dfs_tell(fp), sbuf);
        }
        break;
    }

    dfs_close(fp);
}