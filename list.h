/**********************************************************************/
/*   Following data structure used to construct lists of things.      */
/* $Header: Last edited: 18-Jun-2000 1.5 $ 			      */
/**********************************************************************/
# if !defined(list_h)
# define        list_h

# if __cplusplus
extern "C" {
# endif

/**********************************************************************/
/*   Define following variable to track down memory leak problems.    */
/**********************************************************************/
/*#define MEM_LEAK      */

/**********************************************************************/
/*   Following  macro  used  to  allow  compilation  with ANSI C and  */
/*   non-ANSI C compilers automatically.                              */
/**********************************************************************/
# if !defined(PROTO)
# 	if	defined(__STDC__) || HAVE_PROTOTYPES
#               define  PROTO(x)        x
#       else
#               define  PROTO(x)        ()
#       endif
# endif

# if !defined(EXPORT_FUNCTION)
#	define	EXPORT_FUNCTION
# endif

# define        HEAD_MAGIC      (('h' << 24) | ('m' << 16) | ('a' << 8) | 'g')
# define        LIST_MAGIC      (('l' << 24) | ('m' << 16) | ('a' << 8) | 'g')
# define        HEAD_FREED      (('h' << 24) | ('f' << 16) | ('r' << 8) | 'e')
# define        LIST_FREED      (('l' << 24) | ('f' << 16) | ('r' << 8) | 'e')

	/***********************************************/
	/*   Following  structure  describes the head  */
	/*   of a linked list.                         */
	/***********************************************/
typedef struct Head_t {
	int             l_magic;
	struct  List_t  *l_head;        /* Pointer to first item in list. */
	struct  List_t  *l_tail;        /* Last item in list.             */
	int             l_len;          /* Length of list (for consistency)*/
	int             l_refcnt;       /* Number of pointers to list.  */
	} Head_t, *Head_p;
	
	/***********************************************/
	/*   Following  structure  describes  an atom  */
	/*   in a linked list.                         */
	/***********************************************/
typedef struct List_t {
	int             l_magic;
	struct List_t   *l_next;
	struct List_t   *l_prev;
	char            *l_data;
# if defined(MEM_LEAK)
	char    buf[64];
# endif
	} List_t, *List_p;

struct list_stats {
	unsigned long   lists_alloced;
	unsigned long   atoms_alloced;
	unsigned long   ll_newlist;
	unsigned long   ll_newatom;
	unsigned long   ll_freelist;
	unsigned long   ll_freeatom;
	unsigned long   ll_push;
	unsigned long   ll_pop;
	unsigned long   ll_append;
	unsigned long   ll_remove;
	unsigned long   ll_first;
	unsigned long   ll_last;
	unsigned long   ll_next;
	unsigned long   ll_prev;
	unsigned long   ll_elem;
	unsigned long   ll_incref;
	};
extern struct list_stats __list_stats;

DLL_EXPORT Head_p  EXPORT_FUNCTION ll_newlist PROTO((void));
# if defined(MEM_LEAK)
# define        ll_newatom(a)   ll__newatom(a, __FILE__, __LINE__)
DLL_EXPORT List_p  EXPORT_FUNCTION ll__newatom PROTO((char *, char *, int));
# else
DLL_EXPORT List_p  EXPORT_FUNCTION ll_newatom PROTO((char *));
# endif
DLL_EXPORT void    EXPORT_FUNCTION ll_assertatom PROTO((Head_p, List_p));
DLL_EXPORT void    EXPORT_FUNCTION ll_assertlist PROTO((Head_p));
DLL_EXPORT void    EXPORT_FUNCTION ll_freelist PROTO((Head_p));
DLL_EXPORT void    EXPORT_FUNCTION ll_incref PROTO((Head_p));
DLL_EXPORT void    EXPORT_FUNCTION ll_freeatom PROTO((List_p));
DLL_EXPORT void    EXPORT_FUNCTION ll_push PROTO((Head_p, List_p));
void *ll_pop_item(Head_p hp);
DLL_EXPORT List_p  EXPORT_FUNCTION ll_pop PROTO((Head_p));
DLL_EXPORT void    EXPORT_FUNCTION ll_clear PROTO((Head_p));
DLL_EXPORT void    EXPORT_FUNCTION ll_append PROTO((Head_p, List_p));
DLL_EXPORT void    EXPORT_FUNCTION ll_append_list PROTO((Head_p, Head_p));
DLL_EXPORT List_p  EXPORT_FUNCTION ll_remove PROTO((Head_p, List_p));
DLL_EXPORT List_p  EXPORT_FUNCTION ll_next PROTO((List_p));
DLL_EXPORT List_p  EXPORT_FUNCTION ll_find PROTO((Head_p, void *));
DLL_EXPORT List_p  EXPORT_FUNCTION ll_prev PROTO((List_p));
DLL_EXPORT List_p  EXPORT_FUNCTION ll_first PROTO((Head_p));
DLL_EXPORT List_p  EXPORT_FUNCTION ll_last PROTO((Head_p));
DLL_EXPORT void    EXPORT_FUNCTION *ll_elem PROTO((List_p));
DLL_EXPORT void    EXPORT_FUNCTION ll_advise PROTO((int));
DLL_EXPORT void    EXPORT_FUNCTION ll_insert_after PROTO((Head_p, List_p, List_p));
DLL_EXPORT void    EXPORT_FUNCTION ll_insert_before PROTO((Head_p, List_p, List_p));
DLL_EXPORT void    EXPORT_FUNCTION ll_set_atom PROTO((List_p, char *));

# define        ll_length(hd)   ((hd)->l_len)
# define        ll_refcnt(hd)   ((hd)->l_refcnt)

# if defined(FAST_LIST_FEATURE)
#       define  LL_NEXT(lp) (lp)->l_next
#       define  LL_PREV(lp) (lp)->l_prev
#       define  LL_ELEM(lp) ((void *) (lp)->l_data)
# else /* defined(FAST_LIST_FEATURE) */
#       define  LL_NEXT ll_next
#       define  LL_PREV ll_prev
#       define  LL_ELEM ll_elem
# endif /* defined(FAST_LIST_FEATURE) */

# if __cplusplus
}
# endif
# endif /* list_h */
