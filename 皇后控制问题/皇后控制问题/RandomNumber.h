#pragma once

const unsigned long maxshort = 65536L;  
const unsigned long multiplier = 1194211693L;  
const unsigned long adder = 12345L;
class RandomNumber
{
private:  
    //当前种子  
    unsigned long randSeed;  
public:
	RandomNumber(unsigned long s=0);//构造函数，默认值0表示由系统自动产生种子
	
	~RandomNumber(void);
	  
    unsigned short Random(unsigned long n);//产生0：n-1之间的随机整数  
    double fRandom(void);//产生[0,1)之间的随机实数  
};
  