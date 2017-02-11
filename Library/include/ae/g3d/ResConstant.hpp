// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESCONSTANT_HPP)
#else
#define AE_G3D_INCLUDED_RESCONSTANT_HPP

#include <ae/g3d/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
//@{
/// @brief リソースの定数群。
struct ResConstant
{
    /// 無効なマテリアルインデックス番号。
    static const u16 INVALID_MAT_INDEX = 0xFFFF;

    /// 無効なマテリアルパラメータインデックス番号。
    static const u16 INVALID_MAT_PARAM_INDEX = 0xFFFF;

    /// 無効なマテリアルセットインデックス番号。
    static const u16 INVALID_MAT_SET_INDEX = 0xFFFF;

    /// 無効なモデルインデックス番号。
    static const u16 INVALID_MDL_INDEX = 0xFFFF;

    /// 無効なマテリアル参照インデックス番号。
    static const u16 INVALID_MDL_MAT_REFER_INDEX = 0xFFFF;

    /// 無効なメッシュインデックス番号。
    static const u16 INVALID_MDL_MESH_INDEX = 0xFFFF;

    /// 無効なノードインデックス番号。
    static const u16 INVALID_MDL_NODE_INDEX = 0xFFFF;

    /// 無効なシェイプインデックス番号。
    static const u16 INVALID_MDL_SHAPE_INDEX = 0xFFFF;

    /// 無効なスキニングテーブルインデックス番号。
    static const u16 INVALID_MDL_SKINNING_TABLE_INDEX = 0xFFFF;

    /// 無効なサブメッシュインデックス番号。
    static const u16 INVALID_MDL_SUB_MESH_INDEX = 0xFFFF;

    /// 無効なテクスチャインデックス番号。
    static const u16 INVALID_TEX_INDEX = 0xFFFF;
};
//@}

}} // namespace
#endif
// EOF
