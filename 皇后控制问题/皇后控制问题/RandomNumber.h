#pragma once

const unsigned long maxshort = 65536L;  
const unsigned long multiplier = 1194211693L;  
const unsigned long adder = 12345L;
class RandomNumber
{
private:  
    //��ǰ����  
    unsigned long randSeed;  
public:
	RandomNumber(unsigned long s=0);//���캯����Ĭ��ֵ0��ʾ��ϵͳ�Զ���������
	
	~RandomNumber(void);
	  
    unsigned short Random(unsigned long n);//����0��n-1֮����������  
    double fRandom(void);//����[0,1)֮������ʵ��  
};
  