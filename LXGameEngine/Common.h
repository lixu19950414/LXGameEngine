#ifndef COMMON_H
#define COMMON_H

#define LX_LOG(format, ...) printf(format, ##__VA_ARGS__);
#define LX_SAFE_RELEASE_NULL(pointer) if(pointer != nullptr){pointer->release();pointer=nullptr;};
#define RANDOM_0_1() ((float)rand()/RAND_MAX)
#define RANDOM_MINUS_1_1() (((float)rand()/RAND_MAX)*2.0f-1.0f)
#define LINEAR_INTERPOLATION(src, dst, scale) (src * (1.0f - scale) + dst * scale);

#endif