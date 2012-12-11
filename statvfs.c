#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <inttypes.h>

int main(void)
{
	struct statvfs stat;
	if (statvfs("/ifs", &stat) == -1){
		return 1;
	}
	int bfree = (100 - stat.f_bfree * 100 / stat.f_blocks);
	int bavail =  (100 - stat.f_bavail * 100 / stat.f_blocks);
	printf("/ifs -- Free:      %d%%\n"
	       "        Available: %d%%\n", bfree, bavail);
	return 0;
}