#ifndef __UTILITY_CCOLLECTIONS_H__
#define __UTILITY_CCOLLECTIONS_H__

#include "AbstractList.h"
#include "AbstractSet.h"
#include "AbstractMap.h"
#include "MapEntry.h"
#include "AbstractQueue.h"

using Elastos::IO::IObjectOutputStream;
using Elastos::IO::IObjectInputStream;
using Elastos::Core::IComparator;
using Elastos::Core::IRandom;

namespace Elastos {
namespace Utility {

class Collections
    : public Object
{
public:
    class SynchronizedCollection
        : public Object
        , public ICollection
        , public IIterable
        , public ISerializable
    {
    public:
        SynchronizedCollection(
            /* [in] */ ICollection* collection);

        SynchronizedCollection(
            /* [in] */ ICollection* collection,
            /* [in] */ Object* lock);

        ~SynchronizedCollection();

        CAR_INTERFACE_DECL()

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI Add(
            /* [in] */ IInterface* object);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection);

        CARAPI Clear();

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI Remove(
            /* [in] */ IInterface* object);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToString(
            /* [out] */ String* str);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

    private:
        CARAPI WriteObject(
            /* [in] */ IObjectOutputStream* stream);

    public:
        Object* mLock;
        Boolean mIsStrongLock;
        AutoPtr<ICollection> mC;
    };

    class SynchronizedList
        : public SynchronizedCollection
        , public IList
    {
    public:
        SynchronizedList(
            /* [in] */ IList* l);

        SynchronizedList(
            /* [in] */ IList* l,
            /* [in] */ Object* lock);

        CAR_INTERFACE_DECL()

        CARAPI Add(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object);

        CARAPI Add(
            /* [in] */ IInterface* object);

        CARAPI AddAll(
            /* [in] */ Int32 location,
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ Int32 location,
            /* [in] */ ICollection* collection);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI Get(
            /* [in] */ Int32 location,
            /* [out] */ IInterface** object);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IndexOf(
            /* [in] */ IInterface* object,
            /* [out] */ Int32* index);

        CARAPI LastIndexOf(
            /* [in] */ IInterface* object,
            /* [out] */ Int32* index);

        CARAPI GetListIterator(
            /* [out] */ IListIterator** it);

        CARAPI GetListIterator(
            /* [in] */ Int32 location,
            /* [out] */ IListIterator** it);

        CARAPI Remove(
            /* [in] */ Int32 location,
            /* [out] */ IInterface** object);

        CARAPI Remove(
            /* [in] */ Int32 location);

        CARAPI Set(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object,
            /* [out] */ IInterface** prevObject);

        CARAPI Set(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object);

        CARAPI GetSubList(
            /* [in] */ Int32 start,
            /* [in] */ Int32 end,
            /* [out] */ IList** subList);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Clear();

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

    private:
        CARAPI WriteObject(
            /* [in] */ IObjectOutputStream* stream);

        CARAPI_(AutoPtr<IInterface>) ReadResolve();

    public:
        AutoPtr<IList> mList;
    };

    class SynchronizedRandomAccessList
        : public SynchronizedList
        , public IRandomAccess
    {
    public:
        SynchronizedRandomAccessList(
            /* [in] */ IList* l);

        SynchronizedRandomAccessList(
            /* [in] */ IList* l,
            /* [in] */ Object* lock);

        CAR_INTERFACE_DECL()

        CARAPI GetSubList(
            /* [in] */ Int32 start,
            /* [in] */ Int32 end,
            /* [out] */ IList** subList);

    private:
        CARAPI_(AutoPtr<IInterface>) WriteReplace();
    };

    class SynchronizedSet
        : public SynchronizedCollection
        , public ISet
    {
    public:
        SynchronizedSet(
            /* [in] */ ISet* set);

        SynchronizedSet(
            /* [in] */ ISet* set,
            /* [in] */ Object* lock);

        CAR_INTERFACE_DECL()

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Clear();

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

    private:
        CARAPI WriteObject(
            /* [in] */ IObjectOutputStream* stream);
    };

    class SynchronizedMap
        : public Object
        , public IMap
        , public ISerializable
    {
    public:
        SynchronizedMap(
            /* [in] */ IMap* map);

        SynchronizedMap(
            /* [in] */ IMap* map,
            /* [in] */ Object* lock);

        ~SynchronizedMap();

        CAR_INTERFACE_DECL()

        CARAPI Clear();

        CARAPI ContainsKey(
            /* [in] */ IInterface* key,
            /* [out] */ Boolean* result);

        CARAPI ContainsValue(
            /* [in] */ IInterface* value,
            /* [out] */ Boolean* result);

        CARAPI GetEntrySet(
            /* [out, callee] */ ISet** entries);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI Get(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI GetKeySet(
            /* [out, callee] */ ISet** keySet);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value,
            /* [out] */ PInterface* oldValue);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value);

        CARAPI PutAll(
            /* [in] */ IMap* map);

        CARAPI Remove(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI Remove(
            /* [in] */ PInterface key);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI GetValues(
            /* [out] */ ICollection** value);

        CARAPI ToString(
            /* [out] */ String* str);

    private:
        CARAPI WriteObject(
            /* [in] */ IObjectOutputStream* stream);

    public:
        Object* mLock;
        Boolean mIsStrongLock;
        AutoPtr<IMap> mM;
    };

    class SynchronizedSortedMap
        : public SynchronizedMap
        , public ISortedMap
    {
    public:
        SynchronizedSortedMap(
            /* [in] */ ISortedMap* map);

        SynchronizedSortedMap(
            /* [in] */ ISortedMap* map,
            /* [in] */ Object* lock);

        CAR_INTERFACE_DECL()

        CARAPI GetComparator(
            /* [out] */ IComparator** comp);

        CARAPI GetFirstKey(
            /* [out] */ IInterface** outface);

        CARAPI GetHeadMap(
            /* [in] */ IInterface* endKey,
            /* [out] */ ISortedMap** sortmap);

        CARAPI GetLastKey(
            /* [out] */ IInterface** outface);

        CARAPI GetSubMap(
            /* [in] */ IInterface* startKey,
            /* [in] */ IInterface* endKey,
            /* [out] */ ISortedMap** sortmap);

        CARAPI GetTailMap(
            /* [in] */ IInterface* startKey,
            /* [out] */ ISortedMap** sortmap);

        CARAPI Clear();

        CARAPI ContainsKey(
            /* [in] */ IInterface* key,
            /* [out] */ Boolean* result);

        CARAPI ContainsValue(
            /* [in] */ IInterface* value,
            /* [out] */ Boolean* result);

        CARAPI GetEntrySet(
            /* [out, callee] */ ISet** entries);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI Get(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI GetKeySet(
            /* [out, callee] */ ISet** keySet);

        CARAPI GetValues(
            /* [out] */ ICollection** value);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value,
            /* [out] */ PInterface* oldValue);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value);

