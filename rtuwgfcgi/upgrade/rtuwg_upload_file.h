#ifndef RTUWG_UPLOAD_FILE
#define RTUWG_UPLOAD_FILE


//#include <sysinc.h>


#define EUPLOAD_SUCCESS 0 
#define EUPLOAD_NO_DATA -1
#define EUPLOAD_READ    -2
#define EUPLOAD_WRITE   -3



extern int  upload_file_save_as(const char *save_path,char *save_file_name,int *file_size);




#endif
