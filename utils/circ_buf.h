#ifndef CIRC_BUF_H_
#define CIRC_BUF_H_

#include <stddef.h> /*size_t*/

typedef struct circ_buf circ_buf_t;

typedef enum
{
  CIRC_BUF_NO_ERR = 0,
  CIRC_BUF_ERR_OVERFLOW = 1,
  CIRC_BUF_ERR_UNDERFLOW = 2
}circ_buff_err_t;
extern circ_buff_err_t circ_buff_errno;

circ_buf_t *CircBufCreate(size_t buffer_size);
void CircBufDestroy(circ_buf_t *circ_buff);
int CircBufIsEmpty(const circ_buf_t *circ_buf);
size_t CircBufRead(circ_buf_t *circ_buf, void *buf, size_t count);
size_t CircBufWrite(circ_buf_t *circ_buf, const void *buf, size_t count);
size_t CircBufFreeSpace(const circ_buf_t *circ_buf);
size_t CircBufCapacity(const circ_buf_t *circ_buf);

#endif /*CIRC_BUF_H_*/
