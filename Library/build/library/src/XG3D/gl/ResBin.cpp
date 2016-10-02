// 文字コード：UTF-8
#include <XG3D/ResBin.hpp>

//------------------------------------------------------------------------------
#include <XBase/EnumCheck.hpp>
#include <XBase/Ref.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/StringTraits.hpp>
#include <XG3D/Engine.hpp>
#include "BinResHeader.hpp"
#include "ResMatSetImpl.hpp"
#include "ResMdlImpl.hpp"
#include "ResTexImpl.hpp"

//------------------------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------------------------
ResBin::ResBin(
    const const_ptr_t aBin
    , ::XBase::IAllocator& aAllocator
)
    : mXData()
    , mResMatSetImpls()
    , mResMdlImpls()
    , mResTexImpls()
{
    // XData作成
    ::XData::XData xdata(aBin);
    if (!xdata.isValidData())
    {// 無効なデータ
        return;
    }

    // バイナリチェック
    const BinResHeader* ptr = static_cast<const BinResHeader*>(xdata.dataHeadAddress());
    if (ptr->checkInvalid())
    {
        return;
    }

    // 正当なデータと判断
    mXData = xdata;

    // Implを作成
    struct Header
    {
        uint count;
        ::XData::Reference refs[1]; // 本来は無限長の配列
    };
    {// matSet
        const Header* resMatSets = reinterpret_cast<const Header*>(ref(ptr->matSets));
        mResMatSetImpls.init(resMatSets->count, ::XBase::Ref(aAllocator));
        for (uint i = 0; i < resMatSets->count; ++i)
        {
            mResMatSetImpls->add(
                ::XBase::Ref(mXData)
                , reinterpret_cast<const BinResMatSet*>(ref(resMatSets->refs[i]))
                , ::XBase::Ref(aAllocator)
            );
        }
    }
    {// mdl
        const Header* resMdls = reinterpret_cast<const Header*>(ref(ptr->mdls));
        mResMdlImpls.init(resMdls->count, ::XBase::Ref(aAllocator));
        for (uint i = 0; i < resMdls->count; ++i)
        {
            mResMdlImpls->add(
                ::XBase::Ref(mXData)
                , reinterpret_cast<const BinResMdl*>(ref(resMdls->refs[i]))
                , ::XBase::Ref(aAllocator)
            );
        }
    }
    {// tex
        const Header* resTexs = reinterpret_cast<const Header*>(ref(ptr->texs));
        mResTexImpls.init(resTexs->count, ::XBase::Ref(aAllocator));
        for (uint i = 0; i < resTexs->count; ++i)
        {
            mResTexImpls->add(
                ::XBase::Ref(mXData)
                , reinterpret_cast<const BinResTex*>(ref(resTexs->refs[i]))
                , ::XBase::Ref(aAllocator)
            );
        }
    }
}

//------------------------------------------------------------------------------
ResBin::~ResBin()
{
    release();
}

//------------------------------------------------------------------------------
bool ResBin::isValid()const
{
    return mXData.isValidData();
}

//------------------------------------------------------------------------------
void ResBin::setup()
{
    // チェック
    if (checkInvalid())
    {
        return;
    }

    // matSet
    for (uint i = 0; i < matSetCount(); ++i)
    {
        // 無効なリソースは無視
        if (!matSet(i).isValid())
        {
            continue;
        }

        // セットアップ
        mResMatSetImpls->at(i).setup();
    }

    // mdl
    for (uint i = 0; i < mdlCount(); ++i)
    {
        // 無効なリソースは無視
        if (!mdl(i).isValid())
        {
            continue;
        }

        // セットアップ
        mResMdlImpls->at(i).setup();
    }

    // tex
    for (uint i = 0; i < texCount(); ++i)
    {
        // 無効なリソースは無視
        if (!tex(i).isValid())
        {
            continue;
        }

        // セットアップ
        mResTexImpls->at(i).setup();
    }
}

