//
//  main.c
//  subway
//
//  Created by xiaonizi on 2018/6/17.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#define MAXNUM 512     //地铁最大站数
#define MAXLEN 16         //地铁站名的最大长度
#define INFINITY  32767

struct  station { //车站信息
    char  sname[MAXLEN];      //车站名
    int ischange;          //是否为换乘站，0-否，1-换乘
};

struct weight {
    int wei;         //两个站间的权重，即相差站数，缺省为1
    int lno;          //两个顶点所在的线号
};

struct station BGvertex[MAXNUM];          //地铁网络图顶点数组
struct weight BGweights[MAXNUM][MAXNUM];     //网络图权重数组，邻接矩阵
int Vnum = 0;     //实际地铁总站数

void init_graph(){
    int line_num, line_id, station_num, i, j, k=0, m;
    for(i=0; i<MAXNUM; i++){
        for(j=0; j<MAXNUM; j++){
            BGweights[i][j].wei=INFINITY;
        }
    }
    FILE *fp = fopen("bgstations.txt", "r");
    fscanf(fp, "%d", &line_num);
    k=0;
    for(j=0; j<line_num; j++){
        fscanf(fp, "%d %d", &line_id, &station_num);
        for(i=0; i<station_num; i++, k++){
            fscanf(fp, "%s %d", BGvertex[k].sname, &(BGvertex[k].ischange));
            if(i==0){//某条线第一站
                BGweights[k][k].wei=0;
                BGweights[k][k].lno=line_id;
            }
            else{//不是第一站不是最后一站，和前面一站接上
                BGweights[k][k].wei=0;
                BGweights[k][k-1].wei=1;
                BGweights[k-1][k].wei=1;
                BGweights[k][k].lno=line_id;
                BGweights[k-1][k].lno=line_id;
                BGweights[k][k-1].lno=line_id;
                
            }
            if(i==station_num-1 && strcmp(BGvertex[k].sname, BGvertex[k-i].sname)==0){
                BGweights[k][k-i].wei=0;
                BGweights[k][k-i].wei=0;
            }
            if(BGvertex[k].ischange){
                for(m=0; m<k; m++){
                    if(strcmp(BGvertex[m].sname, BGvertex[k].sname)==0){
                        BGweights[m][k].wei=0;
                        BGweights[k][m].wei=0;
                    }
                }
            }
        }
    }
    fclose(fp);
    Vnum=k;
}

void Dijkstra(char s[], char d[])
{
    int i, j, k, v, minweight, wfound[Vnum], Sweight[Vnum], end, Spath[Vnum], start;
    for(i=0; i<Vnum; i++){
        if(strcmp(BGvertex[i].sname, d)==0){
            end=i;
        }
        if(strcmp(BGvertex[i].sname, s)==0){
            start=i;
        }
    }
    for(i=0; i<Vnum; i++){
    	wfound[i]=0;
        Sweight[i] = BGweights[end][i].wei;
        Spath[i] = end;
    }
    
    for(i=0; i< Vnum-1; i++){
        minweight = INFINITY;
        for(j=0; j<Vnum; j++){
            if( !wfound[j] && ( Sweight[j] < minweight))  {
                v = j;
                minweight = Sweight[v];
            }
        }
        wfound[v] = 1;
        for(k =0; k < Vnum; k++){
            if( !wfound[k]  &&  (minweight + BGweights[v][k].wei < Sweight[k] )){
                Sweight[k] = minweight + BGweights[v][k].wei;
                Spath[k] = v; 
                BGweights[k][v].lno = BGweights[v][v].lno;
            }
        }
    }
    
    
    
    i=start;
	j=Spath[i]; 
	int count = 0, old=start, oldn=Spath[old], samecount=0, final_line;
	printf("%s", BGvertex[i].sname);
	while(strcmp(BGvertex[i].sname, BGvertex[j].sname)==0){
		i=Spath[i];
		j=Spath[i]; 
	}
    while(i!=end){
    	if(strcmp(BGvertex[i].sname, BGvertex[j].sname)==0 && strcmp(BGvertex[i].sname, BGvertex[end].sname)!=0){
    		printf("-%d(%d)-%s", BGweights[i][i].lno, count, BGvertex[i].sname);
    		old = i;
    		oldn=Spath[old];
    		count=0;
		}
        else if(strcmp(BGvertex[i].sname, BGvertex[end].sname)==0){
            printf("-%d(%d)-%s", BGweights[i][i].lno, count, BGvertex[i].sname);
            return;
        }
    	else{
    		count++;
		}
    	i=Spath[i];
    	j=Spath[i];
	}

		printf("-%d(%d)-%s", BGweights[i][i].lno, count, BGvertex[i].sname);

}

int main() {
    char s[MAXLEN], d[MAXLEN];
    scanf("%s %s", s, d);
    init_graph();
    Dijkstra(s, d);
    return 0;
}



