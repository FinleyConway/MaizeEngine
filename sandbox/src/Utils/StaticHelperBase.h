#pragma once

class StaticHelperBase
{
protected:
    StaticHelperBase() = delete;
    virtual ~StaticHelperBase() = delete;
    StaticHelperBase(const StaticHelperBase&) = delete;
    StaticHelperBase& operator=(const StaticHelperBase&) = delete;
};
