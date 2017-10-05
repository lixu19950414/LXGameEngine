#ifndef COMMON_H
#define COMMON_H

#define LX_LOG(format, ...) printf(format, ##__VA_ARGS__);
#define LX_SAFE_RELEASE_NULL(pointer) if(pointer != nullptr){pointer->release();pointer=nullptr;};

#endif