#ifndef CROSSPLATFORM_H_
#define CROSSPLATFORM_H_

    #ifdef _WIN32
        #include "OSwin.h"
    #elif __linux__ 
        #include "OSlinux.h"
    #endif 

#endif // CROSSPLATFORM_H_