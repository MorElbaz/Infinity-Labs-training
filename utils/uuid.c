#include <stddef.h>/* NULL */
#include <unistd.h>/* getpid */

#include "uuid.h"

/*return unique id handel for task*/
/*O(1)*/
uuid_t UidCreate()
{
	uuid_t uid;
	static unsigned long counter = 0;
	
	++counter;
	
	gettimeofday(&uid.time_stamp, NULL);
	uid.uid = counter;
	uid.pid = (unsigned long)getpid();
	
	return (uid);
}	
	
/*return invalid uid*/
/*O(1)*/
uuid_t UidGetInvalid()
{
	static uuid_t uid;
	
	return (uid);
}

/*O(1)*/
int UidIsSameUid(uuid_t uid1, uuid_t uid2)
{
	return ((uid1.time_stamp.tv_sec == uid2.time_stamp.tv_sec) &&
			(uid1.time_stamp.tv_usec == uid2.time_stamp.tv_usec) &&
			(uid1.uid == uid2.uid) &&
			(uid1.pid == uid2.pid));
}
