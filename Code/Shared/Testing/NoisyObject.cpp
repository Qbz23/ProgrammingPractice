#include "NoisyObject.h"
#include "../Logging/Logging.h"

uint32_t NoisyObject::s_CtorCount = 0;
uint32_t NoisyObject::s_DtorCount = 0;
uint32_t NoisyObject::s_OpEqCount = 0;
uint32_t NoisyObject::s_CopyCtorCount = 0;
uint32_t CompositeNoisyObject::s_CtorCount = 0;
uint32_t CompositeNoisyObject::s_DtorCount = 0;
uint32_t CompositeNoisyObject::s_OpEqCount = 0;
uint32_t CompositeNoisyObject::s_CopyCtorCount = 0;

NoisyObject::NoisyObject() 
{ 
    Log::If(Log::bLogNoisyObject, "NoisyObject Ctor\n");
    s_CtorCount += 1;
}

NoisyObject::~NoisyObject()
{
    Log::If(Log::bLogNoisyObject, "NoisyObject Dtor\n");
    s_DtorCount += 1;
}

NoisyObject& NoisyObject::operator=(const NoisyObject& rhs)
{
    Log::If(Log::bLogNoisyObject, "NoisyObject OpEq\n");
    s_OpEqCount += 1;
    return *this;
}

NoisyObject::NoisyObject(const NoisyObject& rhs)
{
    Log::If(Log::bLogNoisyObject, "NoisyObject CopyCtor\n");
    s_CopyCtorCount += 1;
}

uint32_t NoisyObject::GetAndResetCtorCount()
{
    uint32_t temp = s_CtorCount;
    s_CtorCount = 0;
    return temp;
}

uint32_t NoisyObject::GetAndResetDtorCount()
{
    uint32_t temp = s_DtorCount;
    s_DtorCount = 0;
    return temp;
}

uint32_t NoisyObject::GetAndResetOpEqCount()
{
    uint32_t temp = s_OpEqCount;
    s_OpEqCount = 0;
    return temp;
}

uint32_t NoisyObject::GetAndResetCopyCtorCount()
{
    uint32_t temp = s_CopyCtorCount;
    s_CopyCtorCount = 0;
    return temp;
}

CompositeNoisyObject::CompositeNoisyObject()
{
    Log::If(Log::bLogNoisyObject, "CompositeNoisyObject Ctor\n");
    s_CtorCount += 1;
}

CompositeNoisyObject::~CompositeNoisyObject()
{
    Log::If(Log::bLogNoisyObject, "CompositeNoisyObject Dtor\n");
    s_DtorCount += 1;
}

CompositeNoisyObject& CompositeNoisyObject::operator=(const CompositeNoisyObject& rhs)
{
    Log::If(Log::bLogNoisyObject, "CompositeNoisyObject OpEq\n");
    s_OpEqCount += 1;
    return *this;
}

CompositeNoisyObject::CompositeNoisyObject(const CompositeNoisyObject& rhs)
{
    Log::If(Log::bLogNoisyObject, "CompositeNoisyObject CopyCtor\n");
    s_CopyCtorCount += 1;
}

uint32_t CompositeNoisyObject::GetAndResetCtorCount()
{
    uint32_t temp = s_CtorCount;
    s_CtorCount = 0;
    return temp;
}

uint32_t CompositeNoisyObject::GetAndResetDtorCount()
{
    uint32_t temp = s_DtorCount;
    s_DtorCount = 0;
    return temp;
}

uint32_t CompositeNoisyObject::GetAndResetOpEqCount()
{
    uint32_t temp = s_OpEqCount;
    s_OpEqCount = 0;
    return temp;
}

uint32_t CompositeNoisyObject::GetAndResetCopyCtorCount()
{
    uint32_t temp = s_CopyCtorCount;
    s_CopyCtorCount = 0;
    return temp;
}
