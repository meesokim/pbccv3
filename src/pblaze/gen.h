#ifndef PBLAZE_GEN_H
#define PBLAZE_GEN_H
#ifdef __cplusplus

#include "common.h"
#include "wrap.h"
#include "ralloc.h"

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

void genPBlazeCode(ICode *lic);

class I {
public:
    virtual string getName() const = 0;

    class Load;
    class Fetch;
    class Store;
    class Add;
    class Sub;
    class Call;
};

class I::Load : public I {
public:
    Load(reg_info *reg, uint8_t value) : m_reg(reg), m_value(value) { }
    virtual string getName() const {
        stringstream s;
        s << "load " << m_reg->getName() << ", " << (int) m_value;
        return s.str();
    }
private:
    reg_info *m_reg;
    uint8_t m_value;
};

class I::Fetch : public I {
public:
    Fetch(reg_info *reg, uint8_t addr) : m_reg(reg), m_addr(addr) { }
    virtual string getName() const {
        stringstream s;
        s << "fetch " << m_reg->getName() << ", " << std::hex << (int) m_addr;
        return s.str();
    }
private:
    reg_info *m_reg;
    uint8_t m_addr;
};

class I::Store : public I {
public:
    Store(reg_info *reg, uint8_t addr) : m_reg(reg), m_addr(addr) { }
    virtual string getName() const {
        stringstream s;
        s << "store " << m_reg->getName() << ", " << std::hex << (int) m_addr;
        return s.str();
    }
private:
    reg_info *m_reg;
    uint8_t m_addr;
};

class I::Add : public I {
public:
    Add(ICode *ic, unsigned long value) {

    }
    virtual string getName() const { return "add"; }
};

class I::Sub : public I {
public:
    Sub(ICode *ic, unsigned long value) {

    }
    virtual string getName() const { return "sub"; }
};

class I::Call : public I {
public:
    Call(Symbol *func) : m_func(func) { }
    virtual string getName() const {
        stringstream s;
        s << "call " << m_func->rname;
        return s.str();
    }
private:
    Symbol *m_func;
};

inline Emitter& operator<<(Emitter &e, const I &i) {
    e << "\t" << i.getName() << "\n";
}


#endif // __cplusplus
#endif // PBLAZE_GEN_H