        CARAPI PutAll(
            /* [in] */ IMap* map);

        CARAPI Remove(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI Remove(
            /* [in] */ PInterface key);

        CARAPI GetSize(
            /* [out] */ Int32* size);

    private:
        CARAPI WriteObject(
            /* [in] */ IObjectOutputStream* stream);
        AutoPtr<ISortedMap> mSm;
    };

    class SynchronizedSortedSet
        : public SynchronizedSet
        , public ISortedSet
    {
    public:
        SynchronizedSortedSet(
            /* [in] */ ISortedSet* set);

        SynchronizedSortedSet(
            /* [in] */ ISortedSet* set,
            /* [in] */ Object* lock);

        CAR_INTERFACE_DECL()

        CARAPI GetComparator(
            /* [out] */ IComparator** outcom);

        CARAPI GetFirst(
            /* [out] */ IInterface** outface);

        CARAPI GetHeadSet(
            /* [in] */ IInterface* end,
            /* [out] */ ISortedSet** outsort);

        CARAPI GetLast(
            /* [out] */ IInterface** outface);

        CARAPI GetSubSet(
            /* [in] */ IInterface* start,
            /* [in] */ IInterface* end,
            /* [out] */ ISortedSet** outsort);

        CARAPI GetTailSet(
            /* [in] */ IInterface* start,
            /* [out] */ ISortedSet** outsort);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Clear();

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

    private:
        CARAPI WriteObject(
            /* [in] */ IObjectOutputStream* stream);
        AutoPtr<ISortedSet> mSs;
    };

private:
    class Iterator
        : public Object
        , public IIterator
    {
    public:
        Iterator();

        CAR_INTERFACE_DECL()

        CARAPI HasNext(
            /* [out] */ Boolean* result);

        CARAPI GetNext(
            /* [out] */ IInterface** object);

        CARAPI Remove();
    };

    class MyEnumeration
        : public Object
        , public IEnumeration
    {
    public:
        MyEnumeration();

        CAR_INTERFACE_DECL()

        CARAPI HasMoreElements(
            /* [out] */ Boolean* value);

        CARAPI GetNextElement(
            /* [out] */ IInterface** inter);
    };

    class MyEnumeration2
        : public Object
        , public IEnumeration
    {
    public:
        MyEnumeration2(
            /* [in] */ ICollection* c);

        CAR_INTERFACE_DECL()

        CARAPI HasMoreElements(
            /* [out] */ Boolean* value);

        CARAPI GetNextElement(
            /* [out] */ IInterface** inter);
    public:
        AutoPtr<IIterator> mIt;
    };

    class CopiesList
        : public AbstractList
        , public ISerializable
    {
    public:
        CopiesList(
            /* [in] */ Int32 length,
            /* [in] */ IInterface* object);

        CAR_INTERFACE_DECL()

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI Get(
            /* [in] */ Int32 location,
            /* [out] */ IInterface** object);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Clear();

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        CARAPI Add(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object);

        CARAPI AddAll(
            /* [in] */ Int32 location,
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI IndexOf(
            /* [in] */ IInterface* object,
            /* [out] */ Int32* index);

        CARAPI LastIndexOf(
            /* [in] */ IInterface* object,
            /* [out] */ Int32* index);

        CARAPI GetListIterator(
            /* [out] */ IListIterator** it);

        CARAPI GetListIterator(
            /* [in] */ Int32 location,
            /* [out] */ IListIterator** it);

        CARAPI Remove(
            /* [in] */ Int32 location,
            /* [out] */ IInterface** object);

        CARAPI Set(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object,
            /* [out] */ IInterface** prevObject);

        CARAPI GetSubList(
            /* [in] */ Int32 start,
            /* [in] */ Int32 end,
            /* [out] */ IList** subList);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);
        Int32 mN;
        AutoPtr<IInterface> mElement;
    };

public:
    class EmptyList
        : public AbstractList
        , public IRandomAccess
        , public ISerializable
    {
    public:
        CAR_INTERFACE_DECL()

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI Get(
            /* [in] */ Int32 location,
            /* [out] */ IInterface** object);

        CARAPI Set(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object,
            /* [out] */ IInterface** prevObject);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI Clear();

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* contents,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        CARAPI Add(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object);

        CARAPI AddAll(
            /* [in] */ Int32 location,
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI IndexOf(
            /* [in] */ IInterface* object,
            /* [out] */ Int32* index);

        CARAPI LastIndexOf(
            /* [in] */ IInterface* object,
            /* [out] */ Int32* index);

        CARAPI GetListIterator(
            /* [out] */ IListIterator** it);

        CARAPI GetSubList(
            /* [in] */ Int32 start,
            /* [in] */ Int32 end,
            /* [out] */ IList** subList);

        CARAPI GetListIterator(
            /* [in] */ Int32 location,
            /* [out] */ IListIterator** listiterator);

        CARAPI Remove(
            /* [in] */ Int32 location,
            /* [out] */ IInterface** object);

    private:
        CARAPI_(AutoPtr<IInterface>) ReadResolve();
    };

    class EmptySet
        : public AbstractSet
        , public ISerializable
    {
    public:
        CAR_INTERFACE_DECL()

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Clear();

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

    private:
        CARAPI_(AutoPtr<IInterface>) ReadResolve();
    };

    class EmptyMap
        : public AbstractMap
        , public ISerializable
    {
    public:
        CAR_INTERFACE_DECL()

        CARAPI ContainsKey(
            /* [in] */ IInterface* key,
            /* [out] */ Boolean* result);

        CARAPI ContainsValue(
            /* [in] */ IInterface* value,
            /* [out] */ Boolean* result);

        CARAPI GetEntrySet(
            /* [out, callee] */ ISet** entries);

        CARAPI Get(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI GetKeySet(
            /* [out, callee] */ ISet** keySet);

        CARAPI GetValues(
            /* [out] */ ICollection** value);

        CARAPI Clear();

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value,
            /* [out] */ PInterface* oldValue);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value);

        CARAPI PutAll(
            /* [in] */ IMap* map);

        CARAPI Remove(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI Remove(
            /* [in] */ PInterface key);

        CARAPI GetSize(
            /* [out] */ Int32* size);

    private:
        CARAPI_(AutoPtr<IInterface>) ReadResolve();
    };

    class ReverseComparator
        : public Object
        , public IComparator
        , public ISerializable
    {
    public:
        CAR_INTERFACE_DECL()

        CARAPI Compare(
            /* [in] */ IInterface* lhs,
            /* [in] */ IInterface* rhs,
            /* [out] */ Int32* result);

    private:
        CARAPI_(AutoPtr<IInterface>) ReadResolve();

    public:
        static const AutoPtr<ReverseComparator> INSTANCE;
    };

    class ReverseComparator2
        : public Object
        , public IComparator
        , public ISerializable
    {
    public:
        ReverseComparator2(
            /* [in] */ IComparator* comparator);

        CAR_INTERFACE_DECL()

        CARAPI Compare(
            /* [in] */ IInterface* lhs,
            /* [in] */ IInterface* rhs,
            /* [out] */ Int32* result);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);
    public:
        AutoPtr<IComparator> mCmp;
    };

