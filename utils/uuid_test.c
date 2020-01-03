#include <time.h>
#include <stdio.h>

#include "uuid.h"

int main()
{
	uid_t uid1 = UidCreate();
	uid_t uid2 = UidCreate();
	uid_t uid3 = UidGetInvalid();
	
	printf("%ld, %ld\nthe count is: %lu\nthe pid is: %lu\n", uid1.time_stamp.tv_sec,
																 uid1.time_stamp.tv_usec,
																 uid1.uid,
																 uid1.pid);
	
	
	printf("\n%ld, %ld\nthe count is: %lu\nthe pid is: %lu\n", uid2.time_stamp.tv_sec,
																 uid2.time_stamp.tv_usec,
																 uid2.uid,
																 uid2.pid);	
																 
																 
	printf("\n%ld, %ld\nthe count is: %lu\nthe pid is: %lu\n", uid3.time_stamp.tv_sec,
															 uid3.time_stamp.tv_usec,
															 uid3.uid,
															 uid3.pid);		
															 
	
										 
	if (UidIsSameUid(uid1, uid2) == 1)
	{
		fprintf(stderr, "wrong IsSameUid return value\n");
	}
	if (UidIsSameUid(uid1, uid3) == 1)
	{
		fprintf(stderr, "wrong IsSameUid return value for the invalid uid\n");
	}	
	
	puts("\nwell done!");											 
	return 0;
}
