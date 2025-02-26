#include "Buffer.h"

Buffer::Buffer()
{

}

Buffer::~Buffer()
{

}

// 把数据追加到buf_中。
void Buffer::append(const char *data,size_t size)             
{
    buf_.append(data,size);
}
void Buffer::appendwithhead(const char *data,size_t size) 
{
    int len=size;
    buf_.append((char*)&len,4); // 把报文头部填充到回应报文中。
    buf_.append(data,size); // 把报文内容填充到回应报文中。
}

// 从buf_的pos开始，删除nn个字节，pos从0开始。
void Buffer::erase(size_t pos,size_t nn)                             
{
    buf_.erase(pos,nn);
}

// 返回buf_的大小。
size_t Buffer::size()                                                            
{
    return buf_.size();
}

// 返回buf_的首地址。
const char *Buffer::data()                                                  
{
    return buf_.data();
}

// 清空buf_。
void Buffer::clear()                                                            
{
    buf_.clear();
}