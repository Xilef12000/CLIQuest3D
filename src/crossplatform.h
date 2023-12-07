#ifndef CROSSPLATFORM_H_
#define CROSSPLATFORM_H_

    #ifdef _WIN32
    
    #elif __linux__ 
        #include "OSlinux.h"
    #endif 

#endif // CROSSPLATFORM_H_