// 文字コード：UTF-8
#include <ae/g3d/ResBin.hpp>

#include <ae/base/EnumCheck.hpp>
#include <ae/base/Ref.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/StringTraits.hpp>
#include <ae/g3d/Engine.hpp>
#include "BinResHeader.hpp"
#include "ResMatSetImpl.hpp"
#include "ResMdlImpl.hpp"
#include "ResTexImpl.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResBin::ResBin(
    const const_ptr_t aBin,
    ::ae::base::IAllocator& aAllocator
    )
: mXdata()
, mResMatSetImpls()
, mResMdlImpls()
, mResTexImpls()
{
    // Xdata作成
    ::ae::xdata::Xdata xdata(aBin);
    if (!xdata.isValidData()) {
        // 無効なデータ
        return;
    }

    // バイナリチェック
    const BinResHeader* ptr = static_cast<const BinResHeader*>(xdata.dataHeadAddress());
    if (ptr->checkInvalid()) {
        return;
    }

    // 正当なデータと判断
    mXdata = xdata;

    // Implを作成
    struct Header
    {
        int count;
        ::ae::xdata::Reference refs[1]; // 本来は無限長の配列
    };
    {// matSet
        const Header* resMatSets = reinterpret_cast<const Header*>(ref(ptr->matSets));
        mResMatSetImpls.init(resMatSets->count, ::ae::base::Ref(aAllocator));
        for (int i = 0; i < resMatSets->count; ++i) {
            mResMatSetImpls->add(
                ::ae::base::Ref(mXdata),
                reinterpret_cast<const BinResMatSet*>(ref(resMatSets->refs[i])),
                ::ae::base::Ref(aAllocator)
                );
        }
    }
    {// mdl
        const Header* resMdls = reinterpret_cast<const Header*>(ref(ptr->mdls));
        mResMdlImpls.init(resMdls->count, ::ae::base::Ref(aAllocator));
        for (int i = 0; i < resMdls->count; ++i) {
            mResMdlImpls->add(
                ::ae::base::Ref(mXdata),
                reinterpret_cast<const BinResMdl*>(ref(resMdls->refs[i])),
                ::ae::base::Ref(aAllocator)
                );
        }
    }
    {// tex
        const Header* resTexs = reinterpret_cast<const Header*>(ref(ptr->texs));
        mResTexImpls.init(resTexs->count, ::ae::base::Ref(aAllocator));
        for (int i = 0; i < resTexs->count; ++i) {
            mResTexImpls->add(
                ::ae::base::Ref(mXdata),
                reinterpret_cast<const BinResTex*>(ref(resTexs->refs[i])),
                ::ae::base::Ref(aAllocator)
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
    return mXdata.isValidData();
}

//------------------------------------------------------------------------------
void ResBin::setup()
{
    // チェック
    if (checkInvalid()) {
        return;
    }

    // matSet
    for (int i = 0; i < matSetCount(); ++i) {
        // 無効なリソースは無視
        if (!matSet(i).isValid()) {
            continue;
        }

        // セットアップ
        mResMatSetImpls->at(i).setup();
    }

    // mdl
    for (int i = 0; i < mdlCount(); ++i) {
        // 無効なリソースは無視
        if (!mdl(i).isValid()) {
            continue;
        }

        // セットアップ
        mResMdlImpls->at(i).setup();
    }

    // tex
    for (int i = 0; i < texCount(); ++i) {
        // 無効なリソースは無視
        if (!tex(i).isValid()) {
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
    if (checkInvalid()) {
        return;
    }

    // setupと逆順

    // tex
    for (int i = texCount(); 0 < i; --i) {
        // 無効なリソースは無視
        const int idx = i - 1;
        if (!tex(idx).isValid()) {
            continue;
        }

        // セットアップ
        mResTexImpls->at(idx).setup();
    }

    // mdl
    for (int i = mdlCount(); 0 < i; --i) {
        // 無効なリソースは無視
        const int idx = i - 1;
        if (!mdl(idx).isValid()) {
            continue;
        }

        // セットアップ
        mResMdlImpls->at(idx).setup();
    }

    // matSet
    for (int i = matSetCount(); 0 < i; --i) {
        // 無効なリソースは無視
        const int idx = i - 1;
        if (!matSet(idx).isValid()) {
            continue;
        }

        // セットアップ
        mResMatSetImpls->at(idx).setup();
    }
}

//------------------------------------------------------------------------------
int ResBin::matSetCount()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mResMatSetImpls->count();
}

//------------------------------------------------------------------------------
ResMatSet ResBin::matSet(const int aIndex)const
{
    // チェック
    if (checkInvalid()) {
        return ResMatSet();
    }
    return ResMatSet(mResMatSetImpls->at(aIndex));
}

//------------------------------------------------------------------------------
ResMatSet ResBin::matSet(const char* aName)const
{
    // チェック
    if (checkInvalid()) {
        return ResMatSet();
    }

    // 検索
    for (int i = 0; i < mResMatSetImpls->count(); ++i) {
        ResMatSetImpl& impl = mResMatSetImpls->at(i);
        if (::ae::base::StringTraits< char >::Equals(ResMatSet(impl).name(), aName)) {
            return ResMatSet(impl);
        }
    }
    return ResMatSet();
}

//------------------------------------------------------------------------------
int ResBin::mdlCount()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mResMdlImpls->count();
}

//------------------------------------------------------------------------------
ResMdl ResBin::mdl(const int aIndex)const
{
    // チェック
    if (checkInvalid()) {
        return ResMdl();
    }
    return ResMdl(mResMdlImpls->at(aIndex));
}

//------------------------------------------------------------------------------
ResMdl ResBin::mdl(const char* aName)const
{
    // チェック
    if (checkInvalid()) {
        return ResMdl();
    }

    // 検索
    for (int i = 0; i < mResMdlImpls->count(); ++i) {
        ResMdlImpl& impl = mResMdlImpls->at(i);
        if (::ae::base::StringTraits< char >::Equals(ResMdl(impl).name(), aName)) {
            return ResMdl(impl);
        }
    }
    return ResMdl();
}

//------------------------------------------------------------------------------
int ResBin::texCount()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mResTexImpls->count();
}

//------------------------------------------------------------------------------
ResTex ResBin::tex(const int aIndex)const
{
    // チェック
    if (checkInvalid()) {
        return ResTex();
    }
    return ResTex(mResTexImpls->at(aIndex));
}

//------------------------------------------------------------------------------
ResTex ResBin::tex(const char* aName)const
{
    // チェック
    if (checkInvalid()) {
        return ResTex();
    }

    // 検索
    for (int i = 0; i < mResTexImpls->count(); ++i) {
        ResTexImpl& impl = mResTexImpls->at(i);
        if (::ae::base::StringTraits< char >::Equals(ResTex(impl).name(), aName)) {
            return ResTex(impl);
        }
    }
    return ResTex();
}
//------------------------------------------------------------------------------
bool ResBin::checkInvalid()const
{
    // 正しければ何もしない
    if (isValid()) {
        return false;
    }

    // 不正なのでエラー
    AE_BASE_ASSERT_NOT_REACHED();
    return true;
}

//------------------------------------------------------------------------------
const_ptr_t ResBin::ref(const ::ae::xdata::Reference aVal)const
{
    // ポインタ取得
    AE_BASE_ASSERT(isValid());
    const void* ptr = mXdata.labelAddressWithReference(aVal);

    // エラーチェック
    if (::ae::base::PointerCheck::InvalidCheck(ptr)) {
        return 0;
    }

    // 結果を返す
    return const_ptr_t(ptr);
}

}} // namespace
// EOF
