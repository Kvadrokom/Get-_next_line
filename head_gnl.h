#ifndef HEAD_GNL
#define	HEAD_GNL

typedef struct			S_gnl
{
	int					fd;
	char*				rem;
	struct S_gnl*		next;
}						T_gnl;

#endif