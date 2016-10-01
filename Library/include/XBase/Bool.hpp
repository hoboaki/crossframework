/**
 * @file
 * @brief Boolに関するクラス群を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_BOOL_HPP)
#else
#define XBASE_INCLUDED_BOOL_HPP

//------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Types
//@{
    /**
     * @brief BoolTmpl のPOD版。
     */
    template< typename DATA_TYPE >
    struct BoolPODTmpl
    {
        //============================================================
        // private
        DATA_TYPE val_;

        //============================================================
        // public
        /// @name typedef
        //@{
        typedef DATA_TYPE DataType;
        //@}
        
        /// @name operator実装
        //@{
        /**
         * @brief bool値代入。
         * @details
         * これを定義することで下記のコードが実行できるようになります。
         * @code
BoolPODTmpl< int > var;
var = true; // 代入できる
         * @endcode
         */
        BoolPODTmpl< DataType >& operator=( const bool aVal )
        {
            val_ = DataType( aVal ? 1 : 0 );
            return *this;
        }
        
        /**
         * @brief bool値取得。
         * @details
         * これを定義することで下記のコードが実行できるようになります。
         * @code
void func( const BoolPodTmpl< int >& aVal )
{
    bool var = aVal; // boolの値を取得できるのでこのように代入できる
}
         * @endcode
         */
        operator bool()const
        {
            return val_ != 0;
        }
        //@}
    };
    
    /**
     * @brief 組み込み型を指定したbool。
     * @details
     * bool変数のサイズは環境によって変わります。 @n
     * それをを防ぎたいときにこのテンプレート構造体を使います。 @n
     * DATA_TYPEに指定した組み込み型を指定します。@n
     * データとしては0以外の値が入っていたらtrueと扱います。@n
     */
    template< typename DATA_TYPE >
    class BoolTmpl : public BoolPODTmpl< DATA_TYPE >
    {
    public:
        /// @name コンストラクタ
        //@{
        /// falseとして作成。
        BoolTmpl()
        {
            BoolPODTmpl< DATA_TYPE >::val_ = false;
        }
    
        /// 値を指定して作成。
        BoolTmpl( const bool aVal )
        {
            BoolPODTmpl< DATA_TYPE >::val_ = aVal;
        }
        //@}
    };

    /// @name BoolTmpl BoolPODTmpl のtypedef。
    //@{
    typedef BoolPODTmpl< u8  > BoolPOD8;  ///< 8bitPOD版。
    typedef BoolPODTmpl< u16 > BoolPOD16; ///< 16bitPOD版。
    typedef BoolPODTmpl< u32 > BoolPOD32; ///< 32bitPOD版。
    typedef BoolPODTmpl< u64 > BoolPOD64; ///< 64bitPOD版。
    typedef BoolTmpl< u8  >    Bool8;  ///< 8bitクラス版。
    typedef BoolTmpl< u16 >    Bool16; ///< 16bitクラス版。
    typedef BoolTmpl< u32 >    Bool32; ///< 32bitクラス版。
    typedef BoolTmpl< u64 >    Bool64; ///< 64bitクラス版。
    typedef Bool8    Bool;    ///< 標準のクラス版(8bit)。
    typedef BoolPOD8 BoolPOD; ///< 標準のPOD版(8bit)。
    //@}

//@}
}
//------------------------------------------------------------
#endif
// EOF
