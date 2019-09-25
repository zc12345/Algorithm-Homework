#include "RandomNumber.h"
#include <ctime>

RandomNumber::RandomNumber(unsigned long s)//��������  
{  
    if(s==0)  
        randSeed = time(0);//��ϵͳʱ���������  
    else  
        randSeed = s;//���û��ṩ����  
}  


RandomNumber::~RandomNumber(void)
{
}


unsigned short RandomNumber::Random(unsigned long n)//����0��n-1֮����������  
{  
    randSeed=multiplier*randSeed+adder;  
    return (unsigned short)((randSeed>>16) % n);  
}  
double RandomNumber::fRandom(void)//����[0,1)֮������ʵ��  
{  
    return Random(maxshort) / double(maxshort);  
}   