//------------------------------------------------------------------------------
void ResBin::release()
{
    // チェック
    if (checkInvalid())
    {
        return;
    }

    // setupと逆順

    // tex
    for (uint i = texCount(); 0 < i; --i)
    {
        // 無効なリソースは無視
        const uint idx = i - 1;
        if (!tex(idx).isValid())
        {
            continue;
        }

        // セットアップ
        mResTexImpls->at(idx).setup();
    }

    // mdl
    for (uint i = mdlCount(); 0 < i; --i)
    {
        // 無効なリソースは無視
        const uint idx = i - 1;
        if (!mdl(idx).isValid())
        {
            continue;
        }

        // セットアップ
        mResMdlImpls->at(idx).setup();
    }

    // matSet
    for (uint i = matSetCount(); 0 < i; --i)
    {
        // 無効なリソースは無視
        const uint idx = i - 1;
        if (!matSet(idx).isValid())
        {
            continue;
        }

        // セットアップ
        mResMatSetImpls->at(idx).setup();
    }
}

//------------------------------------------------------------------------------
uint ResBin::matSetCount()const
{
    // チェック
    if (checkInvalid())
    {
        return 0;
    }
    return mResMatSetImpls->count();
}

//------------------------------------------------------------------------------
ResMatSet ResBin::matSet(const uint aIndex)const
{
    // チェック
    if (checkInvalid())
    {
        return ResMatSet();
    }
    return ResMatSet(mResMatSetImpls->at(aIndex));
}

//------------------------------------------------------------------------------
ResMatSet ResBin::matSet(const char* aName)const
{
    // チェック
    if (checkInvalid())
    {
        return ResMatSet();
    }

    // 検索
    for (uint i = 0; i < mResMatSetImpls->count(); ++i)
    {
        ResMatSetImpl& impl = mResMatSetImpls->at(i);
        if (::XBase::StringTraits< char >::Equals(ResMatSet(impl).name(), aName))
        {
            return ResMatSet(impl);
        }
    }
    return ResMatSet();
}

//------------------------------------------------------------------------------
uint ResBin::mdlCount()const
{
    // チェック
    if (checkInvalid())
    {
        return 0;
    }
    return mResMdlImpls->count();
}

//------------------------------------------------------------------------------
ResMdl ResBin::mdl(const uint aIndex)const
{
    // チェック
    if (checkInvalid())
    {
        return ResMdl();
    }
    return ResMdl(mResMdlImpls->at(aIndex));
}

//------------------------------------------------------------------------------
ResMdl ResBin::mdl(const char* aName)const
{
    // チェック
    if (checkInvalid())
    {
        return ResMdl();
    }

    // 検索
    for (uint i = 0; i < mResMdlImpls->count(); ++i)
    {
        ResMdlImpl& impl = mResMdlImpls->at(i);
        if (::XBase::StringTraits< char >::Equals(ResMdl(impl).name(), aName))
        {
            return ResMdl(impl);
        }
    }
    return ResMdl();
}

//------------------------------------------------------------------------------
uint ResBin::texCount()const
{
    // チェック
    if (checkInvalid())
    {
        return 0;
    }
    return mResTexImpls->count();
}

//------------------------------------------------------------------------------
ResTex ResBin::tex(const uint aIndex)const
{
    // チェック
    if (checkInvalid())
    {
        return ResTex();
    }
    return ResTex(mResTexImpls->at(aIndex));
}

//------------------------------------------------------------------------------
ResTex ResBin::tex(const char* aName)const
{
    // チェック
    if (checkInvalid())
    {
        return ResTex();
    }

    // 検索
    for (uint i = 0; i < mResTexImpls->count(); ++i)
    {
        ResTexImpl& impl = mResTexImpls->at(i);
        if (::XBase::StringTraits< char >::Equals(ResTex(impl).name(), aName))
        {
            return ResTex(impl);
        }
    }
    return ResTex();
}
//------------------------------------------------------------------------------
bool ResBin::checkInvalid()const
{
    // 正しければ何もしない
    if (isValid())
    {
        return false;
    }

    // 不正なのでエラー
    XBASE_NOT_REACH_ASSERT();
    return true;
}

//------------------------------------------------------------------------------
const_ptr_t ResBin::ref(const ::XData::Reference aVal)const
{
    // ポインタ取得
    XBASE_ASSERT(isValid());
    const void* ptr = mXData.labelAddressWithReference(aVal);

    // エラーチェック
    if (::XBase::PointerCheck::InvalidCheck(ptr))
    {
        return 0;
    }

    // 結果を返す
    return const_ptr_t(ptr);
}

} // namespace
// EOF
