// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_STATEMDLTRANSFORM_HPP)
#else
#define AE_G3D_INCLUDED_STATEMDLTRANSFORM_HPP

#include <ae/base/Matrix34.hpp>
#include <ae/base/Matrix44.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/base/RuntimeArray.hpp>
#include <ae/base/Vector4.hpp>
#include <ae/g3d/ResMdl.hpp>

namespace ae {
namespace g3d {
struct MdlLocalMtx;
}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-State
//@{
    /// @brief モデルのTransformに関するState。
    /// @details
/// 各関数の引数 aNodeIndex はインスタンス元モデルの node のインデックス値に対応します。
class StateMdlTransform : public ::ae::base::NonCopyable
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @brief コンストラクタ。
    /// @param aResMdl インスタンス化するモデル。
    /// @param aAllocator ワーク領域を確保するためのアロケータ。
    StateMdlTransform(
        const ResMdl& aResMdl
        , ::ae::base::IAllocator& aAllocator = ::ae::base::IAllocator::Default()
    );

    /// デストラクタ。
    ~StateMdlTransform();
    //@}

    /// @name 行列計算
    //@{
    void updateWorldMtx(const ::ae::base::Mtx34& aMdlMtx = ::ae::base::Mtx34::Identity()); ///< ワールド行列を更新する。
    //@}

    /// @name 行列アクセス
    //@{
    const ::ae::base::Mtx34 worldMtx(int aNodeIndex)const; ///< 指定番目のノードのワールド行列を取得する。
    //@}

    /// @name 計算結果データ
    //@{
    const ::ae::base::Vec4* bonePosMtxData()const; ///< スキンバインド用ボーン位置変換行列データ。
    const ::ae::base::Vec4* boneNrmMtxData()const; ///< スキンバインド用ボーン法線変換行列データ。
    //@}

private:
    ResMdl mResMdl;
    ::ae::base::RuntimeArray< MdlLocalMtx > mLocalMtxs;
    ::ae::base::RuntimeArray< ::ae::base::Matrix34 > mWorldMtxs;
    ::ae::base::RuntimeArray< ::ae::base::Vec4 > mBonePosMtxs;
    ::ae::base::RuntimeArray< ::ae::base::Vec4 > mBoneNrmMtxs;
    //============================================================
    void resetLocalMtx();
};
//@}

}} // namespace
#endif
// EOF
