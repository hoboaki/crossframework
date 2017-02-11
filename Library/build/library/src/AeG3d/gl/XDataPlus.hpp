// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_XDATAPLUS_HPP)
#else
#define AE_G3D_INCLUDED_XDATAPLUS_HPP

#include <ae/base/RuntimeAssert.hpp>
#include <ae/xdata/Xdata.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// 機能拡張したXdataクラス。
class XdataPlus : public ::ae::xdata::Xdata
{
public:
    // 不正なXdataとして作成。
    XdataPlus() : ::ae::xdata::Xdata(0) {}
    // バイナリデータの先頭アドレスを指定して作成。
    XdataPlus(const void* aPtr)
        : ::ae::xdata::Xdata(aPtr)
    {
    }

    // 参照解決。
    template< typename T >
    const T* ref(const ::ae::xdata::Reference aVal)const
    {
        // ポインタ取得
        const void* ptr = labelAddressWithReference(aVal);

        // エラーチェック
        if (::ae::base::PointerCheck::InvalidCheck(ptr))
        {
            return 0;
        }

        // 結果を返す
        return reinterpret_cast<const T*>(ptr);
    }

    // 参照解決(0を許す版)。
    template< typename T >
    const T* safeRef(const ::ae::xdata::Reference aVal)const
    {
        // ポインタ取得
        const void* ptr = labelAddressWithReference(aVal);

        // エラーチェック
        if (!::ae::base::PointerCheck::IsValid(ptr))
        {
            return 0;
        }

        // 結果を返す
        return reinterpret_cast<const T*>(ptr);
    }
};

}} // namespace
#endif
// EOF
