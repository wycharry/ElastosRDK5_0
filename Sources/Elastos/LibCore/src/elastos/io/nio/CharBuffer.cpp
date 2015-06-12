
#include "CharBuffer.h"
#include "Math.h"
#include "StringBuilder.h"
#include <CharSequenceAdapter.h>
#include <ReadWriteCharArrayBuffer.h>

using Elastos::Core::StringBuilder;

namespace Elastos {
namespace IO {

// {43410042-EC51-485f-9C70-1DDBC11B759D}
extern "C" const InterfaceID EIID_CharBuffer =
    { 0x43410042, 0xec51, 0x485f, { 0x9c, 0x70, 0x1d, 0xdb, 0xc1, 0x1b, 0x75, 0x9d } };

ECode CharBuffer::Allocate(
    /* [in] */ Int32 capacity,
    /* [out] */ ICharBuffer** buf)
{
    VALIDATE_NOT_NULL(buf);

    if (capacity < 0) {
        // throw new IllegalArgumentException("capacity < 0: " + capacity);
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }

    assert(0 && "TODO");
    // *buf = (ICharBuffer*)new ReadWriteCharArrayBuffer(capacity);
    REFCOUNT_ADD(*buf)
    return NOERROR;
}

ECode CharBuffer::Wrap(
    /* [in] */ ArrayOf<Char32>* array,
    /* [out] */ ICharBuffer** buf)
{
    return Wrap(array, 0, array->GetLength(), buf);
}

ECode CharBuffer::Wrap(
    /* [in] */ ArrayOf<Char32>* array,
    /* [in] */ Int32 start,
    /* [in] */ Int32 charCount,
    /* [out] */ ICharBuffer** buf)
{
    VALIDATE_NOT_NULL(buf);

    Int32 arrayLength = array->GetLength();
    if ((start | charCount) < 0 || start > arrayLength || arrayLength - start < charCount) {
        // throw new ArrayIndexOutOfBoundsException(arrayLength, offset,
        //         count);
        return E_ARRAY_INDEX_OUT_OF_BOUNDS_EXCEPTION;
    }
    assert(0 && "TODO");
    AutoPtr<ReadWriteCharArrayBuffer> buffer; // = new ReadWriteCharArrayBuffer(array);
    buffer->mPosition = start;
    buffer->mLimit = start + charCount;
    *buf = (ICharBuffer*)buffer.Get();
    REFCOUNT_ADD(*buf);
    return NOERROR;
}

ECode CharBuffer::WrapSequence(
    /* [in] */ ICharSequence* chseq,
    /* [out] */ ICharBuffer** buf)
{
    VALIDATE_NOT_NULL(buf)
    Int32 len = 0;
    chseq->GetLength(&len);
    assert(0 && "TODO");
    // *buf = (ICharBuffer*)new CharSequenceAdapter(len, chseq);
    REFCOUNT_ADD(*buf)
    return NOERROR;
}

ECode CharBuffer::WrapSequence(
    /* [in] */ ICharSequence* chseq,
    /* [in] */ Int32 start,
    /* [in] */ Int32 end,
    /* [out] */ ICharBuffer** buf)
{
    VALIDATE_NOT_NULL(buf)
    Int32 len = 0;
    chseq->GetLength(&len);
    if (start < 0 || end < start || end > len) {
        // throw new IndexOutOfBoundsException("cs.length()=" + cs.length() + ", start=" + start + ", end=" + end);
        return E_INDEX_OUT_OF_BOUNDS_EXCEPTION;
    }
    assert(0 && "TODO");
    AutoPtr<CharSequenceAdapter> result; // = new CharSequenceAdapter(len, chseq);
    result->mPosition = start;
    result->mLimit = end;
    *buf = (ICharBuffer*)result.Get();
    REFCOUNT_ADD(*buf)
    return NOERROR;
}

CharBuffer::CharBuffer(
    /* [in] */ Int32 capacity)
    : Buffer(1, capacity, NULL)
{}

ECode CharBuffer::GetArray(
    /* [out, callee] */ ArrayOf<Char32>** array)
{
    return ProtectedArray(array);
}

ECode CharBuffer::GetArrayOffset(
    /* [out] */ Int32* offset)
{
    return ProtectedArrayOffset(offset);
}

ECode CharBuffer::GetCharAt(
    /* [in] */ Int32 index,
    /* [out] */ Char32* value)
{
    VALIDATE_NOT_NULL(value);
    Int32 remaining = 0;
    GetRemaining(&remaining);

    if (index < 0 || index >= remaining) {
        // throw new IndexOutOfBoundsException("index=" + index + ", remaining()=" + remaining());
        return E_INDEX_OUT_OF_BOUNDS_EXCEPTION;
    }

    return Get(mPosition + index, value);
}

ECode CharBuffer::CompareTo(
    /* [in] */ ICharBuffer* otherBuffer,
    /* [out] */ Int32* result)
{
    VALIDATE_NOT_NULL(result);
    VALIDATE_NOT_NULL(otherBuffer);

    Int32 remaining = 0;
    Int32 otherRemaining = 0;
    GetRemaining(&remaining);
    IBuffer::Probe(otherBuffer)->GetRemaining(&otherRemaining);

    Int32 compareRemaining = (remaining < otherRemaining) ?
                              remaining : otherRemaining;
    Int32 thisPos = mPosition;
    Int32 otherPos = 0;
    IBuffer::Probe(otherBuffer)->GetPosition(&otherPos);

    Char32 thisByte;
    Char32 otherByte;
    while (compareRemaining > 0) {
        Get(thisPos, &thisByte);
        otherBuffer->Get(otherPos, &otherByte);
        if (thisByte != otherByte) {
            *result = thisByte < otherByte ? -1 : 1;
            return NOERROR;
        }

        thisPos++;
        otherPos++;
        compareRemaining--;
    }

    *result = remaining - otherRemaining;
    return NOERROR;
}

ECode CharBuffer::Get(
    /* [out] */ ArrayOf<Char32>* dst)
{
    return Get(dst, 0, dst->GetLength());
}

ECode CharBuffer::Get(
    /* [out] */ ArrayOf<Char32>* dst,
    /* [in] */ Int32 dstOffset,
    /* [in] */ Int32 charCount)
{
    VALIDATE_NOT_NULL(dst);

    Int32 length = dst->GetLength();
    if ((dstOffset < 0) || (charCount < 0) || ((Int64) dstOffset + (Int64) charCount > length)) {
        return E_INDEX_OUT_OF_BOUNDS_EXCEPTION;
    }

    Int32 remaining = 0;
    GetRemaining(&remaining);
    if (charCount > remaining) {
        return E_BUFFER_UNDER_FLOW_EXCEPTION;
    }
    for (Int32 i = dstOffset; i < dstOffset + charCount; i++) {
        Get(&(*dst)[i]);
    }

    return NOERROR;
}

ECode CharBuffer::HasArray(
    /* [out] */ Boolean* hasArray)
{
    return ProtectedHasArray(hasArray);
}

ECode CharBuffer::GetLength(
    /* [out] */ Int32* number)
{
    return GetRemaining(number);
}

ECode CharBuffer::Put(
    /* [in] */ ArrayOf<Char32>* src)
{
    return Put(src, 0, src->GetLength());
}

ECode CharBuffer::Put(
    /* [in] */ ArrayOf<Char32>* src,
    /* [in] */ Int32 srcOffset,
    /* [in] */ Int32 charCount)
{
    Int32 length = src->GetLength();

    if ((srcOffset < 0) || (charCount < 0) ||
            (Int64) srcOffset + (Int64) charCount > length) {
        return E_INDEX_OUT_OF_BOUNDS_EXCEPTION;
    }

    Int32 remaining = 0;
    GetRemaining(&remaining);
    if (charCount > remaining) {
        // throw new BufferOverflowException();
        return E_BUFFER_OVER_FLOW_EXCEPTION;
    }
    for (Int32 i = srcOffset; i < srcOffset + charCount; i++) {
        Put((*src)[i]);
    }

    return NOERROR;
}

ECode CharBuffer::Put(
    /* [in] */ ICharBuffer* src)
{
    if (src == (ICharBuffer*)this->Probe(EIID_ICharBuffer)) {
        // throw new IllegalArgumentException("src == this");
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }

    Int32 srcRemaining = 0;
    Int32 remaining = 0;
    IBuffer::Probe(src)->GetRemaining(&srcRemaining);
    GetRemaining(&remaining);
    if (srcRemaining > remaining) {
        // throw new BufferOverflowException();
        return E_BUFFER_OVER_FLOW_EXCEPTION;
    }

    AutoPtr< ArrayOf<Char32> > contents = ArrayOf<Char32>::Alloc(srcRemaining);
    FAIL_RETURN(src->Get(contents))
    return Put(contents);
}

ECode CharBuffer::PutString(
    /* [in] */ const String& str)
{
    return PutString(str, 0, str.GetLength());
}

ECode CharBuffer::PutString(
    /* [in] */ const String& str,
    /* [in] */ Int32 start,
    /* [in] */ Int32 end)
{
    Int32 length = str.GetLength();
    if (start < 0 || end < start || end > length) {
        // throw new IndexOutOfBoundsException("str.length()=" + str.length() +
        //             ", start=" + start + ", end=" + end);
        return E_INDEX_OUT_OF_BOUNDS_EXCEPTION;
    }

    Int32 remaining = 0;
    GetRemaining(&remaining);
    if (end - start > remaining) {
        // throw new BufferOverflowException();
        return E_BUFFER_OVER_FLOW_EXCEPTION;
    }
    for (Int32 i = start; i < end; i++) {
        Put(str[i]);
    }

    return NOERROR;
}

ECode CharBuffer::ToString(
    /* [out] */ String* str)
{
    VALIDATE_NOT_NULL(str)
    StringBuilder result(mLimit - mPosition);
    Char32 c;
    for (Int32 i = mPosition; i < mLimit; i++) {
        FAIL_RETURN(Get(i, &c))
        result += c;
    }
    return result.ToString(str);
}

ECode CharBuffer::Append(
    /* [in] */ Char32 c)
{
    return Put(c);
}

ECode CharBuffer::Append(
    /* [in] */ ICharSequence* csq)
{
    if (csq != NULL) {
        String str;
        csq->ToString(&str);
        return PutString(str);
    }
    return PutString(String("null"));
}

ECode CharBuffer::Append(
    /* [in] */ ICharSequence* csq,
    /* [in] */ Int32 start,
    /* [in] */ Int32 end)
{
    if (csq == NULL) {
        //csq = "null";
        return NOERROR;
    }
    AutoPtr<ICharSequence> cs;
    csq->SubSequence(start, end, (ICharSequence**)&cs);
    Int32 len = 0;
    cs->GetLength(&len);
    if (len > 0) {
        String str;
        cs->ToString(&str);
        return PutString(str);
    }
    return NOERROR;
}

ECode CharBuffer::Read(
    /* [in] */ ICharBuffer* target,
    /* [out] */ Int32* number)
{
    VALIDATE_NOT_NULL(number)
    Int32 remaining = 0;
    GetRemaining(&remaining);
    if (target == (ICharBuffer*)this->Probe(EIID_ICharBuffer)) {
        if (remaining == 0) {
            *number = -1;
            return NOERROR;
        }

        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }

    Int32 targetRemaining = 0;
    IBuffer::Probe(target)->GetRemaining(&targetRemaining);
    if (remaining == 0) {
        *number = mLimit > 0 && targetRemaining == 0 ? 0 : -1;
        return NOERROR;
    }

    remaining = Elastos::Core::Math::Min(targetRemaining, remaining);
    if (remaining > 0) {
        AutoPtr<ArrayOf<Char32> > chars = ArrayOf<Char32>::Alloc(remaining);
        Get(chars);
        target->Put(chars);
    }

    *number = remaining;
    return NOERROR;
}

ECode CharBuffer::Equals(
    /* [in] */ IInterface* other,
    /* [out] */ Boolean* rst)
{
    VALIDATE_NOT_NULL(rst)

    if (ICharBuffer::Probe(other) == NULL) {
        *rst = FALSE;
        return NOERROR;
    }

    AutoPtr<ICharBuffer> otherBuffer = (ICharBuffer*) other;
    Int32 thisRemaining = 0;
    Int32 otherRemaining = 0;
    GetRemaining(&thisRemaining);
    IBuffer::Probe(otherBuffer)->GetRemaining(&otherRemaining);
    if (thisRemaining != otherRemaining) {
        *rst = FALSE;
        return NOERROR;
    }

    Int32 myPosition = mPosition;
    Int32 otherPosition = 0;
    IBuffer::Probe(otherBuffer)->GetPosition(&otherPosition);
    Boolean equalSoFar = TRUE;
    Char32 thisChar;
    Char32 otherChar;
    while (equalSoFar && (myPosition < mLimit)) {
        FAIL_RETURN(Get(myPosition++, &thisChar))
        FAIL_RETURN(otherBuffer->Get(otherPosition++, &otherChar))
        equalSoFar = thisChar == otherChar;
    }
    *rst = equalSoFar;
    return NOERROR;
}

} // namespace IO
} // namespace Elastos