    class SingletonSet
        : public AbstractSet
        , public ISerializable
    {
    private:
        class Iterator
            : public Object
            , public IIterator
        {
        public:
            Iterator(
                /* [in] */ SingletonSet* owner);

            CAR_INTERFACE_DECL()

            CARAPI HasNext(
                /* [out] */ Boolean* result);

            CARAPI GetNext(
                /* [out] */ IInterface** object);

            CARAPI Remove();

        public:
            Boolean mHasNext;
            AutoPtr<SingletonSet> mOwner;
        };
    public:
        SingletonSet(
            /* [in] */ IInterface* object);

        CAR_INTERFACE_DECL()

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Clear();

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

    public:
        AutoPtr<IInterface> mElement;
    };

    class SingletonList
        : public AbstractList
        , public ISerializable
    {
    public:
        SingletonList(
            /* [in] */ IInterface* object);

        CAR_INTERFACE_DECL()

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI Get(
            /* [in] */ Int32 location,
            /* [out] */ IInterface** object);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Clear();

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        CARAPI Add(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object);

        CARAPI AddAll(
            /* [in] */ Int32 location,
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI IndexOf(
            /* [in] */ IInterface* object,
            /* [out] */ Int32* index);

        CARAPI LastIndexOf(
            /* [in] */ IInterface* object,
            /* [out] */ Int32* index);

        CARAPI GetListIterator(
            /* [out] */ IListIterator** it);

        CARAPI GetListIterator(
            /* [in] */ Int32 location,
            /* [out] */ IListIterator** it);

        CARAPI Remove(
            /* [in] */ Int32 location,
            /* [out] */ IInterface** object);

        CARAPI Set(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object,
            /* [out] */ IInterface** prevObject);

        CARAPI GetSubList(
            /* [in] */ Int32 start,
            /* [in] */ Int32 end,
            /* [out] */ IList** subList);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

    public:
        AutoPtr<IInterface> mElement;
    };

    class SingletonMap
        : public AbstractMap
        , public ISerializable
    {
    private:
        class MySet
            : public AbstractSet
        {
        private:
            class Iterator
                : public Object
                , public IIterator
            {
            private:
                class MyMapEntry
                    : public MapEntry
                {
                public:
                    MyMapEntry(
                        /* [in] */ IInterface* k,
                        /* [in] */ IInterface* v);

                    CARAPI SetValue(
                        /* [in] */ IInterface* valueReplacer,
                        /* [out] */ IInterface** valueReplacee);
                };

            public:
                Iterator(
                    /* [in] */ MySet* owner);

                CAR_INTERFACE_DECL()

                CARAPI HasNext(
                    /* [out] */ Boolean* result);

                CARAPI GetNext(
                    /* [out] */ IMapEntry** object);

                CARAPI GetNext(
                    /* [out] */ IInterface** object);

                CARAPI Remove();

            public:
                Boolean mHasNext;
                AutoPtr<MySet> mOwner;
            };
        public:
            MySet(
                /* [in] */ SingletonMap* owner);

            CAR_INTERFACE_DECL()

            CARAPI Contains(
                /* [in] */ IInterface* object,
                /* [out] */ Boolean* result);

            CARAPI GetSize(
                /* [out] */ Int32* size);

            CARAPI GetIterator(
                /* [out] */ IIterator** it);

            CARAPI Add(
                /* [in] */ IInterface* object,
                /* [out] */ Boolean* modified);

            CARAPI AddAll(
                /* [in] */ ICollection* collection,
                /* [out] */ Boolean* modified);

            CARAPI Clear();

            CARAPI ContainsAll(
                /* [in] */ ICollection* collection,
                /* [out] */ Boolean* result);

            CARAPI Equals(
                /* [in] */ IInterface* object,
                /* [out] */ Boolean* result);

            CARAPI GetHashCode(
                /* [out] */ Int32* hashCode);

            CARAPI IsEmpty(
                /* [out] */ Boolean* result);

            CARAPI Remove(
                /* [in] */ IInterface* object,
                /* [out] */ Boolean* modified);

            CARAPI RemoveAll(
                /* [in] */ ICollection* collection,
                /* [out] */ Boolean* modified);

            CARAPI RetainAll(
                /* [in] */ ICollection* collection,
                /* [out] */ Boolean* modified);

            CARAPI ToArray(
                /* [out, callee] */ ArrayOf<IInterface*>** array);

            CARAPI ToArray(
                /* [in] */ ArrayOf<IInterface*>* inArray,
                /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        private:
            SingletonMap* mOwner;
        };
    public:
        SingletonMap(
            /* [in] */ IInterface* key,
            /* [in] */ IInterface* value);

        CAR_INTERFACE_DECL()

        CARAPI ContainsKey(
            /* [in] */ IInterface* key,
            /* [out] */ Boolean* result);

        CARAPI ContainsValue(
            /* [in] */ IInterface* value,
            /* [out] */ Boolean* result);

        CARAPI Get(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI GetEntrySet(
            /* [out, callee] */ ISet** entries);

        CARAPI Clear();

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI GetKeySet(
            /* [out, callee] */ ISet** keySet);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value,
            /* [out] */ PInterface* oldValue);

        CARAPI PutAll(
            /* [in] */ IMap* map);

        CARAPI Remove(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI GetValues(
            /* [out] */ ICollection** value);

    protected:
        AutoPtr<IInterface> mK;
        AutoPtr<IInterface> mV;
    };

    class UnmodifiableCollection
        : public Object
        , public ICollection
        , public ISerializable
    {
    private:
        class Iterator
            : public Object
            , public IIterator
        {
        public:
            Iterator(
                /* [in] */ UnmodifiableCollection* owner);

            CAR_INTERFACE_DECL()

            CARAPI HasNext(
                /* [out] */ Boolean* result);

            CARAPI GetNext(
                /* [out] */ IInterface** object);

            CARAPI Remove();
        public:
            AutoPtr<Iterator> mIterator;
        };
    public:
        UnmodifiableCollection(
            /* [in] */ ICollection* collection);

        CAR_INTERFACE_DECL()

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI Add(
            /* [in] */ IInterface* object);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection);

        CARAPI Clear();

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI Remove(
            /* [in] */ IInterface* object);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        CARAPI ToString(
            /* [out] */ String* str);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

    public:
        AutoPtr<ICollection> mC;
    };

    class UnmodifiableList
        : public UnmodifiableCollection
        , public IList
    {
    private:
        class ListIterator
            : public Object
            , public IListIterator
        {
        public:
            ListIterator(
                /* [in] */ UnmodifiableList* owner,
                /* [in] */ Int32 location);

            CAR_INTERFACE_DECL()

            CARAPI Add(
                /* [in] */ IInterface* object);

            CARAPI HasNext(
                /* [out] */ Boolean* result);

            CARAPI HasPrevious(
                /* [out] */ Boolean* result);

            CARAPI GetNext(
                /* [out] */ IInterface** object);

            CARAPI GetNextIndex(
                /* [out] */ Int32* index);

            CARAPI GetPrevious(
                /* [out] */ IInterface** object);

            CARAPI GetPreviousIndex(
                /* [out] */ Int32* index);

            CARAPI Remove();

            CARAPI Set(
                /* [in] */ IInterface* object);
        public:
            AutoPtr<IListIterator> mIterator;
        };
    public:
        UnmodifiableList(
            /* [in] */ IList* l);

        CAR_INTERFACE_DECL()

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI Add(
            /* [in] */ IInterface* object);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ Int32 location,
            /* [in] */ ICollection* collection);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI Get(
            /* [in] */ Int32 location,
            /* [out] */ IInterface** object);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IndexOf(
            /* [in] */ IInterface* object,
            /* [out] */ Int32* index);

        CARAPI LastIndexOf(
            /* [in] */ IInterface* object,
            /* [out] */ Int32* index);

        CARAPI GetListIterator(
            /* [out] */ IListIterator** it);

        CARAPI GetListIterator(
            /* [in] */ Int32 location,
            /* [out] */ IListIterator** it);

        CARAPI Remove(
            /* [in] */ Int32 location,
            /* [out] */ IInterface** object);

        CARAPI Remove(
            /* [in] */ Int32 location);

        CARAPI Set(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object,
            /* [out] */ IInterface** prevObject);

        CARAPI Set(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object);

        CARAPI GetSubList(
            /* [in] */ Int32 start,
            /* [in] */ Int32 end,
            /* [out] */ IList** subList);

        CARAPI Clear();

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        CARAPI Add(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object);

        CARAPI AddAll(
            /* [in] */ Int32 location,
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

    private:
        CARAPI_(AutoPtr<IInterface>) ReadResolve();

    public:
        AutoPtr<IList> mList;
    };

    class UnmodifiableRandomAccessList
        : public UnmodifiableList
        , public IRandomAccess
    {
    public:
        UnmodifiableRandomAccessList(
            /* [in] */ IList* l);

        CAR_INTERFACE_DECL()

        CARAPI GetSubList(
            /* [in] */ Int32 start,
            /* [in] */ Int32 end,
            /* [out] */ IList** subList);

    private:
        CARAPI_(AutoPtr<IInterface>) WriteReplace();
    };

    class UnmodifiableSet
        : public UnmodifiableCollection
        , public ISet
    {
    public:
        UnmodifiableSet(
            /* [in] */ ISet* set);

        CAR_INTERFACE_DECL()

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Clear();

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);
    };

    class UnmodifiableMap
        : public Object
        , public IMap
        , public ISerializable
    {
    private:
        class UnmodifiableEntrySet
            : public UnmodifiableSet
        {
        private:
            class UnmodifiableMapEntry
                : public Object
                , public IMapEntry
            {
            public:
                UnmodifiableMapEntry(
                    /* [in] */ IMapEntry* entry);

                CAR_INTERFACE_DECL()

                CARAPI Equals(
                    /* [in] */ IInterface* entry,
                    /* [out] */ Boolean* result);

                CARAPI GetKey(
                    /* [out] */ PInterface* key);

                CARAPI GetValue(
                    /* [out] */ PInterface* value);

                CARAPI GetHashCode(
                    /* [out] */ Int32* hashCode);

                CARAPI SetValue(
                    /* [in] */ IInterface* valueReplacer,
                    /* [out] */ IInterface** valueReplacee);

                CARAPI ToString(
                    /* [out] */ String* str);

            public:
                AutoPtr<IMapEntry> mMapEntry;
            };

            class Iterator
                : public Object
                , public IIterator
            {
            public:
                Iterator(
                    /* [in] */ UnmodifiableEntrySet* owner);

                CAR_INTERFACE_DECL()

                CARAPI HasNext(
                    /* [out] */ Boolean* result);

                CARAPI GetNext(
                    /* [out] */ IMapEntry** object);

                CARAPI GetNext(
                    /* [out] */ IInterface** object);

                CARAPI Remove();
            public:
                AutoPtr<Iterator> mIterator;
            };

        public:
            UnmodifiableEntrySet(
                /* [in] */ ISet* set);

            CARAPI GetIterator(
                /* [out] */ IIterator** result);

            CARAPI ToArray(
                /* [out, callee] */ ArrayOf<IInterface*>** array);

            CARAPI ToArray(
                /* [in] */ ArrayOf<IInterface*>* inArray,
                /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        };

    public:
        UnmodifiableMap(
            /* [in] */ IMap* map);

        CAR_INTERFACE_DECL()

        CARAPI Clear();

        CARAPI ContainsKey(
            /* [in] */ IInterface* key,
            /* [out] */ Boolean* result);

        CARAPI ContainsValue(
            /* [in] */ IInterface* value,
            /* [out] */ Boolean* result);

        CARAPI GetEntrySet(
            /* [out, callee] */ ISet** entries);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI Get(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI GetKeySet(
            /* [out, callee] */ ISet** keySet);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value,
            /* [out] */ PInterface* oldValue);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value);

        CARAPI PutAll(
            /* [in] */ IMap* map);

        CARAPI Remove(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI Remove(
            /* [in] */ PInterface key);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI GetValues(
            /* [out] */ ICollection** value);

        CARAPI ToString(
            /* [out] */ String* str);
        AutoPtr<IMap> mM;
    };

    class UnmodifiableSortedMap
        : public UnmodifiableMap
        , public ISortedMap
    {
    public:
        UnmodifiableSortedMap(
            /* [in] */ ISortedMap* map);

        CAR_INTERFACE_DECL()

        CARAPI GetComparator(
            /* [out] */ IComparator** comp);

        CARAPI GetFirstKey(
            /* [out] */ IInterface** outface);

        CARAPI GetHeadMap(
            /* [in] */ IInterface* endKey,
            /* [out] */ ISortedMap** sortmap);

        CARAPI GetLastKey(
            /* [out] */ IInterface** outface);

        CARAPI GetSubMap(
            /* [in] */ IInterface* startKey,
            /* [in] */ IInterface* endKey,
            /* [out] */ ISortedMap** sortmap);

        CARAPI GetTailMap(
            /* [in] */ IInterface* startKey,
            /* [out] */ ISortedMap** sortmap);

        CARAPI Clear();

        CARAPI ContainsKey(
            /* [in] */ IInterface* key,
            /* [out] */ Boolean* result);

        CARAPI ContainsValue(
            /* [in] */ IInterface* value,
            /* [out] */ Boolean* result);

        CARAPI GetEntrySet(
            /* [out, callee] */ ISet** entries);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI Get(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI GetKeySet(
            /* [out, callee] */ ISet** keySet);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value,
            /* [out] */ PInterface* oldValue);

        CARAPI PutAll(
            /* [in] */ IMap* map);

        CARAPI Remove(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI GetValues(
            /* [out] */ ICollection** value);
        AutoPtr<ISortedMap> mSm;
    };

    class UnmodifiableSortedSet
        : public UnmodifiableSet
        , public ISortedSet
    {
    public:
        UnmodifiableSortedSet(
            /* [in] */ ISortedSet* set);

        CAR_INTERFACE_DECL()

        CARAPI GetComparator(
            /* [out] */ IComparator** outcom);

        CARAPI GetFirst(
            /* [out] */ IInterface** outface);

        CARAPI GetHeadSet(
            /* [in] */ IInterface* end,
            /* [out] */ ISortedSet** outsort);

        CARAPI GetLast(
            /* [out] */ IInterface** outface);

        CARAPI GetSubSet(
            /* [in] */ IInterface* start,
            /* [in] */ IInterface* end,
            /* [out] */ ISortedSet** outsort);

        CARAPI GetTailSet(
            /* [in] */ IInterface* start,
            /* [out] */ ISortedSet** outsort);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Clear();

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);
        AutoPtr<ISortedSet> mSs;
    };

    class SetFromMap
        : public AbstractSet
        , public ISerializable
    {
    public:
        SetFromMap(
            /* [in] */ IMap* map);

        CAR_INTERFACE_DECL()

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* value);

        CARAPI GetHashCode(
            /* [out] */ Int32* value);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI Clear();

        CARAPI ToString(
            /* [out] */ String* str);

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* contents,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        CARAPI GetIterator(
            /* [out] */ IIterator** result);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

    private:
        CARAPI ReadObject(
            /* [in] */ IObjectInputStream* stream);
        AutoPtr<IMap> mM;
        AutoPtr<ISet> mBackingSet;
    };

    class AsLIFOQueue
        : public AbstractQueue
        , public ISerializable
    {
    public:
        AsLIFOQueue(
            /* [in] */ IDeque* deque);

        CAR_INTERFACE_DECL()

        CARAPI GetIterator(
            /* [out] */ IIterator** result);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI Offer(
            /* [in] */ IInterface* obj,
            /* [out] */ Boolean* result);

        CARAPI Peek(
            /* [out] */ IInterface** obj);

        CARAPI Poll(
            /* [out] */ IInterface** obj);

        CARAPI Add(
            /* [in] */ IInterface* obj,
            /* [out] */ Boolean* result);

        CARAPI Clear();

        CARAPI GetElement(
            /* [out] */ IInterface** object);

        CARAPI Remove(
            /* [out] */ IInterface** obj);

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* contents,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        CARAPI ToString(
            /* [out] */ String* result);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        AutoPtr<IDeque> mQ;
    };

    class CheckedCollection
        : public Object
        , public ICollection
        , public ISerializable
    {
    public:
       CheckedCollection(
            /* [in] */ ICollection* c,
            /* [in] */ InterfaceID type);

        CAR_INTERFACE_DECL()

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetIterator(
            /* [out] */ IIterator** result);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI Add(
            /* [in] */ IInterface* object);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI Remove(
            /* [in] */ IInterface* object);

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection);

        CARAPI Clear();

        CARAPI ToString(
            /* [out] */ String* result);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

    public:
        AutoPtr<ICollection> mC;
        InterfaceID mType;
    };

