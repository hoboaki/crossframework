// 文字コード：UTF-8
#include "ResMatSetImpl.hpp"

#include <ae/base/Ref.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {
//------------------------------------------------------------------------------
namespace {

//------------------------------------------------------------------------------
struct tEntryHeader
{
    ::ae::xdata::SInt32     count;
    ::ae::xdata::Reference  entries[1]; // 本当は無限長配列
};

} // namespace

//------------------------------------------------------------------------------
ResMatSetImpl::ResMatSetImpl(
    const ::ae::xdata::Xdata& aXdata,
    const BinResMatSet* aBinPtr,
    ::ae::base::IAllocator& aAllocator
    )
: xdata(aXdata.ptr())
, binPtr(aBinPtr)
, matImpls()
{
    // mat
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->mats);
        matImpls.init(header->count, ::ae::base::Ref(aAllocator));
        for (int i = 0; i < header->count; ++i) {
            matImpls->add(
                ::ae::base::Ref(xdata),
                xdata.ref< BinResMat >(header->entries[i]),
                ::ae::base::Ref(aAllocator)
                );
        }
    }

}

//------------------------------------------------------------------------------
ResMatSetImpl::~ResMatSetImpl()
{
    release();
}

//------------------------------------------------------------------------------
void ResMatSetImpl::setup()
{
    for (int i = 0; i < matImpls->count(); ++i) {
        matImpls->at(i).setup();
    }
}

//------------------------------------------------------------------------------
void ResMatSetImpl::release()
{
    // setupと逆順
    for (int i = matImpls->count(); 0 < i; --i) {
        matImpls->at(i - 1).release();
    }
}

}} // namespace
// EOF
