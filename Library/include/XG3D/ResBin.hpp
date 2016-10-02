// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESFILE_HPP)
#else
#define XG3D_INCLUDED_RESFILE_HPP

#include <XBase/FunctionAttribute.hpp>
#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include <XBase/Placement.hpp>
#include <XBase/RuntimeAutoArray.hpp>
#include <XBase/ScopedPtr.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include <XG3D/ResMatSet.hpp>
#include <XG3D/ResMdl.hpp>
#include <XG3D/ResTex.hpp>
#include <XData/XData.hpp>

namespace XG3D {
class ResMatSetImpl;
class ResMdlImpl;
class ResTexImpl;
struct BinResBin;
}

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Res
//@{
    /// @brief コンバートされたXG3Dデータを扱うクラス。
    /// @details
/// 各リソースを使って描画する前に setup() を前もって呼ぶようにしてください。
class ResBin : public ::XBase::NonCopyable
{
public:
    /// @name コンストラクタとデストラクタ
    //@{

    /// @brief バイナリデータの先頭アドレスを指定して作成。
    /// @param aBin XG3DConverterでバイナリ化したデータの先頭アドレス。
    /// @param aAllocator ワーク領域を確保するためのアロケータ。
    /// @details 無効なバイナリデータの場合、isValid() == false になります。
    ResBin(const_ptr_t aBin, ::XBase::IAllocator& aAllocator = ::XBase::IAllocator::Default());

    /// @brief セットアップ済みなら release() を呼ぶ。
    ~ResBin();
    //@}

    /// @name 正当性チェック
    //@{
    /// 有効なデータか。
    bool isValid()const;
    //@}

    /// @name セットアップ
    //@{
    void setup();   ///< @brief 描画できる状態にする。 @details プラットフォームによってはGPUにコマンドを発行したりVRAMなどのリソースを消費します。
    void release(); ///< セットアップ済みの状態を初期状態に戻す。
    //@}

    /// @name 各リソースへのアクセス
    //@{
    int        matSetCount()const;                 ///< マテリアルセットリソースの総数。
    ResMatSet   matSet(int aIndex)const;         ///< 指定番目のマテリアルセットリソースの取得。
    ResMatSet   matSet(const char* aName)const;   ///< 指定の名前のマテリアルセットリソースの取得。
    int        mdlCount()const;                    ///< モデルリソースの総数。
    ResMdl      mdl(int aIndex)const;            ///< 指定番目のモデルリソースの取得。
    ResMdl      mdl(const char* aName)const;      ///< 指定の名前のモデルリソースの取得。
    int        texCount()const;                    ///< テクスチャリソースの総数。
    ResTex      tex(int aIndex)const;            ///< 指定番目のテクスチャリソースの取得。
    ResTex      tex(const char* aName)const;      ///< 指定の名前のテクスチャリソースの取得。
    //@}

private:
    typedef ::XBase::RuntimeAutoArray< ResMatSetImpl >  MatSetArray;
    typedef ::XBase::RuntimeAutoArray< ResMdlImpl >     MdlArray;
    typedef ::XBase::RuntimeAutoArray< ResTexImpl >     TexArray;
    //------------------------------------------------------------------------------
    ::XData::XData mXData;
    ::XBase::Placement< MatSetArray >   mResMatSetImpls;
    ::XBase::Placement< MdlArray >      mResMdlImpls;
    ::XBase::Placement< TexArray >      mResTexImpls;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
    const_ptr_t ref(::XData::Reference val)const;
};
//@}

} // namespace
#endif
// EOF