    class CheckedListIterator
        : public Object
        , public IListIterator
    {
    public:
        CheckedListIterator(
            /* [in] */ IListIterator* i,
            /* [in] */ InterfaceID type);

        CAR_INTERFACE_DECL()

        CARAPI HasNext(
            /* [out] */ Boolean* result);

        CARAPI GetNext(
            /* [out] */ IInterface** object);

        CARAPI Remove();

        CARAPI HasPrevious(
            /* [out] */ Boolean* result);

        CARAPI GetPrevious(
            /* [out] */ IInterface** object);

        CARAPI GetNextIndex(
            /* [out] */ Int32* index);

        CARAPI GetPreviousIndex(
            /* [out] */ Int32* index);

        CARAPI Set(
            /* [in] */ IInterface* object);

        CARAPI Add(
            /* [in] */ IInterface* object);

    private:
        AutoPtr<IListIterator> mI;
        InterfaceID mType;
    };

    class CheckedList
        : public CheckedCollection
        , public IList
    {
    public:
       CheckedList(
            /* [in] */ IList* l,
            /* [in] */ InterfaceID type);

        CAR_INTERFACE_DECL()

        CARAPI AddAll(
            /* [in] */ Int32 location,
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ Int32 location,
            /* [in] */ ICollection* collection);

        CARAPI Get(
            /* [in] */ Int32 location,
            /* [out] */ IInterface** object);

        CARAPI Set(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object,
            /* [out] */ IInterface** prevObject);

        CARAPI Set(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object);

        CARAPI Add(
            /* [in] */ IInterface* object);

        CARAPI Add(
            /* [in] */ Int32 location,
            /* [in] */ IInterface* object);

        CARAPI Remove(
            /* [in] */ Int32 location,
            /* [out] */ IInterface** object);

        CARAPI Remove(
            /* [in] */ Int32 location);

        CARAPI IndexOf(
            /* [in] */ IInterface* object,
            /* [out] */ Int32* index);

        CARAPI LastIndexOf(
            /* [in] */ IInterface* object,
            /* [out] */ Int32* index);

        CARAPI GetListIterator(
            /* [out] */ IListIterator** it);

        CARAPI GetListIterator(
            /* [in] */ Int32 location,
            /* [out] */ IListIterator** it);

        CARAPI GetSubList(
            /* [in] */ Int32 start,
            /* [in] */ Int32 end,
            /* [out] */ IList** subList);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Clear();

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

    public:
        AutoPtr<IList> mL;
    };

