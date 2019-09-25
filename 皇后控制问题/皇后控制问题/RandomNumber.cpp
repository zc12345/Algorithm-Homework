#include "RandomNumber.h"
#include <ctime>

RandomNumber::RandomNumber(unsigned long s)//产生种子  
{  
    if(s==0)  
        randSeed = time(0);//用系统时间产生种子  
    else  
        randSeed = s;//由用户提供种子  
}  


RandomNumber::~RandomNumber(void)
{
}


unsigned short RandomNumber::Random(unsigned long n)//产生0：n-1之间的随机整数  
{  
    randSeed=multiplier*randSeed+adder;  
    return (unsigned short)((randSeed>>16) % n);  
}  
double RandomNumber::fRandom(void)//产生[0,1)之间的随机实数  
{  
    return Random(maxshort) / double(maxshort);  
}   