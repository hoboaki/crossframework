// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESFILE_HPP)
#else
#define AE_G3D_INCLUDED_RESFILE_HPP

#include <ae/base/FunctionAttribute.hpp>
#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/base/Placement.hpp>
#include <ae/base/RuntimeAutoArray.hpp>
#include <ae/base/ScopedPtr.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/g3d/ResMatSet.hpp>
#include <ae/g3d/ResMdl.hpp>
#include <ae/g3d/ResTex.hpp>
#include <ae/xdata/Xdata.hpp>

namespace ae {
namespace g3d {
class ResMatSetImpl;
class ResMdlImpl;
class ResTexImpl;
struct BinResBin;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
//@{
    /// @brief コンバートされたAeG3dデータを扱うクラス。
    /// @details
/// 各リソースを使って描画する前に setup() を前もって呼ぶようにしてください。
class ResBin : public ::ae::base::NonCopyable
{
public:
    /// @name コンストラクタとデストラクタ
    //@{

    /// @brief バイナリデータの先頭アドレスを指定して作成。
    /// @param aBin AeG3dConverterでバイナリ化したデータの先頭アドレス。
    /// @param aAllocator ワーク領域を確保するためのアロケータ。
    /// @details 無効なバイナリデータの場合、isValid() == false になります。
    ResBin(const_ptr_t aBin, ::ae::base::IAllocator& aAllocator = ::ae::base::IAllocator::Default());

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
    typedef ::ae::base::RuntimeAutoArray< ResMatSetImpl >  MatSetArray;
    typedef ::ae::base::RuntimeAutoArray< ResMdlImpl >     MdlArray;
    typedef ::ae::base::RuntimeAutoArray< ResTexImpl >     TexArray;
    //------------------------------------------------------------------------------
    ::ae::xdata::Xdata mXdata;
    ::ae::base::Placement< MatSetArray >   mResMatSetImpls;
    ::ae::base::Placement< MdlArray >      mResMdlImpls;
    ::ae::base::Placement< TexArray >      mResTexImpls;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
    const_ptr_t ref(::ae::xdata::Reference val)const;
};
//@}

}} // namespace
#endif
// EOF