    /**
     * A dynamically typesafe view of a RandomAccessList.
     */
    class CheckedRandomAccessList
        : public CheckedList
        , public IRandomAccess
    {
    public:
        CheckedRandomAccessList(
            /* [in] */ IList* l,
            /* [in] */ InterfaceID type);

        CAR_INTERFACE_DECL()
    };

    /**
     * A dynamically typesafe view of a Set.
     */
    class CheckedSet
        : public CheckedCollection
        , public ISet
    {
    public:
       CheckedSet(
            /* [in] */ ISet* s,
            /* [in] */ InterfaceID type);

        CAR_INTERFACE_DECL()

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI GetIterator(
            /* [out] */ IIterator** it);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Clear();

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);
    };

    /**
     * A dynamically typesafe view of a Map.
     */
    class CheckedMap
        : public Object
        , public IMap
        , public ISerializable
    {
    private:
        /**
         * A dynamically typesafe view of a Map.Entry.
         */
        class CheckedEntry
            : public Object
            , public IMapEntry
        {
        public:
            CheckedEntry(
                /* [in] */ IMapEntry* e,
                /* [in] */ InterfaceID valueType);

            CAR_INTERFACE_DECL()

            CARAPI GetKey(
                /* [out] */ PInterface* key);

            CARAPI GetValue(
                /* [out] */ PInterface* value);

            CARAPI SetValue(
                /* [in] */ IInterface* valueReplacer,
                /* [out] */ IInterface** valueReplacee);

            CARAPI Equals(
                /* [in] */ IInterface* entry,
                /* [out] */ Boolean* result);

            CARAPI GetHashCode(
                /* [out] */ Int32* hashCode);

        public:
            AutoPtr<IMapEntry> mE;
            InterfaceID mValueType;
        };
        /**
         * A dynamically typesafe view of an entry set.
         */
        class CheckedEntrySet
            : public Object
            , public ISet
        {
        private:
            class CheckedEntryIterator
                : public Object
                , public IIterator
            {
            public:
                CheckedEntryIterator(
                    /* [in] */ IIterator* i,
                    /* [in] */ InterfaceID valueType);

                CAR_INTERFACE_DECL()

                CARAPI HasNext(
                    /* [out] */ Boolean* result);

                CARAPI Remove();

                CARAPI GetNext(
                    /* [out] */ IMapEntry** object);

                CARAPI GetNext(
                    /* [out] */ IInterface** object);

            public:
                AutoPtr<IIterator> mI;
                InterfaceID mValueType;
            };
        public:
            CheckedEntrySet(
                /* [in] */ ISet* s,
                /* [in] */ InterfaceID valueType);

            CAR_INTERFACE_DECL()

            CARAPI GetIterator(
                /* [out] */ IIterator** result);

            CARAPI ToArray(
                /* [out, callee] */ ArrayOf<IInterface*>** array);

            CARAPI ToArray(
                /* [in] */ ArrayOf<IInterface*>* inArray,
                /* [out, callee] */ ArrayOf<IInterface*>** outArray);

            CARAPI RetainAll(
                /* [in] */ ICollection* collection,
                /* [out] */ Boolean* modified);

            CARAPI RemoveAll(
                /* [in] */ ICollection* collection,
                /* [out] */ Boolean* modified);

            CARAPI ContainsAll(
                /* [in] */ ICollection* collection,
                /* [out] */ Boolean* result);

            CARAPI AddAll(
                /* [in] */ ICollection* collection,
                /* [out] */ Boolean* modified);

            CARAPI Remove(
                /* [in] */ IInterface* object,
                /* [out] */ Boolean* modified);

            CARAPI Contains(
                /* [in] */ IInterface* object,
                /* [out] */ Boolean* result);

            CARAPI Add(
                /* [in] */ IInterface* object,
                /* [out] */ Boolean* modified);

            CARAPI IsEmpty(
                /* [out] */ Boolean* result);

            CARAPI Clear();

            CARAPI GetSize(
                /* [out] */ Int32* size);

            CARAPI GetHashCode(
                /* [out] */ Int32* hashCode);

            CARAPI Equals(
                /* [in] */ IInterface* object,
                /* [out] */ Boolean* result);
        public:
            AutoPtr<ISet> mS;
            InterfaceID mValueType;
        };

    public:
        CheckedMap(
            /* [in] */ IMap* m,
            /* [in] */ InterfaceID keyType,
            /* [in] */ InterfaceID valueType);

        CAR_INTERFACE_DECL()

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI ContainsKey(
            /* [in] */ IInterface* key,
            /* [out] */ Boolean* result);

        CARAPI ContainsValue(
            /* [in] */ IInterface* value,
            /* [out] */ Boolean* result);

        CARAPI Get(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value,
            /* [out] */ PInterface* oldValue);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value);

