#ifndef UUID_H_
#define UUID_H_

#include <sys/time.h> /* timeval */

typedef struct timeval timeval_t;

typedef struct
{
     timeval_t time_stamp;
     unsigned long uid;
     unsigned long pid;
}uuid_t;

/*return unique id handel for task*/
uuid_t UidCreate();

/*return invalid uid*/
uuid_t UidGetInvalid();

int UidIsSameUid(uuid_t uid1, uuid_t uid2); 

#endif /* UUID_H_ */

