#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert(char *filein,char *fileout)
{
    FILE *p = fopen(filein,"rb");
    FILE *q = fopen(fileout,"wb+");
    unsigned char *byte = (unsigned char *)malloc(1);
    unsigned char *buffer = (unsigned char*)malloc(1024*1024*16);
    int cnt=0;
    int flag =0;
    while(!feof(p))
    {
        flag = 1-cnt%2*2;
        fread(byte,1,1,p);
        for(int i=0;i<8;i++)
        {
            if((byte[0]>>i)&0x01==0x01)
            {
                buffer[cnt*8+7-i+8*flag]=0x03;
            }else
            {
                buffer[cnt*8+7-i+8*flag]=0x02;
            }
        }
        cnt++;
    }
    fwrite(buffer,1,(cnt-1)*8,q);
    fclose(p);
    fclose(q);
    free(byte);
    free(buffer);
}

void main(int argc,char* argv[])
{
    char * filein = (char *)malloc(100);
    char * fileout = (char *)malloc(100);
    int start,end,cnt;
    sscanf(argv[1],"%d",&start);
    sscanf(argv[2],"%d",&end);
    cnt = end - start +1;
    for(int i=0;i<cnt;i++)
    {
        sprintf(filein,"%d.raw",i+start);
        sprintf(fileout,"%d.data",i+start);
        convert(filein,fileout);
    }

}