        CARAPI Remove(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI Remove(
            /* [in] */ PInterface key);

        CARAPI PutAll(
            /* [in] */ IMap* map);

        CARAPI Clear();

        CARAPI GetKeySet(
            /* [out, callee] */ ISet** keySet);

        CARAPI GetValues(
            /* [out] */ ICollection** value);

        CARAPI GetEntrySet(
            /* [out, callee] */ ISet** entries);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI ToString(
            /* [out] */ String* result);

    public:
        AutoPtr<IMap> mM;
        InterfaceID mKeyType;
        InterfaceID mValueType;
    };

    /**
     * A dynamically typesafe view of a SortedSet.
     */
    class CheckedSortedSet
        : public CheckedSet
        , public ISortedSet
    {
    public:
        CheckedSortedSet(
            /* [in] */ ISortedSet* s,
            /* [in] */ InterfaceID type);

        CAR_INTERFACE_DECL()

        CARAPI GetComparator(
            /* [out] */ IComparator** outcom);

        CARAPI GetSubSet(
            /* [in] */ IInterface* start,
            /* [in] */ IInterface* end,
            /* [out] */ ISortedSet** outsort);

        CARAPI GetHeadSet(
            /* [in] */ IInterface* end,
            /* [out] */ ISortedSet** outsort);

        CARAPI GetTailSet(
            /* [in] */ IInterface* start,
            /* [out] */ ISortedSet** outsort);

        CARAPI GetFirst(
            /* [out] */ IInterface** outface);

        CARAPI GetLast(
            /* [out] */ IInterface** outface);

        CARAPI GetIterator(
            /* [out] */ IIterator** result);

        CARAPI ToArray(
            /* [out, callee] */ ArrayOf<IInterface*>** array);

        CARAPI ToArray(
            /* [in] */ ArrayOf<IInterface*>* inArray,
            /* [out, callee] */ ArrayOf<IInterface*>** outArray);

        CARAPI RetainAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI RemoveAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI ContainsAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* result);

