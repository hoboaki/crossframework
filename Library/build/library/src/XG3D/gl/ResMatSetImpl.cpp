// 文字コード：UTF-8
#include "ResMatSetImpl.hpp"

//------------------------------------------------------------------------------
#include <XBase/Ref.hpp>

//------------------------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------------------------
namespace {

//------------------------------------------------------------------------------
struct tEntryHeader
{
    ::XData::SInt32     count;
    ::XData::Reference  entries[1]; // 本当は無限長配列
};

} // namespace

//------------------------------------------------------------------------------
ResMatSetImpl::ResMatSetImpl(
    const ::XData::XData& aXData,
    const BinResMatSet* aBinPtr,
    ::XBase::IAllocator& aAllocator
    )
: xdata(aXData.ptr())
, binPtr(aBinPtr)
, matImpls()
{
    // mat
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->mats);
        matImpls.init(header->count, ::XBase::Ref(aAllocator));
        for (int i = 0; i < header->count; ++i) {
            matImpls->add(
                ::XBase::Ref(xdata),
                xdata.ref< BinResMat >(header->entries[i]),
                ::XBase::Ref(aAllocator)
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

} // namespace
// EOF
