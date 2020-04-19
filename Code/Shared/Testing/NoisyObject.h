#include <iostream>

class NoisyObject 
{
public:
    NoisyObject();
    ~NoisyObject();
    NoisyObject& operator=(const NoisyObject& rhs);
    NoisyObject(const NoisyObject& rhs);

    static uint32_t GetAndResetCtorCount();
    static uint32_t GetAndResetDtorCount();
    static uint32_t GetAndResetOpEqCount();
    static uint32_t GetAndResetCopyCtorCount();

private:
    static uint32_t s_CtorCount;
    static uint32_t s_DtorCount;
    static uint32_t s_OpEqCount;
    static uint32_t s_CopyCtorCount;
};

class CompositeNoisyObject
{
public:
    CompositeNoisyObject();
    ~CompositeNoisyObject();
    CompositeNoisyObject& operator=(const CompositeNoisyObject& rhs);
    CompositeNoisyObject(const CompositeNoisyObject& rhs);

    static uint32_t GetAndResetCtorCount();
    static uint32_t GetAndResetDtorCount();
    static uint32_t GetAndResetOpEqCount();
    static uint32_t GetAndResetCopyCtorCount();

private:
    static uint32_t s_CtorCount;
    static uint32_t s_DtorCount;
    static uint32_t s_OpEqCount;
    static uint32_t s_CopyCtorCount;

  
private:
    NoisyObject no1;
    NoisyObject no2;
};