        CARAPI AddAll(
            /* [in] */ ICollection* collection,
            /* [out] */ Boolean* modified);

        CARAPI Remove(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI Contains(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI Add(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* modified);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI Clear();

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);
        AutoPtr<ISortedSet> mSs;
    };

    /**
     * A dynamically typesafe view of a SortedMap.
     */
    class CheckedSortedMap
        : public CheckedMap
        , public ISortedMap
    {
    public:
       CheckedSortedMap(
            /* [in] */ ISortedMap* m,
            /* [in] */ InterfaceID keyType,
            /* [in] */ InterfaceID valueType);

        CAR_INTERFACE_DECL()

        CARAPI GetComparator(
            /* [out] */ IComparator** comp);

        CARAPI GetSubMap(
            /* [in] */ IInterface* startKey,
            /* [in] */ IInterface* endKey,
            /* [out] */ ISortedMap** sortmap);

        CARAPI GetHeadMap(
            /* [in] */ IInterface* endKey,
            /* [out] */ ISortedMap** sortmap);

        CARAPI GetTailMap(
            /* [in] */ IInterface* startKey,
            /* [out] */ ISortedMap** sortmap);

        CARAPI GetFirstKey(
            /* [out] */ IInterface** outface);

        CARAPI GetLastKey(
            /* [out] */ IInterface** outface);

        CARAPI GetSize(
            /* [out] */ Int32* size);

        CARAPI IsEmpty(
            /* [out] */ Boolean* result);

        CARAPI ContainsKey(
            /* [in] */ IInterface* key,
            /* [out] */ Boolean* result);

        CARAPI ContainsValue(
            /* [in] */ IInterface* value,
            /* [out] */ Boolean* result);

        CARAPI Get(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI Put(
            /* [in] */ PInterface key,
            /* [in] */ PInterface value,
            /* [out] */ PInterface* oldValue);

        CARAPI Remove(
            /* [in] */ PInterface key,
            /* [out] */ PInterface* value);

        CARAPI PutAll(
            /* [in] */ IMap* map);

        CARAPI Clear();

        CARAPI GetKeySet(
            /* [out, callee] */ ISet** keySet);

        CARAPI GetValues(
            /* [out] */ ICollection** value);

        CARAPI GetEntrySet(
            /* [out, callee] */ ISet** entries);

        CARAPI Equals(
            /* [in] */ IInterface* object,
            /* [out] */ Boolean* result);

        CARAPI GetHashCode(
            /* [out] */ Int32* hashCode);

    public:
        AutoPtr<ISortedMap> mSm;
    };

public:
    static CARAPI BinarySearch(
        /* [in] */ IList* list,
        /* [in] */ IInterface* object,
        /* [out] */ Int32* index);

    static CARAPI BinarySearch(
        /* [in] */ IList* list,
        /* [in] */ IInterface* object,
        /* [in] */ IComparator* comparator,
        /* [out] */ Int32* index);

    static CARAPI Copy(
        /* [in] */ IList* destination,
        /* [in] */ IList* source);

    static CARAPI NewEnumeration(
        /* [in] */ ICollection* collection,
        /* [out] */ IEnumeration** result);

    static CARAPI Fill(
        /* [in] */ IList* list,
        /* [in] */ IInterface* object);

    static CARAPI Max(
        /* [in] */ ICollection* collection,
        /* [out] */ IInterface** result);

    static CARAPI Max(
        /* [in] */ ICollection* collection,
        /* [in] */ IComparator* comparator,
        /* [out] */ IInterface** result);

    static CARAPI Min(
        /* [in] */ ICollection* collection,
        /* [out] */ IInterface** result);

    static CARAPI Min(
        /* [in] */ ICollection* collection,
        /* [in] */ IComparator* comparator,
        /* [out] */ IInterface** result);

    static CARAPI NCopies(
        /* [in] */ Int32 length,
        /* [in] */ IInterface* object,
        /* [out] */ IList** result);

    static CARAPI Reverse(
        /* [in] */ IList* list);

    static CARAPI ReverseOrder(
        /* [out] */ IComparator** result);

    static CARAPI ReverseOrder(
        /* [in] */ IComparator* c,
        /* [out] */ IComparator** result);

    static CARAPI Shuffle(
        /* [in] */ IList* list);

    static CARAPI Shuffle(
        /* [in] */ IList* list,
        /* [in] */ IRandom* random);

    static CARAPI NewSingleton(
        /* [in] */ IInterface* object,
        /* [out] */ ISet** out);

    static CARAPI NewSingletonList(
        /* [in] */ IInterface* object,
        /* [out] */ IList** result);

    static CARAPI NewSingletonMap(
        /* [in] */ IInterface* key,
        /* [in] */ IInterface* value,
        /* [out] */ IMap** result);

    static CARAPI Sort(
        /* [in] */ IList* list);

    static CARAPI Sort(
        /* [in] */ IList* list,
        /* [in] */ IComparator* comparator);

    static CARAPI Swap(
        /* [in] */ IList* list,
        /* [in] */ Int32 index1,
        /* [in] */ Int32 index2);

    static CARAPI ReplaceAll(
        /* [in] */ IList* list,
        /* [in] */ IInterface* obj,
        /* [in] */ IInterface* obj2,
        /* [out] */ Boolean* result);

    static CARAPI Rotate(
        /* [in] */ IList* lst,
        /* [in] */ Int32 dist);

    static CARAPI IndexOfSubList(
        /* [in] */ IList* list,
        /* [in] */ IList* sublist,
        /* [out] */ Int32* index);

    static CARAPI LastIndexOfSubList(
        /* [in] */ IList* list,
        /* [in] */ IList* sublist,
        /* [out] */ Int32* index);

    static CARAPI NewList(
        /* [in] */ IEnumeration* enumeration,
        /* [out] */ IArrayList** result);

    static CARAPI NewSynchronizedCollection(
        /* [in] */ ICollection* collection,
        /* [out] */ ICollection** result);

    static CARAPI NewSynchronizedList(
        /* [in] */ IList* list,
        /* [out] */ IList** result);

    static CARAPI NewSynchronizedMap(
        /* [in] */ IMap* map,
        /* [out] */ IMap** result);

    static CARAPI NewSynchronizedSet(
        /* [in] */ ISet* set,
        /* [out] */ ISet** result);

    static CARAPI NewSynchronizedSortedMap(
        /* [in] */ ISortedMap* map,
        /* [out] */ ISortedMap** result);

    static CARAPI NewSynchronizedSortedSet(
        /* [in] */ ISortedSet* set,
        /* [out] */ ISortedSet** result);

    static CARAPI NewUnmodifiableCollection(
        /* [in] */ ICollection* collection,
        /* [out] */ ICollection** result);

    static CARAPI NewUnmodifiableList(
        /* [in] */ IList* list,
        /* [out] */ IList** result);

    static CARAPI NewUnmodifiableMap(
        /* [in] */ IMap* map,
        /* [out] */ IMap** result);

    static CARAPI NewUnmodifiableSet(
        /* [in] */ ISet* set,
        /* [out] */ ISet** result);

    static CARAPI NewUnmodifiableSortedMap(
        /* [in] */ ISortedMap* map,
        /* [out] */ ISortedMap** result);

    static CARAPI NewUnmodifiableSortedSet(
        /* [in] */ ISortedSet* set,
        /* [out] */ ISortedSet** result);

    static CARAPI Frequency(
        /* [in] */ ICollection* c,
        /* [in] */ IInterface* o,
        /* [out] */ Int32* result);

    static CARAPI GetEmptyList(
        /* [out] */ IList** result);

    static CARAPI GetEmptySet(
        /* [out] */ ISet** result);

    static CARAPI GetEmptyMap(
        /* [out] */ IMap** result);

    static CARAPI GetEmptyEnumeration(
        /* [out] */ IEnumeration** result);

    static CARAPI GetEmptyIterator(
        /* [out] */ IIterator** result);

    static CARAPI GetEmptyListIterator(
        /* [out] */ IListIterator** result);

    static CARAPI NewCheckedCollection(
        /* [in] */ ICollection* c,
        /* [in] */ const InterfaceID& type,
        /* [out] */ ICollection** result);

    static CARAPI NewCheckedMap(
        /* [in] */ IMap* m,
        /* [in] */ const InterfaceID& keyType,
        /* [in] */ const InterfaceID& valueType,
        /* [out] */ IMap** result);

    static CARAPI NewCheckedList(
        /* [in] */ IList* list,
        /* [in] */ const InterfaceID& type,
        /* [out] */ IList** result);

    static CARAPI NewCheckedSet(
        /* [in] */ ISet* s,
        /* [in] */ const InterfaceID& type,
        /* [out] */ ISet** result);

    static CARAPI NewCheckedSortedMap(
        /* [in] */ ISortedMap* m,
        /* [in] */ const InterfaceID& keyType,
        /* [in] */ const InterfaceID& valueType,
        /* [out] */ ISortedMap** result);

    static CARAPI NewCheckedSortedSet(
        /* [in] */ ISortedSet* s,
        /* [in] */ const InterfaceID& type,
        /* [out] */ ISortedSet** result);

    static CARAPI AddAll(
        /* [in] */ ICollection* c,
        /* [in] */ ArrayOf<IInterface*>* a,
        /* [out] */ Boolean* result);

    static CARAPI Disjoint(
        /* [in] */ ICollection* c1,
        /* [in] */ ICollection* c2,
        /* [out] */ Boolean* result);

    static CARAPI CheckType(
        /* [in] */ IInterface* obj,
        /* [in] */ const InterfaceID& type);

    static CARAPI NewSetFromMap(
        /* [in] */ IMap* map,
        /* [out] */ ISet** result);

    static CARAPI NewAsLifoQueue(
        /* [in] */ IDeque* deque,
        /* [out] */ IQueue** result);

    private:

        Collections();
        ~Collections();

public:
    static const AutoPtr<IList> EMPTY_LIST;
    static const AutoPtr<ISet> EMPTY_SET;
    static const AutoPtr<IMap> EMPTY_MAP;

private:
    static const AutoPtr<IIterator> EMPTY_ITERATOR;
    static const AutoPtr<IEnumeration> EMPTY_ENUMERATION;
};

} // namespace Utility
} // namespace Elastos

#endif // __UTILITY_CCOLLECTIONS_H__