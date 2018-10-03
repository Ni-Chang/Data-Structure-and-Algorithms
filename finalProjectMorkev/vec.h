//
//  vec.h
//  markov
//
//  Created by xiaonizi on 2018/7/5.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#define vec_h

# ifndef __CVECTOR_H__
# define __CVECTOR_H__
# define MIN_LEN 1
# define CVEFAILED -1
# define CVESUCCESS 0
# define CVEPUSHBACK 1
# define CVEPOPBACK 2
# define CVEINSERT  3
# define CVERM    4
# define EXPANED_VAL 1
# define REDUSED_VAL 2

typedef void *citerator;
typedef struct _cvector *cvector;

# ifdef _cplusplus
# define EXTERN_ extern "C"
# else
# define EXTERN_ extern
# endif

EXTERN_ cvector  cvector_create  (const int size              );
EXTERN_ int    cvector_pushback (const cvector cv, void *memb        );
EXTERN_ int    cvector_val_at  (const cvector cv, int index, void *memb );

#endif

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef void *citerator;
typedef struct _cvector
{
    void *cv_pdata;
    int cv_len, cv_tot_len, cv_size;
} *cvector;

# define CWARNING_ITER(cv, iter, file, func, line) \
do {\
if ((cvector_begin(cv) > iter) || (cvector_end(cv) <= iter)) {\
fprintf(stderr, "var(" #iter ") warng out of range, "\
"at file:%s func:%s line:%d!!/n", file, func, line);\
return CVEFAILED;\
}\
} while (0)

# ifdef _cplusplus
# define EXTERN_ extern "C"
# else
# define EXTERN_ extern
# endif

EXTERN_ cvector  cvector_create  (const int size              );
EXTERN_ int    cvector_pushback (const cvector cv, void *memb        );
EXTERN_ int    cvector_val_at  (const cvector cv, int index, void *memb );

cvector cvector_create(const int size)
{
    cvector cv = (cvector)malloc(sizeof (struct _cvector));
    
    if (!cv) return NULL;
    
    cv->cv_pdata = malloc(MIN_LEN * size);
    
    if (!cv->cv_pdata)
    {
        free(cv);
        return NULL;
    }
    
    cv->cv_size = size;
    cv->cv_tot_len = MIN_LEN;
    cv->cv_len = 0;
    
    return cv;
}


int cvector_pushback(const cvector cv, void *memb)
{
    if (cv->cv_len >= cv->cv_tot_len)
    {
        void *pd_sav = cv->cv_pdata;
        cv->cv_tot_len <<= EXPANED_VAL;
        cv->cv_pdata = realloc(cv->cv_pdata, cv->cv_tot_len * cv->cv_size);
        
        if (!cv->cv_pdata)
        {
            cv->cv_pdata = pd_sav;
            cv->cv_tot_len >>= EXPANED_VAL;
            return CVEPUSHBACK;
        }
    }
    
    memcpy(cv->cv_pdata + cv->cv_len * cv->cv_size, memb, cv->cv_size);
    cv->cv_len++;
    
    return CVESUCCESS;
}

int cvector_val_at(const cvector cv, int index, void *memb)
{
    memcpy(memb, cv->cv_pdata + index * cv->cv_size, cv->cv_size);
    return 0;
}

