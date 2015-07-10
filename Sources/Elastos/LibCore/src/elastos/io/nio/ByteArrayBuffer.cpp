#include "ByteArrayBuffer.h"
#include "Memory.h"
#include "ByteBufferAsCharBuffer.h"
#include "ByteBufferAsDoubleBuffer.h"
#include "ByteBufferAsFloatBuffer.h"
#include "ByteBufferAsInt16Buffer.h"
#include "ByteBufferAsInt32Buffer.h"
#include "ByteBufferAsInt64Buffer.h"
#include "CByteOrderHelper.h"

using Libcore::IO::ISizeOf;
using Libcore::IO::Memory;

namespace Elastos {
namespace IO {

ByteArrayBuffer::ByteArrayBuffer(
    /* [in] */ ArrayOf<Byte>* backingArray)
    : ByteBuffer(backingArray->GetLength(), 0)
    , mBackingArray(backingArray)
    , mArrayOffset(0)
    , mIsReadOnly(FALSE)
{
    if (mArrayOffset + mBackingArray->GetLength() > mBackingArray->GetLength()) {
        // throw new IndexOutOfBoundsException("mBackingArray.length=" + mBackingArray.length +
                                              // ", capacity=" + capacity + ", mArrayOffset=" + mArrayOffset);
        assert(0);
    }
}

ByteArrayBuffer::ByteArrayBuffer(
    /* [in] */ Int32 capacity,
    /* [in] */ ArrayOf<Byte>* backingArray,
    /* [in] */ Int32 mArrayOffset,
    /* [in] */ Boolean mIsReadOnly)
    : ByteBuffer(capacity, 0)
    , mBackingArray(backingArray)
    , mArrayOffset(0)
    , mIsReadOnly(FALSE)
{
    if (mArrayOffset + capacity > mBackingArray->GetLength()) {
        // throw new IndexOutOfBoundsException("mBackingArray.length=" + mBackingArray.length +
                                              // ", capacity=" + capacity + ", mArrayOffset=" + mArrayOffset);
        assert(0);
    }
}

AutoPtr<ByteArrayBuffer> ByteArrayBuffer::Copy(
    /* [in] */ ByteArrayBuffer* other,
    /* [in] */ Int32 markOfOther,
    /* [in] */ Boolean mIsReadOnly)
{
    Int32 capvalue = 0;
    other->GetCapacity(&capvalue);
    AutoPtr<ByteArrayBuffer> buf = new ByteArrayBuffer(capvalue, other->mBackingArray, other->mArrayOffset, mIsReadOnly);
    buf->mLimit = other->mLimit;
    buf->mPosition = capvalue;
    buf->mMark = markOfOther;
    return buf;
}

ECode ByteArrayBuffer::AsReadOnlyBuffer(
    /* [out] */ IByteBuffer** buffer)
{
    VALIDATE_NOT_NULL(buffer)

    AutoPtr<ByteArrayBuffer> res = Copy(this, mMark, TRUE);
    *buffer = res;
    REFCOUNT_ADD(*buffer)
    return NOERROR;
}


ECode ByteArrayBuffer::Compact()
{
    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    Int32 remainvalue = 0;
    GetRemaining(&remainvalue);
    // System.arraycopy(mBackingArray, mPosition + mArrayOffset, mBackingArray, mArrayOffset, remaining());
    mBackingArray->Copy(mArrayOffset, mBackingArray, mPosition + mArrayOffset, remainvalue);
    mPosition = mLimit - mPosition;
    mLimit = mCapacity;
    mMark = UNSET_MARK;
    return NOERROR;
}

ECode ByteArrayBuffer::Duplicate(
    /* [out] */ IByteBuffer** buffer)
{
    VALIDATE_NOT_NULL(buffer)

    AutoPtr<ByteArrayBuffer> res = Copy(this, mMark, mIsReadOnly);
    *buffer = (IByteBuffer*) res->Probe(EIID_IByteBuffer);
    REFCOUNT_ADD(*buffer)
    return NOERROR;
}

ECode ByteArrayBuffer::Slice(
    /* [out] */ IByteBuffer** buffer)
{
    VALIDATE_NOT_NULL(buffer)

    Int32 remainvalue = 0;
    GetRemaining(&remainvalue);
    AutoPtr<IByteBuffer> res = (IByteBuffer*) new ByteArrayBuffer(remainvalue,
                                                                  mBackingArray,
                                                                  mArrayOffset + mPosition,
                                                                  mIsReadOnly);
    *buffer = res;
    REFCOUNT_ADD(*buffer)
    return NOERROR;
}

ECode ByteArrayBuffer::IsReadOnly(
    /* [out] */ Boolean* isReadOnly)
{
    VALIDATE_NOT_NULL(isReadOnly)

    *isReadOnly = mIsReadOnly;
    return NOERROR;
}

ECode ByteArrayBuffer::ProtectedArray(
    /* [out, callee] */ ArrayOf<Byte>** array)
{
    VALIDATE_NOT_NULL(array)

    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    *array = mBackingArray;
    REFCOUNT_ADD(*array)
    return NOERROR;
}

ECode ByteArrayBuffer::ProtectedArrayOffset(
    /* [out] */ Int32* offset)
{
    VALIDATE_NOT_NULL(offset)

    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    *offset = mArrayOffset;
    return NOERROR;
}

ECode ByteArrayBuffer::ProtectedHasArray(
    /* [out] */ Boolean* hasArray)
{
    VALIDATE_NOT_NULL(hasArray)

    if (mIsReadOnly) {
        *hasArray = FALSE;
    }
    else {
        *hasArray = TRUE;
    }
    return NOERROR;
}

ECode ByteArrayBuffer::Get(
    /* [out] */ Byte* value)
{
    VALIDATE_NOT_NULL(value)

    if (mPosition == mLimit) {
        // throw new BufferUnderflowException();
        return E_BUFFER_UNDERFLOW_EXCEPTION;
    }
    *value = (*mBackingArray)[mArrayOffset + mPosition++];
    return NOERROR;
}

ECode ByteArrayBuffer::Get(
    /* [in] */ Int32 index,
    /* [out] */ Byte* value)
{
    VALIDATE_NOT_NULL(value)

    FAIL_RETURN(CheckIndex(index));
    *value = (*mBackingArray)[mArrayOffset + index];
    return NOERROR;
}

ECode ByteArrayBuffer::Get(
    /* [in] */ ArrayOf<Byte>* dst,
    /* [in] */ Int32 dstOffset,
    /* [in] */ Int32 byteCount)
{
    Int32 outvalue = 0;
    FAIL_RETURN(CheckGetBounds(1, dst->GetLength(), dstOffset, byteCount, &outvalue))
    // System.arraycopy(mBackingArray, mArrayOffset + mPosition, dst, dstOffset, byteCount);
    dst->Copy(dstOffset, mBackingArray, mArrayOffset + mPosition, byteCount);
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::GetChar(
    /* [out] */ Char32* value)
{
    VALIDATE_NOT_NULL(value)

    Int32 newPosition = mPosition + ISizeOf::CHAR;
    if (newPosition > mLimit) {
        // throw new BufferUnderflowException();
        return E_BUFFER_UNDERFLOW_EXCEPTION;
    }
    Char32 result = (Char32) Memory::PeekInt16(mBackingArray, mArrayOffset + mPosition, mOrder);
    mPosition = newPosition;
    *value = result;
    return NOERROR;
}

ECode ByteArrayBuffer::GetChar(
    /* [in] */ Int32 index,
    /* [out] */ Char32* value)
{
    VALIDATE_NOT_NULL(value)

    FAIL_RETURN(CheckIndex(index, ISizeOf::CHAR));
    *value = (Char32) Memory::PeekInt16(mBackingArray, mArrayOffset + index, mOrder);
    return NOERROR;
}

ECode ByteArrayBuffer::GetDouble(
    /* [out] */ Double* value)
{
    VALIDATE_NOT_NULL(value)

    assert(0 && "TODO");
    // return Double.longBitsToDouble(getLong());
    return NOERROR;
}

ECode ByteArrayBuffer::GetDouble(
    /* [in] */ Int32 index,
    /* [out] */ Double* value)
{
    VALIDATE_NOT_NULL(value)

    assert(0 && "TODO");
    // return Double.longBitsToDouble(getLong(index));
    return NOERROR;
}

ECode ByteArrayBuffer::GetFloat(
    /* [out] */ Float* value)
{
    VALIDATE_NOT_NULL(value)

    assert(0 && "TODO");
    // return Float.intBitsToFloat(getInt());
    return NOERROR;
}

ECode ByteArrayBuffer::GetFloat(
    /* [in] */ Int32 index,
    /* [out] */ Float* value)
{
    VALIDATE_NOT_NULL(value)

    assert(0 && "TODO");
    // return Float.intBitsToFloat(getInt(index));
    return NOERROR;
}

ECode ByteArrayBuffer::GetInt32(
    /* [out] */ Int32* value)
{
    VALIDATE_NOT_NULL(value)

    Int32 newPosition = mPosition + ISizeOf::INT;
    if (newPosition > mLimit) {
        // throw new BufferUnderflowException();
        return E_BUFFER_UNDERFLOW_EXCEPTION;
    }
    Int32 result = Memory::PeekInt32(mBackingArray, mArrayOffset + mPosition, mOrder);
    mPosition = newPosition;
    *value = result;
    return NOERROR;
}

ECode ByteArrayBuffer::GetInt32(
    /* [in] */ Int32 index,
    /* [out] */ Int32* value)
{
    VALIDATE_NOT_NULL(value)

    FAIL_RETURN(CheckIndex(index, ISizeOf::INT));
    *value = Memory::PeekInt32(mBackingArray, mArrayOffset + index, mOrder);
    return NOERROR;
}

ECode ByteArrayBuffer::GetInt64(
    /* [out] */ Int64* value)
{
    VALIDATE_NOT_NULL(value)

    Int32 newPosition = mPosition + ISizeOf::LONG;
    if (newPosition > mLimit) {
        // throw new BufferUnderflowException();
        return E_BUFFER_UNDERFLOW_EXCEPTION;
    }
    Int64 result = Memory::PeekInt64(mBackingArray, mArrayOffset + mPosition, mOrder);
    mPosition = newPosition;
    *value = result;
    return NOERROR;
}

ECode ByteArrayBuffer::GetInt64(
    /* [in] */ Int32 index,
    /* [out] */ Int64* value)
{
    VALIDATE_NOT_NULL(value)

    FAIL_RETURN(CheckIndex(index, ISizeOf::LONG));
    *value = Memory::PeekInt64(mBackingArray, mArrayOffset + index, mOrder);
    return NOERROR;
}

ECode ByteArrayBuffer::GetInt16(
    /* [out] */ Int16* value)
{
    VALIDATE_NOT_NULL(value)

    Int32 newPosition = mPosition + ISizeOf::SHORT;
    if (newPosition > mLimit) {
        // throw new BufferUnderflowException();
        return E_BUFFER_UNDERFLOW_EXCEPTION;
    }
    Int16 result = Memory::PeekInt16(mBackingArray, mArrayOffset + mPosition, mOrder);
    mPosition = newPosition;
    *value = result;
    return NOERROR;
}

ECode ByteArrayBuffer::GetInt16(
    /* [in] */ Int32 index,
    /* [out] */ Int16* value)
{
    VALIDATE_NOT_NULL(value)

    FAIL_RETURN(CheckIndex(index, ISizeOf::SHORT));
    *value = Memory::PeekInt16(mBackingArray, mArrayOffset + index, mOrder);
    return NOERROR;
}

ECode ByteArrayBuffer::IsDirect(
    /* [out] */ Boolean* isDirect)
{
    VALIDATE_NOT_NULL(isDirect)

    *isDirect = FALSE;
    return NOERROR;
}

ECode ByteArrayBuffer::Put(
    /* [in] */ Byte b)
{
    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    if (mPosition == mLimit) {
        // throw new BufferOverflowException();
        return E_BUFFER_OVERFLOW_EXCEPTION;
    }
    (*mBackingArray)[mArrayOffset + mPosition++] = b;
    return NOERROR;
}

ECode ByteArrayBuffer::Put(
    /* [in] */ Int32 index,
    /* [in] */ Byte b)
{
    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    FAIL_RETURN(CheckIndex(index));
    (*mBackingArray)[mArrayOffset + index] = b;
    return NOERROR;
}

ECode ByteArrayBuffer::Put(
    /* [in] */ ArrayOf<Byte>* src,
    /* [in] */ Int32 srcOffset,
    /* [in] */ Int32 byteCount)
{
    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    Int32 outcount = 0;
    FAIL_RETURN(CheckPutBounds(1, src->GetLength(), srcOffset, byteCount, &outcount));
    // System.arraycopy(src, srcOffset, mBackingArray, mArrayOffset + mPosition, byteCount);
    mBackingArray->Copy(mArrayOffset + mPosition, src, srcOffset, byteCount);
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::PutChar(
    /* [in] */ Char32 value)
{
    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    Int32 newPosition = mPosition + ISizeOf::CHAR;
    if (newPosition > mLimit) {
        // throw new BufferOverflowException();
        return E_BUFFER_OVERFLOW_EXCEPTION;
    }
    Memory::PokeInt16(mBackingArray, mArrayOffset + mPosition, (Int16) value, mOrder);
    mPosition = newPosition;
    return NOERROR;
}

ECode ByteArrayBuffer::PutChar(
    /* [in] */ Int32 index,
    /* [in] */ Char32 value)
{
    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    FAIL_RETURN(CheckIndex(index, ISizeOf::CHAR));
    Memory::PokeInt16(mBackingArray, mArrayOffset + index, (Int16) value, mOrder);
    return NOERROR;
}

ECode ByteArrayBuffer::PutDouble(
    /* [in] */ Double value)
{
    assert(0 && "TODO");
    // return putLong(Double.doubleToRawLongBits(value));
    return NOERROR;
}

ECode ByteArrayBuffer::PutDouble(
    /* [in] */ Int32 index,
    /* [in] */ Double value)
{
    assert(0 && "TODO");
    // return putLong(index, Double.doubleToRawLongBits(value));
    return NOERROR;
}

ECode ByteArrayBuffer::PutFloat(
    /* [in] */ Float value)
{
    assert(0 && "TODO");
    // return putInt(Float.floatToRawIntBits(value));
    return NOERROR;
}

ECode ByteArrayBuffer::PutFloat(
    /* [in] */ Int32 index,
    /* [in] */ Float value)
{
    assert(0 && "TODO");
    // return putInt(index, Float.floatToRawIntBits(value));
    return NOERROR;
}

ECode ByteArrayBuffer::PutInt16(
    /* [in] */ Int16 value)
{
    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    Int32 newPosition = mPosition + ISizeOf::SHORT;
    if (newPosition > mLimit) {
        // throw new BufferOverflowException();
        return E_BUFFER_OVERFLOW_EXCEPTION;
    }
    Memory::PokeInt16(mBackingArray, mArrayOffset + mPosition, value, mOrder);
    mPosition = newPosition;
    return NOERROR;
}

ECode ByteArrayBuffer::PutInt16(
    /* [in] */ Int32 index,
    /* [in] */ Int16 value)
{
    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    FAIL_RETURN(CheckIndex(index, ISizeOf::SHORT));
    Memory::PokeInt16(mBackingArray, mArrayOffset + index, value, mOrder);
    return NOERROR;
}

ECode ByteArrayBuffer::PutInt32(
    /* [in] */ Int32 value)
{
    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    Int32 newPosition = mPosition + ISizeOf::INT;
    if (newPosition > mLimit) {
        // throw new BufferOverflowException();
        return E_BUFFER_OVERFLOW_EXCEPTION;
    }
    Memory::PokeInt32(mBackingArray, mArrayOffset + mPosition, value, mOrder);
    mPosition = newPosition;
    return NOERROR;
}

ECode ByteArrayBuffer::PutInt32(
    /* [in] */ Int32 index,
    /* [in] */ Int32 value)
{
    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    FAIL_RETURN(CheckIndex(index, ISizeOf::INT));
    Memory::PokeInt32(mBackingArray, mArrayOffset + index, value, mOrder);
    return NOERROR;
}

ECode ByteArrayBuffer::PutInt64(
    /* [in] */ Int64 value)
{
    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    Int32 newPosition = mPosition + ISizeOf::LONG;
    if (newPosition > mLimit) {
        // throw new BufferOverflowException();
        return E_BUFFER_OVERFLOW_EXCEPTION;
    }
    Memory::PokeInt64(mBackingArray, mArrayOffset + mPosition, value, mOrder);
    mPosition = newPosition;
    return NOERROR;
}

ECode ByteArrayBuffer::PutInt64(
    /* [in] */ Int32 index,
    /* [in] */ Int64 value)
{
    if (mIsReadOnly) {
        // throw new ReadOnlyBufferException();
        return E_READ_ONLY_BUFFER_EXCEPTION;
    }
    FAIL_RETURN(CheckIndex(index, ISizeOf::LONG));
    Memory::PokeInt64(mBackingArray, mArrayOffset + index, value, mOrder);
    return NOERROR;
}

ECode ByteArrayBuffer::AsCharBuffer(
    /* [out] */ ICharBuffer** buffer)
{
    VALIDATE_NOT_NULL(buffer)

    AutoPtr<ICharBuffer> res = ByteBufferAsCharBuffer::AsCharBuffer(this);
    *buffer = res;
    REFCOUNT_ADD(*buffer)
    return NOERROR;
}

ECode ByteArrayBuffer::AsDoubleBuffer(
    /* [out] */ IDoubleBuffer** buffer)
{
    VALIDATE_NOT_NULL(buffer)

    AutoPtr<IDoubleBuffer> res = ByteBufferAsDoubleBuffer::AsDoubleBuffer(this);
    *buffer = res;
    REFCOUNT_ADD(*buffer)
    return NOERROR;
}

ECode ByteArrayBuffer::AsFloatBuffer(
    /* [out] */ IFloatBuffer** buffer)
{
    VALIDATE_NOT_NULL(buffer)

    AutoPtr<IFloatBuffer> res = ByteBufferAsFloatBuffer::AsFloatBuffer(this);
    *buffer = res;
    REFCOUNT_ADD(*buffer)
    return NOERROR;
}

ECode ByteArrayBuffer::AsInt16Buffer(
    /* [out] */ IInt16Buffer** buffer)
{
    VALIDATE_NOT_NULL(buffer)

    AutoPtr<IInt16Buffer> res = ByteBufferAsInt16Buffer::AsInt16Buffer(this);
    *buffer = res;
    REFCOUNT_ADD(*buffer)
    return NOERROR;
}

ECode ByteArrayBuffer::AsInt32Buffer(
    /* [out] */ IInt32Buffer** buffer)
{
    VALIDATE_NOT_NULL(buffer)

    AutoPtr<IInt32Buffer> res = ByteBufferAsInt32Buffer::AsInt32Buffer(this);
    *buffer = res;
    REFCOUNT_ADD(*buffer)
    return NOERROR;
}

ECode ByteArrayBuffer::AsInt64Buffer(
    /* [out] */ IInt64Buffer** buffer)
{
    VALIDATE_NOT_NULL(buffer)

    AutoPtr<IInt64Buffer> res = ByteBufferAsInt64Buffer::AsInt64Buffer(this);
    *buffer = res;
    REFCOUNT_ADD(*buffer)
    return NOERROR;
}

ECode ByteArrayBuffer::GetChars(
    /* [in] */ ArrayOf<Char32>* dst,
    /* [in] */ Int32 dstOffset,
    /* [in] */ Int32 charCount)
{
    Int32 byteCount = 0;
    FAIL_RETURN(CheckGetBounds(ISizeOf::CHAR, dst->GetLength(), dstOffset, charCount, &byteCount));
    Memory::UnsafeBulkGet((Byte*)dst->GetPayload(), 0, byteCount, mBackingArray, mArrayOffset + mPosition, ISizeOf::CHAR, CByteOrderHelper::_IsNeedsSwap(mOrder));
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::GetDoubles(
    /* [in] */ ArrayOf<Double>* dst,
    /* [in] */ Int32 dstOffset,
    /* [in] */ Int32 doubleCount)
{
    Int32 byteCount = 0;
    FAIL_RETURN(CheckGetBounds(ISizeOf::DOUBLE, dst->GetLength(), dstOffset, doubleCount, &byteCount));
    Memory::UnsafeBulkGet((Byte*)dst->GetPayload(), dstOffset, byteCount, mBackingArray, mArrayOffset + mPosition, ISizeOf::DOUBLE, CByteOrderHelper::_IsNeedsSwap(mOrder));
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::GetFloats(
    /* [in] */ ArrayOf<Float>* dst,
    /* [in] */ Int32 dstOffset,
    /* [in] */ Int32 floatCount)
{
    Int32 byteCount = 0;
    FAIL_RETURN(CheckGetBounds(ISizeOf::FLOAT, dst->GetLength(), dstOffset, floatCount, &byteCount));
    Memory::UnsafeBulkGet((Byte*)dst->GetPayload(), dstOffset, byteCount, mBackingArray, mArrayOffset + mPosition, ISizeOf::FLOAT, CByteOrderHelper::_IsNeedsSwap(mOrder));
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::GetInt32s(
    /* [in] */ ArrayOf<Int32>* dst,
    /* [in] */ Int32 dstOffset,
    /* [in] */ Int32 intCount)
{
    Int32 byteCount = 0;
    FAIL_RETURN(CheckGetBounds(ISizeOf::INT, dst->GetLength(), dstOffset, intCount, &byteCount));
    Memory::UnsafeBulkGet((Byte*)dst->GetPayload(), dstOffset, byteCount, mBackingArray, mArrayOffset + mPosition, ISizeOf::INT, CByteOrderHelper::_IsNeedsSwap(mOrder));
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::GetInt64s(
    /* [in] */ ArrayOf<Int64>* dst,
    /* [in] */ Int32 dstOffset,
    /* [in] */ Int32 longCount)
{
    Int32 byteCount = 0;
    FAIL_RETURN(CheckGetBounds(ISizeOf::LONG, dst->GetLength(), dstOffset, longCount, &byteCount));
    Memory::UnsafeBulkGet((Byte*)dst->GetPayload(), dstOffset, byteCount, mBackingArray, mArrayOffset + mPosition, ISizeOf::LONG, CByteOrderHelper::_IsNeedsSwap(mOrder));
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::GetInt16s(
    /* [in] */ ArrayOf<Int16>* dst,
    /* [in] */ Int32 dstOffset,
    /* [in] */ Int32 shortCount)
{
    Int32 byteCount = 0;
    FAIL_RETURN(CheckGetBounds(ISizeOf::SHORT, dst->GetLength(), dstOffset, shortCount, &byteCount));
    Memory::UnsafeBulkGet((Byte*)dst->GetPayload(), dstOffset, byteCount, mBackingArray, mArrayOffset + mPosition, ISizeOf::SHORT, CByteOrderHelper::_IsNeedsSwap(mOrder));
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::PutChars(
    /* [in] */ ArrayOf<Char32>* src,
    /* [in] */ Int32 srcOffset,
    /* [in] */ Int32 charCount)
{
    Int32 byteCount = 0;
    FAIL_RETURN(CheckPutBounds(ISizeOf::CHAR, src->GetLength(), srcOffset, charCount, &byteCount));
    Memory::UnsafeBulkPut(mBackingArray, mArrayOffset + mPosition, byteCount, (Byte*)src->GetPayload(), srcOffset, ISizeOf::CHAR, CByteOrderHelper::_IsNeedsSwap(mOrder));
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::PutDoubles(
    /* [in] */ ArrayOf<Double>* src,
    /* [in] */ Int32 srcOffset,
    /* [in] */ Int32 doubleCount)
{
    Int32 byteCount = 0;
    FAIL_RETURN(CheckPutBounds(ISizeOf::DOUBLE, src->GetLength(), srcOffset, doubleCount, &byteCount));
    Memory::UnsafeBulkPut(mBackingArray, mArrayOffset + mPosition, byteCount, (Byte*)src->GetPayload(), srcOffset, ISizeOf::DOUBLE, CByteOrderHelper::_IsNeedsSwap(mOrder));
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::PutFloats(
    /* [in] */ ArrayOf<Float>* src,
    /* [in] */ Int32 srcOffset,
    /* [in] */ Int32 floatCount)
{
    Int32 byteCount = 0;
    FAIL_RETURN(CheckPutBounds(ISizeOf::FLOAT, src->GetLength(), srcOffset, floatCount, &byteCount));
    Memory::UnsafeBulkPut(mBackingArray, mArrayOffset + mPosition, byteCount, (Byte*)src->GetPayload(), srcOffset, ISizeOf::FLOAT, CByteOrderHelper::_IsNeedsSwap(mOrder));
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::PutInt32s(
    /* [in] */ ArrayOf<Int32>* src,
    /* [in] */ Int32 srcOffset,
    /* [in] */ Int32 intCount)
{
    Int32 byteCount = 0;
    FAIL_RETURN(CheckPutBounds(ISizeOf::INT, src->GetLength(), srcOffset, intCount, &byteCount));
    Memory::UnsafeBulkPut(mBackingArray, mArrayOffset + mPosition, byteCount, (Byte*)src->GetPayload(), srcOffset, ISizeOf::INT, CByteOrderHelper::_IsNeedsSwap(mOrder));
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::PutInt64s(
    /* [in] */ ArrayOf<Int64>* src,
    /* [in] */ Int32 srcOffset,
    /* [in] */ Int32 longCount)
{
    Int32 byteCount = 0;
    FAIL_RETURN(CheckPutBounds(ISizeOf::LONG, src->GetLength(), srcOffset, longCount, &byteCount));
    Memory::UnsafeBulkPut(mBackingArray, mArrayOffset + mPosition, byteCount, (Byte*)src->GetPayload(), srcOffset, ISizeOf::LONG, CByteOrderHelper::_IsNeedsSwap(mOrder));
    mPosition += byteCount;
    return NOERROR;
}

ECode ByteArrayBuffer::PutInt16s(
    /* [in] */ ArrayOf<Int16>* src,
    /* [in] */ Int32 srcOffset,
    /* [in] */ Int32 shortCount)
{
    Int32 byteCount = 0;
    FAIL_RETURN(CheckPutBounds(ISizeOf::SHORT, src->GetLength(), srcOffset, shortCount, &byteCount));
    Memory::UnsafeBulkPut(mBackingArray, mArrayOffset + mPosition, byteCount, (Byte*)src->GetPayload(), srcOffset, ISizeOf::SHORT, CByteOrderHelper::_IsNeedsSwap(mOrder));
    mPosition += byteCount;
    return NOERROR;
}

} // namespace IO
} // namespace Elastos