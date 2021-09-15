#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "memlib.h"
#include "mm.h"
/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/

team_t team = {
	"Malloc lab",
	"Seung    ",
	"20210120",
	"Huh ",
	"20210120"
	};

//* Basic constants and macros: */
#define WSIZE 4 /* Word and header/footer size (bytes) */
#define DSIZE (2 * WSIZE)	 /* Doubleword size (bytes) */
#define CHUNKSIZE (1 << 12)	 /* Extend heap by this amount (bytes) */

/*Max value of 2 values*/
#define MAX(x, y) ((x) > (y) ? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p. */
#define GET(p) (*(uintptr_t *)(p))
#define PUT(p, val) (*(uintptr_t *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~(DSIZE - 1))
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp) ((void *)(bp) - WSIZE) //header pointer가 가리키는 위치 
#define FTRP(bp) ((void *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) //footer pointer가 가리키는 위치

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLK(bp) ((void *)(bp) + GET_SIZE(HDRP(bp))) 
#define PREV_BLK(bp) ((void *)(bp) - GET_SIZE((void *)(bp)-DSIZE)) 

/* Given ptr in free list, get next and previous ptr in the list */
#define GET_NEXT_PTR(bp) (*(char **)(bp + WSIZE)) // 이중포인터 (char **)인 bp가 가리키는 주소에 접근하여 bp + WSIZE에 위치한 값 읽어오기
#define GET_PREV_PTR(bp) (*(char **)(bp)) // 이중포인터 (char **)인 bp가 가리키는 주소에 접근하여 값 읽어오기

/* Puts pointers in the next and previous elements of free list */
#define SET_NEXT_PTR(bp, qp) (GET_NEXT_PTR(bp) = qp) //이중포인터 (char **)인 bp가 가리키는 주소에 접근하여 bp + WSIZE 위치에 qp값 넣기
#define SET_PREV_PTR(bp, qp) (GET_PREV_PTR(bp) = qp) //이중포인터 (char **)인 bp가 가리키는 주소에 접근하여 bp 위치에 qp값 넣기

/* 글로벌 변수 */
static char *heap_listp = 0;
static char *free_list_start = 0;

/* Function prototypes */
static void *coalesce(void *bp);
static void *extend_heap(size_t words);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);

/* Function prototypes for maintaining free list*/
static void insert_in_free_list(void *bp);
static void remove_from_free_list(void *bp);

int mm_init(void) {
    
	/* Create the initial empty heap. */
    if ((heap_listp = mem_sbrk(6*WSIZE) == NULL)) return -1;
    
    PUT(heap_listp, 0);
    PUT(heap_listp + (1*WSIZE), PACK(2*DSIZE, 1));
    PUT(heap_listp + (2*WSIZE), 0);
    PUT(heap_listp + (3*WSIZE), 0);
    PUT(heap_listp + (4*WSIZE), PACK(2*DSIZE, 1));
    PUT(heap_listp + (5*WSIZE), PACK(0, 1));
    free_list_start = heap_listp + 2* WSIZE;

    if (extend_heap(4) == NULL) return -1;
    
    return 0;
}

static void *extend_heap(size_t words) {
    char *bp;
    size_t size;

    size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
    if (size < 16) size = 16; //최소 사이즈는 16으로 설정

    // for more memory space
    if ((int)(bp = mem_sbrk(size)) == -1) return NULL;

    PUT(HDRP(bp), PACK(size, 0)); //free block header
    PUT(FTRP(bp), PACK(size, 0)); //free block footer
    PUT(HDRP(NEXT_BLK(bp)), PACK(0, 1)); // new epilogue header

    return coalesce(bp);
}

static void *coalesce(void *bp) {
    size_t NEXT_ALLOC = GET_ALLOC(HDRP(NEXT_BLK(bp)));
    size_t PREV_ALLOC = GET_ALLOC(HDRP(PREV_BLK(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (PREV_ALLOC && !NEXT_ALLOC) {
        size += GET_SIZE(HDRP(NEXT_))
    }


}