// 文字コード：UTF-8
#include "ResMdlImpl.hpp"

//------------------------------------------------------------------------------
#include <XBase/Ref.hpp>
#include <XG3D/ResMdl.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
namespace {

//------------------------------------------------------------------------------
struct tEntryHeader
{
    ::XData::UInt32     count;
    ::XData::Reference  entries[1]; // 本当は無限長配列
};

} // namespace

//------------------------------------------------------------------------------
ResMdlImpl::ResMdlImpl(
    const ::XData::XData& aXData
    , const BinResMdl* aBinPtr
    , ::XBase::IAllocator& aAllocator
)
    : xdata(aXData.ptr())
    , binPtr(aBinPtr)
    , matReferImpls()
    , shapeImpls()
    , meshImpls()
    , nodeImpls()
{
    // shape
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->shapes);
        shapeImpls.init(header->count, ::XBase::Ref(aAllocator));
        for (uint i = 0; i < header->count; ++i)
        {
            shapeImpls->add(
                ::XBase::Ref(xdata)
                , xdata.ref< BinResMdlShape >(header->entries[i])
                , ::XBase::Ref(aAllocator)
            );
        }
    }

    // matRefer
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->matRefers);
        matReferImpls.init(header->count, ::XBase::Ref(aAllocator));
        for (uint i = 0; i < header->count; ++i)
        {
            matReferImpls->add(
                ::XBase::Ref(xdata)
                , xdata.ref< BinResMdlMatRefer >(header->entries[i])
                , ::XBase::Ref(aAllocator)
            );
        }
    }

    // mesh
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->meshes);
        meshImpls.init(header->count, ::XBase::Ref(aAllocator));
        for (uint i = 0; i < header->count; ++i)
        {
            meshImpls->add(
                ::XBase::Ref(xdata)
                , xdata.ref< BinResMdlMesh >(header->entries[i])
                , ::XBase::Ref(aAllocator)
                , ResMdl(*this)
            );
        }
    }

    // node
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->nodes);
        nodeImpls.init(header->count, ::XBase::Ref(aAllocator));
        for (uint i = 0; i < header->count; ++i)
        {
            nodeImpls->add(
                ::XBase::Ref(xdata)
                , xdata.ref< BinResMdlNode >(header->entries[i])
                , ::XBase::Ref(aAllocator)
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
    for (uint i = 0; i < shapeImpls->count(); ++i)
    {
        shapeImpls->at(i).setup();
    }
}

//------------------------------------------------------------------------------
void ResMdlImpl::release()
{
    // setupと逆順
    for (uint i = shapeImpls->count(); 0 < i; --i)
    {
        shapeImpls->at(i - 1).release();
    }
}

} // namespace
// EOF
