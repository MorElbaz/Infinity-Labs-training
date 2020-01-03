/*reviewed by Tar*/

#include <stdlib.h> /*malloc*/
#include <assert.h>/*assert*/
#include <string.h>/*memcpy*/

#include "circ_buf.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b));

circ_buff_err_t circ_buff_errno = CIRC_BUF_NO_ERR;

struct circ_buf
{
	size_t capacity;
	size_t size;
	size_t read_idx;
	char data[1];
};

/*O(1)*/
circ_buf_t *CircBufCreate(size_t buffer_size)
{
	circ_buf_t *circ_buf = (circ_buf_t *) malloc(sizeof(circ_buf_t) + buffer_size);
	
	if (circ_buf == NULL)
	{
		return (NULL);
	}
	
	circ_buf->capacity = buffer_size;
	circ_buf->size = 0;
	circ_buf->read_idx = 0;
	
	return (circ_buf);	
}

/*O(1)*/
void CircBufDestroy(circ_buf_t *circ_buf)
{
	free(circ_buf);
}

/*O(1)*/
int CircBufIsEmpty(const circ_buf_t *circ_buf)
{
	assert(circ_buf != NULL);
	
	return (circ_buf->size == 0);
}

/*O(n)*/
size_t CircBufRead(circ_buf_t *circ_buf, void *buf, size_t count)
{
	size_t num_bytes;
	size_t actual_count = count;
	
	assert(circ_buf != NULL);
	assert(buf != NULL);
	
	if (circ_buf->size < count)
	{
		actual_count = circ_buf->size;
		circ_buff_errno = CIRC_BUF_ERR_UNDERFLOW;
	}
	
	num_bytes = MIN(actual_count, circ_buf->capacity - circ_buf->read_idx);
	memcpy(buf, circ_buf->data + circ_buf->read_idx, num_bytes);
	memcpy((char *)buf + num_bytes, circ_buf->data, actual_count - num_bytes);
	
	circ_buf->size -= actual_count;
	circ_buf->read_idx = (circ_buf->read_idx + actual_count) % circ_buf->capacity;
	
	return (actual_count);
}

/*O(n)*/
size_t CircBufWrite(circ_buf_t *circ_buf, const void *buf, size_t count)
{
	size_t num_bytes;
	size_t write_idx;
	size_t free_space;
	size_t actual_count = count;
	
	assert(circ_buf != NULL);
	assert(buf != NULL);
	
	free_space = CircBufFreeSpace(circ_buf);
	if (actual_count > free_space)
	{
		actual_count = free_space;
		circ_buff_errno = CIRC_BUF_ERR_OVERFLOW;
	}

	write_idx = (circ_buf->read_idx + circ_buf->size) % circ_buf->capacity;	
	
	num_bytes = MIN(actual_count, circ_buf->capacity - write_idx);
	memcpy(circ_buf->data + write_idx, buf, num_bytes);
	memcpy(circ_buf->data, (char *)buf + num_bytes, actual_count - num_bytes);
	
	circ_buf->size += actual_count;
	
	return (actual_count);		
}

/*O(1)*/
size_t CircBufFreeSpace(const circ_buf_t *circ_buf)
{
	assert(circ_buf != NULL);
	
	return (circ_buf->capacity - circ_buf->size);
}

/*O(1)*/
size_t CircBufCapacity(const circ_buf_t *circ_buf)
{
	assert(circ_buf != NULL);
	
	return (circ_buf->capacity);
}
