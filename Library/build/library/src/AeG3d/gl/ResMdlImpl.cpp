// 文字コード：UTF-8
#include "ResMdlImpl.hpp"

#include <ae/base/Ref.hpp>
#include <ae/g3d/ResMdl.hpp>

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

}} // namespace

//------------------------------------------------------------------------------
ResMdlImpl::ResMdlImpl(
    const ::ae::xdata::Xdata& aXdata,
    const BinResMdl* aBinPtr,
    ::ae::base::IAllocator& aAllocator
    )
: xdata(aXdata.ptr())
, binPtr(aBinPtr)
, matReferImpls()
, shapeImpls()
, meshImpls()
, nodeImpls()
{
    // shape
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->shapes);
        shapeImpls.init(header->count, ::ae::base::Ref(aAllocator));
        for (int i = 0; i < header->count; ++i) {
            shapeImpls->add(
                ::ae::base::Ref(xdata),
                xdata.ref< BinResMdlShape >(header->entries[i]),
                ::ae::base::Ref(aAllocator)
                );
        }
    }

    // matRefer
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->matRefers);
        matReferImpls.init(header->count, ::ae::base::Ref(aAllocator));
        for (int i = 0; i < header->count; ++i) {
            matReferImpls->add(
                ::ae::base::Ref(xdata),
                xdata.ref< BinResMdlMatRefer >(header->entries[i]),
                ::ae::base::Ref(aAllocator)
                );
        }
    }

    // mesh
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->meshes);
        meshImpls.init(header->count, ::ae::base::Ref(aAllocator));
        for (int i = 0; i < header->count; ++i) {
            meshImpls->add(
                ::ae::base::Ref(xdata),
                xdata.ref< BinResMdlMesh >(header->entries[i]),
                ::ae::base::Ref(aAllocator),
                ResMdl(*this)
                );
        }
    }

    // node
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->nodes);
        nodeImpls.init(header->count, ::ae::base::Ref(aAllocator));
        for (int i = 0; i < header->count; ++i) {
            nodeImpls->add(
                ::ae::base::Ref(xdata),
                xdata.ref< BinResMdlNode >(header->entries[i]),
                ::ae::base::Ref(aAllocator)
                );
        }
    }
}

//------------------------------------------------------------------------------
ResMdlImpl::~ResMdlImpl()
{
    release();
}

//------------------------------------------------------------------------------
void ResMdlImpl::setup()
{
    for (int i = 0; i < shapeImpls->count(); ++i) {
        shapeImpls->at(i).setup();
    }
}

//------------------------------------------------------------------------------
void ResMdlImpl::release()
{
    // setupと逆順
    for (int i = shapeImpls->count(); 0 < i; --i) {
        shapeImpls->at(i - 1).release();
    }
}

}} // namespace
// EOF
