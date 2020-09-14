#ifndef HEAD_GNL
#define	HEAD_GNL

typedef struct			S_gnl
{
	int					ret;
    int                 fd;
	char				*buf;
    char                *bufl;
	struct S_gnl		*next;
}						T_gnl;

#endif