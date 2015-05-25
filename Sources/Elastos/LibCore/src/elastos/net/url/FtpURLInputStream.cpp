

#include "FtpURLInputStream.h"
#include "IoUtils.h"

using Elastos::IO::IoUtils;

namespace Elastos {
namespace Net {
namespace Url {

ECode FtpURLInputStream::Init(
    /* [in] */ IInputStream* is,
    /* [in] */ ISocket* controlSocket)
{
    mIs = is;
    mControlSocket = controlSocket;
    return NOERROR;
}


ECode FtpURLInputStream::Available(
    /* [out] */ Int32* number)
{
    return mIs->Available(number);
}

ECode FtpURLInputStream::Close()
{
    IoUtils::CloseQuietly(mIs);
    IoUtils::CloseQuietly(mControlSocket);
    return NOERROR;
}

ECode FtpURLInputStream::Mark(
    /* [in] */ Int32 readLimit)
{
    Object::Autolock lock(mLock);
    return mIs->Mark(readLimit);;
}

ECode FtpURLInputStream::IsMarkSupported(
    /* [out] */ Boolean* supported)
{
    return mIs->IsMarkSupported(supported);
}

ECode FtpURLInputStream::Read(
    /* [out] */ Int32* value)
{
    return mIs->Read(value);
}

ECode FtpURLInputStream::ReadBytesEx(
    /* [out] */ ArrayOf<Byte>* buffer,
    /* [in] */ Int32 offset,
    /* [in] */ Int32 length,
    /* [out] */ Int32* number)
{
    return mIs->ReadBytesEx(buffer, offset, length, number);
}

ECode FtpURLInputStream::Reset()
{
    Object::Autolock lock(mLock);
    return mIs->Reset();;
}

ECode FtpURLInputStream::Skip(
    /* [in] */ Int64 byteCount,
    /* [out] */ Int64* number)
{
    return mIs->Skip(byteCount, number);
}

} // namespace Url
} // namespace Net
} // namespace Elastos