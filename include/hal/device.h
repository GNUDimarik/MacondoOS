/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2022 Dmitry Adzhiev <dmitry.adjiev@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef DEVICE_H
#define DEVICE_H

#include <string.h>
#include <asm/types.h>

namespace hal
{
class Device
{
public:
    static constexpr const int kDeviceNameLength = 64;

    enum Type
    {
        kBlock,
        kCharacter
    };

    Device(const char *name, Type type)
        : type_(type)
    {
        strcpy(name_, name);
    }

    virtual ~Device() = default;

    virtual int write(__u8 *buffer, size_t len) = 0;
    virtual int read(__u8 *buffer, size_t len) = 0;

    const char *name() const
    { return name_; }
    const;
protected:
    void setType(Type type)
    { type_ = type; }
private:
    Type type_;
    char name_[kDeviceNameLength];
};
}

#endif //DEVICE_H