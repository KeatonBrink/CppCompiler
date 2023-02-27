#pragma once

#include <iostream>

#define ShowMesages 1
#if ShowMesages
#define MSG(X) std::cout << X << std::endl;
#else
#define MSG(X) ;
#endif